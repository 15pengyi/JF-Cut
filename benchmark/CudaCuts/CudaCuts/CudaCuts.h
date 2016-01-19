
/********************************************************************************************
* Implementing Graph Cuts on CUDA using algorithm given in CVGPU '08                       ** 
* paper "CUDA Cuts: Fast Graph Cuts on GPUs"                                               **  
*                                                                                          **   
* Copyright (c) 2008 International Institute of Information Technology.                    **  
* All rights reserved.                                                                     **  
*                                                                                          ** 
* Permission to use, copy, modify and distribute this software and its documentation for   ** 
* educational purpose is hereby granted without fee, provided that the above copyright     ** 
* notice and this permission notice appear in all copies of this software and that you do  **
* not sell the software.                                                                   **  
*                                                                                          **
* THE SOFTWARE IS PROVIDED "AS IS" AND WITHOUT WARRANTY OF ANY KIND,EXPRESS, IMPLIED OR    **
* OTHERWISE.                                                                               **  
*                                                                                          **
* Created By Vibhav Vineet.                                                                ** 
********************************************************************************************/

#ifndef _CUDACUTS_H_
#define _CUDACUTS_H_

/*Header files included*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// #include <cutil.h>

#define WIN32

#include <helper_cuda.h>
#include <helper_timer.h>


/* ***************************************************
 * Kernels which perform the push, pull and         **
 * relabel operations. It has the kernel            **
 * which performs the bfs operation. n-edgeweights  **
 * and t-edgeweights are also calculated here       ** 
 * **************************************************/

#include "CudaCuts_kernel.cu"

//#include "cudaCopy.cu"
//#include "cudaStochastic.cu"


#define datacost(pix,lab)     (datacost[(pix)*num_Labels+(lab)] )
#define smoothnesscost(lab1,lab2) (smoothnesscost[(lab1)+(lab2)*num_Labels] )

/*****************************************************************
 * CONTROL_M -- this decides after how many iterations          **
 * m should be changed from 1 to 2. Here m equal to 1           **
 * means one push-pull operation followed by one relabel        **
 * operation and m equal to 2 means two push-pull operations    ** 
 * followed by one relabel operation.                           **
 * **************************************************************/

#define CONTROL_M 40

//////////////////////////////////////////////////////////////
//Functions prototypes                                      //
//////////////////////////////////////////////////////////////

/********************************************************************    
 * cudaCutsInit(width, height, numOfLabels) function sets the      **
 * width, height and numOfLabels of grid. It also initializes the  **
 * block size  on the device and finds the total number of blocks  **
 * running in parallel on the device. It calls checkDevice         **
 * function which checks whether CUDA compatible device is present **
 * on the system or not. It allocates the memory on the host and   **
 * the device for the arrays which are required through the        **
 * function call h_mem_init and segment_init respectively. This    **
 * function returns 0 on success or -1 on failure if there is no   **
 * * * CUDA compatible device is present on the system             **
 * *****************************************************************/

int cudaCutsInit( int, int, int );

/**************************************************
 * function checks whether any CUDA compatible   **
 * device is present on the system or not. It    **
 * returns the number of devices present on the  **
 * system.                                       **
 * ***********************************************/

int checkDevice();

/**************************************************
 * h_mem_init returns allocates and intializes   **
 * memory on the host                            **
 * ***********************************************/

void h_mem_init();

/***************************************************************
 * This function allocates memory for n-edges, t-edges,       **
 * height and mask function, pixelLabels and intializes them  **
 * on the device.                                             **
 * ************************************************************/

void d_mem_init();

/********************************************************
 * This function copies the dataTerm from the host to  **
 * device and also copies the data into datacost array **
 * of size width * height * numOfLabels                **  
 * *****************************************************/

int cudaCutsSetupDataTerm(int *);

/*************************************************************
 * This function copies the smoothnessTerm from the host to  **
 * device and also copies the data into smoothnesscost array **
 * of size numOfLabels * numOfLabels                         **  
 * ***********************************************************/

int cudaCutsSetupSmoothTerm(int *);

/*************************************************************
 * As in our case, when the graph is grid, horizotal and    **
 * vertical cues can be specified. The hcue and vcue array  **
 * of size width * height stores these respectively.        ** 
 * ***********************************************************/

int cudaCutsSetupHCue(int *);
int cudaCutsSetupVCue(int *);

/*********************************************************
 * This function constructs the graph on the device.    **
 * ******************************************************/

int cudaCutsSetupGraph();

/************************************************************
 * The function calls the Cuda Cuts optimization algorithm **
 * and the bfs algorithm so as to assign a label to each   **
 * pixel                                                   ** 
 * *********************************************************/

int cudaCutsAtomicOptimize(  );
int cudaCutsStochasticOptimize();

/***********************************************************
 * This function calls three kernels which performs the   **
 * push, pull and relabel operation                       ** 
 * ********************************************************/

void cudaCutsStochastic( );
void cudaCutsAtomic(  );

/**********************************************************
 * This finds which of the nodes are in source set and   **
 * sink set                                              ** 
 * *******************************************************/

void bfsLabeling();

/****************************************************************
 * This function assigns a label to each pixel and stores them ** 
 * in pixelLabel array of size width * height                  ** 
 * *************************************************************/

int cudaCutsGetResult();

/************************************************************
 * De-allocates all the memory allocated on the host and   **
 * the device.                                             ** 
 * *********************************************************/

void cudaCutsFreeMem();

/***********************************************************
 * These functions calculates the total energy of the     **
 * configuration                                          **
 * ********************************************************/

int cudaCutsGetEnergy( );
int data_energy();
int smooth_energy();

////////////////////////////////////////////////////////////
//Global Variables declared                               //
////////////////////////////////////////////////////////////

/*************************************************
 * n-edges and t-edges                          **
 * **********************************************/

int *d_left_weight, *d_right_weight, *d_down_weight, *d_up_weight, *d_push_reser, *d_sink_weight;
int *s_left_weight, *s_right_weight, *s_down_weight, *s_up_weight, *s_push_reser, *s_sink_weight;
int *d_pull_left, *d_pull_right, *d_pull_down, *d_pull_up;

int *d_stochastic,  *d_stochastic_pixel, *d_terminate ; 

/*************************************************
 * Emergu parameters stored                     **
 * **********************************************/

int *hcue, *vcue, *datacost, *smoothnesscost ;
int *dataTerm, *smoothTerm, *hCue, *vCue ;
int *dDataTerm, *dSmoothTerm, *dHcue, *dVcue, *dPixelLabel ;


/*************************************************
 * Height and mask functions are stored         **
 * **********************************************/

int  *d_relabel_mask, *d_graph_heightr, *d_graph_heightw;

/*************************************************
 * Grid and Block parameters                    **
 * **********************************************/

int graph_size, size_int, width, height, graph_size1, width1, height1, depth, num_Labels;
int blocks_x, blocks_y, threads_x, threads_y, num_of_blocks, num_of_threads_per_block ;

/***************************************************
 * Label of each pixel is stored in this function **
 * *************************************************/

int *pixelLabel ;

bool *d_pixel_mask, h_over, *d_over, *h_pixel_mask ;
int *d_counter, *h_graph_height ;
int *h_reset_mem ;
int cueValues, deviceCheck, deviceCount ;

int *h_stochastic, *h_stochastic_pixel, *h_relabel_mask ; 
int counter ;

#endif
