/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QGCWidget.cpp
 * @brief   QGCWidget class declaration.
 * 
 * This file declares ...
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2013/01/09
 */

#include <climits>
#include <cmath>
#include <iomanip> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <stdint.h>

#include <gl/glew.h>

#include <QKeyEvent>
#include <QTime>

#include "../3rdParty/cl/cl_stacktrace.hpp"
#include "../3rdParty/stacktrace/call_stack_msvc.hpp"
#include "../3rdParty/stacktrace/call_stack_gcc.hpp"
#include "../3rdParty/bench/mfi.h"
#include "../utilities/QIO.h"
#include "../utilities/QUtilityUI.h"
#include "../utilities/QUtilityMath.h"
#include "../utilities/QUtilityCL.h"
#include "../utilities/QUtilityGL.h"
#include "../utilities/QUtilityData.h"
#include "../utilities/QUtilityConsole.h"
#include "../infrastructures/QHoverPoints.h"
#include "../infrastructures/QError.h"
#include "QGCSetting.h"
#include "QGCPanel.h"
#include "QGCWidget.h"

typedef CL_API_ENTRY cl_int (CL_API_CALL *clGetGLContextInfoKHR_fn)(
    const cl_context_properties *properties,
    cl_gl_context_info param_name,
    size_t param_value_size,
    void *param_value,
    size_t *param_value_size_ret);

/**
 * Rename references to this dynamically linked function to avoid
 * collision with static link version
 */
#define clGetGLContextInfoKHR clGetGLContextInfoKHR_proc
static clGetGLContextInfoKHR_fn clGetGLContextInfoKHR;

QGCWidget::QGCWidget(QWidget *parent)
    : QGLWidget(parent),
    corporation(), dataFileName(), dataFilePath(), objectFileName(), gradientFileName(), // Data file
    endian(ENDIAN_LITTLE), volumeSize1D(0), volumeSize(), boxSize(), thickness(), format(FORMAT_UNKNOWN),
    volumeMin(0.0f), volumeMax(0.0f), // Volumetric Data
    gradientMin(0.0f), gradientMax(0.0f), curvatureMin(0.0f), curvatureMax(0.0f), // Feature Data
    simplified(false), // Large Data
    mappingComputed(false), bufferMapping(QSetting::sizeMapping), // Mapping
    histogramComputed(false), bufferHistogram(QSetting::sizeHistogram),
        histogramMin(0.0f), histogramMax(0.0f), // Histogram Data
    initialized(false), error(false), settings(), // Configuration
    mouseMode(MOUSE_UNKNOW), mousePosition(0, 0), // OpenGL Context
    sizLocal(), sizGlobal(),
        progClustering(), progModeling(), progCounting(), progBFS(), progPushRelabel(), progPushRelabelFast(), progJumpFlooding(), progGlobalRelabel(),
            progCut(), progTag(), progRenderNormal(), progRenderPreInt(), progRenderFeature(), progUtility(), progReduce(), // CL Programs
        kerKMeans(), kerCutHistogram(), kerCutDistribution(), // Clustering Kernels
        kerCapacityBK(), kerCapacityLazy(), kerExcessFlowBK(), kerExcessFlowLazy(), // Modeling Kernels
        kerScatterNode(), kerCountNode(), kerScatterCut(), kerCountCut(), // Counting Kernels
        kerPushRelabel(), kerFastRelabel(), kerFastPushX(), kerFastPushY(), kerFastPushZ(), // Push-relabel Kernels
        kerBFSHistogram(), kerBFSJumpFlooding(), kerBFSMapping(), // BFS Kernels
        kerInitGlobalRelabel(), kerGlobalRelabel(), // GLobal Relabel Kernels
        kerInitCut(), kerComputeCut(), kerInitTag(), kerComputeTag(), // Labeling Kernels
        kerReduceFlow(), kerReduceHistogram(), // Reduce Kernels
        kerRenderNormal(), kerRenderPreInt(), kerRenderFeature(), // Rendering Kernels
        kerClear(), kerIntegration(), // Utility Kernels
        devCutHistogram(), devBFSHistogram(), devDistribution(), devCentroid(), devSum(), devCount(), // Modeling Memories
        devActiveTile(), devActiveTileOdd(), devTileList(), // Counting Memories
        devExcessFlow(), devHeight(), devCapacity1(), devCapacity2(), // Graph Memories
        devMask(), devBuffer(), glBuffer(0), // Rendering Memories
        devDone(), devCut(), devFlow(), devHistogram(), devDepth(), // Other Memories
        imgCut2D(), imgCut3D(), imgVolume2D(), imgVolume3D(), imgFeature2D(), imgFeature3D(), imgCut(), imgVolume(), imgFeature(),
            imgTF(), imgIntegration(),
            imgOrigin(), imgRegion(),
        clDevice(), clContext(), clQueue(), // OpenCL Context
    energyData(0), energySmooth(0), groupSize1D(0), clGroupSize(0), clLocalSize(0), flowBlockSize(0), flowBlocks(0), histBlockSize(0), histBlocks(0), groupSize(), blockSize(), clScan(NULL),
        hostMinMask(QGCSetting::sizeTexture), hostMaxMask(QGCSetting::sizeTexture),
        hostCutHistogram(QGCSetting::sizeCutHistogram), hostDistHistogram(QGCSetting::sizeDistHistogram),
        hostCutDistribution(QGCSetting::sizeCutHistogram),
        hostFlow(0), hostHistogram(0), hostDepth(0), hostTileList(0), hostActiveTile(0), hostTileOffset(0),
        hostMask(0), hostExcessFlow(0), hostHeight(0), hostCapacity1(0), hostCapacity2(0), hostCut(0),
        hostCentroid(0), hostSum(0), hostCount(0) // Graph Cut
{
    Q_INVOKABLE
    setMouseTracking(true);
    setAutoBufferSwap(false);
    setAutoFillBackground(false);
}

QGCWidget::~QGCWidget()
{
    this->destroy();
}

void QGCWidget::destroy()
{
    if (clScan) delete clScan;
}

// Step 1 - init connections
void QGCWidget::initConnections(QGCPanel* panel)
{
    this->panel = panel;

    const Ui::QGCPanel* ui = panel->getUI();

    // 1. Graph Cut
    //  -->
    connect(ui->radioButtonModeNormal, SIGNAL(clicked()), this, SLOT(slotToolkitTypeChanged()));
    connect(ui->radioButtonModeBrush, SIGNAL(clicked()), this, SLOT(slotToolkitTypeChanged()));
    connect(ui->radioButtonModeEraser, SIGNAL(clicked()), this, SLOT(slotToolkitTypeChanged()));

    connect(ui->pushButtonCut, SIGNAL(clicked()), this, SLOT(slotCutClicked()));
    connect(ui->pushButtonCutModeling, SIGNAL(clicked()), this, SLOT(slotCutClicked()));
    connect(ui->pushButtonCutAlgorithm, SIGNAL(clicked()), this, SLOT(slotCutClicked()));
    connect(ui->pushButtonClear, SIGNAL(clicked()), this, SLOT(slotClearClicked()));

    connect(ui->pushButtonLoadGraph, SIGNAL(clicked()), this, SLOT(slotLoadGraphClicked()));
    connect(ui->pushButtonSaveGraph, SIGNAL(clicked()), this, SLOT(slotSaveGraphClicked()));
    connect(ui->pushButtonLoadGradient, SIGNAL(clicked()), this, SLOT(slotLoadGradientClicked()));
    connect(ui->pushButtonSaveGradient, SIGNAL(clicked()), this, SLOT(slotSaveGradientClicked()));
    connect(ui->pushButtonLoadFeature, SIGNAL(clicked()), this, SLOT(slotLoadFeatureClicked()));
    connect(ui->pushButtonSaveFeature, SIGNAL(clicked()), this, SLOT(slotSaveFeatureClicked()));
    connect(ui->pushButtonLoadCut, SIGNAL(clicked()), this, SLOT(slotLoadCutClicked()));
    connect(ui->pushButtonSaveCut, SIGNAL(clicked()), this, SLOT(slotSaveCutClicked()));
    connect(ui->pushButtonExport, SIGNAL(clicked()), this, SLOT(slotExportClicked()));

    // 2. Rendering
    //  -->
    connect(ui->radioButtonInterpolationLinear,  SIGNAL(clicked()), this, SLOT(slotUpdateConnectionType()));
    connect(ui->radioButtonInterpolationCubic,  SIGNAL(clicked()), this, SLOT(slotUpdateConnectionType()));
    connect(ui->widgetEditor, SIGNAL(signalControlPointsChanged()), this, SLOT(slotUpdateTransferFunction()));
    connect(ui->pushButtonLoadTransferFunction, SIGNAL(clicked()), this, SLOT(slotLoadTransferFunctionClicked()));
    connect(ui->pushButtonSaveTransferFunction,  SIGNAL(clicked()), this, SLOT(slotSaveTransferFunctionClicked()));

    //  <--
    connect(this, SIGNAL(signalPartitionInitialized(::size_t, float*)), ui->widgetEditor, SLOT(slotSetPartition(::size_t, float*)));
    connect(this, SIGNAL(signalHistogramInitialized(::size_t, float*)), ui->widgetEditor, SLOT(slotInsertHistogram(::size_t, float*)));
    connect(this, SIGNAL(signalHistogramUpdated(int, float*)), ui->widgetEditor, SLOT(slotUpdateHistogram(int, float*)));
}

// Step 2 - init data
void QGCWidget::initCorporation(const std::string &corporation)
{
    this->corporation = corporation;
}

void QGCWidget::initData(const std::string &name)
{
    try
    {
        dataFileName = name;
        int position = dataFileName.find_last_of("\\");
        if (position == std::string::npos) position = dataFileName.find_last_of("/");
        if (position == std::string::npos) position = dataFileName.size() - 1;
        dataFilePath = dataFileName.substr(0, position + 1);

        parseDataFile(dataFileName);
        
        if (!simplified)
        {
            // load original data
            cl_uint voxelSize = getVoxelSize(format);
            std::vector<unsigned char> bufferSource(volumeSize1D * voxelSize);
            if (!QIO::getFileData(dataFilePath + objectFileName, bufferSource.data(), voxelSize * volumeSize1D))
                throw QError(2, Q_RUNTIME_ERROR, "opening data file failed.");
        
            int power = (int)(std::logf(volumeSize1D * sizeof(cl_float) / settings.bufferSizeVolume) / 3) + 1;
            int scale = 1 << power;
            cl_uint4 volumeScale = { scale, scale, scale, 1 };
            cl_uint4 volumeSizeS =
            {
                (volumeSize.s[0] - 1) / volumeScale.s[0] + 1,
                (volumeSize.s[1] - 1) / volumeScale.s[1] + 1,
                (volumeSize.s[2] - 1) / volumeScale.s[2] + 1,
                1
            };
        
            cl_uint volumeSize1DS = volumeSizeS.s[0] * volumeSizeS.s[1] * volumeSizeS.s[2];
            std::vector<unsigned char> bufferDestination(volumeSize1DS * sizeof(float));

            QTime tSimplify = QDateTime::currentDateTime().time();
            volumeMin = std::numeric_limits<float>::max();
            volumeMax = std::numeric_limits<float>::lowest();
            QUtilityData::simplify(bufferSource.data(), bufferDestination.data(), volumeSize, format, endian, volumeScale, volumeMax, volumeMin);
            if (settings.enableLoggingTimeCost) QUtilityConsole::printTimeCost(tSimplify.msecsTo(QDateTime::currentDateTime().time()), "compute simplified model - simplify()");
        
            format = FORMAT_FLOAT;
            endian = ENDIAN_LITTLE;

            volumeSize1D = volumeSize1DS;
            volumeSize = volumeSizeS;

            thickness.s[0] *= volumeScale.s[0];
            thickness.s[1] *= volumeScale.s[1];
            thickness.s[2] *= volumeScale.s[2];

            simplified = true;

            objectFileName = "simplified_" + objectFileName;
            if (!QIO::saveFileData(dataFilePath + objectFileName, bufferDestination.data(), sizeof(float) * volumeSize1D))
                throw QError(2, Q_RUNTIME_ERROR, "saving simplified data file failed.");

            dataFileName = dataFilePath + objectFileName + QGCSetting::extDat;
            saveDataFile(dataFileName);
        }

        if (!histogramComputed || !mappingComputed)
        {
            // load volume data
            std::vector<float> bufferVolume(volumeSize1D);
            cl_uint voxelSize = getVoxelSize(format);
            if (!QIO::getFileData(dataFilePath + objectFileName, bufferVolume.data(), voxelSize * volumeSize1D))
                throw QError(2, Q_RUNTIME_ERROR, "opening raw file failed.");

            // compute histogram
            QTime tComputeHistogram = QDateTime::currentDateTime().time();
            QUtilityData::preprocess(bufferVolume.data(), volumeSize1D, format, endian, QSetting::sizeHistogram,
                bufferHistogram.data(), volumeMin, volumeMax, histogramMin, histogramMax);
            if (settings.enableLoggingTimeCost) QUtilityConsole::printTimeCost(tComputeHistogram.msecsTo(QDateTime::currentDateTime().time()), "compute histogram - preprocess()");

            format = FORMAT_FLOAT;
            endian = ENDIAN_LITTLE;

            histogramComputed = true;
        
            // compute mapping
            QTime tSort = QDateTime::currentDateTime().time();
            std::vector<float> volumeDataSorted((float*)bufferVolume.data(), (float*)bufferVolume.data() + volumeSize1D);
            std::sort(volumeDataSorted.begin(), volumeDataSorted.end());
            if (settings.enableLoggingTimeCost) QUtilityConsole::printTimeCost(tSort.msecsTo(QDateTime::currentDateTime().time()), "compute mapping - sort()");

            QTime tUnique = QDateTime::currentDateTime().time();
            int size = std::distance(volumeDataSorted.begin(), std::unique(volumeDataSorted.begin(), volumeDataSorted.end()));
            volumeDataSorted.resize(size);
            if (settings.enableLoggingTimeCost) QUtilityConsole::printTimeCost(tUnique.msecsTo(QDateTime::currentDateTime().time()), "compute mapping - unique()");

            bufferMapping[0] = 0.0f;
            bufferMapping[QSetting::sizeMapping - 1] = 1.0f;
            for (int i = 1; i < QSetting::sizeMapping - 1; i++)
            {
                cl_long index = (cl_long)size * i / (QSetting::sizeMapping - 1);
                bufferMapping[i] = volumeDataSorted[index];
            }

            mappingComputed = true;
        
            objectFileName = "normalized_" + objectFileName;
            QIO::saveFileData(dataFilePath + objectFileName, bufferVolume.data(), bufferVolume.size() * sizeof(float));

            dataFileName = dataFilePath + objectFileName + QGCSetting::extDat;
            saveDataFile(dataFileName);
        }

        emit signalPartitionInitialized(QSetting::sizeMapping, bufferMapping.data());
        emit signalHistogramInitialized(QSetting::sizeHistogram, bufferHistogram.data());
    }
    catch (QError& e)
    {
        switch (e.level())
        {
        case 0:
            break;
        case 1:
            std::cerr << " > LOG: " << std::endl << e.what();
            break;
        default:
            std::cerr << " > ERROR: " << std::endl << e.what();
            error = true;
            break;
        }
    }
}

void QGCWidget::parseDataFile(const std::string &name)
{
    std::string dataFileContent, line;
    if (!QIO::getFileContent(name, dataFileContent))
        throw QError(2, Q_RUNTIME_ERROR, "opening data file failed.");

    std::stringstream data(dataFileContent, std::stringstream::in);
    bool error = false;
    ::size_t position = std::string::npos;
    while (!data.eof())
    {
        getline(data, line);
        std::stringstream buffer(std::stringstream::in | std::stringstream::out);
        if ((position = line.find("Object File Name")) != std::string::npos)
        {
            if ((position = line.find(':')) == std::string::npos)
            {
                error = true;
                break;
            }
            objectFileName = line.substr(position + 1);
            QUtilityMath::trim(objectFileName);
            if (objectFileName.empty())
            {
                error = true;
                break;
            }
        }
        else if ((position = line.find("Gradient File Name")) != std::string::npos)
        {
            if ((position = line.find(':')) == std::string::npos)
            {
                error = true;
                break;
            }
            gradientFileName = line.substr(position + 1);
            QUtilityMath::trim(gradientFileName);
            if (gradientFileName.empty())
            {
                error = true;
                break;
            }
        }
        else if ((position = line.find("Curvature File Name")) != std::string::npos)
        {
            if ((position = line.find(':')) == std::string::npos)
            {
                error = true;
                break;
            }
            curvatureFileName = line.substr(position + 1);
            QUtilityMath::trim(curvatureFileName);
            if (curvatureFileName.empty())
            {
                error = true;
                break;
            }
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
            if (x <= 1 || y <= 1 || z <= 0)
            {
                error = true;
                break;
            }
            volumeSize.s[0] = x;
            volumeSize.s[1] = y;
            volumeSize.s[2] = z;
            volumeSize1D = volumeSize.s[0] * volumeSize.s[1] * volumeSize.s[2];

            simplified = volumeSize1D * sizeof(cl_float) <= settings.bufferSizeVolume;
        }
        else if ((position = line.find("Slice Thickness")) != std::string::npos)
        {
            if ((position = line.find(':')) == std::string::npos)
            {
                error = true;
                break;
            }
            buffer << line.substr(position + 1);
            float x = 0.0, y = 0.0, z = 0.0;
            buffer >> x >> y >> z;
            if (x <= 0.0 || y <= 0.0 || z <= 0.0)
            {
                error = true;
                break;
            }
            thickness.s[0] = x;
            thickness.s[1] = y;
            thickness.s[2] = z;
        }
        else if ((position = line.find("Format")) != std::string::npos)
        {
            if ((position = line.find(':')) == std::string::npos)
            {
                error = true;
                break;
            }

            if ((position = line.find("UCHAR")) != std::string::npos)
            {
                format = FORMAT_UCHAR;
            }
            else if ((position = line.find("CHAR")) != std::string::npos)
            {
                format = FORMAT_CHAR;
            }
            else if ((position = line.find("USHORT")) != std::string::npos)
            {
                format = FORMAT_USHORT;
            }
            else if ((position = line.find("SHORT")) != std::string::npos)
            {
                format = FORMAT_SHORT;
            }
            else if ((position = line.find("UINT")) != std::string::npos)
            {
                format = FORMAT_UINT;
            }
            else if ((position = line.find("INT")) != std::string::npos)
            {
                format = FORMAT_INT;
            }
            else if ((position = line.find("FLOAT")) != std::string::npos)
            {
                format = FORMAT_FLOAT;
            }
            else
            {
                std::cerr << " > ERROR: cannot process data other than of UCHAR and USHORT format." << std::endl;
                error = true;
            }
        }
        else if ((position = line.find("Window")) != std::string::npos)
        {
            if ((position = line.find(':')) == std::string::npos)
            {
                error = true;
                break;
            }
            buffer << line.substr(position + 1);
            int windowWidth, windowLevel;
            buffer >> windowWidth >> windowLevel;

            const Ui::QGCPanel* ui = panel->getUI();
            if (windowWidth < ui->verticalSliderWindowWidth->minimum() || windowWidth > ui->verticalSliderWindowWidth->maximum()
             || windowLevel < ui->verticalSliderWindowLevel->minimum() || windowLevel > ui->verticalSliderWindowLevel->maximum())
            {
                error = true;
                break;
            }

            ui->verticalSliderWindowWidth->setValue(windowWidth);
            ui->verticalSliderWindowLevel->setValue(windowLevel);
        }
        else if ((position = line.find("Endian")) != std::string::npos)
        {
            if ((position = line.find(':')) == std::string::npos)
            {
                error = true;
                break;
            }
            if ((position = line.find("BIG-ENDIAN")) != std::string::npos)
            {
                endian = ENDIAN_BIG;
            }
            else if ((position = line.find("LITTLE-ENDIAN")) != std::string::npos)
            {
                endian = ENDIAN_LITTLE;
            }
            else
            {
                std::cerr << " > ERROR: cannot process endian other than of BIG-ENDIAN and LITTLE-ENDIAN format." << std::endl;
                error = true;
            }
        }
        else if ((position = line.find("Intensity Extremums")) != std::string::npos)
        {
            if ((position = line.find(':')) == std::string::npos)
            {
                error = true;
                break;
            }
            buffer << line.substr(position + 1);
            buffer >> volumeMin >> volumeMax;
        }
        else if ((position = line.find("Gradient Extremums")) != std::string::npos)
        {
            if ((position = line.find(':')) == std::string::npos)
            {
                error = true;
                break;
            }
            buffer << line.substr(position + 1);
            buffer >> gradientMin >> gradientMax;
        }
        else if ((position = line.find("Curvature Extremums")) != std::string::npos)
        {
            if ((position = line.find(':')) == std::string::npos)
            {
                error = true;
                break;
            }
            buffer << line.substr(position + 1);
            buffer >> curvatureMin >> curvatureMax;
        }
        else if ((position = line.find("Mapping")) != std::string::npos)
        {
            if ((position = line.find(':')) == std::string::npos)
            {
                error = true;
                break;
            }
            int size = 0;
            buffer << line.substr(position + 1);
            buffer >> size;
            if (size != QSetting::sizeMapping)
            {
                error = true;
                break;
            }

            bufferMapping[0] = 0.0f;
            bufferMapping[QSetting::sizeMapping - 1] = 1.0f;
            for (int i = 1; i < QSetting::sizeMapping - 1; i++)
            {
                float point = 0.0f;
                buffer >> point;
                if (point < bufferMapping[i - 1] || point > 1.0f)
                {
                    error = true;
                    break;
                }
                bufferMapping[i] = point;
            }
            if (error) break;

            mappingComputed = true;
        }
        else if ((position = line.find("Histogram Extremums")) != std::string::npos)
        {
            if ((position = line.find(':')) == std::string::npos)
            {
                error = true;
                break;
            }
            buffer << line.substr(position + 1);
            buffer >> histogramMin >> histogramMax;
        }
        else if ((position = line.find("Histogram")) != std::string::npos)
        {
            if ((position = line.find(':')) == std::string::npos)
            {
                error = true;
                break;
            }
            int size = 0;
            buffer << line.substr(position + 1);
            buffer >> size;
            if (size != QSetting::sizeHistogram)
            {
                error = true;
                break;
            }
            
            for (auto i = bufferHistogram.begin(); i != bufferHistogram.end(); i++)
                buffer >> *i;

            histogramComputed = true;
        }
        else
        {
            std::cerr << " > LOG: skipping line \"" << line << "\"." << std::endl;
        }
    }

    if (error) throw QError(2, Q_RUNTIME_ERROR, "parsing data file failed.");

    float actualSize[3];
    float maxActualSize = 0.0;
    for (int i = 0; i < 3; i++)
    {
        actualSize[i] = volumeSize.s[i] * thickness.s[i];
        if (actualSize[i] > maxActualSize) maxActualSize = actualSize[i];
    }

    for (int i = 0; i < 3; i++)
    {
        boxSize.s[i]= actualSize[i] / maxActualSize;
    }
}

void QGCWidget::saveDataFile(const std::string &name)
{
    std::ofstream file(name);
    if (!file) throw QError(1, Q_LOGIC_ERROR, "opening data file failed.");
    
    file << "Object File Name: " << objectFileName << std::endl;
    file << "Resolution: " << volumeSize.s[0] << " " << volumeSize.s[1] << " " << volumeSize.s[2] << std::endl;
    file << "Slice Thickness: " << thickness.s[0] << " " << thickness.s[1] << " " << thickness.s[2] << std::endl;

    file << "Format: ";
    std::string strFormat;
    switch (format)
    {
    case FORMAT_CHAR: 
        file << "CHAR";
        break;
    case FORMAT_UCHAR: 
        file << "UCHAR";
        break;
    case FORMAT_SHORT: 
        file << "SHORT";
        break;
    case FORMAT_USHORT: 
        file << "USHORT";
        break;
    case FORMAT_INT: 
        file << "INT";
        break;
    case FORMAT_UINT: 
        file << "UINT";
        break;
    case FORMAT_FLOAT: 
        file << "FLOAT";
        break;
    default:
        break;
    }
    file << std::endl;

    file << "Endian: ";
    switch (endian)
    {
    case ENDIAN_LITTLE: 
        file << "LITTLE-ENDIAN";
        break;
    case ENDIAN_BIG: 
        file << "BIG-ENDIAN";
        break;
    default:
        break;
    }
    file << std::endl;

    file << "Intensity Extremums: " << volumeMin << " " << volumeMax << std::endl;
    file << "Gradient Extremums: " << gradientMin << " " << gradientMax << std::endl;
    file << "Curvature Extremums: " << curvatureMin << " " << curvatureMax << std::endl;

    if(histogramComputed)
    {
        file << "Histogram Extremums: " << histogramMin << " " << histogramMax << std::endl;
        file << "Histogram: " << QSetting::sizeHistogram;

        for (auto i = bufferHistogram.begin(); i != bufferHistogram.end(); i++)
            file << " " << *i;
        
        file << std::endl;
    }

    if (mappingComputed)
    {
        file << "Mapping: " << QSetting::sizeMapping;
        for (int i = 1; i < QSetting::sizeMapping - 1; i++)
            file << " " << bufferMapping[i];
        file << std::endl;
    }

    if (!gradientFileName.empty())
    {
        file << "Gradient File Name: " << gradientFileName << std::endl;
    }

    if (!curvatureFileName.empty())
    {
        file << "Curvature File Name: " << curvatureFileName << std::endl;
    }

    file.close();
}

// Step 3 - init context
void QGCWidget::initContext()
{
    try
    {
        if (error |= !QUtilityGL::checkSupport()) return;

        initOpenCL();
        initConfigurations();
        initPrograms();

        this->initialized = true;

        initArguments();
    }
    catch (QError& e)
    {
        switch (e.level())
        {
        case 0:
            break;
        case 1:
            std::cerr << " > LOG: " << std::endl << e.what();
            break;
        default:
            std::cerr << " > ERROR: " << std::endl << e.what();
            error = true;
            break;
        }
    }
    catch (cl::Error& e)
    {
        std::cerr << " > CALL STACK: " << std::endl << e.what();
        error = true;
    }
    catch (clogs::InternalError &e)
    {
        std::cerr << " > CLOGS: " << e.what() << std::endl;
        error = true;
    }
}

void QGCWidget::initOpenCL()
{
    // Platform info
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    if (platforms.empty())
        throw QError(2, Q_RUNTIME_ERROR, "platform not available.");
    
    cl_bool openclSupported = 0, openglSupported = 0, imageSupport = 0, deviceSupported = 0;
    std::vector<cl_context_properties> clProperties(0);
    for(auto i = platforms.begin(); i != platforms.end(); i++)
    {
        clGetGLContextInfoKHR = (clGetGLContextInfoKHR_fn) clGetExtensionFunctionAddressForPlatform((*i)(), "clGetGLContextInfoKHR");
        if (!clGetGLContextInfoKHR) continue;

        std::string platformName = i->getInfo<CL_PLATFORM_NAME>();
        openclSupported = platformName.find(corporation) != std::string::npos;
        if(!openclSupported) continue;

        std::string platformVersion = i->getInfo<CL_PLATFORM_VERSION>();
        openclSupported = platformVersion.find("OpenCL 1.") != std::string::npos || platformVersion.find("OpenCL 2.") != std::string::npos;
        if(!openclSupported) continue;
        
        // Device info
        std::vector<cl::Device> devices;
        i->getDevices(CL_DEVICE_TYPE_GPU, &devices);
        
        for (auto j = devices.begin(); j != devices.end(); j++)
        {
            imageSupport = j->getInfo<CL_DEVICE_IMAGE_SUPPORT>();
            if (!imageSupport) continue;

            std::string deviceExtension = j->getInfo<CL_DEVICE_EXTENSIONS>();
            openglSupported = deviceExtension.find(GL_SHARING_EXTENSION) != std::string::npos;
            if (!openglSupported) continue;
            
            // Define OS-specific context properties and create the OpenCL context
            std::vector<cl_context_properties> properties(0);
            #ifdef __APPLE__
                CGLContextObj kCGLContext = CGLGetCurrentContext();
                CGLShareGroupObj kCGLShareGroup = CGLGetShareGroup(kCGLContext);
                properties.push_back(CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE);
                properties.push_back((cl_context_properties)kCGLShareGroup);
                properties.push_back(0);
            #else
                #ifdef UNIX
                    properties.push_back(CL_GL_CONTEXT_KHR);
                    properties.push_back((cl_context_properties)glXGetCurrentContext());
                    properties.push_back(CL_GLX_DISPLAY_KHR);
                    properties.push_back((cl_context_properties)glXGetCurrentDisplay());
                    properties.push_back(CL_CONTEXT_PLATFORM);
                    properties.push_back((cl_context_properties)(*i)());
                    properties.push_back(0);
                #else // Win32
                    properties.push_back(CL_GL_CONTEXT_KHR);
                    properties.push_back((cl_context_properties)wglGetCurrentContext());
                    properties.push_back(CL_WGL_HDC_KHR);
                    properties.push_back((cl_context_properties)wglGetCurrentDC());
                    properties.push_back(CL_CONTEXT_PLATFORM);
                    properties.push_back((cl_context_properties)(*i)());
                    properties.push_back(0);
                #endif
            #endif

            cl_device_id device(0);
            cl_int status = clGetGLContextInfoKHR(properties.data(), CL_CURRENT_DEVICE_FOR_GL_CONTEXT_KHR, sizeof(cl_device_id),  &device, NULL);
            deviceSupported = status == CL_SUCCESS;
            if (!deviceSupported) continue;
            
            clProperties = properties;
            clDevice = cl::Device(device);
            break;
        }

        break;
    }
    if (!openclSupported || !openglSupported || !imageSupport || !deviceSupported)
        throw QError(2, Q_RUNTIME_ERROR, "OpenCL, OpenGL, Image, or Device not supported.");

    clContext = cl::Context(clDevice, clProperties.data());
    
    clQueue = cl::CommandQueue(clContext, clDevice, CL_QUEUE_PROFILING_ENABLE);

    clScan = new clogs::Scan(clContext, clDevice, clogs::Type(clogs::TYPE_INT));

    std::cout << " > INFO: creating a context sharing with OpenGL." << std::endl;
}

void QGCWidget::initConfigurations()
{
    // Brushing
    const Ui::QGCPanel* ui = panel->getUI();
    glm::uvec2 viewSize(ui->spinBoxViewSizeX->value(), ui->spinBoxViewSizeY->value());
    int size = viewSize.x * viewSize.y * 2;
    hostMask.resize(size);

    // Graph Cut
    if (volumeSize.s[2] == 1)
    {
        blockSize = QGCSetting::cl_block_2d;
        ui->spinBoxTile2DX->setValue(blockSize.s[0]);
        ui->spinBoxTile2DY->setValue(blockSize.s[1]);
    }
    else
    {
        blockSize = QGCSetting::cl_block_3d;
        ui->spinBoxTile3DX->setValue(blockSize.s[0]);
        ui->spinBoxTile3DY->setValue(blockSize.s[1]);
        ui->spinBoxTile3DZ->setValue(blockSize.s[2]);
    }

    clLocalSize = QGCSetting::cl_local_size;
    clGroupSize = corporation.find("NVIDIA") == std::string::npos ? QGCSetting::cl_group_size_a : QGCSetting::cl_group_size_n;
    ui->spinBoxMaxGroup->setValue(clGroupSize);

    groupSize.s[0] = (volumeSize.s[0] - 1) / blockSize.s[0] + 1;
    groupSize.s[1] = (volumeSize.s[1] - 1) / blockSize.s[1] + 1;
    groupSize.s[2] = (volumeSize.s[2] - 1) / blockSize.s[2] + 1;
    groupSize.s[3] = 1;
    groupSize1D = groupSize.s[0] * groupSize.s[1] * groupSize.s[2];

    sizLocal  = cl::NDRange(blockSize.s[0], blockSize.s[1] * blockSize.s[2], 1);
    sizGlobal = cl::NDRange(blockSize.s[0], blockSize.s[1] * blockSize.s[2], groupSize1D);

    ::size_t maxBlocks = 512;
    flowBlockSize = QUtilityCL::ceil(volumeSize1D, clGroupSize * maxBlocks) / maxBlocks;
    flowBlocks = (volumeSize1D + flowBlockSize - 1) / flowBlockSize;
    hostFlow.resize(flowBlocks);

    histBlockSize = QUtilityCL::ceil(groupSize1D, clGroupSize * maxBlocks) / maxBlocks;
    histBlocks = (groupSize1D + histBlockSize - 1) / histBlockSize;
    hostHistogram.resize(histBlocks);

    hostTileList.resize(groupSize1D);
    hostActiveTile.resize(groupSize1D + 1);
    hostDepth.resize(groupSize1D + 1);

    hostCut.resize(volumeSize1D);
    hostExcessFlow.resize(volumeSize1D * sizeof(cl_int));
    hostHeight.resize(volumeSize1D * sizeof(cl_int));
    if (volumeSize.s[2] == 1)
    {
        hostCapacity1.resize(volumeSize1D * sizeof(cl_ushort2));
        hostCapacity2.resize(volumeSize1D * sizeof(cl_ushort2));
    }
    else
    {
        hostCapacity1.resize(volumeSize1D * sizeof(cl_uchar4));
        hostCapacity2.resize(volumeSize1D * sizeof(cl_uchar4));
    }

    imgOrigin[2] = imgOrigin[1] = imgOrigin[0] = 0;
    imgRegion[0] = volumeSize.s[0];
    imgRegion[1] = volumeSize.s[1];
    imgRegion[2] = volumeSize.s[2];

    cl_uint k = ui->spinBoxK->maximum();
    hostCentroid.resize(2 * k);
    hostSum.resize(groupSize1D * k);
    hostCount.resize(groupSize1D * k);
}

void QGCWidget::initClustering(const std::string& options, const std::string& headers)
{
    const Ui::QGCPanel* ui = panel->getUI();
    cl_uint k = ui->spinBoxK->maximum();

    if (volumeSize.s[2] == 1)
    {
        imgVolume2D = cl::Image2D(clContext, CL_MEM_READ_ONLY, cl::ImageFormat(CL_INTENSITY, CL_FLOAT), volumeSize.s[0], volumeSize.s[1]);
        imgVolume = imgVolume2D();
        imgCut2D = cl::Image2D(clContext, CL_MEM_READ_ONLY, cl::ImageFormat(CL_RGBA, CL_SNORM_INT8), volumeSize.s[0], volumeSize.s[1]);
        imgCut = imgCut2D();
        imgFeature2D = cl::Image2D(clContext, CL_MEM_READ_ONLY, cl::ImageFormat(CL_RGBA, CL_UNORM_INT8), volumeSize.s[0], volumeSize.s[1]);
        imgFeature = imgFeature2D();
    }
    else
    {
        imgVolume3D = cl::Image3D(clContext, CL_MEM_READ_ONLY, cl::ImageFormat(CL_INTENSITY, CL_FLOAT), volumeSize.s[0], volumeSize.s[1], volumeSize.s[2]);
        imgVolume = imgVolume3D();
        imgCut3D = cl::Image3D(clContext, CL_MEM_READ_ONLY, cl::ImageFormat(CL_RGBA, CL_SNORM_INT8), volumeSize.s[0], volumeSize.s[1], volumeSize.s[2]);
        imgCut = imgCut3D();
        imgFeature3D = cl::Image3D(clContext, CL_MEM_READ_ONLY, cl::ImageFormat(CL_RGBA, CL_UNORM_INT8), volumeSize.s[0], volumeSize.s[1], volumeSize.s[2]);
        imgFeature = imgFeature3D();
    }

    devTileList      = cl::Buffer(clContext, CL_MEM_READ_WRITE, hostTileList.size() * sizeof(cl_int4));
    devActiveTile    = cl::Buffer(clContext, CL_MEM_READ_WRITE, hostActiveTile.size() * sizeof(cl_int));
    devActiveTileOdd = cl::Buffer(clContext, CL_MEM_READ_WRITE, hostActiveTile.size() * sizeof(cl_int));
    devCutHistogram  = cl::Buffer(clContext, CL_MEM_READ_WRITE, hostCutHistogram.size() * sizeof(cl_int));
    devBFSHistogram  = cl::Buffer(clContext, CL_MEM_READ_WRITE, hostDistHistogram.size() * sizeof(cl_int));
    devDistribution  = cl::Buffer(clContext, CL_MEM_READ_WRITE, hostCutDistribution.size() * sizeof(cl_int));
    devDepth         = cl::Buffer(clContext, CL_MEM_READ_WRITE, hostDepth.size() * sizeof(cl_int));
    devCut           = cl::Buffer(clContext, CL_MEM_READ_WRITE, hostCut.size() * sizeof(cl_cut));
    devCentroid      = cl::Buffer(clContext, CL_MEM_READ_WRITE, hostCentroid.size() * sizeof(cl_float4));
    devSum           = cl::Buffer(clContext, CL_MEM_READ_WRITE, hostSum.size() * sizeof(cl_float4));
    devCount         = cl::Buffer(clContext, CL_MEM_READ_WRITE, hostCount.size() * sizeof(cl_int));

    const char *prSources[] = { "graphcut_kmeans.cl", "graphcut_histogram.cl" };
    std::list<std::string> prFiles(prSources, prSources + sizeof(prSources) / sizeof(prSources[0]));
    QUtilityCL::getCachedProgram(clContext, clDevice, progClustering, "./cl/GraphCut/", prFiles, options, headers);

    kerKMeans = cl::Kernel(progClustering, "graphcut_kmeans");
    kerKMeans.setArg(0, volumeSize);
    kerKMeans.setArg(1, imgFeature);
    kerKMeans.setArg(3, devCut);
    kerKMeans.setArg(4, devTileList);
    kerKMeans.setArg(6, devCentroid);
    kerKMeans.setArg(7, devSum);
    kerKMeans.setArg(8, devCount);

    kerCutHistogram = cl::Kernel(progClustering, "graphcut_cut_histogram");
    kerCutHistogram.setArg(0, volumeSize);
    kerCutHistogram.setArg(1, imgFeature);
    kerCutHistogram.setArg(3, QGCSetting::sizeCutHistogram);
    kerCutHistogram.setArg(4, devCutHistogram);
    kerCutHistogram.setArg(5, devCut);

    kerCutDistribution = cl::Kernel(progClustering, "graphcut_cut_distribution");
    kerCutDistribution.setArg(0, volumeSize);
    kerCutDistribution.setArg(1, imgFeature);
    kerCutDistribution.setArg(3, QGCSetting::sizeCutHistogram);
    kerCutDistribution.setArg(4, devDistribution);
    kerCutDistribution.setArg(5, devCut);
}

void QGCWidget::initModeling(const std::string& options, const std::string& headers)
{
    devExcessFlow = cl::Buffer(clContext, CL_MEM_READ_WRITE, hostExcessFlow.size());
    devHeight     = cl::Buffer(clContext, CL_MEM_READ_WRITE, hostHeight.size());
    devCapacity1  = cl::Buffer(clContext, CL_MEM_READ_WRITE, hostCapacity1.size());
    devCapacity2  = cl::Buffer(clContext, CL_MEM_READ_WRITE, hostCapacity2.size());
    
    const char *prSources[] = { "graphcut_compute_capacity.cl", "graphcut_compute_excessflow.cl" };
    std::list<std::string> prFiles(prSources, prSources + sizeof(prSources) / sizeof(prSources[0]));
    QUtilityCL::getCachedProgram(clContext, clDevice, progModeling, "./cl/GraphCut/", prFiles, options, headers);

    kerCapacityBK = cl::Kernel(progModeling, "graphcut_compute_capacity_bk");
    kerCapacityBK.setArg(0, volumeSize);
    kerCapacityBK.setArg(1, imgFeature);
    kerCapacityBK.setArg(2, devCut);
    kerCapacityBK.setArg(3, devCapacity1);
    kerCapacityBK.setArg(4, devCapacity2);

    kerCapacityLazy = cl::Kernel(progModeling, "graphcut_compute_capacity_lazy");
    kerCapacityLazy.setArg(0, volumeSize);
    kerCapacityLazy.setArg(1, imgFeature);
    kerCapacityLazy.setArg(2, devCut);
    kerCapacityLazy.setArg(3, devCapacity1);
    kerCapacityLazy.setArg(4, devCapacity2);

    kerExcessFlowBK = cl::Kernel(progModeling, "graphcut_compute_excessflow_bk");
    kerExcessFlowBK.setArg(0, volumeSize);
    kerExcessFlowBK.setArg(1, imgFeature);
    kerExcessFlowBK.setArg(2, devCut);
    kerExcessFlowBK.setArg(3, devExcessFlow);
    kerExcessFlowBK.setArg(4, devHeight);
    kerExcessFlowBK.setArg(5, QGCSetting::sizeCutHistogram);
    kerExcessFlowBK.setArg(6, devCutHistogram);

    kerExcessFlowLazy = cl::Kernel(progModeling, "graphcut_compute_excessflow_lazy");
    kerExcessFlowLazy.setArg(0, volumeSize);
    kerExcessFlowLazy.setArg(1, imgFeature);
    kerExcessFlowLazy.setArg(2, devCut);
    kerExcessFlowLazy.setArg(3, devExcessFlow);
    kerExcessFlowLazy.setArg(4, devHeight);
    kerExcessFlowLazy.setArg(5, devCentroid);
}

void QGCWidget::initCounting(const std::string& options, const std::string& headers)
{
    const char *prSources[] = { "graphcut_count_block.cl" };
    std::list<std::string> prFiles(prSources, prSources + sizeof(prSources) / sizeof(prSources[0]));
    QUtilityCL::getCachedProgram(clContext, clDevice, progCounting, "./cl/GraphCut/", prFiles, options, headers);

    kerScatterNode = cl::Kernel(progCounting, "graphcut_scatter_node");
    kerScatterNode.setArg(1, devTileList);
    kerScatterNode.setArg(2, groupSize);
    kerScatterNode.setArg(3, devActiveTile);
    kerScatterNode.setArg(4, devActiveTileOdd);

    kerCountNode = cl::Kernel(progCounting, "graphcut_count_node");
    kerCountNode.setArg(0, devExcessFlow);
    kerCountNode.setArg(1, devHeight);
    kerCountNode.setArg(2, volumeSize);
    kerCountNode.setArg(3, groupSize);
    kerCountNode.setArg(4, devActiveTile);
    kerCountNode.setArg(5, devActiveTileOdd);

    kerScatterCut = cl::Kernel(progCounting, "graphcut_scatter_cut");
    kerScatterCut.setArg(1, devTileList);
    kerScatterCut.setArg(2, groupSize);
    kerScatterCut.setArg(3, devActiveTile);

    kerCountCut = cl::Kernel(progCounting, "graphcut_count_cut");
    kerCountCut.setArg(0, volumeSize);
    kerCountCut.setArg(1, devCut);
    kerCountCut.setArg(2, groupSize);
    kerCountCut.setArg(3, devActiveTile);
}

void QGCWidget::initBFS(const std::string& options, const std::string& headers)
{
    const char *prSources[] = { "graphcut_bfs_block.cl" };
    std::list<std::string> prFiles(prSources, prSources + sizeof(prSources) / sizeof(prSources[0]));
    QUtilityCL::getCachedProgram(clContext, clDevice, progBFS, "./cl/GraphCut/", prFiles, options, headers);

    kerBFSJumpFlooding = cl::Kernel(progBFS, "graphcut_bfs_jump_flooding");
    kerBFSJumpFlooding.setArg(0, groupSize);
    kerBFSJumpFlooding.setArg(1, devDepth);

    kerBFSHistogram = cl::Kernel(progBFS, "graphcut_bfs_histogram");
    kerBFSHistogram.setArg(0, groupSize);
    kerBFSHistogram.setArg(1, devDepth);
    kerBFSHistogram.setArg(2, QGCSetting::sizeDistHistogram);
    kerBFSHistogram.setArg(3, devBFSHistogram);
    kerBFSHistogram.setArg(4, devTileList);

    kerBFSMapping = cl::Kernel(progBFS, "graphcut_bfs_mapping");
    kerBFSMapping.setArg(0, groupSize);
    kerBFSMapping.setArg(1, devBFSHistogram);
    kerBFSMapping.setArg(2, devDepth);
    kerBFSMapping.setArg(3, devTileList);

}
void QGCWidget::initPushRelabel(const std::string& options, const std::string& headers)
{
    const char *prSources[] = { "graphcut_push_relabel.cl" };
    std::list<std::string> prFiles(prSources, prSources + sizeof(prSources) / sizeof(prSources[0]));
    QUtilityCL::getCachedProgram(clContext, clDevice, progPushRelabel, "./cl/GraphCut/", prFiles, options, headers);

    kerPushRelabel = cl::Kernel(progPushRelabel, "graphcut_relabel_push");
    kerPushRelabel.setArg(0, devExcessFlow);
    kerPushRelabel.setArg(1, devHeight);
    kerPushRelabel.setArg(2, devCapacity1);
    kerPushRelabel.setArg(3, devCapacity2);
    kerPushRelabel.setArg(4, volumeSize);
    kerPushRelabel.setArg(5, devTileList);
    kerPushRelabel.setArg(6, devActiveTile);
}

void QGCWidget::initPushRelabelFast(const std::string& options, const std::string& headers)
{
    const char *prSources[] = { "graphcut_push_relabel_fast.cl" };
    std::list<std::string> prFiles(prSources, prSources + sizeof(prSources) / sizeof(prSources[0]));
    QUtilityCL::getCachedProgram(clContext, clDevice, progPushRelabelFast, "./cl/GraphCut/", prFiles, options, headers);

    kerFastRelabel = cl::Kernel(progPushRelabelFast, "graphcut_fast_relabel");
    kerFastRelabel.setArg(0, volumeSize);
    kerFastRelabel.setArg(1, devExcessFlow);
    kerFastRelabel.setArg(2, devHeight);
    kerFastRelabel.setArg(3, devCapacity1);
    kerFastRelabel.setArg(4, devCapacity2);
    kerFastRelabel.setArg(5, devTileList);

    kerFastPushX = cl::Kernel(progPushRelabelFast, "graphcut_fast_push_x");
    kerFastPushX.setArg(0, volumeSize);
    kerFastPushX.setArg(1, devExcessFlow);
    kerFastPushX.setArg(2, devHeight);
    kerFastPushX.setArg(3, devCapacity1);
    kerFastPushX.setArg(4, devCapacity2);
    kerFastPushX.setArg(5, devTileList);

    kerFastPushY = cl::Kernel(progPushRelabelFast, "graphcut_fast_push_y");
    kerFastPushY.setArg(0, volumeSize);
    kerFastPushY.setArg(1, devExcessFlow);
    kerFastPushY.setArg(2, devHeight);
    kerFastPushY.setArg(3, devCapacity1);
    kerFastPushY.setArg(4, devCapacity2);
    kerFastPushY.setArg(5, devTileList);

    if (volumeSize.s[2] > 1)
    {
        kerFastPushZ = cl::Kernel(progPushRelabelFast, "graphcut_fast_push_z");
        kerFastPushZ.setArg(0, volumeSize);
        kerFastPushZ.setArg(1, devExcessFlow);
        kerFastPushZ.setArg(2, devHeight);
        kerFastPushZ.setArg(3, devCapacity1);
        kerFastPushZ.setArg(4, devCapacity2);
        kerFastPushZ.setArg(5, devTileList);
    }
}

void QGCWidget::initCut(const std::string& options, const std::string& headers)
{
    const char *prSources[] = { "graphcut_compute_cut.cl" };
    std::list<std::string> prFiles(prSources, prSources + sizeof(prSources) / sizeof(prSources[0]));
    QUtilityCL::getCachedProgram(clContext, clDevice, progCut, "./cl/GraphCut/", prFiles, options, headers);

    kerInitCut = cl::Kernel(progCut, "graphcut_init_cut");
    kerInitCut.setArg(0, volumeSize);
    kerInitCut.setArg(1, devExcessFlow);
    kerInitCut.setArg(2, devCut);
    kerInitCut.setArg(3, groupSize);
    kerInitCut.setArg(4, devDepth);
    
    kerComputeCut = cl::Kernel(progCut, "graphcut_compute_cut");
    kerComputeCut.setArg(0, devExcessFlow);
    kerComputeCut.setArg(1, devHeight);
    kerComputeCut.setArg(2, devCapacity1);
    kerComputeCut.setArg(3, devCapacity2);
    kerComputeCut.setArg(4, volumeSize);
    kerComputeCut.setArg(5, devCut);
    kerComputeCut.setArg(6, groupSize);
    kerComputeCut.setArg(7, devTileList);
    kerComputeCut.setArg(8, devDone);
}

void QGCWidget::initTag(const std::string& options, const std::string& headers)
{
    const char *prSources[] = { "graphcut_compute_tag.cl" };
    std::list<std::string> prFiles(prSources, prSources + sizeof(prSources) / sizeof(prSources[0]));
    QUtilityCL::getCachedProgram(clContext, clDevice, progTag, "./cl/GraphCut/", prFiles, options, headers);

    kerInitTag = cl::Kernel(progTag, "graphcut_init_tag");
    kerInitTag.setArg(0, volumeSize);
    kerInitTag.setArg(1, devCut);
    kerInitTag.setArg(2, groupSize);
    kerInitTag.setArg(3, devDepth);

    kerComputeTag = cl::Kernel(progTag, "graphcut_compute_tag");
    kerComputeTag.setArg(0, volumeSize);
    kerComputeTag.setArg(1, devCut);
    kerComputeTag.setArg(2, groupSize);
    kerComputeTag.setArg(3, devTileList);
    kerComputeTag.setArg(4, devDone);
}

void QGCWidget::initGlobalRelabel(const std::string& options, const std::string& headers)
{
    devDone = cl::Buffer(clContext, CL_MEM_READ_WRITE, sizeof(cl_int2));

    const char *prSources[] = { "graphcut_global_relabel.cl" };
    std::list<std::string> prFiles(prSources, prSources + sizeof(prSources) / sizeof(prSources[0]));
    QUtilityCL::getCachedProgram(clContext, clDevice, progGlobalRelabel, "./cl/GraphCut/", prFiles, options, headers);

    kerInitGlobalRelabel = cl::Kernel(progGlobalRelabel, "graphcut_init_global_relabel");
    kerInitGlobalRelabel.setArg(0, volumeSize);
    kerInitGlobalRelabel.setArg(1, devExcessFlow);
    kerInitGlobalRelabel.setArg(2, devHeight);
    kerInitGlobalRelabel.setArg(3, groupSize);
    kerInitGlobalRelabel.setArg(4, devDepth);

    kerGlobalRelabel = cl::Kernel(progGlobalRelabel, "graphcut_global_relabel");
    kerGlobalRelabel.setArg(0, volumeSize);
    kerGlobalRelabel.setArg(1, devHeight);
    kerGlobalRelabel.setArg(2, devCapacity1);
    kerGlobalRelabel.setArg(3, devCapacity2);
    kerGlobalRelabel.setArg(4, groupSize);
    kerGlobalRelabel.setArg(5, devTileList);
    kerGlobalRelabel.setArg(6, devDone);
}

void QGCWidget::initReduce(const std::string& options, const std::string& headers)
{
    devFlow = cl::Buffer(clContext, CL_MEM_READ_WRITE, hostFlow.size() * sizeof(cl_int));
    devHistogram = cl::Buffer(clContext, CL_MEM_READ_WRITE, hostHistogram.size() * sizeof(cl_int));

    const char *prSources[] = { "reduce.cl" };
    std::list<std::string> prFiles(prSources, prSources + sizeof(prSources) / sizeof(prSources[0]));
    QUtilityCL::getCachedProgram(clContext, clDevice, progReduce, "./cl/Infrastructures/", prFiles, options, headers);
    
    kerReduceFlow = cl::Kernel(progReduce, "reduce_flow");
    kerReduceFlow.setArg(0, devFlow);
    kerReduceFlow.setArg(1, devExcessFlow);
    kerReduceFlow.setArg(2, flowBlockSize);
    kerReduceFlow.setArg(3, volumeSize1D);
    
    kerReduceHistogram = cl::Kernel(progReduce, "reduce_histogram");
    kerReduceHistogram.setArg(0, devHistogram);
    kerReduceHistogram.setArg(1, devDepth);
    kerReduceHistogram.setArg(2, histBlockSize);
    kerReduceHistogram.setArg(3, groupSize);
}

void QGCWidget::initRendering(const std::string& options, const std::string& headers)
{
    glGenBuffers(1, &glBuffer);
    if (!QUtilityGL::checkGLStatus(__FILE__, __LINE__, "glGenBuffers()"))
        throw QError(2, Q_RUNTIME_ERROR, "glGenBuffers() failed.");

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, glBuffer);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, hostMask.size() * sizeof(cl_uchar4), 0, GL_STREAM_DRAW);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    devBuffer = cl::BufferGL(clContext, CL_MEM_WRITE_ONLY, glBuffer);
    devMask = cl::Buffer(clContext, CL_MEM_WRITE_ONLY, hostMask.size() * sizeof(cl_uchar));

    imgTF = cl::Image2D(clContext, CL_MEM_READ_ONLY, cl::ImageFormat(CL_RGBA, CL_FLOAT), QGCSetting::sizeTransferFunction1D, 1U);
    imgIntegration = cl::Image2D(clContext, CL_MEM_READ_WRITE, cl::ImageFormat(CL_RGBA, CL_FLOAT), QGCSetting::sizePreIntegration, QGCSetting::sizePreIntegration);

    const Ui::QGCPanel* ui = panel->getUI();
    glm::uvec2 viewSize(ui->spinBoxViewSizeX->value(), ui->spinBoxViewSizeY->value());

    cl::Program  *programs[3] = { &progRenderNormal, &progRenderPreInt, &progRenderFeature };
    cl::Kernel *kerRenders[3] = {  kerRenderNormal,   kerRenderPreInt,   kerRenderFeature  };
    const char *prSources[] = { "graphcut_render_ray_casting.cl", "graphcut_render_ray_casting_preint.cl", "graphcut_render_ray_casting_feature.cl" };
    for (int i = 0; i < 3; i++)
    {
        cl::Program &program = programs[i][0];
        std::list<std::string> prFiles(1, prSources[i]);
        QUtilityCL::getCachedProgram(clContext, clDevice, program, "./cl/GraphCut/", prFiles, options, headers);

        cl::Kernel *kernels = kerRenders[i];
        kernels[0] = cl::Kernel(program, "graphcut_render_volume");
        kernels[1] = cl::Kernel(program, "graphcut_render_volume_object");
        kernels[2] = cl::Kernel(program, "graphcut_compute_visibility");
        for (int j = 0; j < 3; j++)
        {
            cl::Kernel& kernel = kernels[j];
            kernel.setArg(0, settings.inverseMVPMatrix);
            kernel.setArg(1, j < 2 ? devBuffer : devMask);
            kernel.setArg(2, j < 2 ? imgCut    : devCut());
            kernel.setArg(3, i < 2 ? imgVolume : imgFeature);
            kernel.setArg(4, volumeSize);
            kernel.setArg(5, imgIntegration);
            kernel.setArg(6, imgTF);
            kernel.setArg(7, viewSize.x);
            kernel.setArg(8, viewSize.y);
            kernel.setArg(12, boxSize);
        }
    }
}

void QGCWidget::initUtility(const std::string& options, const std::string& headers)
{
    const char *prSources[] = { "initialization.cl", "integration.cl" };
    std::list<std::string> prFiles(prSources, prSources + sizeof(prSources) / sizeof(prSources[0]));
    QUtilityCL::getCachedProgram(clContext, clDevice, progUtility, "./cl/Infrastructures/", prFiles, options, headers);

    kerClear = cl::Kernel(progUtility, "clear");

    kerIntegration = cl::Kernel(progUtility, "pre_integration");
    kerIntegration.setArg(0, imgTF);
    kerIntegration.setArg(1, imgIntegration);
}

void QGCWidget::initPrograms()
{
    std::ostringstream optionStream;
    optionStream << " -D cl_max_height=" << QGCSetting::cl_max_height;
    optionStream << " -D cl_max_flow=" << QGCSetting::cl_max_flow;
    optionStream << " -D cl_local_size=" << clLocalSize;
    optionStream << " -D cl_group_size=" << clGroupSize;
    if (volumeSize.s[2] == 1)
    {
        optionStream << " -D cl_image_2d ";
        optionStream << " -D cl_block_2d_x=" << blockSize.s[0];
        optionStream << " -D cl_block_2d_y=" << blockSize.s[1];
        optionStream << " -D cl_index_2d=" << (1 + (blockSize.s[0] + 2) * 1);
        optionStream << " -D cl_shift_2d_x="   << QGCSetting::cl_shift_2d.x;
        optionStream << " -D cl_shift_2d_y="   << QGCSetting::cl_shift_2d.y;
        optionStream << " -D cl_shift_max=" << QGCSetting::cl_shift_2d.w;
    }
    else
    {
        optionStream << " -D cl_block_3d_x=" << blockSize.s[0];
        optionStream << " -D cl_block_3d_y=" << blockSize.s[1];
        optionStream << " -D cl_block_3d_z=" << blockSize.s[2];
        optionStream << " -D cl_index_3d=" << (1 + (blockSize.s[0] + 2) * (1 + (blockSize.s[1] + 2) * 1));
        optionStream << " -D cl_shift_3d_x="   << QGCSetting::cl_shift_3d.x;
        optionStream << " -D cl_shift_3d_y="   << QGCSetting::cl_shift_3d.y;
        optionStream << " -D cl_shift_3d_z="   << QGCSetting::cl_shift_3d.z;
        optionStream << " -D cl_shift_max=" << QGCSetting::cl_shift_3d.w;
    }
    std::string options = optionStream.str();
    std::string headers = QGCSetting::defCut;

    initClustering(options, headers);
    initModeling(options, headers);
    initCounting(options, headers);
    initBFS(options, headers);
    initGlobalRelabel(options, headers);
    initPushRelabel(options, headers);
    initPushRelabelFast(options, headers);
    initCut(options, headers);
    initTag(options, headers);
    initReduce(options, headers);
    initRendering(options, headers);
    initUtility(options, headers);
}

void QGCWidget::initArguments()
{
    std::vector<float> bufferVolume(volumeSize1D);
    if (!QIO::getFileData(dataFilePath + objectFileName, bufferVolume.data(), bufferVolume.size() * sizeof(float)))
        throw QError(2, Q_RUNTIME_ERROR, "opening raw data failed.");
    
    std::vector<cl_uchar4> bufferFeature(volumeSize1D);
    for (int i = 0; i < volumeSize1D; i++)
    {
        cl_uchar *t = bufferFeature[i].s;
        t[3] = t[2] = t[1] = t[0] = bufferVolume[i] * std::numeric_limits<cl_uchar>::max();
    }
    
    if (volumeSize.s[2] == 1)
    {
        clQueue.enqueueWriteImage(imgVolume2D,  true, imgOrigin, imgRegion, 0, 0, bufferVolume.data());
        clQueue.enqueueWriteImage(imgFeature2D, true, imgOrigin, imgRegion, 0, 0, bufferFeature.data());
        clearTexture(devExcessFlow, sizeof(cl_int));
        clearTexture(devHeight,     sizeof(cl_int));
        clearTexture(devCapacity1,  sizeof(cl_uchar4));
        clearTexture(devCapacity2,  sizeof(cl_uchar4));
    }
    else
    {
        clQueue.enqueueWriteImage(imgVolume3D,  true, imgOrigin, imgRegion, 0, 0, bufferVolume.data());
        clQueue.enqueueWriteImage(imgFeature3D, true, imgOrigin, imgRegion, 0, 0, bufferFeature.data());
        clearTexture(devExcessFlow, sizeof(cl_int));
        clearTexture(devHeight,     sizeof(cl_int));
        clearTexture(devCapacity1,  sizeof(cl_short2));
        clearTexture(devCapacity2,  sizeof(cl_short2));
    }
    clearTexture(devCut, sizeof(cl_cut));
    clearTexture(devFlow, hostFlow.size(), sizeof(int));
    clearTexture(devHistogram, hostHistogram.size(), sizeof(int));
    
    if (volumeSize.s[2] == 1)
        clQueue.enqueueCopyBufferToImage(devCut, imgCut2D, 0, imgOrigin, imgRegion);
    else
        clQueue.enqueueCopyBufferToImage(devCut, imgCut3D, 0, imgOrigin, imgRegion);

    const Ui::QGCPanel* ui = panel->getUI();
    ui->tabBrushing->slotLoad();
    ui->tabMode->slotLoad();
    ui->tabColor->slotLoad();
    
    ui->tabAlgorithm->slotLoad();
    ui->tabModeling->slotLoad();
    ui->tabConvergence->slotLoad();
    ui->tabFeature->slotLoad();
    ui->tabOpenCL->slotLoad();

    ui->tabProjection->slotLoad();
    ui->tabRayCasting->slotLoad();
    ui->tabPreIntegration->slotLoad();
    ui->tabView->slotLoad();

    slotLoadTransferFunctionClicked();
    slotLoadFeatureClicked();
    slotLoadCutClicked();
}

// Step 4 - message loop

// initializeGL
void QGCWidget::initializeGL()
{
    initContext();
}

// resizeGL
void QGCWidget::resizeGL(int w, int h)
{
    if (error) return;

    const Ui::QGCPanel* ui = panel->getUI();
    ui->spinBoxViewSizeX->setValue(w == 0 ? 1 : w);
    ui->spinBoxViewSizeY->setValue(h == 0 ? 1 : h);

    glm::uvec2 viewSize(ui->spinBoxViewSizeX->value(), ui->spinBoxViewSizeY->value());
    glViewport(0, 0,  viewSize.x, viewSize.y);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    setProjection();

    updatePixelBuffer();

    repaint();
}

void QGCWidget::updatePixelBuffer()
{
    const Ui::QGCPanel* ui = panel->getUI();
    glm::uvec2 viewSize(ui->spinBoxViewSizeX->value(), ui->spinBoxViewSizeY->value());
    cl::Kernel *kerRenders[3] = { kerRenderNormal,  kerRenderPreInt,  kerRenderFeature };
    for (int i = 0; i < 3; i++)
    {
        cl::Kernel* kernels = kerRenders[i];
        for (int j = 0; j < 3; j++)
        {
            cl::Kernel& kernel = kernels[j];
            kernel.setArg(7, viewSize.x);
            kernel.setArg(8, viewSize.y);
        }
    }

    if (viewSize.x * viewSize.y > hostMask.size())
    {
        int size = viewSize.x * viewSize.y * 2;
        hostMask.resize(size);

        if (glBuffer)
        {
            glDeleteBuffers(1, &this->glBuffer);
            if (!QUtilityGL::checkGLStatus(__FILE__, __LINE__, "glDeleteBuffers()"))
                throw QError(2, Q_RUNTIME_ERROR, "glDeleteBuffers() failed.");
        }

        glGenBuffers(1, &glBuffer);
        if (!QUtilityGL::checkGLStatus(__FILE__, __LINE__, "glGenBuffers()"))
            throw QError(2, Q_RUNTIME_ERROR, "glGenBuffers() failed.");

        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, glBuffer);
        glBufferData(GL_PIXEL_UNPACK_BUFFER, hostMask.size() * sizeof(cl_uchar4), 0, GL_STREAM_DRAW);
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

        devBuffer = cl::BufferGL(clContext, CL_MEM_WRITE_ONLY, glBuffer);
        devMask = cl::Buffer(clContext, CL_MEM_WRITE_ONLY, hostMask.size() * sizeof(cl_uchar));

        cl::Kernel *kerRenders[3] = { kerRenderNormal,  kerRenderPreInt,  kerRenderFeature };
        for (int i = 0; i < 3; i++)
        {
            cl::Kernel* kernels = kerRenders[i];
            for (int j = 0; j < 3; j++)
            {
                cl::Kernel& kernel = kernels[j];
                kernel.setArg(1, j < 2 ? devBuffer : devMask);
            }
        }
    }
}

// paintGL
void QGCWidget::paintGL()
{
    if (error) return;

    try
    {
        drawMask();
        drawVolume();
        drawWireFrame();
        paintForeground();
        swapBuffers();
    }
    catch (QError& e)
    {
        switch (e.level())
        {
        case 0:
            break;
        case 1:
            std::cerr << " > LOG: " << std::endl << e.what();
            break;
        default:
            std::cerr << " > ERROR: " << std::endl << e.what();
            error = true;
            break;
        }
    }
    catch (cl::Error& e)
    {
        std::cerr << " > CALL STACK: " << std::endl << e.what();
        error = true;
    }
    catch (clogs::InternalError &e)
    {
        std::cerr << " > CLOGS: " << e.what() << std::endl;
        error = true;
    }
}

void QGCWidget::drawVolumeCL()
{
    cl_uint textureOffset = getRayCastingObject();

    const Ui::QGCPanel* ui = panel->getUI();
    cl_float sampleRatio = ui->doubleSpinBoxSampleRatio->value();
    cl_float sampleScale = ui->spinBoxSampleScale->value();
    cl_uint sampleNumber = ui->spinBoxSampleNumber->value();
    cl_float windowWidth = (float)ui->verticalSliderWindowWidth->value() / ui->verticalSliderWindowWidth->maximum();
    cl_float windowLevel = (float)ui->verticalSliderWindowLevel->value() / ui->verticalSliderWindowLevel->maximum();
    cl_uint4 viewSize = { ui->spinBoxViewSizeX->value(), ui->spinBoxViewSizeY->value(), 0, 0 };
    cl::NDRange local(ui->spinBoxLocalSize2DX->value(), ui->spinBoxLocalSize2DY->value());
    cl::NDRange global(QUtilityCL::ceil(local, viewSize));
    cl::Kernel* kernels = ui->radioButtonNormal->isChecked() ? kerRenderNormal : (ui->radioButtonPreIntegration->isChecked() ? kerRenderPreInt : kerRenderFeature);
    cl::Kernel& kernel = kernels[textureOffset ? 1 : 0];
    kernel.setArg(0, settings.inverseMVPMatrix);
    kernel.setArg(9, sampleNumber);
    kernel.setArg(10, sampleRatio);
    kernel.setArg(11, sampleScale);
    kernel.setArg(13, windowWidth);
    kernel.setArg(14, windowLevel);
    if (textureOffset)
    {
        kernel.setArg(15, textureOffset);
    }
    else
    {
        glm::vec4 colorFore = QUtilityUI::getColor(ui->pushButtonColorFore->toolTip(), ui->spinBoxColorFore->value());
        glm::vec4 colorBack = QUtilityUI::getColor(ui->pushButtonColorBack->toolTip(), ui->spinBoxColorBack->value());
        glm::vec4 colorCut  = QUtilityUI::getColor(ui->pushButtonColorCut->toolTip(),  ui->spinBoxColorCut->value());
        glm::vec4 colorTag  = QUtilityUI::getColor(ui->pushButtonColorTag->toolTip(),  ui->spinBoxColorTag->value());
        kernel.setArg(15, colorFore);
        kernel.setArg(16, colorBack);
        kernel.setArg(17, colorCut);
        kernel.setArg(18, colorTag);
    }
    
    glm::quat viewRotation(ui->doubleSpinBoxRotationW->value(), ui->doubleSpinBoxRotationX->value(), ui->doubleSpinBoxRotationY->value(), ui->doubleSpinBoxRotationZ->value());
    getIMVPMatrix(viewRotation);

    std::vector<cl::Memory> buffers(1, devBuffer);
    clQueue.enqueueAcquireGLObjects(&buffers);
    clQueue.enqueueNDRangeKernel(kernel, cl::NullRange, global, local);
    clQueue.enqueueReleaseGLObjects(&buffers);
    clQueue.finish();
}

void QGCWidget::drawVolume()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Draw image from PBO
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    const Ui::QGCPanel* ui = panel->getUI();
    glm::uvec2 viewSize(ui->spinBoxViewSizeX->value(), ui->spinBoxViewSizeY->value());
    glOrtho(0.0f, viewSize.x, 0.0f, viewSize.y, -1.0f, 1.0f);

    glRasterPos2i(0, 0);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, glBuffer);

    drawVolumeCL();

    glDrawPixels(viewSize.x, viewSize.y, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    if (!QUtilityGL::checkGLStatus(__FILE__, __LINE__, "glDrawPixels()"))
        throw QError(2, Q_RUNTIME_ERROR, "glDrawPixels() failed.");
    
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glPopAttrib();
}

void QGCWidget::drawWireFrame()
{
    const Ui::QGCPanel* ui = panel->getUI();
    glm::uvec2 viewSize(ui->spinBoxViewSizeX->value(), ui->spinBoxViewSizeY->value());
    glm::vec3 viewTranslation(ui->doubleSpinBoxTranslationX->value(), ui->doubleSpinBoxTranslationY->value(), ui->doubleSpinBoxTranslationZ->value());
    glm::quat viewRotation(ui->doubleSpinBoxRotationW->value(), ui->doubleSpinBoxRotationX->value(), ui->doubleSpinBoxRotationY->value(), ui->doubleSpinBoxRotationZ->value());

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0,  viewSize.x, viewSize.y);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    setProjection();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(viewTranslation.x, viewTranslation.y, viewTranslation.z);

    glm::vec4 angleAxis = QUtilityMath::getAxisAngle(viewRotation);
    glRotatef(angleAxis.w * 180.0 / M_PI, angleAxis.x, angleAxis.y, angleAxis.z);

    glClear(GL_DEPTH_BUFFER_BIT);

    GLuint quads = glGenLists(1);
    glNewList(quads, GL_COMPILE);

    glBegin(GL_QUADS);
    glVertex3f(-boxSize.s[0], -boxSize.s[1], -boxSize.s[2]);
    glVertex3f(-boxSize.s[0], -boxSize.s[1],  boxSize.s[2]);
    glVertex3f(-boxSize.s[0],  boxSize.s[1],  boxSize.s[2]);
    glVertex3f(-boxSize.s[0],  boxSize.s[1], -boxSize.s[2]);

    glVertex3f( boxSize.s[0],  boxSize.s[1],  boxSize.s[2]);
    glVertex3f( boxSize.s[0], -boxSize.s[1],  boxSize.s[2]);
    glVertex3f( boxSize.s[0], -boxSize.s[1], -boxSize.s[2]);
    glVertex3f( boxSize.s[0],  boxSize.s[1], -boxSize.s[2]);

    glVertex3f(-boxSize.s[0], -boxSize.s[1], -boxSize.s[2]);
    glVertex3f( boxSize.s[0], -boxSize.s[1], -boxSize.s[2]);
    glVertex3f( boxSize.s[0], -boxSize.s[1],  boxSize.s[2]);
    glVertex3f(-boxSize.s[0], -boxSize.s[1],  boxSize.s[2]);

    glVertex3f( boxSize.s[0],  boxSize.s[1],  boxSize.s[2]);
    glVertex3f( boxSize.s[0],  boxSize.s[1], -boxSize.s[2]);
    glVertex3f(-boxSize.s[0],  boxSize.s[1], -boxSize.s[2]);
    glVertex3f(-boxSize.s[0],  boxSize.s[1],  boxSize.s[2]);

    glVertex3f(-boxSize.s[0], -boxSize.s[1], -boxSize.s[2]);
    glVertex3f(-boxSize.s[0],  boxSize.s[1], -boxSize.s[2]);
    glVertex3f( boxSize.s[0],  boxSize.s[1], -boxSize.s[2]);
    glVertex3f( boxSize.s[0], -boxSize.s[1], -boxSize.s[2]);

    glVertex3f( boxSize.s[0],  boxSize.s[1],  boxSize.s[2]);
    glVertex3f(-boxSize.s[0],  boxSize.s[1],  boxSize.s[2]);
    glVertex3f(-boxSize.s[0], -boxSize.s[1],  boxSize.s[2]);
    glVertex3f( boxSize.s[0], -boxSize.s[1],  boxSize.s[2]);
    glEnd();

    glEndList();

    glColor3f(0.25, 0.25, 0.25);

    glBlendFunc(GL_ZERO, GL_ONE);
    glPolygonMode(GL_FRONT, GL_FILL);
    glCallList(quads);
    
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(1.0, 1.0);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPolygonMode(GL_FRONT, GL_LINE);
    glCallList(quads);
    
    glDisable(GL_CULL_FACE);
    glDisable(GL_POLYGON_OFFSET_FILL);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    float arrowSize = 0.05f;
    float scale = 0.2f;
    cl_float4 maxSize = 
    {
        boxSize.s[0] + scale * 2,
        boxSize.s[1] + scale * 2,
        boxSize.s[2] + scale * 2
    };
    
    glColor3f(0.75f, 0.25f, 0.25f);
    glBegin(GL_LINES);
    glVertex3f(-boxSize.s[0], -boxSize.s[1], -boxSize.s[2]);
    glVertex3f( maxSize.s[0] + scale, -boxSize.s[1], -boxSize.s[2]);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f( maxSize.s[0] + scale, -boxSize.s[1], -boxSize.s[2]);
    glVertex3f( maxSize.s[0] + scale - arrowSize * 2, -boxSize.s[1] + arrowSize, -boxSize.s[2]);
    glVertex3f( maxSize.s[0] + scale - arrowSize * 2, -boxSize.s[1], -boxSize.s[2]);

    glVertex3f( maxSize.s[0] + scale, -boxSize.s[1], -boxSize.s[2]);
    glVertex3f( maxSize.s[0] + scale - arrowSize * 2, -boxSize.s[1], -boxSize.s[2] + arrowSize);
    glVertex3f( maxSize.s[0] + scale - arrowSize * 2, -boxSize.s[1], -boxSize.s[2]);
    glEnd();

    glColor3f(0.25f, 0.75f, 0.25f);
    glBegin(GL_LINES);
    glVertex3f(-boxSize.s[0], -boxSize.s[1], -boxSize.s[2]);
    glVertex3f(-boxSize.s[0],  maxSize.s[1] + scale, -boxSize.s[2]);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(-boxSize.s[0],  maxSize.s[1] + scale, -boxSize.s[2]);
    glVertex3f(-boxSize.s[0] + arrowSize,  maxSize.s[1] + scale - arrowSize * 2, -boxSize.s[2]);
    glVertex3f(-boxSize.s[0],  maxSize.s[1] + scale - arrowSize * 2, -boxSize.s[2]);

    glVertex3f(-boxSize.s[0],  maxSize.s[1] + scale, -boxSize.s[2]);
    glVertex3f(-boxSize.s[0],  maxSize.s[1] + scale - arrowSize * 2, -boxSize.s[2] + arrowSize);
    glVertex3f(-boxSize.s[0],  maxSize.s[1] + scale - arrowSize * 2, -boxSize.s[2]);
    glEnd();

    glColor3f(0.25f, 0.25f, 0.75f);
    glBegin(GL_LINES);
    glVertex3f(-boxSize.s[0], -boxSize.s[1], -boxSize.s[2]);
    glVertex3f(-boxSize.s[0], -boxSize.s[1],  maxSize.s[2] + scale);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(-boxSize.s[0], -boxSize.s[1],  maxSize.s[2] + scale);
    glVertex3f(-boxSize.s[0] + arrowSize, -boxSize.s[1],  maxSize.s[2] + scale - arrowSize * 2);
    glVertex3f(-boxSize.s[0], -boxSize.s[1],  maxSize.s[2] + scale - arrowSize * 2);

    glVertex3f(-boxSize.s[0], -boxSize.s[1],  maxSize.s[2] + scale);
    glVertex3f(-boxSize.s[0], -boxSize.s[1] + arrowSize,  maxSize.s[2] + scale - arrowSize * 2);
    glVertex3f(-boxSize.s[0], -boxSize.s[1],  maxSize.s[2] + scale - arrowSize * 2);
    glEnd();

    glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_LINES);

    int number = (int)((maxSize.s[0] + boxSize.s[0]) / scale) + 1;
    for (int i = 1; i < number; i++)
    {
        glVertex3f(-boxSize.s[0] + i * scale, -boxSize.s[1], -boxSize.s[2]);
        glVertex3f(-boxSize.s[0] + i * scale,  maxSize.s[1], -boxSize.s[2]);
        glVertex3f(-boxSize.s[0] + i * scale, -boxSize.s[1], -boxSize.s[2]);
        glVertex3f(-boxSize.s[0] + i * scale, -boxSize.s[1],  maxSize.s[2]);
    }

    number = (int)((maxSize.s[1] + boxSize.s[1]) / scale) + 1;
    for (int i = 1; i < number; i++)
    {
        glVertex3f(-boxSize.s[0], -boxSize.s[1] + i * scale, -boxSize.s[2]);
        glVertex3f( maxSize.s[0], -boxSize.s[1] + i * scale, -boxSize.s[2]);
        glVertex3f(-boxSize.s[0], -boxSize.s[1] + i * scale, -boxSize.s[2]);
        glVertex3f(-boxSize.s[0], -boxSize.s[1] + i * scale,  maxSize.s[2]);
    }

    number = (int)((maxSize.s[2] + boxSize.s[2]) / scale) + 1;
    for (int i = 1; i < number; i++)
    {
        glVertex3f(-boxSize.s[0],  -boxSize.s[1], -boxSize.s[2] + i * scale);
        glVertex3f( maxSize.s[0], -boxSize.s[1], -boxSize.s[2] + i * scale);
        glVertex3f(-boxSize.s[0], -boxSize.s[1], -boxSize.s[2] + i * scale);
        glVertex3f(-boxSize.s[0],  maxSize.s[1], -boxSize.s[2] + i * scale);
    }
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPopAttrib();
}

void QGCWidget::drawMask()
{}

void QGCWidget::drawParameters()
{
    const Ui::QGCPanel* ui = panel->getUI();
    glm::uvec2 viewSize(ui->spinBoxViewSizeX->value(), ui->spinBoxViewSizeY->value());
    glm::vec3 viewTranslation(ui->doubleSpinBoxTranslationX->value(), ui->doubleSpinBoxTranslationY->value(), ui->doubleSpinBoxTranslationZ->value());
    glm::quat viewRotation(ui->doubleSpinBoxRotationW->value(), ui->doubleSpinBoxRotationX->value(), ui->doubleSpinBoxRotationY->value(), ui->doubleSpinBoxRotationZ->value());

    QPainter painter(this);

    glm::vec4 axisAngle = QUtilityMath::getAxisAngle(viewRotation);
    painter.drawText(5, viewSize.y - 120, QString("Gradient: (%1, %2)").arg(gradientMin, 0, 'f', 3).arg(gradientMax, 0, 'f', 3));
    painter.drawText(5, viewSize.y - 100, QString("Curvature: (%1, %2)").arg(curvatureMin, 0, 'f', 3).arg(curvatureMax, 0, 'f', 3));
    painter.drawText(5, viewSize.y - 80,  QString("Foregound: (%1, %2)").arg(hostMinMask[0], 0, 'f', 3).arg(hostMaxMask[0], 0, 'f', 3));
    painter.drawText(5, viewSize.y - 60,  QString("Background: (%1, %2)").arg(hostMinMask[1], 0, 'f', 3).arg(hostMaxMask[1], 0, 'f', 3));
    painter.drawText(5, viewSize.y - 40,  QString("Translation: (%1, %2, %3)").arg(viewTranslation.x, 0, 'f', 3).arg(viewTranslation.y, 0, 'f', 3).arg(viewTranslation.z, 0, 'f', 3));
    painter.drawText(5, viewSize.y - 20,  QString("Rotation: axis - (%1, %2, %3), angle - (%4)").arg(axisAngle.x, 0, 'f', 3).arg(axisAngle.y, 0, 'f', 3).arg(axisAngle.z, 0, 'f', 3).arg(axisAngle.w * 180.0f / M_PI, 0, 'f', 3));
}

void QGCWidget::drawFocusArea()
{
    const Ui::QGCPanel* ui = panel->getUI();
    cl_uint offset = getBrushingObject();
    if (offset < 2 && !ui->radioButtonModeNormal->isChecked())
    {
        int size = ui->spinBoxSize->value();

        QPushButton *pushButton = offset == 0 ? ui->pushButtonColorFore : ui->pushButtonColorBack;
        glm::vec4 color = QUtilityUI::getColor(pushButton->toolTip());
        
        QPainter painter(this);
        painter.setBrush(QColor::fromRgbF(color.r, color.g, color.b, 0.25f));
        painter.setPen(Qt::gray);
        const Ui::QGCPanel* ui = panel->getUI();
        if (ui->radioButtonShapeCircle->isChecked())
            painter.drawEllipse(QPoint(mousePosition.x, mousePosition.y), size / 2, size / 2);
        else if (ui->radioButtonShapeSquare->isChecked())
            painter.drawRect(mousePosition.x - size / 2, mousePosition.y - size / 2, size, size);
        else
            painter.drawRect(mousePosition.x - size / 2, mousePosition.y - size / 2, size, size);
    }
}

void QGCWidget::drawColorBar()
{
    const Ui::QGCPanel* ui = panel->getUI();
    glm::uvec2 viewSize(ui->spinBoxViewSizeX->value(), ui->spinBoxViewSizeY->value());
    int width = ui->widgetEditor->width();

    QPainter painter(this);

    int barWidth = 30;
    glm::ivec4 padding(50, 80, 50, 0); // Top Right Bottom Left
    QRect rect = QRect(viewSize.x - padding.y - barWidth, padding.x, barWidth, viewSize.y - padding.x - padding.z);
    QHoverPoints* hoverPoints = ui->widgetEditor->getHoverPoints();
    QLinearGradient gradient(rect.bottomLeft(), rect.topLeft());
    std::vector<float> positions;
    QUtilityData::computePartitionPositions(hoverPoints, width, positions, QGCSetting::sizeMapping, bufferMapping.data());
    switch (hoverPoints->connectionType())
    {
    case QHoverPoints::LineConnection:
        QUtilityUI::generateLinearGradient(gradient, width, hoverPoints, 0.0f);
        break;
    case QHoverPoints::CurveConnection:
        QUtilityUI::generateCubicGradient(gradient, width, hoverPoints, QSetting::sizeTransferFunction1D, positions, 0.0f);
        break;
    }

    painter.setBrush(QBrush(gradient));
    painter.setPen(QColor(31, 31, 31));
    painter.drawRect(rect);

    int lineNumber = 8, lineWidth = 8, textPadding = 5;
    QSize textSize(50, 16);

    int index = 0;
    const QPolygonF& points = hoverPoints->points();
    for (int i = 0; i < lineNumber; i++)
    {
        float x = (float)width * i / (lineNumber - 1);
        while (points[index + 1].x() < x) index++;
        float ratio = (float)(x - points[index].x()) / (points[index + 1].x() - points[index].x());
        float value = volumeMin + (volumeMax - volumeMin) * (positions[index] * (1 - ratio) + positions[index + 1] * ratio);
        QPoint location(rect.right(), rect.bottom() - rect.height() * i / (lineNumber - 1));
        painter.drawLine(QPoint(location.x() - lineWidth, location.y()), location);
        painter.drawText(QRect(location.x() + textPadding, location.y() - textSize.height() / 2, textSize.width(), textSize.height()), Qt::AlignCenter, QString::number(value,'f', 2));
    }
}

void QGCWidget::paintBackground()
{
    QPainter painter(this);
}

void QGCWidget::paintForeground()
{
    drawColorBar();
    drawParameters();
    drawFocusArea();
}

// mouseEvent
void QGCWidget::mousePressEvent(QMouseEvent *event)
{
    mousePosition.x = event->x();
    mousePosition.y = event->y();

    if (event->buttons() & Qt::LeftButton)
    {
        mouseMode = MOUSE_ROTATE;
    }
    else if (event->buttons() & Qt::MidButton)
    {
        mouseMode = MOUSE_TRANSLATE;
    }
    else if (event->buttons() & Qt::RightButton)
    {
        mouseMode = MOUSE_DOLLY;
    }
    else
    {
        mouseMode = MOUSE_UNKNOW;
    }

    const Ui::QGCPanel* ui = panel->getUI();
    cl_uint offset = getBrushingObject();
    if (offset < 2 && !ui->radioButtonModeNormal->isChecked()) shot();
    
    repaint();
}

void QGCWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mousePosition.x = event->x();
    mousePosition.y = event->y();

    mouseMode = MOUSE_UNKNOW;

    repaint();
}

void QGCWidget::mouseMoveEvent(QMouseEvent *event)
{
    const Ui::QGCPanel* ui = panel->getUI();
    if (ui->radioButtonModeNormal->isChecked())
    {
        glm::uvec2 viewSize(ui->spinBoxViewSizeX->value(), ui->spinBoxViewSizeY->value());
        glm::quat viewRotation(ui->doubleSpinBoxRotationW->value(), ui->doubleSpinBoxRotationX->value(), ui->doubleSpinBoxRotationY->value(), ui->doubleSpinBoxRotationZ->value());

        float dx = (event->x() - mousePosition.x) / (float)viewSize.x;
        float dy = (event->y() - mousePosition.y) / (float)viewSize.y;

        glm::vec3 mouse(dx, -dy, 0.0);
        glm::vec3 view(0.0, 0.0, -1.0);
        glm::vec3 axis(glm::normalize(glm::cross(mouse, view)));

        switch (mouseMode)
        {
        case MOUSE_DOLLY:
            {
                float viewTranslationZ = ui->doubleSpinBoxTranslationZ->value();
                ui->doubleSpinBoxTranslationZ->setValue(viewTranslationZ + dy);
            }
            break;
        case MOUSE_ROTATE:
            {
                viewRotation = glm::rotate(glm::quat(), std::sqrt(dx * dx + dy * dy) * 180, axis) * viewRotation;
                ui->doubleSpinBoxRotationX->setValue(viewRotation.x);
                ui->doubleSpinBoxRotationY->setValue(viewRotation.y);
                ui->doubleSpinBoxRotationZ->setValue(viewRotation.z);
                ui->doubleSpinBoxRotationW->setValue(viewRotation.w);
            }
            break;
        case MOUSE_TRANSLATE:
            {
                glm::vec3 viewTranslation(ui->doubleSpinBoxTranslationX->value(), ui->doubleSpinBoxTranslationY->value(), ui->doubleSpinBoxTranslationZ->value());
                viewTranslation = viewTranslation + mouse;
                ui->doubleSpinBoxTranslationX->setValue(viewTranslation.x);
                ui->doubleSpinBoxTranslationY->setValue(viewTranslation.y);
                ui->doubleSpinBoxTranslationZ->setValue(viewTranslation.z);
            }
            break;
        default:
            break;
        }
    }

    mousePosition.x = event->x();
    mousePosition.y = event->y();

    repaint();
}

void QGCWidget::wheelEvent(QWheelEvent *event)
{
    repaint();
}

// keyPressEvent
void QGCWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
    case Qt::Key_Q:
        // close();
        break;
    case Qt::Key_Plus:
        break;
    case Qt::Key_Minus:
        break;
    case Qt::Key_Comma:
        break;
    case Qt::Key_Period:
        break;
    case Qt::Key_S:
        slotSaveTransferFunctionClicked();
        break;
    case Qt::Key_L:
        slotLoadTransferFunctionClicked();
        break;
    case Qt::Key_P:
        break;
    case Qt::Key_Space:
        settings.enableLoggingFPS = !settings.enableLoggingFPS;
        settings.enableLoggingTimeCost = !settings.enableLoggingTimeCost;
        break;
    }

    repaint();
}

// K-Means

void QGCWidget::kmeans(cl_long& nsecKMeans, cl_uint offset)
{
    cl_int status = CL_SUCCESS;

    clearTexture(devDistribution, QGCSetting::sizeCutHistogram, sizeof(cl_uint));

    const Ui::QGCPanel* ui = panel->getUI();
    glm::vec4 weight = glm::normalize(glm::vec4(ui->doubleSpinBoxWeightX->value(), ui->doubleSpinBoxWeightY->value(), ui->doubleSpinBoxWeightZ->value(), ui->doubleSpinBoxWeightW->value()));
    glm::vec4 scale = weight / std::numeric_limits<cl_uchar>::max();
    kerCutDistribution.setArg(2, offset);
    kerCutDistribution.setArg(6, weight);

    enqueue3DKernel(kerCutDistribution);

    clQueue.enqueueReadBuffer(devDistribution, true, 0, QGCSetting::sizeCutHistogram * sizeof(cl_uint), hostCutDistribution.data());
    std::vector<int> distributionData;
    for (int i = 0; i < QGCSetting::sizeCutHistogram; i++)
        if (hostCutDistribution[i] > 0) distributionData.push_back(hostCutDistribution[i]);

    if (distributionData.empty())
        throw QError(1, Q_LOGIC_ERROR, "no labels.");

    cl_uint k = ui->spinBoxK->value();
    std::vector<glm::vec4> centroid(k);
    cl_uint distributionSize(distributionData.size() - 1);
    cl::size_t<3> origin, region;
    region[2] = region[1] = region[0] = 1;
    for (int i = 0; i < k; i++)
    {
        int index = distributionData[distributionSize * i / (k - 1)] - 1;
        origin[0] = index % volumeSize.s[0];
        index /= volumeSize.s[0];
        origin[1] = index % volumeSize.s[1];
        index /= volumeSize.s[1];
        origin[2] = index;

        cl_uchar4 t;
        if (volumeSize.s[2] == 1)
            clQueue.enqueueReadImage(imgFeature2D, true, origin, region, 0, 0, &t);
        else
            clQueue.enqueueReadImage(imgFeature3D, true, origin, region, 0, 0, &t);
        centroid[i] = glm::vec4(t.s[0], t.s[1], t.s[2], t.s[3]) * scale;
    }

    std::vector<cl::Event> countEvents(1);
    kerCountCut.setArg(4, offset);
    clQueue.enqueueNDRangeKernel(kerCountCut, cl::NullRange, sizGlobal, sizLocal, NULL, &countEvents[0]);
    nsecKMeans += QUtilityCL::getElapsedTime(countEvents, clQueue);

    std::vector<cl::Event> scanEvents(1);
    clScan->enqueue(clQueue, devActiveTile, groupSize1D + 1, NULL, NULL, &scanEvents[0]);
    nsecKMeans += QUtilityCL::getElapsedTime(scanEvents, clQueue);

    cl_int listSize = 0, listOffset = 0;
    clQueue.enqueueReadBuffer(devActiveTile, true, groupSize1D * sizeof(cl_int), sizeof(cl_int), &listSize);

    std::vector<cl::Event> scatterEvents(1);
    kerScatterCut.setArg(0, listOffset);
    enqueue3DKernel(kerScatterCut, groupSize, &scatterEvents[0]);
    nsecKMeans += QUtilityCL::getElapsedTime(scatterEvents, clQueue);

    hostTileOffset.clear();
    hostTileOffset.push_back(0);
    hostTileOffset.push_back(listSize);
    
    cl::NDRange global(sizGlobal);
    const_cast<::size_t*>((const ::size_t*)global)[2] = listSize;

    kerKMeans.setArg(2, offset);
    kerKMeans.setArg(5, k);
    kerKMeans.setArg(9, weight);

    int iterations = ui->spinBoxKMeansIterations->value();
    glm::vec4* pCentroid = hostCentroid.data() + k * offset;
    float error(0.0f);
    int countt(0);
    for (int i = 0; i < iterations; i++)
    {
        memcpy(pCentroid, centroid.data(), centroid.size() * sizeof(cl_float4));
        clQueue.enqueueWriteBuffer(devCentroid, true, k * sizeof(cl_float4) * offset, k * sizeof(cl_float4), pCentroid);
        
        std::vector<cl::Event> kMeansEvents(1);
        clQueue.enqueueNDRangeKernel(kerKMeans, cl::NullRange, global, sizLocal, NULL, &kMeansEvents[0]);
        nsecKMeans += QUtilityCL::getElapsedTime(kMeansEvents, clQueue);

        clQueue.enqueueReadBuffer(devSum,   true, 0, listSize * k * sizeof(cl_float4), hostSum.data());
        clQueue.enqueueReadBuffer(devCount, true, 0, listSize * k * sizeof(cl_int),    hostCount.data());

        memset(centroid.data(), 0, centroid.size() * sizeof(cl_float4));
        error = 0.0f;
        countt = 0;
        for (int i = 0; i < k; i++)
        {
            int count(0);
            for (int j = 0; j < listSize; j++)
            {
                centroid[i] += hostSum[j * k + i];
                count += hostCount[j * k + i];
            }
            if (count > 0) centroid[i] /= count;
            countt += count;

            error = std::max<float>(error, glm::length(centroid[i] - pCentroid[i]));
        }
        if (error < (1.0f / 1024)) break;
    }

    std::cout.precision(5);
    std::cout.setf(std::ios::fixed, std:: ios::floatfield);
    std::cout << " > INFO: kmeans - error " << offset << " " << error << "." << std::endl;
}

// Graph Cut
void QGCWidget::countActiveBlock(cl_long& nsecCount)
{
    std::vector<cl::Event> countEvents(1);
    clQueue.enqueueNDRangeKernel(kerCountNode, NULL, sizGlobal, sizLocal, NULL, &countEvents[0]);
    nsecCount += QUtilityCL::getElapsedTime(countEvents, clQueue);
    
    std::vector<cl::Event> scanEvents(2);
    clScan->enqueue(clQueue, devActiveTile, groupSize1D + 1, NULL, NULL, &scanEvents[0]);
    clScan->enqueue(clQueue, devActiveTileOdd, groupSize1D + 1, NULL, NULL, &scanEvents[1]);
    nsecCount += QUtilityCL::getElapsedTime(scanEvents, clQueue);

    cl_int listSize, listSizeOdd;
    clQueue.enqueueReadBuffer(devActiveTile,    true, groupSize1D * sizeof(cl_int), sizeof(cl_int), &listSize);
    clQueue.enqueueReadBuffer(devActiveTileOdd, true, groupSize1D * sizeof(cl_int), sizeof(cl_int), &listSizeOdd);
    
    std::vector<cl::Event> scatterEvents(1);
    kerScatterNode.setArg(0, listSize);
    enqueue3DKernel(kerScatterNode, groupSize, &scatterEvents[0]);
    nsecCount += QUtilityCL::getElapsedTime(scatterEvents, clQueue);
    
    hostTileOffset.clear();
    hostTileOffset.push_back(0);
    hostTileOffset.push_back(listSize);
    hostTileOffset.push_back(listSize + listSizeOdd);
}

void QGCWidget::relabelPush(cl_long& nsecRelabelPush)
{
    if (hostTileOffset.empty()) return;

    cl::NDRange global(sizGlobal);
    cl::NDRange offset(0, 0, 0);
    std::vector<cl::Event> relabelPushEvents(hostTileOffset.size() - 1);
    for (cl_int i = 1; i < hostTileOffset.size(); i++)
    {
        cl_uint start = hostTileOffset[i - 1];
        cl_uint end = hostTileOffset[i];
        if (start == end) { relabelPushEvents[i - 1] = 0; continue; }
        
        const_cast<::size_t*>((const ::size_t*)global)[2] = end - start;
        const_cast<::size_t*>((const ::size_t*)offset)[2] = start;
        clQueue.enqueueNDRangeKernel(kerPushRelabel, offset, global, sizLocal, NULL, &relabelPushEvents[i - 1]);
    }
    nsecRelabelPush += QUtilityCL::getElapsedTime(relabelPushEvents, clQueue);
}

void QGCWidget::relabelPushFast(cl_long& nsecRelabelPush)
{
    if (hostTileOffset.empty()) return;
    
    cl::NDRange local( blockSize.s[0] >> 1, blockSize.s[1] * blockSize.s[2], 1);
    cl::NDRange global(blockSize.s[0] >> 1, blockSize.s[1] * blockSize.s[2], hostTileOffset.back());
    
    std::vector<cl::Event> fastRelabelEvents(2);
    for (cl_uint parity = 0; parity < 2; parity++)
    {
        kerFastRelabel.setArg(6, parity);
        clQueue.enqueueNDRangeKernel(kerFastRelabel, cl::NullRange, global, local, NULL, &fastRelabelEvents[parity]);
    }
    nsecRelabelPush += QUtilityCL::getElapsedTime(fastRelabelEvents, clQueue);
    
    ::size_t* localt  = const_cast<::size_t*>((const ::size_t*)local);
    ::size_t* globalt = const_cast<::size_t*>((const ::size_t*)global);

    cl_uint t;
    std::vector<cl::Event> fastPushEvents(2);

    globalt[1] = localt[1] = t = blockSize.s[1] * blockSize.s[2];
    globalt[0] = localt[0] = std::max<cl_uint>(1, clLocalSize / t);
    for (cl_uint parity = 0; parity < 2; parity++)
    {
        kerFastPushX.setArg(6, parity);
        clQueue.enqueueNDRangeKernel(kerFastPushX, cl::NullRange, global, local, NULL, &fastPushEvents[parity]);
    }
    nsecRelabelPush += QUtilityCL::getElapsedTime(fastPushEvents, clQueue);
    
    globalt[1] = localt[1] = t = blockSize.s[0] * blockSize.s[2];
    globalt[0] = localt[0] = std::max<cl_uint>(1, clLocalSize / t);
    for (cl_uint parity = 0; parity < 2; parity++)
    {
        kerFastPushY.setArg(6, parity);
        clQueue.enqueueNDRangeKernel(kerFastPushY, cl::NullRange, global, local, NULL, &fastPushEvents[parity]);
    }
    nsecRelabelPush += QUtilityCL::getElapsedTime(fastPushEvents, clQueue);
    
    if (volumeSize.s[2] > 1)
    {
        globalt[1] = localt[1] = blockSize.s[0] * blockSize.s[1];
        globalt[0] = localt[0] = 1;
        for (cl_uint parity = 0; parity < 2; parity++)
        {
            kerFastPushZ.setArg(6, parity);
            clQueue.enqueueNDRangeKernel(kerFastPushZ, cl::NullRange, global, local, NULL, &fastPushEvents[parity]);
        }
        nsecRelabelPush += QUtilityCL::getElapsedTime(fastPushEvents, clQueue);
    }
}

void QGCWidget::globalRelabel(cl_long& nsecInit)
{
    std::vector<cl::Event> initBFSEvents(1);
    clQueue.enqueueNDRangeKernel(kerInitGlobalRelabel, cl::NullRange, sizGlobal, sizLocal, NULL, &initBFSEvents[0]);
    nsecInit += QUtilityCL::getElapsedTime(initBFSEvents, clQueue);

    computeBFS(nsecInit);

    std::vector<cl::Event> globalRelabelEvents(hostTileOffset.size() - 1, 0);
    cl::NDRange global(sizGlobal);
    cl::NDRange offset(0, 0, 0);
    cl_int done = 0;
    int i = 0, delta = 1, last = hostTileOffset.size();
    while (!done)
    {
        done = 1;
        clQueue.enqueueWriteBuffer(devDone, true, 0, sizeof(done), &done);
        for (i += delta; i != last; i += delta)
        {
            cl_uint start = hostTileOffset[i - 1];
            cl_uint end = hostTileOffset[i];
            if (start == end) { globalRelabelEvents[i - 1] = 0; continue; }

            const_cast<::size_t*>((const ::size_t*)global)[2] = end - start;
            const_cast<::size_t*>((const ::size_t*)offset)[2] = start;
            clQueue.enqueueNDRangeKernel(kerGlobalRelabel, offset, global, sizLocal, NULL, &globalRelabelEvents[i - 1]);
        }
        nsecInit += QUtilityCL::getElapsedTime(globalRelabelEvents, clQueue);

        clQueue.enqueueReadBuffer(devDone, true, 0, sizeof(done), &done);
        last = hostTileOffset.size() - last;
        delta = -delta; // back and forth
    }
}

void QGCWidget::shot()
{
    const Ui::QGCPanel* ui = panel->getUI();
    glm::uvec2 viewSize(ui->spinBoxViewSizeX->value(), ui->spinBoxViewSizeY->value());
    QImage image(viewSize.x, viewSize.y, QImage::Format_ARGB32);
    QPainter painter(&image);
    painter.setCompositionMode(QPainter::CompositionMode_Source);  
    painter.fillRect(image.rect(), Qt::transparent);

    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.setBrush(Qt::gray);
    painter.setPen(Qt::transparent);

    int size = ui->spinBoxSize->value();
    if (ui->radioButtonShapeCircle->isChecked())
        painter.drawEllipse(QPoint(mousePosition.x, mousePosition.y), size / 2, size / 2);
    else if (ui->radioButtonShapeSquare->isChecked())
        painter.drawRect(mousePosition.x - size / 2, mousePosition.y - size / 2, size, size);
    else
        painter.drawRect(mousePosition.x - size / 2, mousePosition.y - size / 2, size, size);

    int bytesPerLine = image.bytesPerLine();
    for (int i = 0; i < viewSize.y; i++)
    {
        unsigned char* pMask = hostMask.data() + i * viewSize.x;
        unsigned int* pImage = (unsigned int*)(image.bits() + (viewSize.y - 1 - i) * bytesPerLine);
        for (int j = 0; j < viewSize.x; j++) pMask[j] = pImage[j] > 0;
    }
    clQueue.enqueueWriteBuffer(devMask, true, 0, hostMask.size() * sizeof(cl_uchar), hostMask.data());
    
    std::vector<cl::Event> visibilityEvents(1);
    cl_uint offset = getBrushingObject();
    computeVisibility(offset, &visibilityEvents[0]);
    cl_long nsecVisibility = QUtilityCL::getElapsedTime(visibilityEvents, clQueue);
    std::cout << " > GPU TIME: computeVisibility() - " << nsecVisibility * 1e-6 << std::endl;
    
    if (volumeSize.s[2] == 1)
        clQueue.enqueueCopyBufferToImage(devCut, imgCut2D, 0, imgOrigin, imgRegion);
    else
        clQueue.enqueueCopyBufferToImage(devCut, imgCut3D, 0, imgOrigin, imgRegion);

    QTime tComputeDistribution = QDateTime::currentDateTime().time();
    computeExtremum(offset);
    if (settings.enableLoggingTimeCost) QUtilityConsole::printTimeCost(tComputeDistribution.msecsTo(QDateTime::currentDateTime().time()), "computeExtremum()");
}

// 0. Infrastrctures
void QGCWidget::setProjection()
{
    const Ui::QGCPanel* ui = panel->getUI();
    glm::uvec2 viewSize(ui->spinBoxViewSizeX->value(), ui->spinBoxViewSizeY->value());
    float viewZNear = ui->doubleSpinBoxZNear->value();
    float viewZFar = ui->doubleSpinBoxZFar->value();
    if (ui->radioButtonPerspective->isChecked())
    {
        float viewFOVY = ui->spinBoxFOVY->value();
        gluPerspective(viewFOVY, (GLfloat)viewSize.x / viewSize.y, viewZNear, viewZFar);
    }
    else
    {
        unsigned int min = std::max<unsigned int>(1, std::min<unsigned int>(viewSize.x, viewSize.y));
        float viewOrtho = (float)ui->spinBoxOrthogonal->value() / ui->spinBoxOrthogonal->maximum();
        float width  = viewOrtho / min * viewSize.x;
        float height = viewOrtho / min * viewSize.y;
        glOrtho(-width, width, -height, height, viewZNear, viewZFar);
    }
}

cl_uint QGCWidget::getVoxelSize(QDataFormat format)
{
    switch(format)
    {
    case FORMAT_CHAR:
    case FORMAT_UCHAR:
        return cl_uint(1);
    case FORMAT_SHORT:
    case FORMAT_USHORT:
        return cl_uint(2);
    case FORMAT_INT:
    case FORMAT_UINT:
    case FORMAT_FLOAT:
        return cl_uint(4);
    default:
        return cl_uint(0);
    }
}

void QGCWidget::getIMVPMatrix(const glm::quat& quaternion)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    setProjection();
    
    glm::mat4 projectionMatrix;
    glGetFloatv(GL_PROJECTION_MATRIX, &projectionMatrix[0][0]);

    glPopMatrix();

    const Ui::QGCPanel* ui = panel->getUI();
    glm::vec3 viewTranslation(ui->doubleSpinBoxTranslationX->value(), ui->doubleSpinBoxTranslationY->value(), ui->doubleSpinBoxTranslationZ->value());
    glm::mat4 modelViewMatrix = glm::translate(glm::mat4(1.0f), viewTranslation) * glm::mat4_cast(quaternion);
    settings.inverseMVPMatrix = glm::inverse(projectionMatrix * modelViewMatrix);
}

// 1. Graph Cut
void QGCWidget::slotToolkitTypeChanged()
{
    if (error) return;

    const Ui::QGCPanel* ui = panel->getUI();
    if (ui->radioButtonModeNormal->isChecked())
        this->setCursor(Qt::ArrowCursor);
    else if (ui->radioButtonModeBrush->isChecked())
        this->setCursor(QCursor(QPixmap(QCoreApplication::applicationDirPath() + "Resources/images/brush.png").scaled(15, 15, Qt::IgnoreAspectRatio)));
    else
        this->setCursor(QCursor(QPixmap(QCoreApplication::applicationDirPath() + "Resources/images/eraser.png").scaled(15, 15, Qt::IgnoreAspectRatio)));

    update();
}

void QGCWidget::slotCutClicked()
{
    if (error) return;

    try
    {
        const Ui::QGCPanel* ui = panel->getUI();
        int countIterations = ui->spinBoxCountIterations->value();
        int totalIterations = ui->spinBoxTotalIterations->value();
        int printIterations = ui->spinBoxPrintIterations->value();
        int cutIterations = QUtilityCL::ceil(countIterations, ui->spinBoxCutIterations->value());
        int iterations = 0;

        cl_long currFlow = 0, initFlow = 0;
        cl_long nsecInit = 0, nsecRelabelPush = 0, nsecCount = 0, nsecCut = 0, nsecFlow = 0;

        if (ui->checkBoxCut->isChecked())
        {
            slotLoadCutClicked();
        }
        
        if (ui->checkBoxGraph->isChecked())
        {
            slotLoadGraphClicked();
        }
        else
        {
            slotModelClicked();
        }
        
        if (ui->radioButtonGlobalRelabel->isChecked())
        {
            globalRelabel(nsecInit);
        }
        else
        {
            clearTexture(devHeight, sizeof(cl_int));
        }
        
        std::cout.precision(5);
        std::cout.setf(std::ios::fixed, std:: ios::floatfield);
        
        if (ui->checkBoxPrint->isChecked())
        {
            reduceFlow(initFlow, nsecFlow);
        }

        QTime tGraphCut = QDateTime::currentDateTime().time();
        bool finished = false;
        while (!finished && iterations < totalIterations)
        {
            if (iterations % countIterations == 0)
            {
                countActiveBlock(nsecCount);
            }

            if (ui->radioButtonCutMethodJFCut->isChecked())
            {
                relabelPush(nsecRelabelPush);
            }
            else
            {
                relabelPushFast(nsecRelabelPush);
            }

            iterations++;

            if (ui->checkBoxPrint->isChecked())
            {
                if (iterations % printIterations == 0)
                {
                    reduceFlow(currFlow, nsecFlow);
                    std::cout << " > FLOW: computeCurrentFlow() - " << iterations << " - " << (initFlow - currFlow)  << std::endl;
                }
            }

            if (iterations % cutIterations == 0)
            {
                computeCut(nsecCut, finished);
            }
        }
        if (settings.enableLoggingTimeCost) QUtilityConsole::printTimeCost(tGraphCut.msecsTo(QDateTime::currentDateTime().time()), "graphCut() total - ");

        if (ui->checkBoxComputeTag->isChecked())
        {
            computeTag(nsecCut);
        }

        if (ui->checkBoxEnergy->isChecked())
        {
            clQueue.enqueueReadBuffer(devCut, true, 0, hostCut.size() * sizeof(cl_cut), hostCut.data());
            
            energyData   = 0;
            energySmooth = 0;

            if (volumeSize.s[2] == 1)
            {
                glm::ivec2 vSize(volumeSize.s[0], volumeSize.s[1]);
                glm::ivec2 vOffset(1, vSize.x);
                cl_int *ef = (cl_int*)hostExcessFlow.data();
                cl_ushort2 *c1 = (cl_ushort2*)hostCapacity1.data();
                cl_ushort2 *c2 = (cl_ushort2*)hostCapacity2.data();
                cl_cut *cut = hostCut.data();
                for (int y = 0; y < vSize.y; y++)
                    for (int x = 0; x < vSize.x; x++, cut++, ef++, c1++, c2++)
                    {
                        cl_int excessFlow = *ef;
                        cl_char object = cut->object;
                        if (excessFlow > 0)
                            energyData += object == 0 ? excessFlow : 0;
                        else
                            energyData += object == 0 ? 0 : -excessFlow;

                        if (object)
                        {
                            if (x < vSize.x - 1 && ((cut + vOffset.x)->object != object)) energySmooth += c1->s[0];
                            if (y < vSize.y - 1 && ((cut + vOffset.y)->object != object)) energySmooth += c1->s[1];
                            if (y > 0           && ((cut - vOffset.y)->object != object)) energySmooth += c2->s[0];
                            if (x > 0           && ((cut - vOffset.x)->object != object)) energySmooth += c2->s[1];
                        }
                    };
            }
            else
            {
                glm::ivec3 vSize(volumeSize.s[0], volumeSize.s[1], volumeSize.s[2]);
                glm::ivec3 vOffset(1, vSize.x, vSize.x * vSize.y);
                cl_long data(0), smooth(0);
                cl_int *ef = (cl_int*)hostExcessFlow.data();
                cl_uchar4 *c1 = (cl_uchar4*)hostCapacity1.data();
                cl_uchar4 *c2 = (cl_uchar4*)hostCapacity2.data();
                cl_cut *cut = hostCut.data();
                for (int z = 0; z < vSize.z; z++)
                    for (int y = 0; y < vSize.y; y++)
                        for (int x = 0; x < vSize.x; x++, cut++, ef++, c1++, c2++)
                        {
                            int index = x + vSize.x * (y + vSize.y * z);
                            cl_int excessFlow = *ef;
                            cl_char object = cut->object;
                            if (excessFlow > 0)
                                energyData += object == 0 ? excessFlow : 0;
                            else
                                energyData += object == 0 ? 0 : -excessFlow;

                            if (object)
                            {
                                if (x < vSize.x - 1 && (cut + vOffset.x)->object != object) energySmooth += c1->s[0];
                                if (y < vSize.y - 1 && (cut + vOffset.y)->object != object) energySmooth += c1->s[1];
                                if (z < vSize.z - 1 && (cut + vOffset.z)->object != object) energySmooth += c1->s[2];
                                if (z > 0           && (cut - vOffset.z)->object != object) energySmooth += c2->s[0];
                                if (y > 0           && (cut - vOffset.y)->object != object) energySmooth += c2->s[1];
                                if (x > 0           && (cut - vOffset.x)->object != object) energySmooth += c2->s[2];
                            }
                        };
            }

            std::cout << " > ENERGY: graphCut() data - " << energyData << ", smooth - " << energySmooth << std::endl;
        }
        
        std::cout << " > GPU TIME: graphCut() push / relabel - " << nsecRelabelPush * 1e-6 << ", cut - " << nsecCut * 1e-6 << std::endl;
        std::cout << " > GPU TIME: graphCut() init - " << nsecInit * 1e-6 << ", count - " << nsecCount * 1e-6 << ", flow - " << nsecFlow * 1e-6 << std::endl;
        std::cout << " > DATA: graphCut() itrs - " << iterations << std::endl;
        
        if (volumeSize.s[2] == 1)
            clQueue.enqueueCopyBufferToImage(devCut, imgCut2D, 0, imgOrigin, imgRegion);
        else
            clQueue.enqueueCopyBufferToImage(devCut, imgCut3D, 0, imgOrigin, imgRegion);

        repaint();
    }
    catch (QError& e)
    {
        switch (e.level())
        {
        case 0:
            break;
        case 1:
            std::cerr << " > LOG: " << std::endl << e.what();
            break;
        default:
            std::cerr << " > ERROR: " << std::endl << e.what();
            error = true;
            break;
        }
    }
    catch (cl::Error& e)
    {
        std::cerr << " > CALL STACK: " << std::endl << e.what();
        error = true;
    }
    catch (clogs::InternalError &e)
    {
        std::cerr << " > CLOGS: " << e.what() << std::endl;
        error = true;
    }
}

void QGCWidget::slotModelClicked()
{
    if (error) return;

    QTime tModel = QDateTime::currentDateTime().time();

    const Ui::QGCPanel* ui = panel->getUI();
    bool lazy = ui->radioButtonLazySnapping->isChecked();

    cl_long nsecCapacity = 0;
    computeCapacity(nsecCapacity, lazy);
    std::cout << " > GPU TIME: model() capacity - " << nsecCapacity * 1e-6 << std::endl;
    
    if (lazy)
    {
        cl_long nsecKMeans = 0;
        for (int i = 0; i < 2; i++) kmeans(nsecKMeans, i);
        std::cout << " > GPU TIME: model() k-means - " << nsecKMeans * 1e-6 << std::endl;

        cl_long nsecExcessFlow = 0;
        computeExcessFlowLazy(nsecExcessFlow);
        std::cout << " > GPU TIME: model() excess flow - " << nsecExcessFlow * 1e-6 << std::endl;
    }
    else
    {
        cl_uint2 sum = { 0, 0 };
        for (int i = 0; i < 2; i++)
        {
            computeHistogram(i);
            for (int j = 0; j < QGCSetting::sizeCutHistogram; j++)
                sum.s[i] += hostCutHistogram[j];
        }
        
        cl_long nsecExcessFlow = 0;
        computeExcessFlowBK(nsecExcessFlow, sum);
        std::cout << " > GPU TIME: model() excess flow - " << nsecExcessFlow * 1e-6 << std::endl;
    }
    
    if (ui->checkBoxEnergy->isChecked())
    {
        clQueue.enqueueReadBuffer(devExcessFlow, true, 0, hostExcessFlow.size(), hostExcessFlow.data());
        clQueue.enqueueReadBuffer(devCapacity1,  true, 0, hostCapacity1.size(),  hostCapacity1.data());
        clQueue.enqueueReadBuffer(devCapacity2,  true, 0, hostCapacity2.size(),  hostCapacity2.data());
    }

    if (settings.enableLoggingTimeCost) QUtilityConsole::printTimeCost(tModel.msecsTo(QDateTime::currentDateTime().time()), "model()");
}

void QGCWidget::slotClearClicked()
{
    if (error) return;

    QTime tInitializeTexture = QDateTime::currentDateTime().time();
    cl_uint offset = getBrushingObject();

    clearTexture(devCut, volumeSize1D, sizeof(cl_cut), offset * sizeof(cl_char), sizeof(cl_char));
    
    if (volumeSize.s[2] == 1)
        clQueue.enqueueCopyBufferToImage(devCut, imgCut2D, 0, imgOrigin, imgRegion);
    else
        clQueue.enqueueCopyBufferToImage(devCut, imgCut3D, 0, imgOrigin, imgRegion);

    if (settings.enableLoggingTimeCost) QUtilityConsole::printTimeCost(tInitializeTexture.msecsTo(QDateTime::currentDateTime().time()), "clearTexture()");

    QTime tComputeDistribution = QDateTime::currentDateTime().time();
    computeExtremum(offset);
    if (settings.enableLoggingTimeCost) QUtilityConsole::printTimeCost(tComputeDistribution.msecsTo(QDateTime::currentDateTime().time()), "computeExtremum()");
    
    repaint();
}

void QGCWidget::slotLoadGraphClicked()
{
    if (error) return;
    
    if (volumeSize.s[2] == 1)
    {
        if (!QIO::getFileData(dataFilePath + objectFileName + QGCSetting::extExcessFlow, hostExcessFlow.data(), hostExcessFlow.size())
         || !QIO::getFileData(dataFilePath + objectFileName + QGCSetting::extCapacity1,  hostCapacity1.data(),  hostCapacity1.size())
         || !QIO::getFileData(dataFilePath + objectFileName + QGCSetting::extCapacity2,  hostCapacity2.data(),  hostCapacity2.size()))
        {
            cl_uint4 nodeSize =
            {
                QUtilityCL::ceil(blockSize.s[0], volumeSize.s[0]),
                QUtilityCL::ceil(blockSize.s[1], volumeSize.s[1]),
                1, 1
            };
            cl_uint nodeSize1D = nodeSize.s[0] * nodeSize.s[1] * nodeSize.s[2];
            std::vector<cl_node_2d> node(nodeSize1D);
            if (!QIO::getFileData(dataFilePath + objectFileName + QGCSetting::extNode, node.data(), node.size() * sizeof(cl_node_2d)))
            {
                loadMFI();
            }
            else
            {
                cl_int *ef = (cl_int*)hostExcessFlow.data();
                cl_ushort2 *c1 = (cl_ushort2*)hostCapacity1.data(), *c2 = (cl_ushort2*)hostCapacity2.data();
                for (int y = 0; y < volumeSize.s[1]; y++)
                    for (int x = 0; x < volumeSize.s[0]; x++, ef++, c1++, c2++)
                    {
                        cl_node_2d* n = node.data() + x + nodeSize.s[0] * y;
                        ef[0] = n->excessFlow;
                        c1->s[0] = n->capacity[0];
                        c1->s[1] = n->capacity[1];
                        c2->s[0] = n->capacity[2];
                        c2->s[1] = n->capacity[3];
                    };
            }
            
            if (!QIO::saveFileData(dataFilePath + objectFileName + QGCSetting::extExcessFlow, hostExcessFlow.data(), hostExcessFlow.size())) return;
            if (!QIO::saveFileData(dataFilePath + objectFileName + QGCSetting::extCapacity1,  hostCapacity1.data(),  hostCapacity1.size()))  return;
            if (!QIO::saveFileData(dataFilePath + objectFileName + QGCSetting::extCapacity2,  hostCapacity2.data(),  hostCapacity2.size()))  return;
        }
    }
    else
    {
        if (!QIO::getFileData(dataFilePath + objectFileName + QGCSetting::extExcessFlow, hostExcessFlow.data(), hostExcessFlow.size())
         || !QIO::getFileData(dataFilePath + objectFileName + QGCSetting::extCapacity1,  hostCapacity1.data(),  hostCapacity1.size())
         || !QIO::getFileData(dataFilePath + objectFileName + QGCSetting::extCapacity2,  hostCapacity2.data(),  hostCapacity2.size()))
        {
            cl_uint4 nodeSize =
            {
                QUtilityCL::ceil(blockSize.s[0], volumeSize.s[0]),
                QUtilityCL::ceil(blockSize.s[1], volumeSize.s[1]),
                QUtilityCL::ceil(blockSize.s[2], volumeSize.s[2]),
                1
            };
            cl_uint nodeSize1D = nodeSize.s[0] * nodeSize.s[1] * nodeSize.s[2];
            std::vector<cl_node_3d> node(nodeSize1D);
            if (!QIO::getFileData(dataFilePath + objectFileName + QGCSetting::extNode, node.data(), node.size() * sizeof(cl_node_3d)))
            {
                loadMFI();
            }
            else
            {
                cl_int *ef = (cl_int*)hostExcessFlow.data();
                cl_uchar4 *c1 = (cl_uchar4*)hostCapacity1.data(), *c2 = (cl_uchar4*)hostCapacity2.data();
                for (int z = 0; z < volumeSize.s[2]; z++)
                    for (int y = 0; y < volumeSize.s[1]; y++)
                        for (int x = 0; x < volumeSize.s[0]; x++, ef++, c1++, c2++)
                        {
                            cl_node_3d* n = node.data() + x + nodeSize.s[0] * (y + nodeSize.s[1] * z);
                            ef[0] = n->excessFlow;
                            c1->s[0] = n->capacity[0];
                            c1->s[1] = n->capacity[1];
                            c1->s[2] = n->capacity[2];
                            c2->s[0] = n->capacity[3];
                            c2->s[1] = n->capacity[4];
                            c2->s[2] = n->capacity[5];
                        };
            }

            if (!QIO::saveFileData(dataFilePath + objectFileName + QGCSetting::extExcessFlow, hostExcessFlow.data(), hostExcessFlow.size())) return;
            if (!QIO::saveFileData(dataFilePath + objectFileName + QGCSetting::extCapacity1,  hostCapacity1.data(),  hostCapacity1.size()))  return;
            if (!QIO::saveFileData(dataFilePath + objectFileName + QGCSetting::extCapacity2,  hostCapacity2.data(),  hostCapacity2.size()))  return;
        }
    }

    clQueue.enqueueWriteBuffer(devExcessFlow, true, 0, hostExcessFlow.size(), hostExcessFlow.data());
    clQueue.enqueueWriteBuffer(devCapacity1,  true, 0, hostCapacity1.size(),  hostCapacity1.data());
    clQueue.enqueueWriteBuffer(devCapacity2,  true, 0, hostCapacity2.size(),  hostCapacity2.data());
    clearTexture(devHeight, sizeof(cl_int));
}

void QGCWidget::slotSaveGraphClicked()
{
    if (error) return;

    if (!hostExcessFlow.empty() && !hostCapacity1.empty() && !hostCapacity2.empty())
    {
        if (!QIO::saveFileData(dataFilePath + objectFileName + QGCSetting::extExcessFlow, hostExcessFlow.data(), hostExcessFlow.size())) return;
        if (!QIO::saveFileData(dataFilePath + objectFileName + QGCSetting::extCapacity1,  hostCapacity1.data(),  hostCapacity1.size()))  return;
        if (!QIO::saveFileData(dataFilePath + objectFileName + QGCSetting::extCapacity2,  hostCapacity2.data(),  hostCapacity2.size()))  return;

        saveMFI();
    }
}

void QGCWidget::slotLoadGradientClicked()
{
    if (error) return;

    std::vector<glm::vec4> bufferFeature(volumeSize1D);
    if (!QIO::getFileData(dataFilePath + gradientFileName, bufferFeature.data(), bufferFeature.size() * sizeof(glm::vec4))) return;

    float scale = gradientMax == 0.0f ? 0.0f : std::numeric_limits<unsigned char>::max() / gradientMax;
    std::vector<cl_uchar4> buffer(volumeSize1D);
    for (int i = 0; i < volumeSize1D; i++)
    {
        glm::vec4 f = bufferFeature[i] * scale;
        cl_uchar *t = buffer[i].s;
        t[0] = f.x; t[1] = f.y;
        t[2] = f.z; t[3] = f.w;
    }

    if (volumeSize.s[2] == 1)
        clQueue.enqueueWriteImage(imgFeature2D, true, imgOrigin, imgRegion, 0, 0, buffer.data());
    else
        clQueue.enqueueWriteImage(imgFeature3D, true, imgOrigin, imgRegion, 0, 0, buffer.data());
}

void QGCWidget::slotSaveGradientClicked()
{
    if (error) return;

    // load volume data
    std::vector<float> bufferVolume(volumeSize1D);
    cl_uint voxelSize = getVoxelSize(format);
    if (!QIO::getFileData(dataFilePath + objectFileName, bufferVolume.data(), voxelSize * volumeSize1D))
        throw QError(1, Q_LOGIC_ERROR, "opening raw data failed");

    std::vector<glm::vec4> bufferGradient(volumeSize1D);
    for (int i = volumeSize1D - 1; i >= 0; i--)
        bufferGradient[i].w = bufferVolume[i];

    // compute gradient
    int kernelR = QGCSetting::sizeFilter / 2;
    int kernelS = kernelR * 2 + 1;
    std::vector<float> kernel(kernelS * kernelS * kernelS);
    std::vector<float> bufferTemp(volumeSize1D);
    float* k = kernel.data() + kernelR + kernelS * (kernelR + kernelS * kernelR);
    float* gaussian0 = QGCSetting::filterGaussian0 + kernelR;
    float* gaussian1 = QGCSetting::filterGaussian1 + kernelR;

    std::cerr << " > WAIT: compute gradient - x direction " << volumeSize.s[2] << " slices." << std::endl;
    for (int z = -kernelR; z <= kernelR; z++)
        for (int y = -kernelR; y <= kernelR; y++)
            for (int x = -kernelR; x <= kernelR; x++)
                k[x + kernelS * (y + kernelS * z)] = gaussian1[x] * gaussian0[y] * gaussian0[z];

    std::cerr << " > WAIT: ";
    QUtilityMath::convolution_3(bufferTemp.data(), bufferVolume.data(), kernel.data(), volumeSize.s[0], volumeSize.s[1], volumeSize.s[2], kernelR);
    std::cerr << std::endl;

    for (int i = 0; i < volumeSize1D; i++)
        bufferGradient[i].x = bufferTemp[i];

    std::cerr << " > WAIT: compute gradient - y direction " << volumeSize.s[2] << " slices." << std::endl;
    for (int z = -kernelR; z <= kernelR; z++)
        for (int y = -kernelR; y <= kernelR; y++)
            for (int x = -kernelR; x <= kernelR; x++)
                k[x + kernelS * (y + kernelS * z)] = gaussian0[x] * gaussian1[y] * gaussian0[z];

    std::cerr << " > WAIT: ";
    QUtilityMath::convolution_3(bufferTemp.data(), bufferVolume.data(), kernel.data(), volumeSize.s[0], volumeSize.s[1], volumeSize.s[2], kernelR);
    std::cerr << std::endl;

    for (int i = 0; i < volumeSize1D; i++)
        bufferGradient[i].y = bufferTemp[i];

    if (volumeSize.s[2] > 1)
    {
        std::cerr << " > WAIT: compute gradient - z direction " << volumeSize.s[2] << " slices." << std::endl;
        for (int z = -kernelR; z <= kernelR; z++)
            for (int y = -kernelR; y <= kernelR; y++)
                for (int x = -kernelR; x <= kernelR; x++)
                    k[x + kernelS * (y + kernelS * z)] = gaussian0[x] * gaussian0[y] * gaussian1[z];

        std::cerr << " > WAIT: ";
        QUtilityMath::convolution_3(bufferTemp.data(), bufferVolume.data(), kernel.data(), volumeSize.s[0], volumeSize.s[1], volumeSize.s[2], kernelR);
        std::cerr << std::endl;

        for (int i = 0; i < volumeSize1D; i++)
            bufferGradient[i].z = bufferTemp[i];
    }

    glm::vec4* gradient = bufferGradient.data();
    gradientMin = std::numeric_limits<float>::max();
    gradientMax = std::numeric_limits<float>::lowest();
    for (int i = 0; i < volumeSize1D; i++)
    {
        float length = glm::length(glm::vec3(gradient->x, gradient->y, gradient->z));
        gradientMin = std::min<float>(gradientMin, length);
        gradientMax = std::max<float>(gradientMax, length);
        gradient++;
    }

    gradientFileName = objectFileName + QGCSetting::extGradient;
    if (!QIO::saveFileData(dataFilePath + gradientFileName, bufferGradient.data(), bufferGradient.size() * sizeof(glm::vec4)))
        throw QError(1, Q_LOGIC_ERROR, "saving gradient failed");

    dataFileName = dataFilePath + gradientFileName + QGCSetting::extDat;
    saveDataFile(dataFileName);
}

void QGCWidget::slotLoadFeatureClicked()
{
    if (error) return;

    std::vector<cl_uchar4> bufferColor(volumeSize1D);
    if (QIO::getFileData(dataFilePath + objectFileName + QGCSetting::extColor, bufferColor.data(), bufferColor.size() * sizeof(cl_uchar4)))
    {
        if (volumeSize.s[2] == 1)
            clQueue.enqueueWriteImage(imgFeature2D, true, imgOrigin, imgRegion, 0, 0, bufferColor.data());
        else
            clQueue.enqueueWriteImage(imgFeature3D, true, imgOrigin, imgRegion, 0, 0, bufferColor.data());
    }
    else
    {
        std::vector<glm::vec4> bufferFeature(volumeSize1D);
        if (!QIO::getFileData(dataFilePath + curvatureFileName, bufferFeature.data(), bufferFeature.size() * sizeof(glm::vec4))) return;
        
        float curvatureAbs = std::max<float>(std::abs(curvatureMin), std::abs(curvatureMax));
        float curvatureScale = curvatureAbs == 0.0f ? 0.0f : std::numeric_limits<unsigned char>::max() / curvatureAbs * 0.5f;
        float gradientScale = gradientMax == 0.0f ? 0.0f : std::numeric_limits<unsigned char>::max() / gradientMax;
        glm::vec4 scale(curvatureScale, curvatureScale, gradientScale, std::numeric_limits<unsigned char>::max());
        std::vector<cl_uchar4> buffer(volumeSize1D);
        for (int i = 0; i < volumeSize1D; i++)
        {
            glm::vec4 f = bufferFeature[i] * scale;
            cl_uchar *t = buffer[i].s;
            t[0] = f.x; t[1] = f.y;
            t[2] = f.z; t[3] = f.w;
        }
        if (volumeSize.s[2] == 1)
            clQueue.enqueueWriteImage(imgFeature2D, true, imgOrigin, imgRegion, 0, 0, buffer.data());
        else
            clQueue.enqueueWriteImage(imgFeature3D, true, imgOrigin, imgRegion, 0, 0, buffer.data());
    }
}

void QGCWidget::slotSaveFeatureClicked()
{
    if (error) return;

    // load gradient data
    std::vector<glm::vec4> bufferGradient(volumeSize1D);
    if (!QIO::getFileData(dataFilePath + gradientFileName, bufferGradient.data(), bufferGradient.size() * sizeof(glm::vec4))) return;

    int kernelR = QGCSetting::sizeFilter / 2;
    int kernelS = kernelR * 2 + 1;
    std::vector<glm::mat3x3> kernel(kernelS * kernelS * kernelS);
    float* gaussian0 = QGCSetting::filterGaussian0 + kernelR;
    float* gaussian1 = QGCSetting::filterGaussian1 + kernelR;
    float* gaussian2 = QGCSetting::filterGaussian2 + kernelR;

    glm::mat3x3* k = kernel.data() + kernelR + kernelS * (kernelR + kernelS * kernelR);
    for (int z = -kernelR; z <= kernelR; z++)
        for (int y = -kernelR; y <= kernelR; y++)
            for (int x = -kernelR; x <= kernelR; x++)
            {
                glm::mat3x3* kt = k + x + kernelS * (y + kernelS * z);
                (*kt)[0][0] = gaussian2[x] * gaussian0[y] * gaussian0[z];
                (*kt)[1][1] = gaussian0[x] * gaussian2[y] * gaussian0[z];
                (*kt)[2][2] = gaussian0[x] * gaussian0[y] * gaussian2[z];

                (*kt)[0][1] = (*kt)[1][0] = gaussian1[x] * gaussian1[y] * gaussian0[z];
                (*kt)[1][2] = (*kt)[2][1] = gaussian0[x] * gaussian1[y] * gaussian1[z];
                (*kt)[2][0] = (*kt)[0][2] = gaussian1[x] * gaussian0[y] * gaussian1[z];
            };

    std::cerr << " > WAIT: compute curvature - " << volumeSize.s[2] << " slices." << std::endl;
    std::cerr << " > WAIT: ";
    float epsilon = 5e-3;
    std::vector<glm::vec4> bufferCurvature(volumeSize1D);
    glm::vec4* gradient = bufferGradient.data();
    glm::vec4* curvature = bufferCurvature.data();
    curvatureMin = std::numeric_limits<float>::max();
    curvatureMax = std::numeric_limits<float>::lowest();
    for (int z = 0; z < volumeSize.s[2]; z++)
    {
        std::cerr << ".";
        for (int y = 0; y < volumeSize.s[1]; y++)
            for (int x = 0; x < volumeSize.s[0]; x++)
            {
                glm::vec3 normal(-gradient->x, -gradient->y, -gradient->z);
                float length = glm::length(normal);
                float scale = length < epsilon ? 0.0f : 1.0f / length;
                normal *= scale;

                glm::mat3x3 p = glm::mat3x3(1.0f) - glm::mat3x3(normal * normal.x, normal * normal.y, normal * normal.z);
                glm::mat3x3 h = glm::mat3x3(0.0f);
                for (int dz = -kernelR; dz <= kernelR; dz++)
                    for (int dy = -kernelR; dy <= kernelR; dy++)
                        for (int dx = -kernelR; dx <= kernelR; dx++)
                        {
                            int xt = glm::clamp<int>(x + dx, 0, volumeSize.s[0] - 1);
                            int yt = glm::clamp<int>(y + dy, 0, volumeSize.s[1] - 1);
                            int zt = glm::clamp<int>(z + dz, 0, volumeSize.s[2] - 1);
                            h += bufferGradient[xt + volumeSize.s[0] * (yt + volumeSize.s[1] * zt)].w * k[-(dx + kernelS * (dy + kernelS * dz))];
                        };

                glm::mat3x3 gt = -p * h * p * scale;
                glm::mat3x3 gf = gt * glm::transpose(gt);
                float t = gt[0][0] + gt[1][1] + gt[2][2];
                float f = std::sqrt(gf[0][0] + gf[1][1] + gf[2][2]);
                float r = std::sqrt(2 * f * f - t * t);
                float k1 = (t + r) / 2;
                float k2 = (t - r) / 2;

                curvatureMin = std::min<float>(curvatureMin, std::min<float>(k1, k2));
                curvatureMax = std::max<float>(curvatureMax, std::max<float>(k1, k2));

                curvature->x = k1;
                curvature->y = k2;
                curvature->z = length;
                curvature->w = gradient->w;

                gradient++;
                curvature++;
            };
    };
    std::cerr << std::endl;

    curvatureFileName = objectFileName + QGCSetting::extCurvature;
    if (!QIO::saveFileData(dataFilePath + curvatureFileName, bufferCurvature.data(), bufferCurvature.size() * sizeof(glm::vec4))) return;

    dataFileName = dataFilePath + curvatureFileName + QGCSetting::extDat;
    saveDataFile(dataFileName);
}

void QGCWidget::slotLoadCutClicked()
{
    if (error) return;

    if (!QIO::getFileData(dataFilePath + objectFileName + QGCSetting::extCut, hostCut.data(), hostCut.size() * sizeof(cl_cut))) return;

    clQueue.enqueueWriteBuffer(devCut, true, 0, hostCut.size() * sizeof(cl_cut), hostCut.data());

    if (volumeSize.s[2] == 1)
        clQueue.enqueueCopyBufferToImage(devCut, imgCut2D, 0, imgOrigin, imgRegion);
    else
        clQueue.enqueueCopyBufferToImage(devCut, imgCut3D, 0, imgOrigin, imgRegion);

    for (int i = 0; i < QGCSetting::sizeTexture; i++)
        computeExtremum(i);

    repaint();
}

void QGCWidget::slotSaveCutClicked()
{
    if (error) return;

    clQueue.enqueueReadBuffer(devCut, true, 0, hostCut.size() * sizeof(cl_cut), hostCut.data());
    QIO::saveFileData(dataFilePath + objectFileName + QGCSetting::extCut, hostCut.data(), hostCut.size() * sizeof(cl_cut));
}

void QGCWidget::slotExportClicked()
{
    if (error) return;

    const Ui::QGCPanel* ui = panel->getUI();
    if (ui->radioButtonRayCastingObjectAll->isChecked()) return;

    clQueue.enqueueReadBuffer(devCut, true, 0, hostCut.size() * sizeof(cl_cut), hostCut.data());

    QString name;
    int offset = 0;
    if (ui->radioButtonRayCastingObjectFore->isChecked())
    {
        name = "foreground";
        offset = 0;
    }
    else if (ui->radioButtonRayCastingObjectBack->isChecked())
    {
        name = "background";
        offset = 1;
    }
    else if (ui->radioButtonRayCastingObjectCut->isChecked())
    {
        name = "object";
        offset = 2;
    }
    else
    {
        name = "tag";
        offset = 3;
    }

    QImage source(volumeSize.s[0], volumeSize.s[1], QImage::Format_ARGB32);
    for (int i = 0; i < volumeSize.s[2]; i++)
    {
        source.fill(Qt::white);
        cl_char* cut = (cl_char*)hostCut.data() + (i * volumeSize.s[0] * volumeSize.s[1]) * sizeof(cl_cut) + offset;
        for (int y = 0; y < volumeSize.s[1]; y++)
            for (int x = 0; x < volumeSize.s[0]; x++, cut += sizeof(cl_cut))
                if (*cut) source.setPixel(x, y, qRgb(0, 0, 0));
        
        QString fileName = volumeSize.s[2] == 1 ?
            QString("%1%2-%3.bmp").arg(dataFilePath.c_str()).arg(objectFileName.c_str()).arg(name).toLocal8Bit() :
            QString("%1%2-%3-%4.bmp").arg(dataFilePath.c_str()).arg(objectFileName.c_str()).arg(name).arg(i + 1, QString::number(volumeSize.s[2]).size(), 10, QChar('0')).toLocal8Bit();
        source.save(fileName);
    }
}

void QGCWidget::enqueue3DKernel(const cl::Kernel& kernel, cl::Event* event)
{
    enqueue3DKernel(kernel, volumeSize, event);
}

void QGCWidget::enqueue3DKernel(const cl::Kernel& kernel, cl_uint4 kernelSize, cl::Event* event)
{
    cl_int status = CL_SUCCESS;

    const Ui::QGCPanel* ui = panel->getUI();
    cl::NDRange local(ui->spinBoxLocalSize3DX->value(), ui->spinBoxLocalSize3DY->value(), ui->spinBoxLocalSize3DZ->value());
    cl::NDRange global = QUtilityCL::getGlobalSize(local, kernelSize);
    clQueue.enqueueNDRangeKernel(kernel, NULL, global, local, NULL, event);
}

void QGCWidget::clearTexture(const cl::Buffer& texture, cl_uint textureStride, cl::Event* event)
{
    clearTexture(texture, volumeSize1D, textureStride, event);
}

void QGCWidget::clearTexture(const cl::Buffer& texture, cl_uint textureEnd, cl_uint textureStride, cl::Event* event)
{
    clearTexture(texture, textureEnd, textureStride, 0, textureStride, event);
}

void QGCWidget::clearTexture(const cl::Buffer& texture, cl_uint textureEnd, cl_uint textureStride, cl_uint clearOffset, cl_uint clearSize, cl::Event* event)
{
    clearTexture(texture, 0, textureEnd, textureStride, clearOffset, clearSize, event);
}

void QGCWidget::clearTexture(const cl::Buffer& texture, cl_uint textureStart, cl_uint textureEnd, cl_uint textureStride, cl_uint clearOffset, cl_uint clearSize, cl::Event* event)
{
    cl_uint textureOffset = textureStart;
    cl_uint textureSize = textureEnd - textureStart;
    if (textureSize == 0)
        throw QError(1, Q_LOGIC_ERROR, "size is zero.");
    const Ui::QGCPanel* ui = panel->getUI();
    cl::NDRange local(ui->spinBoxLocalSize1DX->value());
    cl::NDRange global(QUtilityCL::ceil(local, textureSize));
    kerClear.setArg(0, texture);
    kerClear.setArg(1, textureEnd);
    kerClear.setArg(2, textureStride);
    kerClear.setArg(3, clearOffset);
    kerClear.setArg(4, clearSize);
    clQueue.enqueueNDRangeKernel(kerClear, cl::NullRange, global, local, NULL, event);
}

void QGCWidget::computeBFS(cl_long& nsecBFS)
{
    cl_uint maxSizeBFS = std::max(groupSize.s[0], std::max(groupSize.s[1], groupSize.s[2]));
    cl_uint size = 0, jumpSizeBFS = 1;
    for (; jumpSizeBFS < maxSizeBFS; jumpSizeBFS <<= 1, size++);

    std::vector<cl::Event> jumpFloodBFSEvents(size << 1);
    for (int i = size - 1; i >= 0; i--)
    {
        jumpSizeBFS = 1 << i;
        kerBFSJumpFlooding.setArg(2, jumpSizeBFS);
		enqueue3DKernel(kerBFSJumpFlooding, groupSize, &jumpFloodBFSEvents[(i << 1) + 0]);
        enqueue3DKernel(kerBFSJumpFlooding, groupSize, &jumpFloodBFSEvents[(i << 1) + 1]);
    }
    nsecBFS += QUtilityCL::getElapsedTime(jumpFloodBFSEvents, clQueue);

    cl_int maximum = 0;
    reduceHistogram(maximum, nsecBFS);
    if (maximum == 2 * QGCSetting::cl_shift_2d.w || maximum == 3 * QGCSetting::cl_shift_3d.w)
        throw QError(1, Q_LOGIC_ERROR, "no labels.");

    cl_int distSize = maximum + 2;
    if (distSize > QGCSetting::sizeDistHistogram)
        throw QError(1, Q_LOGIC_ERROR, "large distance is not supported.");

    std::vector<cl::Event> scanBFSEvents(4);
    clearTexture(devBFSHistogram, distSize, sizeof(cl_int), &scanBFSEvents[0]);
    enqueue3DKernel(kerBFSHistogram, groupSize, &scanBFSEvents[1]);
    clScan->enqueue(clQueue, devBFSHistogram, distSize, NULL, NULL, &scanBFSEvents[2]);
    enqueue3DKernel(kerBFSMapping, groupSize, &scanBFSEvents[3]);
    nsecBFS += QUtilityCL::getElapsedTime(scanBFSEvents, clQueue);

    hostTileOffset.resize(distSize);
    clQueue.enqueueReadBuffer(devBFSHistogram, true, 0, distSize * sizeof(cl_int), hostTileOffset.data());
}

void QGCWidget::computeVisibility(cl_uint offset, cl::Event* event)
{
    const Ui::QGCPanel* ui = panel->getUI();
    cl_uint sampleNumber = ui->spinBoxSampleNumber->value();
    cl_float sampleScale = ui->spinBoxSampleScale->value();
    cl_float sampleRatio = ui->doubleSpinBoxSampleRatio->value();
    cl_float windowWidth = (float)ui->verticalSliderWindowWidth->value() / ui->verticalSliderWindowWidth->maximum();
    cl_float windowLevel = (float)ui->verticalSliderWindowLevel->value() / ui->verticalSliderWindowLevel->maximum();
    cl_float alpha = (float)ui->spinBoxOpacity->value() / ui->spinBoxOpacity->maximum();
    cl_uint4 viewSize = { ui->spinBoxViewSizeX->value(), ui->spinBoxViewSizeY->value(), 0, 0 };
    cl::NDRange local(ui->spinBoxLocalSize2DX->value(), ui->spinBoxLocalSize2DY->value());
    cl::NDRange global(QUtilityCL::ceil(local, viewSize));
    cl::Kernel& kernel = ui->radioButtonNormal->isChecked() ? kerRenderNormal[2] : (ui->radioButtonPreIntegration->isChecked() ? kerRenderPreInt[2] : kerRenderFeature[2]);
    kernel.setArg(0,  settings.inverseMVPMatrix);
    kernel.setArg(9,  sampleNumber);
    kernel.setArg(10, sampleRatio);
    kernel.setArg(11, sampleScale);
    kernel.setArg(13, windowWidth);
    kernel.setArg(14, windowLevel);
    kernel.setArg(15, offset);
    kernel.setArg(16, alpha);
    clQueue.enqueueNDRangeKernel(kernel, cl::NullRange, global, local, NULL, event);
}

void QGCWidget::computeExtremum(cl_uint offset)
{
    computeHistogram(offset);

    hostMinMask[offset] = 1.0f;
    hostMaxMask[offset] = 0.0f;
    for (int i = 0; i < QGCSetting::sizeCutHistogram; i++)
        if (hostCutHistogram[i] > 0)
        {
            float value = (float)i / (QGCSetting::sizeCutHistogram - 1);
            hostMinMask[offset] = std::min<float>(value, hostMinMask[offset]);
            hostMaxMask[offset] = std::max<float>(value, hostMaxMask[offset]);
        };
}

void QGCWidget::computeHistogram(cl_uint offset)
{
    clearTexture(devCutHistogram, QGCSetting::sizeCutHistogram, sizeof(cl_uint));

    cl_int status = CL_SUCCESS;

    const Ui::QGCPanel* ui = panel->getUI();
    glm::vec4 weight = glm::normalize(glm::vec4(ui->doubleSpinBoxWeightX->value(), ui->doubleSpinBoxWeightY->value(), ui->doubleSpinBoxWeightZ->value(), ui->doubleSpinBoxWeightW->value()));
    kerCutHistogram.setArg(2, offset);
    kerCutHistogram.setArg(6, weight);
    enqueue3DKernel(kerCutHistogram);
    clQueue.enqueueReadBuffer(devCutHistogram, true, 0, QGCSetting::sizeCutHistogram * sizeof(cl_uint), hostCutHistogram.data());
}

void QGCWidget::computeCapacity(cl_long& nsecCapacity, bool lazy)
{
    cl_int status = CL_SUCCESS;

    const Ui::QGCPanel* ui = panel->getUI();
    glm::vec4 weight = glm::normalize(glm::vec4(ui->doubleSpinBoxWeightX->value(), ui->doubleSpinBoxWeightY->value(), ui->doubleSpinBoxWeightZ->value(), ui->doubleSpinBoxWeightW->value()));
    
    cl::Kernel& kernel = lazy ? kerCapacityLazy : kerCapacityBK;
    kernel.setArg(5, weight);
    if (!lazy)
    {
        cl_float sigma = ui->doubleSpinBoxBKNeighbor->value();
        kernel.setArg(6, sigma);
    }
    else
    {
        cl_float lambda = ui->doubleSpinBoxLazyNeighbor->value();
        kernel.setArg(6, lambda);
    }

    std::vector<cl::Event> capacityEvents(1);
    enqueue3DKernel(kernel, &capacityEvents[0]);
    nsecCapacity += QUtilityCL::getElapsedTime(capacityEvents, clQueue);
}

void QGCWidget::computeExcessFlowBK(cl_long& nsecExcessFlow, cl_uint2 sum)
{
    const Ui::QGCPanel* ui = panel->getUI();
    glm::vec4 weight = glm::normalize(glm::vec4(ui->doubleSpinBoxWeightX->value(), ui->doubleSpinBoxWeightY->value(), ui->doubleSpinBoxWeightZ->value(), ui->doubleSpinBoxWeightW->value()));
    cl_float lambda = ui->doubleSpinBoxBKTerminal->value();
    cl_uint k = ui->spinBoxK->value();
    kerExcessFlowBK.setArg(7, lambda);
    kerExcessFlowBK.setArg(8, sum);
    kerExcessFlowBK.setArg(9, weight);
    
    std::vector<cl::Event> excessFlowEvents(1);
    enqueue3DKernel(kerExcessFlowBK, &excessFlowEvents[0]);
    nsecExcessFlow += QUtilityCL::getElapsedTime(excessFlowEvents, clQueue);
}

void QGCWidget::computeExcessFlowLazy(cl_long& nsecExcessFlow)
{
    const Ui::QGCPanel* ui = panel->getUI();
    glm::vec4 weight = glm::normalize(glm::vec4(ui->doubleSpinBoxWeightX->value(), ui->doubleSpinBoxWeightY->value(), ui->doubleSpinBoxWeightZ->value(), ui->doubleSpinBoxWeightW->value()));
    cl_float lambda = ui->doubleSpinBoxLazyTerminal->value();
    cl_uint k = ui->spinBoxK->value();
    kerExcessFlowLazy.setArg(6, lambda);
    kerExcessFlowLazy.setArg(7, k);
    kerExcessFlowLazy.setArg(8, weight);

    std::vector<cl::Event> excessFlowEvents(1);
    enqueue3DKernel(kerExcessFlowLazy, &excessFlowEvents[0]);
    nsecExcessFlow += QUtilityCL::getElapsedTime(excessFlowEvents, clQueue);
}

void QGCWidget::computeCut(cl_long& nsecCut, bool& finished)
{
    std::vector<cl::Event> initCutEvents(1);
    clQueue.enqueueNDRangeKernel(kerInitCut, NULL, sizGlobal, sizLocal, NULL, &initCutEvents[0]);
    nsecCut += QUtilityCL::getElapsedTime(initCutEvents, clQueue);
    
    computeBFS(nsecCut);
    
    std::vector<cl::Event> cutEvents(hostTileOffset.size() - 1);
    cl::NDRange global(sizGlobal);
    cl::NDRange offset(0, 0, 0);
    cl_int2 done = { 0, 0 };
    int i = 0, delta = 1, last = hostTileOffset.size();
    while (!done.s[0] && !done.s[1])
    {
        done.s[0] = 1;
        done.s[1] = 0;
        clQueue.enqueueWriteBuffer(devDone, true, 0, sizeof(cl_int2), &done);
        for (i += delta; i != last; i += delta)
        {
            cl_uint start = hostTileOffset[i - 1];
            cl_uint end = hostTileOffset[i];
			if (start == end) { cutEvents[i - 1] = 0; continue; }
                        
			const_cast<::size_t*>((const ::size_t*)global)[2] = end - start;
			const_cast<::size_t*>((const ::size_t*)offset)[2] = start;
			clQueue.enqueueNDRangeKernel(kerComputeCut, offset, global, sizLocal, NULL, &cutEvents[i - 1]);
        }
        nsecCut += QUtilityCL::getElapsedTime(cutEvents, clQueue);

        clQueue.enqueueReadBuffer(devDone, true, 0, sizeof(cl_int2), &done);
        last = hostTileOffset.size() - last;
        delta = -delta; // back and forth
    }
    
    finished = !done.s[1];
}

void QGCWidget::computeTag(cl_long& nsecTag)
{
    std::vector<cl::Event> initTagEvents(1);
    clQueue.enqueueNDRangeKernel(kerInitTag, cl::NullRange, sizGlobal, sizLocal, NULL, &initTagEvents[0]);
    nsecTag += QUtilityCL::getElapsedTime(initTagEvents, clQueue);

    computeBFS(nsecTag);

    std::vector<cl::Event> tagEvents(hostTileOffset.size() - 1);
    cl::NDRange global(sizGlobal);cl::NDRange offset(0, 0, 0);
    cl_int done = 0;
    int i = 0, delta = 1, last = hostTileOffset.size();
    while (!done)
    {
        done = 1;
        clQueue.enqueueWriteBuffer(devDone, true, 0, sizeof(done), &done);

        for (i += delta; i != last; i += delta)
        {
            cl_uint start = hostTileOffset[i - 1];
            cl_uint end = hostTileOffset[i];
            if (start == end) { tagEvents[i - 1] = 0; continue; }

            const_cast<::size_t*>((const ::size_t*)global)[2] = end - start;
            const_cast<::size_t*>((const ::size_t*)offset)[2] = start;
            clQueue.enqueueNDRangeKernel(kerComputeTag, offset, global, sizLocal, NULL, &tagEvents[i - 1]);
        }
        nsecTag += QUtilityCL::getElapsedTime(tagEvents, clQueue);

        clQueue.enqueueReadBuffer(devDone, true, 0, sizeof(done), &done);
        last = hostTileOffset.size() - last;
        delta = -delta; // back and forth
    }
}

void QGCWidget::reduceFlow(cl_long& sum, cl_long& nsecFlow)
{
    std::vector<cl::Event> reduceEvents(1);
    clQueue.enqueueNDRangeKernel(kerReduceFlow, cl::NullRange, cl::NDRange(clGroupSize * flowBlocks), cl::NDRange(clGroupSize), NULL, &reduceEvents[0]);
    nsecFlow += QUtilityCL::getElapsedTime(reduceEvents, clQueue);

    clQueue.enqueueReadBuffer(devFlow, true, 0, hostFlow.size() * sizeof(cl_int), hostFlow.data());
    sum = 0;
    for (auto i = hostFlow.begin(); i != hostFlow.end(); i++)
        sum += *i;
}

void QGCWidget::reduceHistogram(cl_int& maximum, cl_long& nsecnsecHistogram)
{
    std::vector<cl::Event> reduceEvents(1);
    clQueue.enqueueNDRangeKernel(kerReduceHistogram, cl::NullRange, cl::NDRange(clGroupSize * histBlocks), cl::NDRange(clGroupSize), NULL, &reduceEvents[0]);
    nsecnsecHistogram += QUtilityCL::getElapsedTime(reduceEvents, clQueue);

    clQueue.enqueueReadBuffer(devHistogram, true, 0, hostHistogram.size() * sizeof(cl_int), hostHistogram.data());
    maximum = 0;
    for (auto i = hostHistogram.begin(); i != hostHistogram.end(); i++)
        maximum = std::max<int>(maximum, *i);
}

void QGCWidget::loadMFI()
{

}

void QGCWidget::saveMFI()
{
    MFI* mfi = (MFI*)malloc(sizeof(MFI));

    mfi->dimension         = volumeSize.s[2] == 1 ? 2 : 3;
    mfi->connectivity      = volumeSize.s[2] == 1 ? 4 : 6;
    mfi->width             = volumeSize.s[0];
    mfi->height            = volumeSize.s[1];
    mfi->depth             = volumeSize.s[2];
    mfi->maxflow           = energyData + energySmooth;
    mfi->symmetric_arcs    = true;

    for (int i = 0; i < 4096; i++)
    { 
        mfi->metadata[i]   = 0; 
    }

    mfi->active_count      = 0;
    mfi->type_terminal_cap = MFI::TYPE_UINT32;
    mfi->type_neighbor_cap = volumeSize.s[2] == 1 ? MFI::TYPE_UINT16 : MFI::TYPE_UINT8;

    mfi->cap_source        = 0;
    mfi->cap_sink          = 0;
    mfi->cap_neighbor      = 0;
    mfi->active_mask       = 0;

    int num_nodes = mfi->width * mfi->height * mfi->depth;

    int table_sizeof[3] = { sizeof(uint8_t), sizeof(uint16_t), sizeof(uint32_t) };

    int sizeof_type_terminal_cap = table_sizeof[mfi->type_terminal_cap];
    int sizeof_type_neighbor_cap = table_sizeof[mfi->type_neighbor_cap];

    mfi->cap_source   = malloc(num_nodes * sizeof_type_terminal_cap);
    mfi->cap_sink     = malloc(num_nodes * sizeof_type_terminal_cap);
    
    mfi->cap_neighbor = (void**)malloc(mfi->connectivity * sizeof(void*));

    for (int i = 0; i < mfi->connectivity; i++)
    {
        mfi->cap_neighbor[i] = malloc(num_nodes * sizeof_type_neighbor_cap);
    }

    int num_active_nodes = 0;
    cl_int* ptrExcessFlow     = (cl_int*)hostExcessFlow.data();
    cl_int* ptrCapacitySource = (cl_int*)mfi->cap_source;
    cl_int* ptrCapacitySink   = (cl_int*)mfi->cap_sink;
    for (int i = 0; i < num_nodes; i++)
    {
        if (ptrExcessFlow[i] >= 0)
        {
            ptrCapacitySource[i] = ptrExcessFlow[i];
            ptrCapacitySink[i] = 0;
            num_active_nodes++;
        }
        else
        {
            ptrCapacitySource[i] = 0;
            ptrCapacitySink[i] = -ptrExcessFlow[i];
        }
    }

    mfi->active_count = num_active_nodes;

    if (volumeSize.s[2] == 1)
    {
        cl_ushort* ptrCapacityNeighbor[4] =
        {
            (cl_ushort*)mfi->cap_neighbor[0], (cl_ushort*)mfi->cap_neighbor[1],
            (cl_ushort*)mfi->cap_neighbor[2], (cl_ushort*)mfi->cap_neighbor[3]
        };

        cl_ushort2* ptrCapacity1 = (cl_ushort2*)hostCapacity1.data();
        cl_ushort2* ptrCapacity2 = (cl_ushort2*)hostCapacity2.data();
        for (int i = 0; i < num_nodes; i++)
        {
            ptrCapacityNeighbor[MFI::ARC_GE][i] = ptrCapacity1[i].s[0];
            ptrCapacityNeighbor[MFI::ARC_EG][i] = ptrCapacity1[i].s[1];

            ptrCapacityNeighbor[MFI::ARC_EL][i] = ptrCapacity2[i].s[0];
            ptrCapacityNeighbor[MFI::ARC_LE][i] = ptrCapacity2[i].s[1];
        }
    }
    else
    {
        cl_uchar* ptrCapacityNeighbor[6] =
        {
            (cl_uchar*)mfi->cap_neighbor[0], (cl_uchar*)mfi->cap_neighbor[1],
            (cl_uchar*)mfi->cap_neighbor[2], (cl_uchar*)mfi->cap_neighbor[3],
            (cl_uchar*)mfi->cap_neighbor[4], (cl_uchar*)mfi->cap_neighbor[5]
        };
        
        cl_uchar4* ptrCapacity1 = (cl_uchar4*)hostCapacity1.data();
        cl_uchar4* ptrCapacity2 = (cl_uchar4*)hostCapacity2.data();
        for (int i = 0; i < num_nodes; i++)
        {
            ptrCapacityNeighbor[MFI::ARC_GEE][i] = ptrCapacity1[i].s[0];
            ptrCapacityNeighbor[MFI::ARC_EGE][i] = ptrCapacity1[i].s[1];
            ptrCapacityNeighbor[MFI::ARC_EEG][i] = ptrCapacity1[i].s[2];
            
            ptrCapacityNeighbor[MFI::ARC_EEL][i] = ptrCapacity2[i].s[0];
            ptrCapacityNeighbor[MFI::ARC_ELE][i] = ptrCapacity2[i].s[1];
            ptrCapacityNeighbor[MFI::ARC_LEE][i] = ptrCapacity2[i].s[2];
        }
    }
    
    mfi->active_mask  = (unsigned char*)malloc(num_nodes*sizeof(unsigned char));

    for(int i = 0; i < num_nodes; i++)
    {
        if (hostCut[i].foreground)
        {
            mfi->active_mask[i] = 1;
        }
        else if (hostCut[i].background)
        {
            mfi->active_mask[i] = 2;
        }
        else if (hostCut[i].object)
        {
            mfi->active_mask[i] = 3;
        }
        else if (hostCut[i].tag)
        {
            mfi->active_mask[i] = 4;
        }
        else
        {
            mfi->active_mask[i] = 0;
        }
    }

    mfi_write(mfi, (dataFilePath + objectFileName + QGCSetting::extMFI).c_str());

    mfi_free(mfi);
}

cl_uint QGCWidget::getBrushingObject()
{
    const Ui::QGCPanel* ui = panel->getUI();
    if (ui->radioButtonBrushingObjectFore->isChecked())
        return 0;
    else if (ui->radioButtonBrushingObjectBack->isChecked())
        return 1;
    else if (ui->radioButtonBrushingObjectCut->isChecked())
        return 2;
    else
        return 3;
}

cl_uint QGCWidget::getRayCastingObject()
{
    const Ui::QGCPanel* ui = panel->getUI();
    if (ui->radioButtonRayCastingObjectAll->isChecked())
        return 0;
    else if (ui->radioButtonRayCastingObjectFore->isChecked())
        return 1;
    else if (ui->radioButtonRayCastingObjectBack->isChecked())
        return 2;
    else if (ui->radioButtonRayCastingObjectCut->isChecked())
        return 3;
    else
        return 4;
}

// 2. Rendering
void QGCWidget::slotUpdateTransferFunction()
{
    if (error || !this->initialized) return;

    updateTransferFunction();
    update();
}

void QGCWidget::updateTransferFunction()
{
    const Ui::QGCPanel* ui = panel->getUI();
    QHoverPoints* hoverPoints = ui->widgetEditor->getHoverPoints();

    // transform point opacity
    const QVector<QColor>& orgColors = hoverPoints->colors();
    std::vector<glm::vec4> colors;
    for (QVector<QColor>::const_iterator i = orgColors.begin(); i != orgColors.end(); i++)
        colors.push_back(glm::vec4(i->redF(), i->greenF(), i->blueF(), i->alphaF()));

    // transform point position
    int width = ui->widgetEditor->width();
    std::vector<float> positions;
    QUtilityData::computePartitionPositions(hoverPoints, width, positions, QSetting::sizeMapping, mappingComputed ? bufferMapping.data() : NULL);
    
    // generate transfer function
    int index(0);
    glm::vec4* ptrTransferFunction = settings.bufferTransferFunction1D.data();
    for (int i = 0; i < QSetting::sizeTransferFunction1D; i++)
    {
        float x = (float)i / (QSetting::sizeTransferFunction1D - 1);
        while (positions[index + 1] < x) index++;
        float ratio = positions[index + 1] == positions[index] ? 0.0f : float(x - positions[index]) / (positions[index + 1] - positions[index]);
        switch (hoverPoints->connectionType())
        {
        case QHoverPoints::LineConnection:
            *(ptrTransferFunction++) = colors[index] * (1.0f - ratio) + colors[index + 1] * ratio;
            break;
        case QHoverPoints::CurveConnection:
            *(ptrTransferFunction++) = QUtilityUITemplate<glm::vec4>::cubicTo(ratio, colors[index], colors[index + 1]);
            break;
        }
    }

    cl::size_t<3> origin, region;
    origin[0] = origin[1] = origin[2] = 0;
    region[0] = QSetting::sizeTransferFunction1D;
    region[1] = region[2] = 1;
    clQueue.enqueueWriteImage(imgTF, true, origin, region, 0, 0, settings.bufferTransferFunction1D.data());
    
    preInteration();
}

void QGCWidget::preInteration()
{
    const Ui::QGCPanel* ui = panel->getUI();
    cl_uint preIntBias = ui->spinBoxPreIntegrationBias->value();
    cl_uint preIntScale = ui->spinBoxPreIntegrationScale->value();
    cl::NDRange local(ui->spinBoxLocalSize2DX->value(), ui->spinBoxLocalSize2DY->value());
    cl::NDRange global = QUtilityCL::ceil(local, QSetting::sizePreIntegration);
    kerIntegration.setArg(2, preIntBias);
    kerIntegration.setArg(3, preIntScale);
    clQueue.enqueueNDRangeKernel(kerIntegration, cl::NullRange, global, local);
    clQueue.finish();
}

void QGCWidget::slotLoadTransferFunctionClicked()
{
    if (error) return;

    const Ui::QGCPanel* ui = panel->getUI();
    ui->widgetEditor->load(dataFilePath);

    switch (ui->widgetEditor->getHoverPoints()->connectionType())
    {
    case QHoverPoints::LineConnection:
        ui->radioButtonInterpolationLinear->setChecked(true);
        break;
    case QHoverPoints::CurveConnection:
        ui->radioButtonInterpolationCubic->setChecked(true);
        break;
    default:
        break;
    }
}

void QGCWidget::slotSaveTransferFunctionClicked()
{
    if (error) return;

    const Ui::QGCPanel* ui = panel->getUI();
    ui->widgetEditor->save(dataFilePath);
}

void QGCWidget::slotUpdateConnectionType()
{
    if (error) return;

    const Ui::QGCPanel* ui = panel->getUI();
    QHoverPoints* hoverPoints = ui->widgetEditor->getHoverPoints();
    if (ui->radioButtonInterpolationLinear->isChecked())
        hoverPoints->setConnectionType(QHoverPoints::LineConnection);
    else
        hoverPoints->setConnectionType(QHoverPoints::CurveConnection);
}