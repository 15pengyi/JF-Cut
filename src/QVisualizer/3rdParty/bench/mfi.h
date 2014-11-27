#ifndef MFI_H_
#define MFI_H_

struct MFI                   
{  
  int             dimension;         
  int             connectivity;      
  
  int             width;             
  int             height;            
  int             depth;             
  
  long long       maxflow;
    
  bool            symmetric_arcs;

  char            metadata[4096];

  int             active_count;
  unsigned char*  active_mask;
   
  enum Type       { TYPE_UINT8, TYPE_UINT16, TYPE_UINT32 };
  
  Type            type_terminal_cap;
  Type            type_neighbor_cap;
    
  void*           cap_source;
  void*           cap_sink;    
  void**          cap_neighbor;

  enum Arc
  {
    // 2-dimensional / 4-connected
    ARC_LE  =  0, // (-1, 0)
    ARC_GE  =  1, // (+1, 0)
    ARC_EL  =  2, // ( 0,-1)
    ARC_EG  =  3, // ( 0,+1)

    // 2-dimensional / 8-connected
    ARC_LL  =  4, // (-1,-1)
    ARC_GL  =  5, // (+1,-1)
    ARC_LG  =  6, // (-1,+1)
    ARC_GG  =  7, // (+1,+1)

    // 3-dimensional / 6-connected
    ARC_LEE =  0, // (-1, 0, 0)
    ARC_GEE =  1, // (+1, 0, 0)
    ARC_ELE =  2, // ( 0,-1, 0)
    ARC_EGE =  3, // ( 0,+1, 0)
    ARC_EEL =  4, // ( 0, 0,-1)
    ARC_EEG =  5, // ( 0, 0,+1)
    
    // 3-dimensional / 18-connected
    ARC_LLE =  6, // (-1,-1, 0)
    ARC_GLE =  7, // (+1,-1, 0)
    ARC_LGE =  8, // (-1,+1, 0)
    ARC_GGE =  9, // (+1,+1, 0)
    ARC_ELL = 10, // ( 0,-1,-1)
    ARC_EGL = 11, // ( 0,+1,-1) 
    ARC_ELG = 12, // ( 0,-1,+1)
    ARC_EGG = 13, // ( 0,+1,+1)
    ARC_LEL = 14, // (-1, 0,-1)
    ARC_LEG = 15, // (-1, 0,+1)
    ARC_GEL = 16, // (+1, 0,-1)
    ARC_GEG = 17, // (+1, 0,+1)
    
    // 3-dimensional / 26-connected
    ARC_LLL = 18, // (-1,-1,-1)
    ARC_GLL = 19, // (+1,-1,-1)
    ARC_LGL = 20, // (-1,+1,-1)
    ARC_GGL = 21, // (+1,+1,-1)
    ARC_LLG = 22, // (-1,-1,+1)
    ARC_GLG = 23, // (+1,-1,+1)
    ARC_LGG = 24, // (-1,+1,+1)
    ARC_GGG = 25  // (+1,+1,+1)
  };
};


MFI* mfi_read(const char* filename);
void mfi_free(MFI* mfi);

bool mfi_write(MFI* mfi,const char* filename);

#endif
