
/***********************************************************************************************
 * * Implementing Graph Cuts on CUDA using algorithm given in CVGPU '08                       **
 * * paper "CUDA Cuts: Fast Graph Cuts on GPUs"                                               **
 * *                                                                                          **
 * * Copyright (c) 2008 International Institute of Information Technology.                    **
 * * All rights reserved.                                                                     **
 * *                                                                                          **
 * * Permission to use, copy, modify and distribute this software and its documentation for   **
 * * educational purpose is hereby granted without fee, provided that the above copyright     **
 * * notice and this permission notice appear in all copies of this software and that you do  **
 * * not sell the software.                                                                   **
 * *                                                                                          **
 * * THE SOFTWARE IS PROVIDED "AS IS" AND WITHOUT WARRANTY OF ANY KIND,EXPRESS, IMPLIED OR    **
 * * OTHERWISE.                                                                               **
 * *                                                                                          **
 * * Created By Vibhav Vineet.                                                                **
 * ********************************************************************************************/

#ifndef _PUSHRELABEL_KERNEL_CU_
#define _PUSHRELABEL_KERNEL_CU_

#include "CudaCuts.h"

/************************************************
 * Push operation is performed                 ** 
 * *********************************************/

__global__ void
kernel_push1_atomic( int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
		int *g_sink_weight, int *g_push_reser, int *g_pull_left, int *g_pull_right, int *g_pull_down, 
		int *g_pull_up, int *g_relabel_mask, int *g_graph_height, int *g_height_write,
		int graph_size, int width, int rows, int graph_size1, int width1, int rows1 )
{
		int x1 = threadIdx.x ;
		int y1 = threadIdx.y ;
		int x  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
		int y  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
		int thid = __umul24( y , width1 ) + x ;

		__shared__ int height_fn[356];

		
		int temp_mult = __umul24(y1+1 , 34 ) + x1 + 1, temp_mult1 = __umul24(y1,32) + x1 ;

		height_fn[temp_mult] = g_graph_height[thid] ;

		(threadIdx.x == 31 && x < width1 - 1 ) ? height_fn[temp_mult + 1] =  (g_graph_height[thid + 1]) : 0;
		(threadIdx.x == 0 && x > 0 ) ? height_fn[temp_mult - 1] = (g_graph_height[thid - 1]) : 0;
		(threadIdx.y == 7 && y < rows1 - 1 ) ? height_fn[temp_mult + 34] = (g_graph_height[thid + width1]) : 0;
		(threadIdx.y == 0 && y > 0 ) ? height_fn[temp_mult - 34] = (g_graph_height[thid - width1]) : 0;

		__syncthreads();

		int flow_push = 0, min_flow_pushed = 0 ;
		flow_push = g_push_reser[thid] ;


		if( thid < graph_size1 && g_relabel_mask[thid] == 1 && x < width-1 && x > 0 && y < rows-1 && y > 0 )
		{
			int temp_weight = 0;


			temp_weight = g_sink_weight[thid] ;
			min_flow_pushed = flow_push ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == 1 )
			{
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				g_sink_weight[thid] = temp_weight ;
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
			}


			flow_push = g_push_reser[thid] ;

			min_flow_pushed = flow_push ;

			temp_weight = g_left_weight[thid] ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult - 1] + 1 )
			{
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_left_weight[thid] , min_flow_pushed);
				atomicAdd(&g_right_weight[thid-1],min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid-1], min_flow_pushed);

			}else atomicSub(&g_pull_left[thid-1], 1) ;

			flow_push = g_push_reser[thid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_up_weight[thid] ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult - 34] + 1)
			{
				(temp_weight<flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;

				atomicSub(&g_up_weight[thid] , min_flow_pushed);
				atomicAdd(&g_down_weight[thid-width1],min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid-width1], min_flow_pushed);

			} else atomicSub(&g_pull_up[thid - width1] , 1) ;


			flow_push = g_push_reser[thid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_right_weight[thid] ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult + 1] + 1 )
			{
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_right_weight[thid] , min_flow_pushed);
				atomicAdd(&g_left_weight[thid+1],min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid+1], min_flow_pushed);
			}else atomicSub( &g_pull_right[thid + 1], 1) ;


			flow_push = g_push_reser[thid] ;

			min_flow_pushed = flow_push ;
			temp_weight = g_down_weight[thid] ;


			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult + 34] + 1 )
			{
				(temp_weight<flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_down_weight[thid] , min_flow_pushed);
				atomicAdd(&g_up_weight[thid+width1], min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid+width1], min_flow_pushed);
			}else atomicSub( &g_pull_down[thid+width1], 1) ;
		}

}

__global__ void
kernel_relabel_atomic( int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
		int *g_sink_weight, int *g_push_reser, int *g_pull_left, int *g_pull_right, int *g_pull_down, 
		int *g_pull_up, int *g_relabel_mask, int *g_graph_height, int *g_height_write,
		int graph_size, int width, int rows, int graph_size1, int width1, int rows1 )
{
	int x1 = threadIdx.x ;
	int y1 = threadIdx.y ;
	int x  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
	int y  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
	int thid = __umul24( y , width1 ) + x ;

	__shared__ int height_fn[356];


	int temp_mult = __umul24(y1+1 , 34 ) + x1 + 1, temp_mult1 = __umul24(y1,32) + x1 ;

	height_fn[temp_mult] = g_graph_height[thid] ;

	(threadIdx.x == 31 && x < width1 - 1 ) ? height_fn[temp_mult + 1] =  (g_graph_height[thid + 1]) : 0;
	(threadIdx.x == 0 && x > 0 ) ? height_fn[temp_mult - 1] = (g_graph_height[thid - 1]) : 0;
	(threadIdx.y == 7 && y < rows1 - 1 ) ? height_fn[temp_mult + 34] = (g_graph_height[thid + width1]) : 0;
	(threadIdx.y == 0 && y > 0 ) ? height_fn[temp_mult - 34] = (g_graph_height[thid - width1]) : 0;

	__syncthreads();


	int min_flow_pushed = g_left_weight[thid] ;
	int flow_push = g_push_reser[thid] ;

	if(flow_push <= 0 || (g_left_weight[thid] == 0 && g_right_weight[thid] == 0 && g_down_weight[thid] == 0 && g_up_weight[thid] == 0 && g_sink_weight[thid] == 0))
		g_relabel_mask[thid] = 2 ;
	else
	{
		( flow_push > 0 && ( ( (height_fn[temp_mult] == height_fn[temp_mult-1] + 1 ) && g_left_weight[thid] > 0  ) ||( (height_fn[temp_mult] == height_fn[temp_mult+1]+1 ) && g_right_weight[thid] > 0) || ( ( height_fn[temp_mult] == height_fn[temp_mult+34]+1 ) && g_down_weight[thid] > 0) || ( (height_fn[temp_mult] == height_fn[temp_mult-34]+1 ) && g_up_weight[thid] > 0 ) || ( height_fn[temp_mult] == 1 && g_sink_weight[thid] > 0 )  ) ) ? g_relabel_mask[thid] = 1 : g_relabel_mask[thid] = 0 ;
	}


	__syncthreads();

	if(thid < graph_size1 && x < width - 1  && x > 0 && y < rows - 1  && y > 0  )
	{
		if(g_sink_weight[thid] > 0)
		{
			g_height_write[thid] = 1 ;
		}
		else
		{
			int min_height = graph_size ;
			(min_flow_pushed > 0 && min_height > height_fn[temp_mult - 1] ) ? min_height = height_fn[temp_mult - 1] : 0 ;
			(g_right_weight[thid] > 0 && min_height > height_fn[temp_mult + 1]) ? min_height = height_fn[temp_mult + 1] : 0 ;
			(g_down_weight[thid] > 0 && min_height > height_fn[temp_mult + 34] ) ? min_height = height_fn[temp_mult + 34] : 0 ;
			(g_up_weight[thid] > 0 && min_height > height_fn[temp_mult - 34] ) ? min_height = height_fn[temp_mult - 34] : 0 ;
			g_height_write[thid] = min_height + 1 ;
		}
	}

}


__global__ void
kernel_relabel_stochastic( int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
		int *g_sink_weight, int *g_push_reser, /*int *g_pull_left, int *g_pull_right, int *g_pull_down, int *g_pull_up, */
		int *g_relabel_mask, int *g_graph_height, int *g_height_write,
		int graph_size, int width, int rows, int graph_size1, int width1, int rows1, int *d_stochastic, int *g_block_num )
{
		int x1 = threadIdx.x ;
		int y1 = threadIdx.y ;
		int x  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
		int y  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
		int thid = __umul24( y , width1 ) + x ;

		__shared__ int height_fn[356];


		int temp_mult = __umul24(y1+1 , 34 ) + x1 + 1, temp_mult1 = __umul24(y1,32) + x1 ;

		height_fn[temp_mult] = g_graph_height[thid] ;

		(threadIdx.x == 31 && x < width1 - 1 ) ? height_fn[temp_mult + 1] =  (g_graph_height[thid + 1]) : 0;
		(threadIdx.x == 0 && x > 0 ) ? height_fn[temp_mult - 1] = (g_graph_height[thid - 1]) : 0;
		(threadIdx.y == 7 && y < rows1 - 1 ) ? height_fn[temp_mult + 34] = (g_graph_height[thid + width1]) : 0;
		(threadIdx.y == 0 && y > 0 ) ? height_fn[temp_mult - 34] = (g_graph_height[thid - width1]) : 0;

		__syncthreads();


		int min_flow_pushed = g_left_weight[thid] ;
		int flow_push = g_push_reser[thid] ;

		if(flow_push <= 0 || (g_left_weight[thid] == 0 && g_right_weight[thid] == 0 && g_down_weight[thid] == 0 && g_up_weight[thid] == 0 && g_sink_weight[thid] == 0))
			g_relabel_mask[thid] = 2 ;
		else
		{
			( flow_push > 0 && ( ( (height_fn[temp_mult] == height_fn[temp_mult-1] + 1 ) && g_left_weight[thid] > 0  ) ||( (height_fn[temp_mult] == height_fn[temp_mult+1]+1 ) && g_right_weight[thid] > 0) || ( ( height_fn[temp_mult] == height_fn[temp_mult+34]+1 ) && g_down_weight[thid] > 0) || ( (height_fn[temp_mult] == height_fn[temp_mult-34]+1 ) && g_up_weight[thid] > 0 ) || ( height_fn[temp_mult] == 1 && g_sink_weight[thid] > 0 )  ) ) ? g_relabel_mask[thid] = 1 : g_relabel_mask[thid] = 0 ;
		}


		__syncthreads();

		if(thid < graph_size1 && x < width - 1  && x > 0 && y < rows - 1  && y > 0  )
		{
			if(g_sink_weight[thid] > 0)
			{
				g_height_write[thid] = 1 ;
			}
			else
			{
				int min_height = graph_size ;
				(min_flow_pushed > 0 && min_height > height_fn[temp_mult - 1] ) ? min_height = height_fn[temp_mult - 1] : 0 ;
				(g_right_weight[thid] > 0 && min_height > height_fn[temp_mult + 1]) ? min_height = height_fn[temp_mult + 1] : 0 ;
				(g_down_weight[thid] > 0 && min_height > height_fn[temp_mult + 34] ) ? min_height = height_fn[temp_mult + 34] : 0 ;
				(g_up_weight[thid] > 0 && min_height > height_fn[temp_mult - 34] ) ? min_height = height_fn[temp_mult - 34] : 0 ;
				g_height_write[thid] = min_height + 1 ;
			}
		}

}









__global__ void
kernel_push2_atomic( int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
		int *g_sink_weight, int *g_push_reser, int *g_pull_left, int *g_pull_right, int *g_pull_down, int *g_pull_up, 
		int *g_relabel_mask, int *g_graph_height, int *g_height_write,
		int graph_size, int width, int rows, int graph_size1, int width1, int rows1)
{
	int x1 = threadIdx.x ;
	int y1 = threadIdx.y ;
	int x  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
	int y  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
	int thid = __umul24( y , width1 ) + x ;

	__shared__ int height_fn[356];


	int temp_mult = __umul24(y1+1 , 34 ) + x1 + 1, temp_mult1 = __umul24(y1,32) + x1 ;

	height_fn[temp_mult] = g_graph_height[thid] ;

	(threadIdx.x == 31 && x < width1 - 1 ) ? height_fn[temp_mult + 1] =  (g_graph_height[thid + 1]) : 0;
	(threadIdx.x == 0 && x > 0 ) ? height_fn[temp_mult - 1] = (g_graph_height[thid - 1]) : 0;
	(threadIdx.y == 7 && y < rows1 - 1 ) ? height_fn[temp_mult + 34] = (g_graph_height[thid + width1]) : 0;
	(threadIdx.y == 0 && y > 0 ) ? height_fn[temp_mult - 34] = (g_graph_height[thid - width1]) : 0;

	__syncthreads();

	int flow_push = 0, min_flow_pushed = 0 ;
	flow_push = g_push_reser[thid] ;

	
		if( thid < graph_size1 && g_relabel_mask[thid] == 1 && x < width-1 && x > 0 && y < rows-1 && y > 0 )
		{
			
			int temp_weight = 0;


			temp_weight = g_sink_weight[thid] ;
			min_flow_pushed = flow_push ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == 1 )
			{
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				g_sink_weight[thid] = temp_weight ;
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
			}


			flow_push = g_push_reser[thid] ;

			min_flow_pushed = flow_push ;

			temp_weight = g_left_weight[thid] ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult - 1] + 1 )
			{
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_left_weight[thid] , min_flow_pushed);
				atomicAdd(&g_right_weight[thid-1],min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid-1], min_flow_pushed);

			}else atomicSub(&g_pull_left[thid-1], 1) ;

			flow_push = g_push_reser[thid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_up_weight[thid] ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult - 34] + 1)
			{
				(temp_weight<flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;

				atomicSub(&g_up_weight[thid] , min_flow_pushed);
				atomicAdd(&g_down_weight[thid-width1],min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid-width1], min_flow_pushed);

			} else atomicSub(&g_pull_up[thid - width1] , 1) ;


			flow_push = g_push_reser[thid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_right_weight[thid] ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult + 1] + 1 )
			{
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_right_weight[thid] , min_flow_pushed);
				atomicAdd(&g_left_weight[thid+1],min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid+1], min_flow_pushed);
			}else atomicSub( &g_pull_right[thid + 1], 1) ;


			flow_push = g_push_reser[thid] ;

			min_flow_pushed = flow_push ;
			temp_weight = g_down_weight[thid] ;


			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult + 34] + 1 )
			{
				(temp_weight<flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_down_weight[thid] , min_flow_pushed);
				atomicAdd(&g_up_weight[thid+width1], min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid+width1], min_flow_pushed);
			}else atomicSub( &g_pull_down[thid+width1], 1) ;
		}
	
		__syncthreads() ; 
		min_flow_pushed = g_left_weight[thid] ;
		flow_push = g_push_reser[thid] ;

		if(flow_push <= 0 || (g_left_weight[thid] == 0 && g_right_weight[thid] == 0 && g_down_weight[thid] == 0 && g_up_weight[thid] == 0 && g_sink_weight[thid] == 0))
			g_relabel_mask[thid] = 2 ;
		else
		{
			( flow_push > 0 && ( ( (height_fn[temp_mult] == height_fn[temp_mult-1] + 1 ) && g_left_weight[thid] > 0  ) ||( (height_fn[temp_mult] == height_fn[temp_mult+1]+1 ) && g_right_weight[thid] > 0) || ( ( height_fn[temp_mult] == height_fn[temp_mult+34]+1 ) && g_down_weight[thid] > 0) || ( (height_fn[temp_mult] == height_fn[temp_mult-34]+1 ) && g_up_weight[thid] > 0 ) || ( height_fn[temp_mult] == 1 && g_sink_weight[thid] > 0 )  ) ) ? g_relabel_mask[thid] = 1 : g_relabel_mask[thid] = 0 ;
		}




		__syncthreads() ;


		if( thid < graph_size1 && g_relabel_mask[thid] == 1 && x < width-1 && x > 0 && y < rows-1 && y > 0 )
		{
			int temp_weight = 0;


			temp_weight = g_sink_weight[thid] ;
			min_flow_pushed = flow_push ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == 1 )
			{
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				g_sink_weight[thid] = temp_weight ;
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
			}


			flow_push = g_push_reser[thid] ;

			min_flow_pushed = flow_push ;

			temp_weight = g_left_weight[thid] ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult - 1] + 1 )
			{
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_left_weight[thid] , min_flow_pushed);
				atomicAdd(&g_right_weight[thid-1],min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid-1], min_flow_pushed);

			}else atomicSub(&g_pull_left[thid-1], 1) ;

			flow_push = g_push_reser[thid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_up_weight[thid] ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult - 34] + 1)
			{
				(temp_weight<flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;

				atomicSub(&g_up_weight[thid] , min_flow_pushed);
				atomicAdd(&g_down_weight[thid-width1],min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid-width1], min_flow_pushed);

			} else atomicSub(&g_pull_up[thid - width1] , 1) ;


			flow_push = g_push_reser[thid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_right_weight[thid] ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult + 1] + 1 )
			{
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_right_weight[thid] , min_flow_pushed);
				atomicAdd(&g_left_weight[thid+1],min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid+1], min_flow_pushed);
			}else atomicSub( &g_pull_right[thid + 1], 1) ;


			flow_push = g_push_reser[thid] ;

			min_flow_pushed = flow_push ;
			temp_weight = g_down_weight[thid] ;


			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult + 34] + 1 )
			{
				(temp_weight<flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_down_weight[thid] , min_flow_pushed);
				atomicAdd(&g_up_weight[thid+width1], min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid+width1], min_flow_pushed);
			}else atomicSub( &g_pull_down[thid+width1], 1) ;
		}
}

__global__ void
kernel_End( int *g_stochastic, int *g_count_blocks, int *g_counter)
{
	int thid = blockIdx.x * blockDim.x + threadIdx.x ; 
	if( thid < ( *g_counter ) )
	{
		if( g_stochastic[thid] == 1 )
			atomicAdd(g_count_blocks,1);
			//(*g_count_blocks) = (*g_count_blocks) + 1 ; 
	}
}


/*__global__ void
kernel_End( int *g_stochastic, int *g_count_blocks, int *g_counter)
{
	int thid = blockIdx.x * blockDim.x + threadIdx.x ; 
	if( thid < ( *g_counter ) )
	{
		if( g_stochastic[thid] == 1 )
			atomicAdd(g_count_blocks,1);
			//(*g_count_blocks) = (*g_count_blocks) + 1 ; 
	}
}
*/



__global__ void
kernel_push1_start_atomic( int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
		int *g_sink_weight, int *g_push_reser, 
		int *g_relabel_mask, int *g_graph_height, int *g_height_write,
		int graph_size, int width, int rows, int graph_size1, int width1, int rows1, int *d_relabel, int *d_stochastic, int *d_counter, bool *d_finish)
{
		int x1 = threadIdx.x ;
		int y1 = threadIdx.y ;
		int x  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
		int y  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
		int thid = __umul24( y , width1 ) + x ;

		__shared__ int height_fn[356];


		int temp_mult = __umul24(y1+1 , 34 ) + x1 + 1, temp_mult1 = __umul24(y1,32) + x1 ;

		height_fn[temp_mult] = g_graph_height[thid] ;

		(threadIdx.x == 31 && x < width1 - 1 ) ? height_fn[temp_mult + 1] =  (g_graph_height[thid + 1]) : 0;
		(threadIdx.x == 0 && x > 0 ) ? height_fn[temp_mult - 1] = (g_graph_height[thid - 1]) : 0;
		(threadIdx.y == 7 && y < rows1 - 1 ) ? height_fn[temp_mult + 34] = (g_graph_height[thid + width1]) : 0;
		(threadIdx.y == 0 && y > 0 ) ? height_fn[temp_mult - 34] = (g_graph_height[thid - width1]) : 0;

		__syncthreads();

		int flow_push = 0, min_flow_pushed = 0 ;
		flow_push = g_push_reser[thid] ;


		if( thid < graph_size1 && g_relabel_mask[thid] == 1 && x < width-1 && x > 0 && y < rows-1 && y > 0 )
		{
			int temp_weight = 0;


			temp_weight = g_sink_weight[thid] ;
			min_flow_pushed = flow_push ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == 1 )
			{
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				g_sink_weight[thid] = temp_weight ;
				atomicSub(&g_push_reser[thid] , min_flow_pushed);

				flow_push = flow_push - min_flow_pushed ;
			}



		}


		__syncthreads() ;
		min_flow_pushed = g_left_weight[thid] ;

			( flow_push > 0 && ( ((height_fn[temp_mult] == height_fn[temp_mult-1] + 1 ) && min_flow_pushed > 0  ) ||( (height_fn[temp_mult] == height_fn[temp_mult+1]+1 ) && g_right_weight[thid] > 0) || ( ( height_fn[temp_mult] == height_fn[temp_mult+34]+1 ) && g_down_weight[thid] > 0) || ( (height_fn[temp_mult] == height_fn[temp_mult-34]+1 ) && g_up_weight[thid] > 0 ) || ( height_fn[temp_mult] == 1 && g_sink_weight[thid] > 0 )  ) ) ? g_relabel_mask[thid] = 1 : g_relabel_mask[thid] = 0 ;



		if(thid < graph_size1 && x < width - 1  && x > 0 && y < rows - 1  && y > 0  )
		{
			if(g_sink_weight[thid] > 0)
			{
				g_height_write[thid] = 1 ;
			}
			else
			{
				int min_height = graph_size ;
				(min_flow_pushed > 0 && min_height > height_fn[temp_mult - 1] ) ? min_height = height_fn[temp_mult - 1] : 0 ;
				(g_right_weight[thid] > 0 && min_height > height_fn[temp_mult + 1]) ? min_height = height_fn[temp_mult + 1] : 0 ;
				(g_down_weight[thid] > 0 && min_height > height_fn[temp_mult + 34] ) ? min_height = height_fn[temp_mult + 34] : 0 ;
				(g_up_weight[thid] > 0 && min_height > height_fn[temp_mult - 34] ) ? min_height = height_fn[temp_mult - 34] : 0 ;
				g_height_write[thid] = min_height + 1 ;
			}
		}

}



__global__ void
kernel_push1_stochastic( int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
		int *g_sink_weight, int *g_push_reser, /*int *g_pull_left, int *g_pull_right, int *g_pull_down, int *g_pull_up,*/
		int *g_relabel_mask, int *g_graph_height, int *g_height_write,
		int graph_size, int width, int rows, int graph_size1, int width1, int rows1, int *d_stochastic,int *g_block_num )
{
	if(d_stochastic[blockIdx.y * (*g_block_num) + blockIdx.x] == 1 )
	{
		int x1 = threadIdx.x ;
		int y1 = threadIdx.y ;
		int x  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
		int y  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
		int thid = __umul24( y , width1 ) + x ;

		__shared__ int height_fn[356];
		
		int temp_mult = __umul24(y1+1 , 34 ) + x1 + 1, temp_mult1 = __umul24(y1,32) + x1 ;

		height_fn[temp_mult] = g_graph_height[thid] ;

		(threadIdx.x == 31 && x < width1 - 1 ) ? height_fn[temp_mult + 1] =  (g_graph_height[thid + 1]) : 0;
		(threadIdx.x == 0 && x > 0 ) ? height_fn[temp_mult - 1] = (g_graph_height[thid - 1]) : 0;
		(threadIdx.y == 7 && y < rows1 - 1 ) ? height_fn[temp_mult + 34] = (g_graph_height[thid + width1]) : 0;
		(threadIdx.y == 0 && y > 0 ) ? height_fn[temp_mult - 34] = (g_graph_height[thid - width1]) : 0;

		__syncthreads();

		int flow_push = 0, min_flow_pushed = 0 ;
		flow_push = g_push_reser[thid] ;


		if( thid < graph_size1 && g_relabel_mask[thid] == 1 && x < width-1 && x > 0 && y < rows-1 && y > 0 )
		{
			int temp_weight = 0;


			temp_weight = g_sink_weight[thid] ;
			min_flow_pushed = flow_push ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == 1 )
			{
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				g_sink_weight[thid] = temp_weight ;
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
			}


			flow_push = g_push_reser[thid] ;

			min_flow_pushed = flow_push ;

			temp_weight = g_left_weight[thid] ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult - 1] + 1 )
			{
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_left_weight[thid] , min_flow_pushed);
				atomicAdd(&g_right_weight[thid-1],min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid-1], min_flow_pushed);

			}//else atomicSub(&g_pull_left[thid-1], 1) ;



			flow_push = g_push_reser[thid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_up_weight[thid] ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult - 34] + 1)
			{
				(temp_weight<flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;

				atomicSub(&g_up_weight[thid] , min_flow_pushed);
				atomicAdd(&g_down_weight[thid-width1],min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid-width1], min_flow_pushed);

			} //else atomicSub(&g_pull_up[thid - width1] , 1) ;


			flow_push = g_push_reser[thid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_right_weight[thid] ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult + 1] + 1 )
			{
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_right_weight[thid] , min_flow_pushed);
				atomicAdd(&g_left_weight[thid+1],min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid+1], min_flow_pushed);
			}//else atomicSub( &g_pull_right[thid + 1], 1) ;


			flow_push = g_push_reser[thid] ;

			min_flow_pushed = flow_push ;
			temp_weight = g_down_weight[thid] ;


			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult + 34] + 1 )
			{
				(temp_weight<flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_down_weight[thid] , min_flow_pushed);
				atomicAdd(&g_up_weight[thid+width1], min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid+width1], min_flow_pushed);
			}//else atomicSub( &g_pull_down[thid+width1], 1) ;
		}
	}

}



__global__ void
kernel_push2_stochastic( int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
		int *g_sink_weight, int *g_push_reser, int *g_pull_left, int *g_pull_right, int *g_pull_down, int *g_pull_up,
		int *g_relabel_mask, int *g_graph_height, int *g_height_write,
		int graph_size, int width, int rows, int graph_size1, int width1, int rows1, int *d_relabel, int *d_stochastic, int *d_counter, bool *d_finish, int *g_block_num)
{
	if(d_stochastic[blockIdx.y * (*g_block_num) + blockIdx.x] == 1 )
	{
		int x1 = threadIdx.x ;
		int y1 = threadIdx.y ;
		int x  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
		int y  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
		int thid = __umul24( y , width1 ) + x ;

		__shared__ int height_fn[356];


		int temp_mult = __umul24(y1+1 , 34 ) + x1 + 1, temp_mult1 = __umul24(y1,32) + x1 ;

		height_fn[temp_mult] = g_graph_height[thid] ;

		(threadIdx.x == 31 && x < width1 - 1 ) ? height_fn[temp_mult + 1] =  (g_graph_height[thid + 1]) : 0;
		(threadIdx.x == 0 && x > 0 ) ? height_fn[temp_mult - 1] = (g_graph_height[thid - 1]) : 0;
		(threadIdx.y == 7 && y < rows1 - 1 ) ? height_fn[temp_mult + 34] = (g_graph_height[thid + width1]) : 0;
		(threadIdx.y == 0 && y > 0 ) ? height_fn[temp_mult - 34] = (g_graph_height[thid - width1]) : 0;

		__syncthreads();

		int flow_push = 0, min_flow_pushed = 0 ;
		flow_push = g_push_reser[thid] ;


		if( thid < graph_size1 && g_relabel_mask[thid] == 1 && x < width-1 && x > 0 && y < rows-1 && y > 0 )
		{
			int temp_weight = 0;


			temp_weight = g_sink_weight[thid] ;
			min_flow_pushed = flow_push ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == 1 )
			{
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				g_sink_weight[thid] = temp_weight ;
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
			}


			flow_push = g_push_reser[thid] ;

			min_flow_pushed = flow_push ;

			temp_weight = g_left_weight[thid] ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult - 1] + 1 )
			{
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_left_weight[thid] , min_flow_pushed);
				atomicAdd(&g_right_weight[thid-1],min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid-1], min_flow_pushed);

			}else atomicSub(&g_pull_left[thid-1], 1) ;



			flow_push = g_push_reser[thid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_up_weight[thid] ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult - 34] + 1)
			{
				(temp_weight<flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;

				atomicSub(&g_up_weight[thid] , min_flow_pushed);
				atomicAdd(&g_down_weight[thid-width1],min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid-width1], min_flow_pushed);

			} else atomicSub(&g_pull_up[thid - width1] , 1) ;


			flow_push = g_push_reser[thid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_right_weight[thid] ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult + 1] + 1 )
			{
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_right_weight[thid] , min_flow_pushed);
				atomicAdd(&g_left_weight[thid+1],min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid+1], min_flow_pushed);
			}else atomicSub( &g_pull_right[thid + 1], 1) ;


			flow_push = g_push_reser[thid] ;

			min_flow_pushed = flow_push ;
			temp_weight = g_down_weight[thid] ;


			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult + 34] + 1 )
			{
				(temp_weight<flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_down_weight[thid] , min_flow_pushed);
				atomicAdd(&g_up_weight[thid+width1], min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid+width1], min_flow_pushed);
			}else atomicSub( &g_pull_down[thid+width1], 1) ;
		}
			
			
		__syncthreads() ; 
		min_flow_pushed = g_left_weight[thid] ;
		flow_push = g_push_reser[thid] ;

		if(flow_push <= 0 || (g_left_weight[thid] == 0 && g_right_weight[thid] == 0 && g_down_weight[thid] == 0 && g_up_weight[thid] == 0 && g_sink_weight[thid] == 0))
			g_relabel_mask[thid] = 2 ;
		else
		{
			( flow_push > 0 && ( ( (height_fn[temp_mult] == height_fn[temp_mult-1] + 1 ) && g_left_weight[thid] > 0  ) ||( (height_fn[temp_mult] == height_fn[temp_mult+1]+1 ) && g_right_weight[thid] > 0) || ( ( height_fn[temp_mult] == height_fn[temp_mult+34]+1 ) && g_down_weight[thid] > 0) || ( (height_fn[temp_mult] == height_fn[temp_mult-34]+1 ) && g_up_weight[thid] > 0 ) || ( height_fn[temp_mult] == 1 && g_sink_weight[thid] > 0 )  ) ) ? g_relabel_mask[thid] = 1 : g_relabel_mask[thid] = 0 ;
		}




		__syncthreads() ;




		if( thid < graph_size1 && g_relabel_mask[thid] == 1 && x < width-1 && x > 0 && y < rows-1 && y > 0 )
		{
			int temp_weight = 0;


			temp_weight = g_sink_weight[thid] ;
			min_flow_pushed = flow_push ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == 1 )
			{
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				g_sink_weight[thid] = temp_weight ;
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
			}


			flow_push = g_push_reser[thid] ;

			min_flow_pushed = flow_push ;

			temp_weight = g_left_weight[thid] ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult - 1] + 1 )
			{
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_left_weight[thid] , min_flow_pushed);
				atomicAdd(&g_right_weight[thid-1],min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid-1], min_flow_pushed);

			}else atomicSub(&g_pull_left[thid-1], 1) ;



			flow_push = g_push_reser[thid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_up_weight[thid] ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult - 34] + 1)
			{
				(temp_weight<flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;

				atomicSub(&g_up_weight[thid] , min_flow_pushed);
				atomicAdd(&g_down_weight[thid-width1],min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid-width1], min_flow_pushed);

			} else atomicSub(&g_pull_up[thid - width1] , 1) ;


			flow_push = g_push_reser[thid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_right_weight[thid] ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult + 1] + 1 )
			{
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_right_weight[thid] , min_flow_pushed);
				atomicAdd(&g_left_weight[thid+1],min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid+1], min_flow_pushed);
			}else atomicSub( &g_pull_right[thid + 1], 1) ;


			flow_push = g_push_reser[thid] ;

			min_flow_pushed = flow_push ;
			temp_weight = g_down_weight[thid] ;


			if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == height_fn[temp_mult + 34] + 1 )
			{
				(temp_weight<flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_down_weight[thid] , min_flow_pushed);
				atomicAdd(&g_up_weight[thid+width1], min_flow_pushed);
				atomicSub(&g_push_reser[thid] , min_flow_pushed);
				atomicAdd(&g_push_reser[thid+width1], min_flow_pushed);
			}else atomicSub( &g_pull_down[thid+width1], 1) ;
		}

		

	}
}






__global__ void
kernel_bfs_t(int *g_push_reser, int  *g_sink_weight, int *g_graph_height, bool *g_pixel_mask,
		int vertex_num, int width, int height, int vertex_num1, int width1, int height1)
{

	int thid = __umul24(blockIdx.x, blockDim.x) + threadIdx.x ;

	if(thid < vertex_num && g_pixel_mask[thid] == true )
	{
		int col = thid % width1 , row = thid / width1 ;

		if(col > 0 && row > 0 && col < width - 1 && row < height - 1 && g_push_reser[thid] > 0 )
		{
			g_graph_height[thid] = 1 ;
			g_pixel_mask[thid] = false ;
		}
		else
			if(g_sink_weight[thid] > 0)
			{
				g_graph_height[thid] = -1 ;
				g_pixel_mask[thid] = false ;
			}
	}
}

		

__global__ void
kernel_push_stochastic1( int *g_push_reser, int *s_push_reser, int *g_count_blocks, bool *g_finish, int *g_block_num, int width1)
{
	int x  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
	int y  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
	int thid = __umul24( y , width1 ) + x ;
	
	s_push_reser[thid] = g_push_reser[thid] ;
	
	if( thid == 0 )
	{
		if((*g_count_blocks) == 0 )
			(*g_finish) = false ; 
	}
}


__global__ void
kernel_push_atomic2( int *g_terminate, int *g_push_reser, int *s_push_reser, int *g_block_num, int width1)
{

	int x  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
	int y  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
	int thid = __umul24( y , width1 ) + x ;
	
	if( s_push_reser[thid] - g_push_reser[thid] != 0)
	{
		g_terminate[blockIdx.y * (*g_block_num) + blockIdx.x] = 1 ;
	}

}



__global__ void
kernel_push_stochastic2( int *g_terminate, int *g_relabel_mask, int *g_push_reser, int *s_push_reser, int *d_stochastic, int *g_block_num, int width1)
{

	int x  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
	int y  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
	int thid = __umul24( y , width1 ) + x ;
	
	if( s_push_reser[thid] - g_push_reser[thid] != 0)
	{
		g_terminate[blockIdx.y * (*g_block_num) + blockIdx.x] = 1 ;
	}

	if ( g_relabel_mask[thid] == 1 )
	{
		d_stochastic[blockIdx.y * (*g_block_num) + blockIdx.x] = 1 ;
	} 

}



__global__ void
kernel_push1_start_stochastic( int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
		int *g_sink_weight, int *g_push_reser,
		int *g_relabel_mask, int *g_graph_height, int *g_height_write,
		int graph_size, int width, int rows, int graph_size1, int width1, int rows1, int *d_relabel, int *d_stochastic, int *d_counter, bool *d_finish)
{
	int x1 = threadIdx.x ;
	int y1 = threadIdx.y ;
	int x  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
	int y  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
	int thid = __umul24( y , width1 ) + x ;

	__shared__ int height_fn[356];


	int temp_mult = __umul24(y1+1 , 34 ) + x1 + 1, temp_mult1 = __umul24(y1,32) + x1 ;

	height_fn[temp_mult] = g_graph_height[thid] ;

	(threadIdx.x == 31 && x < width1 - 1 ) ? height_fn[temp_mult + 1] =  (g_graph_height[thid + 1]) : 0;
	(threadIdx.x == 0 && x > 0 ) ? height_fn[temp_mult - 1] = (g_graph_height[thid - 1]) : 0;
	(threadIdx.y == 7 && y < rows1 - 1 ) ? height_fn[temp_mult + 34] = (g_graph_height[thid + width1]) : 0;
	(threadIdx.y == 0 && y > 0 ) ? height_fn[temp_mult - 34] = (g_graph_height[thid - width1]) : 0;

	__syncthreads();

	int flow_push = 0, min_flow_pushed = 0 ;
	flow_push = g_push_reser[thid] ;


	if( thid < graph_size1 && g_relabel_mask[thid] == 1 && x < width-1 && x > 0 && y < rows-1 && y > 0 )
	{
		int temp_weight = 0;


		temp_weight = g_sink_weight[thid] ;
		min_flow_pushed = flow_push ;

		if(temp_weight > 0 && flow_push > 0 && height_fn[temp_mult] == 1 )
		{
			(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
			temp_weight = temp_weight - min_flow_pushed ;
			g_sink_weight[thid] = temp_weight ;
			atomicSub(&g_push_reser[thid] , min_flow_pushed);

			flow_push = flow_push - min_flow_pushed ;
		}



	}


	__syncthreads() ;
	min_flow_pushed = g_left_weight[thid] ;

	( flow_push > 0 && ( ((height_fn[temp_mult] == height_fn[temp_mult-1] + 1 ) && min_flow_pushed > 0  ) ||( (height_fn[temp_mult] == height_fn[temp_mult+1]+1 ) && g_right_weight[thid] > 0) || ( ( height_fn[temp_mult] == height_fn[temp_mult+34]+1 ) && g_down_weight[thid] > 0) || ( (height_fn[temp_mult] == height_fn[temp_mult-34]+1 ) && g_up_weight[thid] > 0 ) || ( height_fn[temp_mult] == 1 && g_sink_weight[thid] > 0 )  ) ) ? g_relabel_mask[thid] = 1 : g_relabel_mask[thid] = 0 ;



	if(thid < graph_size1 && x < width - 1  && x > 0 && y < rows - 1  && y > 0  )
	{
		if(g_sink_weight[thid] > 0)
		{
			g_height_write[thid] = 1 ;
		}
		else
		{
			int min_height = graph_size ;
			(min_flow_pushed > 0 && min_height > height_fn[temp_mult - 1] ) ? min_height = height_fn[temp_mult - 1] : 0 ;
			(g_right_weight[thid] > 0 && min_height > height_fn[temp_mult + 1]) ? min_height = height_fn[temp_mult + 1] : 0 ;
			(g_down_weight[thid] > 0 && min_height > height_fn[temp_mult + 34] ) ? min_height = height_fn[temp_mult + 34] : 0 ;
			(g_up_weight[thid] > 0 && min_height > height_fn[temp_mult - 34] ) ? min_height = height_fn[temp_mult - 34] : 0 ;
			g_height_write[thid] = min_height + 1 ;
		}
	}

}



__global__ void
kernel_bfs(int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
		int *g_graph_height, bool *g_pixel_mask, int vertex_num,int width,int height,
		int vertex_num1, int width1, int height1, bool *g_over, int *g_counter)
{
	/*******************************
	 *threadId is calculated ******
	 *****************************/

	int thid = __umul24(blockIdx.x, blockDim.x) + threadIdx.x ;

	if(thid < vertex_num && g_pixel_mask[thid] == true)
	{
		int col = thid % width1 , row = thid / width1 ;

		if(col < width - 1 && col > 0 && row < height - 1 && row > 0 )
		{
			int height_l = 0, height_d = 0, height_u = 0 , height_r = 0 ;
			height_r = g_graph_height[thid+1] ;
			height_l = g_graph_height[thid-1] ;
			height_d = g_graph_height[thid+width1] ;
			height_u = g_graph_height[thid-width1] ;

			if(((height_l == (*g_counter) && g_right_weight[thid-1] > 0)) ||((height_d == (*g_counter) && g_up_weight[thid+width1] > 0) || ( height_r == (*g_counter) && g_left_weight[thid+1] > 0 ) || ( height_u == (*g_counter) && g_down_weight[thid-width1] > 0 ) ))
			{
				g_graph_height[thid] = (*g_counter) + 1 ;
				g_pixel_mask[thid] = false ;
				*g_over = true ;
			}
		}
	}
}



/************************************************************
 * functions to construct the graph on the device          **
 * *********************************************************/

__device__
void add_edge(int from, int to, int cap, int rev_cap, int type, int *d_left_weight,
		int *d_right_weight, int *d_down_weight, int *d_up_weight)
{
	if(type==1)
	{
		d_left_weight[from] = d_left_weight[from]+cap;
		d_right_weight[to] = d_right_weight[to]+rev_cap;
	}
	if(type==2)
	{
		d_right_weight[from] = d_right_weight[from]+cap;
		d_left_weight[to] = d_left_weight[to]+rev_cap;
	}
	if(type==3)
	{
		d_down_weight[from] = d_down_weight[from]+cap;
		d_up_weight[to] = d_up_weight[to]+rev_cap;
	}
	if(type==4)
	{
		d_up_weight[from] = d_up_weight[from]+cap;
		d_down_weight[to] = d_down_weight[to]+cap;
	}
}

__device__
void add_tweights(int i, int cap_source, int  cap_sink, int *d_push_reser, int *d_sink_weight)
{
	int diff = cap_source - cap_sink ;

	if(diff>0)
	{
		d_push_reser[i] = d_push_reser[i] + diff ;
	}
	else
	{
		d_sink_weight[i] = d_sink_weight[i] - diff ;
	}
}

__device__
void add_term1(int i, int A, int B, int *d_push_reser, int *d_sink_weight)
{
	add_tweights(i,B,A, d_push_reser, d_sink_weight);
}

__device__
void add_t_links_Cue(int alpha_label, int thid, int *d_left_weight, int *d_right_weight,
		int *d_down_weight, int *d_up_weight, int *d_push_reser, int *d_sink_weight,
		int *dPixelLabel, int *dDataTerm, int width , int height, int num_labels)
{
	{
		if(dPixelLabel[thid]!=alpha_label) {
			add_term1(thid , dDataTerm[thid*num_labels+alpha_label] , dDataTerm[thid * num_labels + dPixelLabel[thid]], d_push_reser, d_sink_weight  );
		}
	}
}


__device__
void add_t_links(int alpha_label, int thid, int *d_left_weight, int *d_right_weight,
		int *d_down_weight, int *d_up_weight, int *d_push_reser, int *d_sink_weight,
		int *dPixelLabel, int *dDataTerm, int width , int height, int num_labels)
{
	{
		if(dPixelLabel[thid]!=alpha_label) {
			add_term1(thid , dDataTerm[thid*num_labels+alpha_label] , dDataTerm[thid * num_labels + dPixelLabel[thid]], d_push_reser, d_sink_weight  );
		}
	}
}



__device__
void add_term2(int x, int y, int A, int B, int C, int D, int type, int *d_left_weight,
		int *d_right_weight, int *d_down_weight, int *d_up_weight, int *d_push_reser, int *d_sink_weight  )
{
	if ( A+D > C+B) {
		int delta = A+D-C-B;
		int subtrA = delta/3;

		A = A-subtrA;
		C = C+subtrA;
		B = B+(delta-subtrA*2);
#ifdef COUNT_TRUNCATIONS
		truncCnt++;
#endif
	}
#ifdef COUNT_TRUNCATIONS
	totalCnt++;
#endif

	add_tweights(x, D, A, d_push_reser, d_sink_weight);

	B -= A; C -= D;

	if (B < 0)
	{
		add_tweights(x, 0, B, d_push_reser, d_sink_weight);
		add_tweights(y, 0, -B, d_push_reser, d_sink_weight ) ;
		add_edge(x, y, 0, B+C,type , d_left_weight, d_right_weight, d_down_weight, d_up_weight );
	}
	else if (C < 0)
	{
		add_tweights(x, 0, -C, d_push_reser, d_sink_weight);
		add_tweights(y, 0, C , d_push_reser, d_sink_weight);
		add_edge(x, y, B+C, 0,type , d_left_weight, d_right_weight, d_down_weight, d_up_weight);
	}
	else
	{
		add_edge(x, y, B, C,type, d_left_weight, d_right_weight , d_down_weight, d_up_weight);
	}
}


__device__
void set_up_expansion_energy_G_ARRAY(int alpha_label,int thid, int *d_left_weight,int *d_right_weight,
		int *d_down_weight, int *d_up_weight, int *d_push_reser,
		int *d_sink_weight, int *dPixelLabel, int *dDataTerm, int *dSmoothTerm,
		int width , int height, int num_labels )
{
	int x,y,nPix;

	int weight;

	int i = thid ;
	{
		if(dPixelLabel[i]!=alpha_label)
		{
			y = i/width;
			x = i - y*width;

			if ( x < width - 1 )
			{
				nPix = i + 1;
				weight = 1 ;
				if ( dPixelLabel[nPix] != alpha_label )
				{
					add_term2(i,nPix,
							( dSmoothTerm[alpha_label + alpha_label * num_labels]) * weight,
							( dSmoothTerm[alpha_label + dPixelLabel[nPix]*num_labels]) * weight,
							( dSmoothTerm[ dPixelLabel[i] +  alpha_label * num_labels] ) * weight,
							( dSmoothTerm[ dPixelLabel[i] +  dPixelLabel[nPix] * num_labels] )  * weight,

							2, d_left_weight, d_right_weight, d_down_weight, d_up_weight, d_push_reser, d_sink_weight); // 1-left, 2-right, 3-down, 4-up
				}
				else   add_term1(i,
						( dSmoothTerm[alpha_label + dPixelLabel[nPix] * num_labels]) * weight,
						( dSmoothTerm[dPixelLabel[i] + alpha_label*num_labels]) * weight,
						d_push_reser, d_sink_weight);
			}

			if ( y < height - 1 )
			{
				nPix = i + width;
				weight = 1 ;
				if ( dPixelLabel[nPix] != alpha_label )
				{
					add_term2(i,nPix,
							( dSmoothTerm[alpha_label + alpha_label * num_labels]) * weight,
							( dSmoothTerm[alpha_label + dPixelLabel[nPix]*num_labels]) * weight,
							( dSmoothTerm[ dPixelLabel[i] +  alpha_label * num_labels] ) * weight,
							( dSmoothTerm[ dPixelLabel[i] +  dPixelLabel[nPix] * num_labels] )  * weight,



							3, d_left_weight, d_right_weight, d_down_weight, d_up_weight, d_push_reser, d_sink_weight );
				}
				else   add_term1(i,
						( dSmoothTerm[alpha_label + dPixelLabel[nPix] * num_labels]) * weight,
						( dSmoothTerm[dPixelLabel[i] + alpha_label*num_labels]) * weight,
						d_push_reser, d_sink_weight);
			}
			if ( x > 0 )
			{
				nPix = i - 1;
				weight = 1 ;
				if ( dPixelLabel[nPix] == alpha_label )
					add_term1(i,
							( dSmoothTerm[alpha_label + dPixelLabel[nPix] * num_labels]) * weight,
							( dSmoothTerm[dPixelLabel[i] + alpha_label*num_labels]) * weight,
							d_push_reser, d_sink_weight );
			}

			if ( y > 0 )
			{
				nPix = i - width;
				weight = 1 ;
				if ( dPixelLabel[nPix] == alpha_label )
				{
					add_term1(i,

							( dSmoothTerm[alpha_label + alpha_label * num_labels]) * weight,
							( dSmoothTerm[dPixelLabel[i] + alpha_label*num_labels]) * weight,
							d_push_reser, d_sink_weight);
				}
			}
		}
	}
}



__device__
void set_up_expansion_energy_G_ARRAY_Cue(int alpha_label,int thid, int *d_left_weight,int *d_right_weight,
		int *d_down_weight, int *d_up_weight, int *d_push_reser,
		int *d_sink_weight, int *dPixelLabel, int *dDataTerm, int *dSmoothTerm,
		int *dHcue, int *dVcue, int width , int height, int num_labels )
{
	int x,y,nPix;

	int weight;

	int i = thid ;
	{
		if(dPixelLabel[i]!=alpha_label)
		{
			y = i/width;
			x = i - y*width;

			if ( x < width - 1 )
			{
				nPix = i + 1;
				weight=dHcue[i];
				if ( dPixelLabel[nPix] != alpha_label )
				{
					add_term2(i,nPix,
							( dSmoothTerm[alpha_label + alpha_label * num_labels]) * weight,
							( dSmoothTerm[alpha_label + dPixelLabel[nPix]*num_labels]) * weight,
							( dSmoothTerm[ dPixelLabel[i] +  alpha_label * num_labels] ) * weight,
							( dSmoothTerm[ dPixelLabel[i] +  dPixelLabel[nPix] * num_labels] )  * weight,

							2, d_left_weight, d_right_weight, d_down_weight, d_up_weight, d_push_reser, d_sink_weight); // 1-left, 2-right, 3-down, 4-up
				}
				else   add_term1(i,
						( dSmoothTerm[alpha_label + dPixelLabel[nPix] * num_labels]) * weight,
						( dSmoothTerm[dPixelLabel[i] + alpha_label*num_labels]) * weight,
						d_push_reser, d_sink_weight);
			}


			if ( y < height - 1 )
			{
				nPix = i + width;
				weight=dVcue[i];
				if ( dPixelLabel[nPix] != alpha_label )
				{
					add_term2(i,nPix,
							( dSmoothTerm[alpha_label + alpha_label * num_labels]) * weight,
							( dSmoothTerm[alpha_label + dPixelLabel[nPix]*num_labels]) * weight,
							( dSmoothTerm[ dPixelLabel[i] +  alpha_label * num_labels] ) * weight,
							( dSmoothTerm[ dPixelLabel[i] +  dPixelLabel[nPix] * num_labels] )  * weight,



							3, d_left_weight, d_right_weight, d_down_weight, d_up_weight, d_push_reser, d_sink_weight );
				}
				else   add_term1(i,
						( dSmoothTerm[alpha_label + dPixelLabel[nPix] * num_labels]) * weight,
						( dSmoothTerm[dPixelLabel[i] + alpha_label*num_labels]) * weight,
						d_push_reser, d_sink_weight);
			}
			if ( x > 0 )
			{
				nPix = i - 1;
				weight=dHcue[nPix];
				if ( dPixelLabel[nPix] == alpha_label )
					add_term1(i,
							( dSmoothTerm[alpha_label + dPixelLabel[nPix] * num_labels]) * weight,
							( dSmoothTerm[dPixelLabel[i] + alpha_label*num_labels]) * weight,
							d_push_reser, d_sink_weight );
			}

			if ( y > 0 )
			{
				nPix = i - width;
				weight = dVcue[nPix] ;
				if ( dPixelLabel[nPix] == alpha_label )
				{
					add_term1(i,

							( dSmoothTerm[alpha_label + alpha_label * num_labels]) * weight,
							( dSmoothTerm[dPixelLabel[i] + alpha_label*num_labels]) * weight,
							d_push_reser, d_sink_weight);
				}
			}
		}
	}
}



__global__
void CudaWeightCue(int alpha_label, int *d_left_weight, int *d_right_weight, int *d_down_weight,
		int *d_up_weight, int *d_push_reser, int *d_sink_weight, int *dPixelLabel,
		int *dDataTerm, int *dSmoothTerm, int *dHcue, int *dVcue, int width, int height, int num_labels )
{
	int thid = blockIdx.x * 256 + threadIdx.x ;

	add_t_links_Cue(alpha_label, thid, d_left_weight, d_right_weight, d_down_weight, d_up_weight, d_push_reser, d_sink_weight, dPixelLabel, dDataTerm, width, height, num_labels);

	set_up_expansion_energy_G_ARRAY_Cue(alpha_label, thid, d_left_weight, d_right_weight, d_down_weight, d_up_weight, d_push_reser, d_sink_weight, dPixelLabel, dDataTerm, dSmoothTerm, dHcue, dVcue, width, height, num_labels);
}


__global__
void CudaWeight(int alpha_label, int *d_left_weight, int *d_right_weight, int *d_down_weight,
		int *d_up_weight, int *d_push_reser, int *d_sink_weight, int *dPixelLabel,
		int *dDataTerm, int *dSmoothTerm, int width, int height, int num_labels)
{
	int thid = blockIdx.x * 256 + threadIdx.x ;

	add_t_links(alpha_label, thid, d_left_weight, d_right_weight, d_down_weight, d_up_weight, d_push_reser, d_sink_weight, dPixelLabel, dDataTerm, width, height, num_labels);

	set_up_expansion_energy_G_ARRAY(alpha_label, thid, d_left_weight, d_right_weight, d_down_weight, d_up_weight, d_push_reser, d_sink_weight, dPixelLabel, dDataTerm, dSmoothTerm, width, height, num_labels);
}



/*********************************************************
 * function which adjusts the array size for efficiency **
 * consideration                                        **
 * ******************************************************/

__global__
void adjustedgeweight(int *d_left_weight, int *d_right_weight, int *d_down_weight, int *d_up_weight,
		int *d_push_reser, int *d_sink_weight, int *temp_left_weight, int *temp_right_weight,
		int *temp_down_weight, int *temp_up_weight, int *temp_push_reser, int *temp_sink_weight,
		int width, int height, int graph_size, int width1, int height1, int graph_size1)
{
	int thid = blockIdx.x * 256 + threadIdx.x ;

	if( thid < graph_size1 )
	{
		int row = thid / width1 , col = thid % width1 ;

		if(row < height && col < width)
		{
			temp_left_weight[row* width1 + col] = d_left_weight[row * width + col] ;
			temp_right_weight[row * width1 + col] = d_right_weight[row * width + col] ;
			temp_down_weight[row * width1 + col] = d_down_weight[row * width + col] ;
			temp_up_weight[row * width1 + col] = d_up_weight[row * width + col] ;
			temp_push_reser[row * width1 + col] = d_push_reser[row * width + col] ;
			temp_sink_weight[row * width1 + col] = d_sink_weight[row * width + col] ;

		}
		else
		{
			temp_left_weight[row * width1 + col] = 0 ;
			temp_right_weight[row * width1 + col] = 0 ;
			temp_down_weight[row * width1 + col] = 0 ;
			temp_up_weight[row * width1 + col] = 0 ;
			temp_push_reser[row * width1 + col] = 0 ;
			temp_sink_weight[row * width1 + col] = 0 ;
		}
	}
}



/************************************************************
 * Intializes memory on the gpu                            **
 * ********************************************************/

__global__
void copyedgeweight( int *d_left_weight, int *d_right_weight, int *d_down_weight, int *d_up_weight,
		int *d_push_reser, int *d_sink_weight, int *temp_left_weight, int *temp_right_weight,
		int *temp_down_weight, int *temp_up_weight, int *temp_push_reser, int *temp_sink_weight,
		int *d_pull_left, int *d_pull_right, int *d_pull_down, int *d_pull_up, int *d_relabel_mask,
		int *d_graph_heightr, int *d_graph_heightw, int width, int height, int graph_size, int width1, int height1, int graph_size1)
{
	int thid = blockIdx.x * 256 + threadIdx.x ;

	if( thid < graph_size1 )
	{
		d_left_weight[thid] = temp_left_weight[thid] ;
		d_right_weight[thid] = temp_right_weight[thid] ;
		d_down_weight[thid] = temp_down_weight[thid] ;
		d_up_weight[thid] = temp_up_weight[thid] ;
		d_push_reser[thid] = temp_push_reser[thid] ;
		d_sink_weight[thid] = temp_sink_weight[thid] ;

		d_pull_left[thid] = 0 ;
		d_pull_right[thid] = 0 ;
		d_pull_down[thid] = 0 ;
		d_pull_up[thid] = 0 ;
		d_relabel_mask[thid] = 0 ;
		d_graph_heightr[thid] = 1 ;
		d_graph_heightw[thid] = 1 ;

	}
}




#endif
