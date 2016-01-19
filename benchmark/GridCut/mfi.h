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

/**
template <typename T>
inline long long computeExcessFlowFromCut(MFI* mfi, char* cutData)
{
    int w = mfi->width;
    int h = mfi->height;
    int d = mfi->depth;
    int min = std::numeric_limits<int>::lowest();
    int max = std::numeric_limits<int>::max();
    long long maxFlow = 0;
    T* cap_source = (T*)mfi->cap_source;
    T* cap_sink = (T*)mfi->cap_sink;
    int sourceCount = 0, sinkCount = 0;
    for(int z=0;z<d;z++)
        for(int y=0;y<h;y++)
            for(int x=0;x<w;x++)
            {
                T source = *(cap_source);
                T sink = *(cap_sink);
                if (cutData[0])
                {
                    *(cap_source) = 999999;
                    sourceCount++;
                }
                else
                {
                    *(cap_source) = 0;
                }
                if (cutData[1])
                {
                    *(cap_sink) = 999999;
                    sinkCount++;
                }
                else
                {
                    *(cap_sink) = 0;
                }
                cutData += 4;
                cap_source++;
                cap_sink++;
                maxFlow += std::min<T>(source, sink);
            };
    return maxFlow;
}

template <typename T>
inline long long computeExcessFlow(MFI* mfi, int* excessFlow)
{
    int w = mfi->width;
    int h = mfi->height;
    int d = mfi->depth;
    long long maxFlow = 0;
    T* cap_source = (T*)mfi->cap_source;
    T* cap_sink = (T*)mfi->cap_sink;
    for(int z=0;z<d;z++)
        for(int y=0;y<h;y++)
            for(int x=0;x<w;x++)
            {
                T source = *(cap_source++);
                T sink = *(cap_sink++);
                *(excessFlow++) = (int)source - sink;
                maxFlow += std::min<T>(source, sink);
            };
    return maxFlow;
}

template <typename T>
inline void clampCapacity(MFI* mfi)
{
    int w = mfi->width;
    int h = mfi->height;
    int d = mfi->depth;
    const int size = mfi->connectivity;
    if (size == 4)
    {
        T* cap_neighbor[4] = {
            (T*)(mfi->cap_neighbor[0]),
            (T*)(mfi->cap_neighbor[1]),
            (T*)(mfi->cap_neighbor[2]),
            (T*)(mfi->cap_neighbor[3])
        };
        for (int y = 0; y < h; y++)
            for (int x = 0; x < w; x++)
            {
                if (x == w - 1)
                {
                    *(cap_neighbor[MFI::ARC_GE]) = 0;
                }
                else
                {
                    *(cap_neighbor[MFI::ARC_LE] + 1) = *(cap_neighbor[MFI::ARC_GE]);
                    if (x == 0) *(cap_neighbor[MFI::ARC_LE]) = 0;
                }
                if (y == h - 1)
                {
                    *(cap_neighbor[MFI::ARC_EG]) = 0;
                }
                else
                {
                    *(cap_neighbor[MFI::ARC_EL] + w) = *(cap_neighbor[MFI::ARC_EG]);
                    if (y == 0) *(cap_neighbor[MFI::ARC_EL]) = 0;
                }

                cap_neighbor[MFI::ARC_GE]++;
                cap_neighbor[MFI::ARC_EG]++;
                cap_neighbor[MFI::ARC_EL]++;
                cap_neighbor[MFI::ARC_LE]++;
            };
    }
    else if (size == 6)
    {
        T* cap_neighbor[6] = {
            (T*)(mfi->cap_neighbor[0]),
            (T*)(mfi->cap_neighbor[1]),
            (T*)(mfi->cap_neighbor[2]),
            (T*)(mfi->cap_neighbor[3]),
            (T*)(mfi->cap_neighbor[4]),
            (T*)(mfi->cap_neighbor[5])
        };
        for (int z = 0; z < d; z++)
            for (int y = 0; y < h; y++)
                for (int x = 0; x < w; x++)
                {
                    if (x == w - 1)
                    {
                        *(cap_neighbor[MFI::ARC_GEE]) = 0;
                    }
                    else
                    {
                        *(cap_neighbor[MFI::ARC_LEE] + 1) = *(cap_neighbor[MFI::ARC_GEE]);
                        if (x == 0) *(cap_neighbor[MFI::ARC_LEE]) = 0;
                    }
                    if (y == h - 1)
                    {
                        *(cap_neighbor[MFI::ARC_EGE]) = 0;
                    }
                    else
                    {
                        *(cap_neighbor[MFI::ARC_ELE] + w) = *(cap_neighbor[MFI::ARC_EGE]);
                        if (y == 0) *(cap_neighbor[MFI::ARC_ELE]) = 0;
                    }
                    if (z == d - 1)
                    {
                        *(cap_neighbor[MFI::ARC_EEG]) = 0;
                    }
                    else
                    {
                        *(cap_neighbor[MFI::ARC_EEL] + w * h) = *(cap_neighbor[MFI::ARC_EEG]);
                        if (z == 0) *(cap_neighbor[MFI::ARC_EEL]) = 0;
                    }

                    cap_neighbor[MFI::ARC_GEE]++;
                    cap_neighbor[MFI::ARC_EGE]++;
                    cap_neighbor[MFI::ARC_EEG]++;
                    cap_neighbor[MFI::ARC_EEL]++;
                    cap_neighbor[MFI::ARC_ELE]++;
                    cap_neighbor[MFI::ARC_LEE]++;
                };
    }
}

template <typename T>
inline void computeCapacity(MFI* mfi, int* capacity)
{
    int w = mfi->width;
    int h = mfi->height;
    int d = mfi->depth;
    const int size = mfi->connectivity;
    if (size == 4)
    {
        T* cap_neighbor[4] = {
            (T*)(mfi->cap_neighbor[0]),
            (T*)(mfi->cap_neighbor[1]),
            (T*)(mfi->cap_neighbor[2]),
            (T*)(mfi->cap_neighbor[3])
        };
        for(int y=0;y<h;y++)
            for(int x=0;x<w;x++)
            {
                *(capacity++) = *(cap_neighbor[MFI::ARC_GE]++);
                *(capacity++) = *(cap_neighbor[MFI::ARC_EG]++);
                *(capacity++) = 0.0f;
                *(capacity++) = 0.0f;
                *(capacity++) = *(cap_neighbor[MFI::ARC_EL]++);
                *(capacity++) = *(cap_neighbor[MFI::ARC_LE]++);
            };
    }
    else if (size == 6)
    {
        T* cap_neighbor[6] = {
            (T*)(mfi->cap_neighbor[0]),
            (T*)(mfi->cap_neighbor[1]),
            (T*)(mfi->cap_neighbor[2]),
            (T*)(mfi->cap_neighbor[3]),
            (T*)(mfi->cap_neighbor[4]),
            (T*)(mfi->cap_neighbor[5])
        };
        for(int z=0;z<d;z++)
            for(int y=0;y<h;y++)
                for(int x=0;x<w;x++)
                {
                    *(capacity++) = *(cap_neighbor[MFI::ARC_GEE]++);
                    *(capacity++) = *(cap_neighbor[MFI::ARC_EGE]++);
                    *(capacity++) = *(cap_neighbor[MFI::ARC_EEG]++);
                    *(capacity++) = *(cap_neighbor[MFI::ARC_EEL]++);
                    *(capacity++) = *(cap_neighbor[MFI::ARC_ELE]++);
                    *(capacity++) = *(cap_neighbor[MFI::ARC_LEE]++);
                };
    }
}

template <typename T>
inline void scaleNeighborCapacity(MFI* mfi)
{
    int w = mfi->width;
    int h = mfi->height;
    int d = mfi->depth;

    int sizeof_type_neighbor_cap = sizeof(T);
    int size = mfi->connectivity;
    if (size == 4)
    {
        int wt = w << 1;
        int ht = h << 1;
        int num_nodes_t = wt * ht;

        T* cap_neighbor[4] =
        {
            (T*)(mfi->cap_neighbor[0]),
            (T*)(mfi->cap_neighbor[1]),
            (T*)(mfi->cap_neighbor[2]),
            (T*)(mfi->cap_neighbor[3])
        };

        T* cap_neighbor_t[4];
        for(int i = 0; i < size; i++)
            cap_neighbor_t[i] = (T*)malloc(num_nodes_t * sizeof_type_neighbor_cap);

        for(int yt = 0; yt < ht; yt++)
            for(int xt = 0; xt < wt; xt++)
            {
                int x[2] = { xt / 2, std::min<int>((xt + 1) / 2, w - 1) };
                int y[2] = { yt / 2, std::min<int>((yt + 1) / 2, h - 1) };
                int sum[4] = { 0, 0, 0, 0 };
                for (int yi = 0; yi < 2; yi++)
                    for (int xi = 0; xi <2; xi++)
                        for(int i = 0; i < size; i++)
                            sum[i] += cap_neighbor[i][x[xi] + w * y[yi]];

                for(int i = 0; i < size; i++)
                    cap_neighbor_t[i][xt + wt * yt] = sum[i] >> 2;
            };

        for(int i = 0; i < size; i++)
            free(mfi->cap_neighbor[i]);

        for(int i = 0; i < size; i++)
            mfi->cap_neighbor[i] = cap_neighbor_t[i];
    }
    else if (size == 6)
    {
        int wt = w << 1;
        int ht = h << 1;
        int dt = d << 1;
        int num_nodes_t = wt * ht * dt;

        T* cap_neighbor[6] =
        {
            (T*)(mfi->cap_neighbor[0]),
            (T*)(mfi->cap_neighbor[1]),
            (T*)(mfi->cap_neighbor[2]),
            (T*)(mfi->cap_neighbor[3]),
            (T*)(mfi->cap_neighbor[4]),
            (T*)(mfi->cap_neighbor[5])
        };
        
        T* cap_neighbor_t[6];
        for(int i = 0; i < size; i++)
            cap_neighbor_t[i] = (T*)malloc(num_nodes_t * sizeof_type_neighbor_cap);
        
        for(int zt = 0; zt < dt; zt++)
            for(int yt = 0; yt < ht; yt++)
                for(int xt = 0; xt < wt; xt++)
                {
                    int x[2] = { xt / 2, std::min<int>((xt + 1) / 2, w - 1) };
                    int y[2] = { yt / 2, std::min<int>((yt + 1) / 2, h - 1) };
                    int z[2] = { zt / 2, std::min<int>((zt + 1) / 2, d - 1) };
                    int sum[6] = { 0, 0, 0, 0, 0, 0 };
                    for (int zi = 0; zi < 2; zi++)
                        for (int yi = 0; yi < 2; yi++)
                            for (int xi = 0; xi <2; xi++)
                                for(int i = 0; i < size; i++)
                                    sum[i] += cap_neighbor[i][x[xi] + w * (y[yi] + h * z[zi])];

                    for(int i = 0; i < size; i++)
                        cap_neighbor_t[i][xt + wt * (yt + ht * zt)] = sum[i] >> 3;
                };

        for(int i = 0; i < size; i++)
            free(mfi->cap_neighbor[i]);

        for(int i = 0; i < size; i++)
            mfi->cap_neighbor[i] = cap_neighbor_t[i];
    }
}

template <typename T>
inline void scaleTerminalCapacity(MFI* mfi)
{
    int w = mfi->width;
    int h = mfi->height;
    int d = mfi->depth;

    int sizeof_type_terminal_cap = sizeof(T);
    int size = mfi->connectivity;
    if (size == 4)
    {
        int wt = w << 1;
        int ht = h << 1;
        int num_nodes_t = wt * ht;

        T* cap_terminal[2] =
        {
            (T*)(mfi->cap_source),
            (T*)(mfi->cap_sink)
        };

        T* cap_terminal_t[2];
        for(int i = 0; i < 2; i++)
            cap_terminal_t[i] = (T*)malloc(num_nodes_t * sizeof_type_terminal_cap);

        for(int yt = 0; yt < ht; yt++)
            for(int xt = 0; xt < wt; xt++)
            {
                int x[2] = { xt / 2, std::min<int>((xt + 1) / 2, w - 1) };
                int y[2] = { yt / 2, std::min<int>((yt + 1) / 2, h - 1) };
                int sum[2] = { 0, 0 };
                for (int yi = 0; yi < 2; yi++)
                    for (int xi = 0; xi <2; xi++)
                        for(int i = 0; i < 2; i++)
                            sum[i] += cap_terminal[i][x[xi] + w * y[yi]];

                int flow = std::min<int>(sum[0], sum[1]);
                for(int i = 0; i < 2; i++)
                    cap_terminal_t[i][xt + wt * yt] = (sum[i] - flow) >> 2;
            };

        free(mfi->cap_source);
        free(mfi->cap_sink);

        mfi->cap_source = cap_terminal_t[0];
        mfi->cap_sink = cap_terminal_t[1];
    }
    else if (size == 6)
    {
        int wt = w << 1;
        int ht = h << 1;
        int dt = d << 1;
        int num_nodes_t = wt * ht * dt;

        T* cap_terminal[2] =
        {
            (T*)(mfi->cap_source),
            (T*)(mfi->cap_sink)
        };

        T* cap_terminal_t[2];
        for(int i = 0; i < 2; i++)
            cap_terminal_t[i] = (T*)malloc(num_nodes_t * sizeof_type_terminal_cap);

        for(int zt = 0; zt < dt; zt++)
            for(int yt = 0; yt < ht; yt++)
                for(int xt = 0; xt < wt; xt++)
                {
                    int x[2] = { xt / 2, std::min<int>((xt + 1) / 2, w - 1) };
                    int y[2] = { yt / 2, std::min<int>((yt + 1) / 2, h - 1) };
                    int z[2] = { zt / 2, std::min<int>((zt + 1) / 2, d - 1) };
                    int sum[2] = { 0, 0 };
                    for (int zi = 0; zi < 2; zi++)
                        for (int yi = 0; yi < 2; yi++)
                            for (int xi = 0; xi <2; xi++)
                                for(int i = 0; i < 2; i++)
                                    sum[i] += cap_terminal[i][x[xi] + w * (y[yi] + h * z[zi])];

                    int flow = std::min<int>(sum[0], sum[1]);
                    for(int i = 0; i < 2; i++)
                        cap_terminal_t[i][xt + wt * (yt + ht * zt)] = (sum[i] - flow) >> 3;
                };

        free(mfi->cap_source);
        free(mfi->cap_sink);

        mfi->cap_source = cap_terminal_t[0];
        mfi->cap_sink = cap_terminal_t[1];
    }
}
//*/
#endif
