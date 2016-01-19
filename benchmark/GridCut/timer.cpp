#ifdef _WIN32
  #define WIN32_LEAN_AND_MEAN
  #ifndef NOMINMAX
    #define NOMINMAX
  #endif    
  #include <windows.h>
#else
  #include <sys/time.h>
#endif

#ifdef _WIN32
  static bool timerInit = false;
  static double timerFreq;
  static LARGE_INTEGER timerStart;
  
  void timerReset()
  {
    if (!timerInit)
    {
      LARGE_INTEGER freq;
      QueryPerformanceFrequency(&freq);
      timerFreq = (double)freq.QuadPart;
      timerInit = true;
    }
    
    QueryPerformanceCounter(&timerStart);
  }
  
  double timerGet()
  {
    LARGE_INTEGER timerNow;
    QueryPerformanceCounter(&timerNow);
  
    return (((((double)(timerNow.QuadPart - timerStart.QuadPart)) / timerFreq)*1000000.0))/1000.0;
  }
#else
  static long long int timerStart;
  
  void timerReset() 
  {
    timeval tv;
    gettimeofday(&tv,0);
    
    timerStart = ((long long int)tv.tv_sec)*1000000LL + ((long long int)tv.tv_usec);
  }
  
  double timerGet()
  {
    timeval tv;
    gettimeofday(&tv,0);

    long long int timerNow = ((long long int)tv.tv_sec)*1000000LL + ((long long int)tv.tv_usec);
    
    return ((double)(timerNow-timerStart))/1000.0;
  }
#endif
