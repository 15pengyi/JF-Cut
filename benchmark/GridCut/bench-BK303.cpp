#include <cstdio>
#include <cstdlib>
#include <vector>

#include <graph.h>

#include "dataset.h"
#include "mfi.h"
#include "timer.h"
#include "QIO.h"

double t1;
double t2;

#define CLOCK_START()    { timerReset();    t1 = timerGet(); }
#define CLOCK_STOP(TIME) { t2 = timerGet(); *TIME = t2-t1;   }

template<typename type_terminal_cap,typename type_neighbor_cap>
void run_BK303_2D_4C(MFI* mfi,unsigned char* out_label,int* out_maxflow,double* time_init,double* time_maxflow,double* time_output)
{
  const int w = mfi->width;
  const int h = mfi->height;
  
  const type_terminal_cap* cap_source = (type_terminal_cap*)mfi->cap_source;
  const type_terminal_cap* cap_sink   = (type_terminal_cap*)mfi->cap_sink;
  
  const type_neighbor_cap* cap_neighbor[4] = { (type_neighbor_cap*)(mfi->cap_neighbor[0]),
                                               (type_neighbor_cap*)(mfi->cap_neighbor[1]),
                                               (type_neighbor_cap*)(mfi->cap_neighbor[2]),
                                               (type_neighbor_cap*)(mfi->cap_neighbor[3]) };
     
  typedef Graph<int,int,int> GraphType;
  
  CLOCK_START();
  GraphType* graph = new GraphType(w*h,w*h*2);
        
  graph->add_node(w*h);
   
  for(int y=0;y<h;y++)
  for(int x=0;x<w;x++)
  {    
    graph->add_tweights(x+y*w,cap_source[x+y*w],cap_sink[x+y*w]);

    if (x<w-1) graph->add_edge(x+y*w,(x+1)+y*w,cap_neighbor[MFI::ARC_GE][x+y*w],cap_neighbor[MFI::ARC_LE][(x+1)+y*w]);
    if (y<h-1) graph->add_edge(x+y*w,x+(y+1)*w,cap_neighbor[MFI::ARC_EG][x+y*w],cap_neighbor[MFI::ARC_EL][x+(y+1)*w]);
  }
  CLOCK_STOP(time_init);

  CLOCK_START();
  *out_maxflow = graph->maxflow();
  CLOCK_STOP(time_maxflow);
     
  CLOCK_START();
  for(int xy=0;xy<w*h;xy++) out_label[xy] = graph->what_segment(xy);
  
  delete graph;
  CLOCK_STOP(time_output);
}

template<typename type_terminal_cap,typename type_neighbor_cap>
void run_BK303_3D_6C(MFI* mfi,unsigned char* out_label,int* out_maxflow,double* time_init,double* time_maxflow,double* time_output)
{
  const int w = mfi->width;
  const int h = mfi->height;
  const int d = mfi->depth;
  
  const type_terminal_cap* cap_source = (type_terminal_cap*)mfi->cap_source;
  const type_terminal_cap* cap_sink   = (type_terminal_cap*)mfi->cap_sink;
  
  const type_neighbor_cap* cap_neighbor[6] = { (type_neighbor_cap*)(mfi->cap_neighbor[0]),
                                               (type_neighbor_cap*)(mfi->cap_neighbor[1]),
                                               (type_neighbor_cap*)(mfi->cap_neighbor[2]),
                                               (type_neighbor_cap*)(mfi->cap_neighbor[3]),
                                               (type_neighbor_cap*)(mfi->cap_neighbor[4]),
                                               (type_neighbor_cap*)(mfi->cap_neighbor[5]) };
    
  const int num_nodes = w*h*d;
  const int num_edges = (w-1)*(h*d) + (h-1)*(w*d) + (d-1)*(w*h);
  
  typedef Graph<int,int,int> GraphType;

  CLOCK_START();
  GraphType* graph = new GraphType(num_nodes,num_edges); 
        
  graph->add_node(num_nodes); 
  
  for(int z=0;z<d;z++)
  for(int y=0;y<h;y++)
  for(int x=0;x<w;x++)
  {
    graph->add_tweights(x+y*w+z*(w*h),cap_source[x+y*w+z*(w*h)],cap_sink[x+y*w+z*(w*h)]);

    if (x<w-1) graph->add_edge(x+y*w+z*(w*h),(x+1)+y*w+z*(w*h),cap_neighbor[MFI::ARC_GEE][x+y*w+z*(w*h)],cap_neighbor[MFI::ARC_LEE][(x+1)+y*w+z*(w*h)]);
    if (y<h-1) graph->add_edge(x+y*w+z*(w*h),x+(y+1)*w+z*(w*h),cap_neighbor[MFI::ARC_EGE][x+y*w+z*(w*h)],cap_neighbor[MFI::ARC_ELE][x+(y+1)*w+z*(w*h)]);
    if (z<d-1) graph->add_edge(x+y*w+z*(w*h),x+y*w+(z+1)*(w*h),cap_neighbor[MFI::ARC_EEG][x+y*w+z*(w*h)],cap_neighbor[MFI::ARC_EEL][x+y*w+(z+1)*(w*h)]);
  }   
  CLOCK_STOP(time_init);

  CLOCK_START();
  *out_maxflow = graph->maxflow();
  CLOCK_STOP(time_maxflow);

  CLOCK_START();
  for(int xyz=0;xyz<num_nodes;xyz++) out_label[xyz] = graph->what_segment(xyz);
  
  delete graph;
  CLOCK_STOP(time_output);
}

template<typename type_terminal_cap,typename type_neighbor_cap>
void run_BK303_3D_26C(MFI* mfi,unsigned char* out_label,int* out_maxflow,double* time_init,double* time_maxflow,double* time_output)
{
  const int w = mfi->width;
  const int h = mfi->height;
  const int d = mfi->depth;
  
  const type_terminal_cap* cap_source = (type_terminal_cap*)mfi->cap_source;
  const type_terminal_cap* cap_sink   = (type_terminal_cap*)mfi->cap_sink;
  
  const type_neighbor_cap* cap_neighbor[26] = { (type_neighbor_cap*)(mfi->cap_neighbor[ 0]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[ 1]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[ 2]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[ 3]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[ 4]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[ 5]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[ 6]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[ 7]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[ 8]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[ 9]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[10]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[11]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[12]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[13]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[14]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[15]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[16]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[17]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[18]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[19]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[20]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[21]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[22]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[23]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[24]),
                                                (type_neighbor_cap*)(mfi->cap_neighbor[25]) };
                                                    
  const int num_nodes = w*h*d;
  const int num_edges = 13*w*h*d;
  
  typedef Graph<int,int,int> GraphType;

  CLOCK_START();
  GraphType* graph = new GraphType(num_nodes,num_edges); 
        
  graph->add_node(num_nodes);
  
  for(int z=0;z<d;z++)
  for(int y=0;y<h;y++)
  for(int x=0;x<w;x++)
  {
    graph->add_tweights(x+y*w+z*(w*h),cap_source[x+y*w+z*(w*h)],cap_sink[x+y*w+z*(w*h)]);

    if (x<w-1 && y<h-1 && z<d-1) graph->add_edge(x+y*w+z*(w*h),(x+1)+(y+1)*w+(z+1)*(w*h),cap_neighbor[MFI::ARC_GGG][x+y*w+z*(w*h)],cap_neighbor[MFI::ARC_LLL][(x+1)+(y+1)*w+(z+1)*(w*h)]);
    if (x<w-1          && z<d-1) graph->add_edge(x+y*w+z*(w*h),(x+1)+(y  )*w+(z+1)*(w*h),cap_neighbor[MFI::ARC_GEG][x+y*w+z*(w*h)],cap_neighbor[MFI::ARC_LEL][(x+1)+(y  )*w+(z+1)*(w*h)]);
    if (x<w-1 && y>0   && z<d-1) graph->add_edge(x+y*w+z*(w*h),(x+1)+(y-1)*w+(z+1)*(w*h),cap_neighbor[MFI::ARC_GLG][x+y*w+z*(w*h)],cap_neighbor[MFI::ARC_LGL][(x+1)+(y-1)*w+(z+1)*(w*h)]);
    if (x<w-1 && y<h-1         ) graph->add_edge(x+y*w+z*(w*h),(x+1)+(y+1)*w+(z  )*(w*h),cap_neighbor[MFI::ARC_GGE][x+y*w+z*(w*h)],cap_neighbor[MFI::ARC_LLE][(x+1)+(y+1)*w+(z  )*(w*h)]);
    if (x<w-1                  ) graph->add_edge(x+y*w+z*(w*h),(x+1)+(y  )*w+(z  )*(w*h),cap_neighbor[MFI::ARC_GEE][x+y*w+z*(w*h)],cap_neighbor[MFI::ARC_LEE][(x+1)+(y  )*w+(z  )*(w*h)]);
    if (x<w-1 && y>0           ) graph->add_edge(x+y*w+z*(w*h),(x+1)+(y-1)*w+(z  )*(w*h),cap_neighbor[MFI::ARC_GLE][x+y*w+z*(w*h)],cap_neighbor[MFI::ARC_LGE][(x+1)+(y-1)*w+(z  )*(w*h)]);
    if (x<w-1 && y<h-1 && z>0  ) graph->add_edge(x+y*w+z*(w*h),(x+1)+(y+1)*w+(z-1)*(w*h),cap_neighbor[MFI::ARC_GGL][x+y*w+z*(w*h)],cap_neighbor[MFI::ARC_LLG][(x+1)+(y+1)*w+(z-1)*(w*h)]);
    if (x<w-1          && z>0  ) graph->add_edge(x+y*w+z*(w*h),(x+1)+(y  )*w+(z-1)*(w*h),cap_neighbor[MFI::ARC_GEL][x+y*w+z*(w*h)],cap_neighbor[MFI::ARC_LEG][(x+1)+(y  )*w+(z-1)*(w*h)]);
    if (x<w-1 && y>0   && z>0  ) graph->add_edge(x+y*w+z*(w*h),(x+1)+(y-1)*w+(z-1)*(w*h),cap_neighbor[MFI::ARC_GLL][x+y*w+z*(w*h)],cap_neighbor[MFI::ARC_LGG][(x+1)+(y-1)*w+(z-1)*(w*h)]);
    if (         y<h-1 && z<d-1) graph->add_edge(x+y*w+z*(w*h),(x  )+(y+1)*w+(z+1)*(w*h),cap_neighbor[MFI::ARC_EGG][x+y*w+z*(w*h)],cap_neighbor[MFI::ARC_ELL][(x  )+(y+1)*w+(z+1)*(w*h)]);
    if (                  z<d-1) graph->add_edge(x+y*w+z*(w*h),(x  )+(y  )*w+(z+1)*(w*h),cap_neighbor[MFI::ARC_EEG][x+y*w+z*(w*h)],cap_neighbor[MFI::ARC_EEL][(x  )+(y  )*w+(z+1)*(w*h)]);
    if (         y>0   && z<d-1) graph->add_edge(x+y*w+z*(w*h),(x  )+(y-1)*w+(z+1)*(w*h),cap_neighbor[MFI::ARC_ELG][x+y*w+z*(w*h)],cap_neighbor[MFI::ARC_EGL][(x  )+(y-1)*w+(z+1)*(w*h)]);
    if (         y<h-1         ) graph->add_edge(x+y*w+z*(w*h),(x  )+(y+1)*w+(z  )*(w*h),cap_neighbor[MFI::ARC_EGE][x+y*w+z*(w*h)],cap_neighbor[MFI::ARC_ELE][(x  )+(y+1)*w+(z  )*(w*h)]);
  }   
  CLOCK_STOP(time_init);

  CLOCK_START();
  *out_maxflow = graph->maxflow();
  CLOCK_STOP(time_maxflow);

  CLOCK_START()
  for(int xyz=0;xyz<num_nodes;xyz++) out_label[xyz] = graph->what_segment(xyz);
  
  delete graph;
  CLOCK_STOP(time_output);
}

int main(int argc,char** argv) 
{
  void (*run_BK303[4][27][3][3])(MFI*,unsigned char*,int*,double*,double*,double*);                                               \

  run_BK303[2][ 4][MFI::TYPE_UINT8 ][MFI::TYPE_UINT8 ] = run_BK303_2D_4C<unsigned char ,unsigned char >;
  run_BK303[2][ 4][MFI::TYPE_UINT16][MFI::TYPE_UINT8 ] = run_BK303_2D_4C<unsigned short,unsigned char >;
  run_BK303[2][ 4][MFI::TYPE_UINT32][MFI::TYPE_UINT8 ] = run_BK303_2D_4C<unsigned int,  unsigned char >;
  run_BK303[2][ 4][MFI::TYPE_UINT8 ][MFI::TYPE_UINT16] = run_BK303_2D_4C<unsigned char ,unsigned short>;
  run_BK303[2][ 4][MFI::TYPE_UINT16][MFI::TYPE_UINT16] = run_BK303_2D_4C<unsigned short,unsigned short>;
  run_BK303[2][ 4][MFI::TYPE_UINT32][MFI::TYPE_UINT16] = run_BK303_2D_4C<unsigned int,  unsigned short>;
  run_BK303[2][ 4][MFI::TYPE_UINT8 ][MFI::TYPE_UINT32] = run_BK303_2D_4C<unsigned char ,unsigned int  >;
  run_BK303[2][ 4][MFI::TYPE_UINT16][MFI::TYPE_UINT32] = run_BK303_2D_4C<unsigned short,unsigned int  >;
  run_BK303[2][ 4][MFI::TYPE_UINT32][MFI::TYPE_UINT32] = run_BK303_2D_4C<unsigned int,  unsigned int  >;
  run_BK303[3][ 6][MFI::TYPE_UINT8 ][MFI::TYPE_UINT8 ] = run_BK303_3D_6C<unsigned char ,unsigned char >;
  run_BK303[3][ 6][MFI::TYPE_UINT16][MFI::TYPE_UINT8 ] = run_BK303_3D_6C<unsigned short,unsigned char >;
  run_BK303[3][ 6][MFI::TYPE_UINT32][MFI::TYPE_UINT8 ] = run_BK303_3D_6C<unsigned int,  unsigned char >;
  run_BK303[3][ 6][MFI::TYPE_UINT8 ][MFI::TYPE_UINT16] = run_BK303_3D_6C<unsigned char ,unsigned short>;
  run_BK303[3][ 6][MFI::TYPE_UINT16][MFI::TYPE_UINT16] = run_BK303_3D_6C<unsigned short,unsigned short>;
  run_BK303[3][ 6][MFI::TYPE_UINT32][MFI::TYPE_UINT16] = run_BK303_3D_6C<unsigned int,  unsigned short>;
  run_BK303[3][ 6][MFI::TYPE_UINT8 ][MFI::TYPE_UINT32] = run_BK303_3D_6C<unsigned char ,unsigned int  >;
  run_BK303[3][ 6][MFI::TYPE_UINT16][MFI::TYPE_UINT32] = run_BK303_3D_6C<unsigned short,unsigned int  >;
  run_BK303[3][ 6][MFI::TYPE_UINT32][MFI::TYPE_UINT32] = run_BK303_3D_6C<unsigned int,  unsigned int  >;
  run_BK303[3][26][MFI::TYPE_UINT8 ][MFI::TYPE_UINT8 ] = run_BK303_3D_26C<unsigned char ,unsigned char >;
  run_BK303[3][26][MFI::TYPE_UINT16][MFI::TYPE_UINT8 ] = run_BK303_3D_26C<unsigned short,unsigned char >;
  run_BK303[3][26][MFI::TYPE_UINT32][MFI::TYPE_UINT8 ] = run_BK303_3D_26C<unsigned int,  unsigned char >;
  run_BK303[3][26][MFI::TYPE_UINT8 ][MFI::TYPE_UINT16] = run_BK303_3D_26C<unsigned char ,unsigned short>;
  run_BK303[3][26][MFI::TYPE_UINT16][MFI::TYPE_UINT16] = run_BK303_3D_26C<unsigned short,unsigned short>;
  run_BK303[3][26][MFI::TYPE_UINT32][MFI::TYPE_UINT16] = run_BK303_3D_26C<unsigned int,  unsigned short>;
  run_BK303[3][26][MFI::TYPE_UINT8 ][MFI::TYPE_UINT32] = run_BK303_3D_26C<unsigned char ,unsigned int  >;
  run_BK303[3][26][MFI::TYPE_UINT16][MFI::TYPE_UINT32] = run_BK303_3D_26C<unsigned short,unsigned int  >;
  run_BK303[3][26][MFI::TYPE_UINT32][MFI::TYPE_UINT32] = run_BK303_3D_26C<unsigned int,  unsigned int  >;
    
  const char* dataset_path = argc==2 ? argv[1] : "./dataset";
    
  int num_instances = (sizeof(instances)/sizeof(Instance));
  
  printf("instance                            time-init  time-maxflow  time-output  total\n");

  for(int i=0;i<num_instances;i++)
  {
    double sum_time_init = 0.0;
    double sum_time_maxflow = 0.0;
    double sum_time_output = 0.0;

    for(int j=0;j<instances[i].count;j++)
    {
      char filename[1024];
      
      if (instances[i].count==1)
      {
        sprintf(filename,instances[i].filename,dataset_path);
      }
      else
      {
        sprintf(filename,instances[i].filename,dataset_path,j);
      }
      
      MFI* mfi = mfi_read(filename);
      
      if (!mfi)
      {
        printf("FAILED to read instance %s\n",filename);
        continue;
      }
      /**
      bool scale = false;
      bool filter = false;
      std::string extension;

      if (scale)
      {
          switch (mfi->type_terminal_cap)
          {
          case MFI::TYPE_UINT8:
              scaleTerminalCapacity<unsigned char>(mfi);
              break;
          case MFI::TYPE_UINT16:
              scaleTerminalCapacity<unsigned short>(mfi);
              break;
          case MFI::TYPE_UINT32:
              scaleTerminalCapacity<unsigned int>(mfi);
              break;
          }

          switch (mfi->type_neighbor_cap)
          {
          case MFI::TYPE_UINT8:
              scaleNeighborCapacity<unsigned char>(mfi);
              break;
          case MFI::TYPE_UINT16:
              scaleNeighborCapacity<unsigned short>(mfi);
              break;
          case MFI::TYPE_UINT32:
              scaleNeighborCapacity<unsigned int>(mfi);
              break;
          }

          mfi->width <<= 1;
          mfi->height <<= 1;
          if (mfi->dimension == 3) mfi->depth <<= 1;
          mfi->active_count = mfi->width * mfi->height * mfi->depth;

          free(mfi->active_mask);
          mfi->active_mask = (unsigned char*)malloc(mfi->active_count);
          memset(mfi->active_mask, 1, mfi->active_count);

          extension = std::string(".scaled");
      }
      
      if (filter)
      {
          int size = mfi->width * mfi->height * mfi->depth;
          std::string cutFile(std::string(filename) + std::string(".cut"));
          std::vector<char> cutData(size * 4);
          QIO::getFileData(cutFile, cutData.data(), cutData.size());
          switch (mfi->type_terminal_cap)
          {
          case MFI::TYPE_UINT8:
              {
                  computeExcessFlowFromCut<unsigned char>(mfi, cutData.data());
                  clampCapacity<unsigned short>(mfi);
              }
              break;
          case MFI::TYPE_UINT16:
              {
                  computeExcessFlowFromCut<unsigned short>(mfi, cutData.data());
                  clampCapacity<unsigned short>(mfi);
              }
              break;
          case MFI::TYPE_UINT32:
              {
                  computeExcessFlowFromCut<unsigned int>(mfi, cutData.data());
                  clampCapacity<unsigned short>(mfi);
              }
              break;
          }

          extension = std::string(".filtered");
      }
      else
      {
          int size = mfi->width * mfi->height * mfi->depth;
          std::vector<int> excessFlow(size);
          switch (mfi->type_terminal_cap)
          {
          case MFI::TYPE_UINT8:
              {
                  unsigned char maxSource, maxSink;
                  computeExcessFlow<unsigned char>(mfi, excessFlow.data());
              }
              break;
          case MFI::TYPE_UINT16:
              {
                  unsigned short maxSource, maxSink;
                  computeExcessFlow<unsigned short>(mfi, excessFlow.data());
              }
              break;
          case MFI::TYPE_UINT32:
              {
                  unsigned int maxSource, maxSink;
                  computeExcessFlow<unsigned int>(mfi, excessFlow.data());
              }
              break;
          }
          QIO::saveFileData(std::string(filename) + ".ef", excessFlow.data(), excessFlow.size() * sizeof(int));

          if (mfi->connectivity == 4 || mfi->connectivity == 6)
          {
              std::vector<int> capacity(size * 6);
              int* ptrCapacity = capacity.data();
              switch (mfi->type_neighbor_cap)
              {
              case MFI::TYPE_UINT8:
                  clampCapacity<unsigned char>(mfi);
                  computeCapacity<unsigned char>(mfi, capacity.data());
                  break;
              case MFI::TYPE_UINT16:
                  clampCapacity<unsigned short>(mfi);
                  computeCapacity<unsigned short>(mfi, capacity.data());
                  break;
              case MFI::TYPE_UINT32:
                  clampCapacity<unsigned int>(mfi);
                  computeCapacity<unsigned int>(mfi, capacity.data());
                  break;
              }

              QIO::saveFileData(std::string(filename) + ".c", capacity.data(), capacity.size() * sizeof(int));
          }
      }
      //*/
      
      unsigned char* label = (unsigned char*)malloc(mfi->width*mfi->height*mfi->depth);
      /**/
      int maxflow = -1;
      
      double time_init;
      double time_maxflow;
      double time_output;
      
      run_BK303[mfi->dimension]
               [mfi->connectivity]
               [mfi->type_terminal_cap]
               [mfi->type_neighbor_cap](mfi,label,&maxflow,&time_init,&time_maxflow,&time_output);
      
      sum_time_init    += time_init;
      sum_time_maxflow += time_maxflow;
      sum_time_output  += time_output;
      
      /**
      std::string name(filename);
      printf("%s, (%d, %d, %d, %d, %d, %d)\n", name.c_str(),
          mfi->width, mfi->height, mfi->depth, mfi->connectivity, maxflow, mfi->maxflow);
      
      if (!extension.empty())
      {
          name += extension;
          mfi->maxflow = maxflow;
          mfi_write(mfi, name.c_str());
      }
      //*/

      /**/
      if (maxflow != mfi->maxflow)
      {
        printf("INVALID maxflow value returned for instance %s\n",filename);
        return 1;
      }
      //*/
      free(label);
      
      mfi_free(mfi);      
    }

    double sum_time_total = sum_time_init + sum_time_maxflow + sum_time_output;

    printf("%-38s % 6.0f        % 6.0f       % 6.0f % 6.0f\n",
           instances[i].name,sum_time_init,sum_time_maxflow,sum_time_output,sum_time_total);
  }

  return 0;  
}