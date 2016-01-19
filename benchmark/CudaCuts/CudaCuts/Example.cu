
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

#define CUT_EXIT(argc, argv) \
    if (!checkCmdLineFlag(argc, (const char**)argv, "noprompt")) { \
        printf("\nPress ENTER to exit...\n"); \
        fflush( stdout); \
        fflush( stderr); \
        getchar(); \
    } \
    exit(EXIT_SUCCESS);

#include "CudaCuts.cu"
#include "Example.h"

#include <string.h>

#include "cl/cl.h"

#include "QIO.h"
#include "QUtility.h"

using namespace std; 

int main(int argc,char** argv)
{
	load_files(argv[1]) ;

	int initCheck = cudaCutsInit(width, height ,num_Labels) ;
	
	printf("Compute Capability %d\n",initCheck);

	if( initCheck > 0 )
	{
		printf("The grid is initialized successfully\n");
	}
	else 
		if( initCheck == -1 )
		{
			printf("Error: Please check the device present on the system\n");
		}

	int dataCheck   =  cudaCutsSetupDataTerm( dataTerm );

	if( dataCheck == 0 )
	{
		printf("The dataterm is set properly\n");
		
	}
	else 
		if( dataCheck == -1 )
		{
			printf("Error: Please check the device present on the system\n");
		}

	int smoothCheck =  cudaCutsSetupSmoothTerm( smoothTerm );

	if( smoothCheck == 0 )
	{
		printf("The smoothnessterm is set properly\n");
	}
	else
		if( smoothCheck == -1 )
		{
			printf("Error: Please check the device present on the system\n");
		}

	int hcueCheck   =  cudaCutsSetupHCue( hCue );

	if( hcueCheck == 0 )
	{
		printf("The HCue is set properly\n");
	}
	else
		if( hcueCheck == -1 )
		{
			printf("Error: Please check the device present on the system\n");
		}

	int vcueCheck   =  cudaCutsSetupVCue( vCue );

	if( vcueCheck == 0 )
	{
		printf("The VCue is set properly\n");
	}
	else 
		if( vcueCheck == -1 )
		{
			printf("Error: Please check the device present on the system\n");
		}

	int graphCheck = cudaCutsSetupGraph();

	if( graphCheck == 0 )
	{
		printf("The graph is constructed successfully\n");
	}
	else 
		if( graphCheck == -1 )
		{
			printf("Error: Please check the device present on the system\n");
		}

	int optimizeCheck = -1; 
	if( initCheck == 1 )
	{
		//CudaCuts involving atomic operations are called
		//optimizeCheck = cudaCutsAtomicOptimize();
		//CudaCuts involving stochastic operations are called
		optimizeCheck = cudaCutsStochasticOptimize();
	}

	if( optimizeCheck == 0 )
	{
		printf("The algorithm successfully converged\n");
	}
	else 
		if( optimizeCheck == -1 )
		{
			printf("Error: Please check the device present on the system\n");
		}

	int resultCheck = cudaCutsGetResult( );

	if( resultCheck == 0 )
	{
		printf("The pixel labels are successfully stored\n");
	}
	else 
		if( resultCheck == -1 )
		{
			printf("Error: Please check the device present on the system\n");
		}
		
	int energy = cudaCutsGetEnergy(); 
    printf("TOTAL ENERGY: %d\n",energy);

	initFinalImage();
	
	cudaCutsFreeMem();
	
	exit(1);
	CUT_EXIT(argc,argv);
}

bool parseDataFile(const std::string& name, std::string& objectFileName, cl_uint4& volumeSize, cl_ulong& maxFLow)
{
    std::string dataFileContent, line;
    if (!QIO::getFileContent(name, dataFileContent)) return false;

    std::stringstream data(dataFileContent, std::stringstream::in);
    bool error = false;
    ::size_t position = std::string::npos;
    while (!data.eof())
    {
        getline(data, line);
        std::stringstream buffer(std::stringstream::in | std::stringstream::out);
        if ((position = line.find("ObjectFileName")) != std::string::npos)
        {
            if ((position = line.find(':')) == std::string::npos)
            {
                error = true;
                break;
            }
            objectFileName = line.substr(position + 1);
            QUtility::trim(objectFileName);
        }
        else if ((position = line.find("Resolution")) != std::string::npos)
        {
            if ((position = line.find(':')) == std::string::npos)
            {
                error = true;
                break;
            }
            buffer << line.substr(position + 1);
            unsigned int x = 0, y = 0, z = 0;
            buffer >> x >> y >> z;
            if (x <= 0 || y <= 0 || z <= 0)
            {
                error = true;
                break;
            }
            volumeSize.s[0] = x;
            volumeSize.s[1] = y;
            volumeSize.s[2] = z;
        }
        else if ((position = line.find("MaxFlow")) != std::string::npos)
        {
            if ((position = line.find(':')) == std::string::npos)
            {
                error = true;
                break;
            }
            buffer << line.substr(position + 1);
            int flow = 0;
            buffer >> flow;
            if (flow < 0)
            {
                error = true;
                break;
            }

            maxFLow = flow;
        }
        else
        {
            std::cerr << " > WARNING: skipping line \"" << line << "\"." << std::endl;
        }
    }

    if (error)
    {
        std::cerr << " > ERROR: parsing \"" << line << "\"." << std::endl;
        return false;
    }

    return true;
}

void load_files(char *filename)
{
    /**
	LoadDataFile(filename, width, height, num_Labels, dataTerm, smoothTerm, hCue, vCue);
    /*/
    LoadDataFileBenchmark(filename, width, height, num_Labels, dataTerm, smoothTerm, hCue, vCue);
    //*/
}

void initFinalImage()
{
	out_pixel_values=(int**)malloc(sizeof(int*)*height);

	for(int i = 0 ; i < height ; i++ )
	{
		out_pixel_values[i] = (int*)malloc(sizeof(int) * width ) ;
		for(int j = 0 ; j < width ; j++ ) {
			out_pixel_values[i][j]=0;
		}
	}

	writeImage() ;
}

void writeImage()
{
	for(int i = 0 ; i <  graph_size1 ; i++)
	{

		int row = i / width1, col = i % width1 ;

		if(row >= 0 && col >= 0 && row <= height -1 && col <= width - 1 )
			out_pixel_values[row][col]=pixelLabel[i]*255;
	}

	write_image();
}

void write_image()
{

	FILE* fp=fopen("result_sponge/flower_cuda_test.pgm","w");

	fprintf(fp,"%c",'P');
	fprintf(fp,"%c",'2');
	fprintf(fp,"%c",'\n');
	fprintf(fp,"%d %c %d %c ",width,' ',height,'\n');
	fprintf(fp,"%d %c",255,'\n');

	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			fprintf(fp,"%d\n",out_pixel_values[i][j]);
		}
	}
	fclose(fp);
}

void LoadDataFile(char *filename, int &width, int &height, int &nLabels,
		int *&dataCostArray,
		int *&smoothCostArray,
		int *&hCue,
		int *&vCue)
{
	printf("enterd\n");
	
	FILE *fp = fopen(filename,"r");
	
	fscanf(fp,"%d %d %d",&width,&height,&nLabels);
    
	int i, n, x, y;
	int gt;
	for(i = 0; i < width * height; i++)
		fscanf(fp,"%d",&gt);
    
	dataCostArray = new int[width * height * nLabels];
	for(int c=0; c < nLabels; c++) {
		n = c;
		for(i = 0; i < width * height; i++) {
			fscanf(fp,"%d",&dataCostArray[n]);
			n += nLabels;
		}
	}
    
	hCue = new int[width * height];
	vCue = new int[width * height];

	n = 0;
	for(y = 0; y < height; y++) {
		for(x = 0; x < width-1; x++) {
			fscanf(fp,"%d",&hCue[n++]);
		}
		hCue[n++] = 0;
	}

	n = 0;
	for(y = 0; y < height-1; y++) {
		for(x = 0; x < width; x++) {
			fscanf(fp,"%d",&vCue[n++]);
		}
	}
	for(x = 0; x < width; x++) {
		vCue[n++] = 0;
	}
    
	fclose(fp);
	smoothCostArray = new int[nLabels * nLabels];

	smoothCostArray[0] = 0 ;
	smoothCostArray[1] = 1 ;
	smoothCostArray[2] = 1 ;
	smoothCostArray[3] = 0 ;
}

void LoadDataFileBenchmark(char *filename, int &width, int &height, int &nLabels,
		int *&dataCostArray,
		int *&smoothCostArray,
		int *&hCue,
		int *&vCue)
{
    std::string original = "original/";
    std::string scaled = "scaled/";
    std::string scaled2 = "scaled-2/";
    std::string flower = "flower/normalized_flower.raw.dat";
    std::string person = "person/normalized_person.raw.dat";
    std::string sponge = "sponge/normalized_sponge.raw.dat";

    std::string path = "F:/88Datasets/Image Data/";
    std::string type = scaled2;
    std::string instance = flower;
    std::string dataFileName(path + type + instance);
    int position = dataFileName.find_last_of("\\");
    if (position == std::string::npos) position = dataFileName.find_last_of("/");
    if (position == std::string::npos) position = dataFileName.size() - 1;
    std::string dataFilePath = dataFileName.substr(0, position + 1);

    std::string objectFileName;
    cl_uint4 volumeSize;
    cl_ulong maxFlow;
    parseDataFile(dataFileName, objectFileName, volumeSize, maxFlow);

    std::string nodeFileExtension = ".node";
    cl_uint4 clTileSize2D = { 16, 16,  1,  1 };
    cl_uint4 nodeSize =
    {
        QUtility::ceil(clTileSize2D.s[0], volumeSize.s[0]),
        QUtility::ceil(clTileSize2D.s[1], volumeSize.s[1]),
        1,
        1
    };

    ::size_t size = nodeSize.s[0] * nodeSize.s[1];
    std::vector<cl_node_2d> clNode(size);
    if (!QIO::getFileData(dataFilePath + objectFileName + nodeFileExtension, clNode.data(), clNode.size() * sizeof(cl_node_2d))) return;
    
    printf("enterd\n");
	
    width = volumeSize.s[0];
    height = volumeSize.s[1];
    nLabels = 2;
	
	dataCostArray = new int[width * height * nLabels];
	hCue = new int[width * height];
	vCue = new int[width * height];
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            int index = x + width * y;
            cl_node_2d* node = clNode.data() + x + nodeSize.s[0] * y;
            if (node->excessFlow > 0)
            {
                dataCostArray[index * nLabels + 0] = node->excessFlow;
                dataCostArray[index * nLabels + 1] = 0;
            }
            else
            {
                dataCostArray[index * nLabels + 0] = 0;
                dataCostArray[index * nLabels + 1] = -node->excessFlow;
            }

            hCue[index] = node->capacity[0];
            vCue[index] = node->capacity[1];
        };

	smoothCostArray = new int[nLabels * nLabels];

	smoothCostArray[0] = 0 ;
	smoothCostArray[1] = 1 ;
	smoothCostArray[2] = 1 ;
	smoothCostArray[3] = 0 ;
}