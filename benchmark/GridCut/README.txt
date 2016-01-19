This is a simple benchmark for measuring the speed of maxflow/mincut solvers.
The benchmark contains extensive dataset of maxflow instances and code for
measuring runtimes of two solvers: GridCut [1] and BK maxflow-v3.01 [2].
The dataset contains instances from University of Western Ontario [3],
Middlebury College [4] and Czech Technical University in Prague [5].
The instances are stored in binary format which allows faster reading and
easier transfer compared to DIMACS. See mfi.cpp and mfi.h for details.

To run the benchmark with GridCut:
1) download GridCut from http://gridcut.com
2) unzip GridCut_v1.zip to the "code/GridCut" subdirectory
3) type "make bench-GridCut"
4) run bench-GridCut

To run the benchmark with BK maxflow-v3.01:
1) download BK maxflow from http://vision.csd.uwo.ca/code/maxflow-v3.01.zip
2) unzip maxflow-v3.01.zip to the "code/BK301" subdirectory
3) type "make bench-BK301"
4) run bench-BK301

References:
[1] GridCut, http://gridcut.com
[2] BK maxflow-v3.01, http://vision.csd.uwo.ca/code/maxflow-v3.01.zip
[3] Max-flow problem instances in vision, http://vision.csd.uwo.ca/maxflow-data
[4] Middlebury MRF Benchmark, http://vision.middlebury.edu/MRF
[5] DCGI FEE CTU, http://dcgi.felk.cvut.cz
