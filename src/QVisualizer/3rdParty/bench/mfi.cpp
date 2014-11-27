#include <cstdlib>
#include <cstdio>
#include <cassert>

#include <stdint.h>

#include "mfi.h"

#pragma pack(push)
#pragma pack(1)

struct Header
{
  int32_t  dimension;
  int32_t  connectivity;

  int32_t  width;
  int32_t  height;
  int32_t  depth;
  
  int64_t  maxflow;    
      
  int32_t  symmetric_arcs;

  int8_t   metadata[4096];

  int32_t  active_count;
      
  int32_t  type_terminal_cap;
  int32_t  type_neighbor_cap;
};

#pragma pack(pop)

bool mfi_write(MFI* mfi,const char* filename)
{
  assert(mfi!=0);
  
  FILE* f = fopen(filename,"wb");
    
  if (f==0) { return false; }
    
  char magic[3] = { 'M', 'F', 'I' };
  fwrite(magic,sizeof(magic),1,f);
    
  Header header;

  header.dimension         = mfi->dimension;
  header.connectivity      = mfi->connectivity;
  header.width             = mfi->width;
  header.height            = mfi->height;
  header.depth             = mfi->depth;
  header.maxflow           = mfi->maxflow;
  header.symmetric_arcs    = mfi->symmetric_arcs;

  for(int i=0;i<4096;i++)
  { 
    header.metadata[i]     = mfi->metadata[i];
  }

  header.active_count      = mfi->active_count;
  header.type_terminal_cap = mfi->type_terminal_cap;
  header.type_neighbor_cap = mfi->type_neighbor_cap;
  
  fwrite(&header,sizeof(Header),1,f);  
  
  if (mfi->dimension==2) { mfi->depth = 1; }
  
  int num_nodes = mfi->width * mfi->height * mfi->depth;
  
  int table_sizeof[3] = { sizeof(uint8_t),
                          sizeof(uint16_t),
                          sizeof(uint32_t) };

  int sizeof_type_terminal_cap = table_sizeof[mfi->type_terminal_cap];
  int sizeof_type_neighbor_cap = table_sizeof[mfi->type_neighbor_cap];

  fwrite(mfi->cap_source,sizeof_type_terminal_cap,num_nodes,f);
  fwrite(mfi->cap_sink,sizeof_type_terminal_cap,num_nodes,f);

  for(int i=0;i<mfi->connectivity;i++)
  {
    fwrite(mfi->cap_neighbor[i],sizeof_type_neighbor_cap,num_nodes,f);
  }

  uint8_t* active_mask = (uint8_t*)malloc(num_nodes*sizeof(uint8_t));
  
  for(int i=0;i<num_nodes;i++)
  {
    active_mask[i] = mfi->active_mask[i];
  }
  
  fwrite(active_mask,sizeof(uint8_t),num_nodes,f);
    
  free(active_mask);
  
  fclose(f);
    
  return true;
}

MFI* mfi_read(const char* filename)
{  
  FILE* f = fopen(filename,"rb");
  
  if (f==0) { return 0; }
  
  char magic[3];
  fread(magic,sizeof(magic),1,f);
  
  if (ferror(f)) { fclose(f); return 0; }

  if (!(magic[0]=='M' && magic[1]=='F' && magic[2]=='I')) { fclose(f); return 0; }
    
  Header header;
  fread(&header,sizeof(Header),1,f);
  
  if (ferror(f)) { fclose(f); return 0; }
  
  MFI* mfi = (MFI*)malloc(sizeof(MFI));
  
  mfi->dimension         = header.dimension;
  mfi->connectivity      = header.connectivity;
  mfi->width             = header.width;
  mfi->height            = header.height;
  mfi->depth             = header.depth;
  mfi->maxflow           = header.maxflow;
  mfi->symmetric_arcs    = header.symmetric_arcs != 0;

  for(int i=0;i<4096;i++)
  { 
    mfi->metadata[i]     = header.metadata[i]; 
  }

  mfi->active_count      = header.active_count;
  mfi->type_terminal_cap = (MFI::Type)header.type_terminal_cap;
  mfi->type_neighbor_cap = (MFI::Type)header.type_neighbor_cap;

  mfi->cap_source        = 0;
  mfi->cap_sink          = 0;
  mfi->cap_neighbor      = 0;
  mfi->active_mask       = 0;
    
  if (mfi->dimension==2) { mfi->depth = 1; }
  
  int num_nodes = mfi->width * mfi->height * mfi->depth;
  
  int table_sizeof[3] = { sizeof(uint8_t),
                          sizeof(uint16_t),
                          sizeof(uint32_t) };

  int sizeof_type_terminal_cap = table_sizeof[mfi->type_terminal_cap];
  int sizeof_type_neighbor_cap = table_sizeof[mfi->type_neighbor_cap];

  mfi->cap_source   = malloc(num_nodes*sizeof_type_terminal_cap);
  mfi->cap_sink     = malloc(num_nodes*sizeof_type_terminal_cap);
  
  mfi->cap_neighbor = (void**)malloc(mfi->connectivity*sizeof(void*));
  
  for(int i=0;i<mfi->connectivity;i++)
  {
    mfi->cap_neighbor[i] = malloc(num_nodes*sizeof_type_neighbor_cap);
  }

  fread(mfi->cap_source,sizeof_type_terminal_cap,num_nodes,f);
  fread(mfi->cap_sink,sizeof_type_terminal_cap,num_nodes,f);

  for(int i=0;i<mfi->connectivity;i++)
  {
    fread(mfi->cap_neighbor[i],sizeof_type_neighbor_cap,num_nodes,f);
  }
  
  uint8_t* active_mask = (uint8_t*)malloc(num_nodes*sizeof(uint8_t));
  
  fread(active_mask,sizeof(uint8_t),num_nodes,f);
  
  mfi->active_mask  = (unsigned char*)malloc(num_nodes*sizeof(unsigned char));
  
  for(int i=0;i<num_nodes;i++)
  {
    mfi->active_mask[i] = active_mask[i];
  }
  
  free(active_mask);
  
  fclose(f);
  
  return mfi;
}

void mfi_free(MFI* mfi)
{
  if (mfi!=0)
  {
    free(mfi->active_mask);

    for(int i=0;i<mfi->connectivity;i++)
    {
      free(mfi->cap_neighbor[i]);
    }
    
    free(mfi->cap_neighbor);
    free(mfi->cap_sink);    
    free(mfi->cap_source);
    
    free(mfi);
  }
}
