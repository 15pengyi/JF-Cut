all: bench-GridCut bench-BK303

bench-GridCut: bench-GridCut.cpp dataset.h mfi.cpp mfi.h timer.cpp timer.h
	g++ -m64 -I./code/GridCut/include -DNDEBUG -O3 -march=native -mtune=generic -fpermissive -o bench-GridCut bench-GridCut.cpp mfi.cpp timer.cpp

bench-BK303: bench-BK303.cpp dataset.h mfi.cpp mfi.h timer.cpp timer.h
	g++ -m64 -I./code/BK303 -DNDEBUG -O3 -march=native -mtune=generic -o bench-BK303 bench-BK303.cpp mfi.cpp timer.cpp ./code/BK303/graph.cpp ./code/BK303/maxflow.cpp

clean:
	rm -f bench-GridCut bench-BK303

