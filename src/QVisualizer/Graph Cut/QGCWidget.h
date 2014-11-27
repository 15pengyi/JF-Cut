/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QGCWidget.h
 * @brief   QGCWidget class definition.
 * 
 * This file defines the main process of Marching Cubes Algorithm.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2013/01/09
 */

#ifndef QGCWIDGET
#define QGCWIDGET

#include <vector>
#include <list>

#include <gl/glew.h>

#include <gtc/quaternion.hpp>

#include "../3rdParty/cl/cl_stacktrace.hpp"
#include <clogs/scan.h>

#include <QGLWidget>

#include "QGCSetting.h"

enum QMouseMode;
enum QDataFormat;
enum QEndianness;

class QKeyEvent;

class QHoverPoints;
class QGCPanel;

class QGCWidget : public QGLWidget
{
    Q_OBJECT
    
public:
    QGCWidget(QWidget *parent = 0);
    ~QGCWidget();
    
    // Data file
    std::string corporation;
    std::string dataFilePath, dataFileName;
    std::string objectFileName, gradientFileName, curvatureFileName;
    
    // Volumetric Data
    QEndianness endian;
    QDataFormat format;
    cl_uint volumeSize1D;
    cl_uint4 volumeSize;
    cl_float4 boxSize, thickness;
    float volumeMin, volumeMax;
    
    // Simplification
    bool simplified;

    // Feature Data
    float gradientMin, gradientMax;
    float curvatureMin, curvatureMax;

    // Mapping
    bool mappingComputed;
    std::vector<float> bufferMapping;

    // Histogram Data
    bool histogramComputed;
    std::vector<float> bufferHistogram;
    float histogramMin, histogramMax;

    // Configuration
    bool initialized;
    bool error;
    QGCSetting settings;
    
    // OpenGL Context
    QMouseMode mouseMode;
    glm::ivec2 mousePosition;
    
    // OpenCL Context
    cl::NDRange sizLocal, sizGlobal;
    cl::Program progClustering, progModeling, progCounting, progBFS, progPushRelabel, progPushRelabelFast,
        progCut, progTag, progJumpFlooding, progGlobalRelabel, progReduce,
        progRenderNormal, progRenderPreInt, progRenderFeature, progUtility;
    cl::Kernel kerKMeans, kerCutHistogram, kerCutDistribution,
        kerCapacityBK, kerCapacityLazy, kerExcessFlowBK, kerExcessFlowLazy,
        kerPushRelabel, kerFastRelabel, kerFastPushX, kerFastPushY, kerFastPushZ,
        kerScatterNode, kerCountNode, kerScatterCut, kerCountCut,
        kerInitCut, kerComputeCut, kerInitTag, kerComputeTag,
        kerBFSHistogram, kerBFSJumpFlooding, kerBFSMapping,
        kerInitGlobalRelabel, kerGlobalRelabel,
        kerReduceFlow, kerReduceHistogram, kerClear, kerIntegration,
        kerRenderNormal[3], kerRenderPreInt[3], kerRenderFeature[3];
    cl::Buffer devCutHistogram, devBFSHistogram, devDistribution, devCentroid, devSum, devCount,
        devActiveTile, devActiveTileOdd, devTileList,
        devExcessFlow, devHeight, devCapacity1, devCapacity2,
        devDone, devCut, devFlow, devHistogram, devDepth, devMask, devBuffer;
    cl_uint glBuffer;
    cl::Image2D imgCut2D, imgVolume2D, imgFeature2D, imgTF, imgIntegration;
    cl::Image3D imgCut3D, imgVolume3D, imgFeature3D;
    cl_mem imgVolume, imgCut, imgFeature;
    cl::size_t<3> imgOrigin, imgRegion;
    cl::Device clDevice;
    cl::Context clContext;
    cl::CommandQueue clQueue;
    clogs::Scan* clScan;

    // Widget
    QGCPanel* panel;
    
    // Graph Cut
    cl_ulong energyData, energySmooth;
    cl_uint groupSize1D, clGroupSize, clLocalSize, flowBlockSize, flowBlocks, histBlockSize, histBlocks;
    cl_uint4 groupSize, blockSize;
    std::vector<cl_float> hostMinMask, hostMaxMask;
    std::vector<cl_int> hostFlow, hostHistogram;
    std::vector<cl_int> hostCutHistogram, hostDistHistogram, hostCutDistribution, hostDepth, hostActiveTile, hostTileOffset;
    std::vector<glm::ivec4> hostTileList;
    std::vector<unsigned char> hostMask, hostExcessFlow, hostHeight, hostCapacity1, hostCapacity2;
    std::vector<cl_cut> hostCut;
    std::vector<glm::vec4> hostCentroid, hostSum;
    std::vector<int> hostCount;
    
    void destroy();
    
    // Step 1 - init connections
    void initConnections(QGCPanel* panel);

    // Step 2 - init data
    void initCorporation(const std::string &corporation);
    void initData(const std::string &name);
    void parseDataFile(const std::string &name);
    void saveDataFile(const std::string &name);
    
    // Step 3 - init context
    void initContext();
    void initConfigurations();
    void initOpenCL();
    void initPrograms();
    void initArguments();

    void initClustering(const std::string& options, const std::string& headers);
    void initModeling(const std::string& options, const std::string& headers);
    void initCounting(const std::string& options, const std::string& headers);
    void initBFS(const std::string& options, const std::string& headers);
    void initPushRelabel(const std::string& options, const std::string& headers);
    void initPushRelabelFast(const std::string& options, const std::string& headers);
    void initCut(const std::string& options, const std::string& headers);
    void initTag(const std::string& options, const std::string& headers);
    void initGlobalRelabel(const std::string& options, const std::string& headers);
    void initReduce(const std::string& options, const std::string& headers);
    void initRendering(const std::string& options, const std::string& headers);
    void initUtility(const std::string& options, const std::string& headers);
    
    // Step 4 - message loop

    // resizeGL
    void updatePixelBuffer();
    
    // paintGL
    void drawMask();
    void drawVolumeCL();
    void drawVolume();
    void drawWireFrame();
    void drawFocusArea();
    void drawParameters();
    void drawColorBar();

    void paintForeground();
    void paintBackground();
    
    void printFPS(unsigned long milliseconds);

    // K-Means
    void kmeans(cl_long& nsecKMeans, cl_uint offset);

    // Graph Cut
    void globalRelabel(cl_long& nsecInit);

    void countActiveBlock(cl_long& nsecCount);
    void relabelPush(cl_long& nsecRelabelPush);
    void relabelPushFast(cl_long& nsecRelabelPush);

    void shot();

    // 0. Infrastructures
    cl_uint getVoxelSize(QDataFormat format);
    void getIMVPMatrix(const glm::quat& quaternion);
    void setProjection();

    // 1. Graph Cut
    // -->
public slots:
    void slotToolkitTypeChanged();
    void slotCutClicked();
    void slotModelClicked();
    void slotClearClicked();

    void slotLoadGraphClicked();
    void slotSaveGraphClicked();
    void slotLoadGradientClicked();
    void slotSaveGradientClicked();
    void slotLoadFeatureClicked();
    void slotSaveFeatureClicked();
    void slotLoadCutClicked();
    void slotSaveCutClicked();
    void slotExportClicked();

public:
    void enqueue3DKernel(const cl::Kernel& kernel, cl::Event* event = NULL);
    void enqueue3DKernel(const cl::Kernel& kernel, cl_uint4 kernelSize, cl::Event* event = NULL);
    
    void clearTexture(const cl::Buffer& texture, cl_uint textureStride, cl::Event* event = NULL);
    void clearTexture(const cl::Buffer& texture, cl_uint textureEnd, cl_uint textureStride, cl::Event* event = NULL);
    void clearTexture(const cl::Buffer& texture, cl_uint textureEnd, cl_uint textureStride, cl_uint clearOffset, cl_uint clearSize, cl::Event* event = NULL);
    void clearTexture(const cl::Buffer& texture, cl_uint textureStart, cl_uint textureEnd, cl_uint textureStride, cl_uint clearOffset, cl_uint clearSize, cl::Event* event = NULL);

    void computeBFS(cl_long& nsecBFS);
    void computeVisibility(cl_uint offset, cl::Event* event = NULL);
    void computeExtremum(cl_uint offset);
    void computeHistogram(cl_uint offset);

    void computeCapacity(cl_long& nsecCapacity, bool lazy = false);
    void computeExcessFlowBK(cl_long& nsecExcessFlow, cl_uint2 sum);
    void computeExcessFlowLazy(cl_long& nsecExcessFlow);
    
    void computeCut(cl_long& nsecFinal, bool& finished);
    void computeTag(cl_long& nsecFinal);
    
    void reduceFlow(cl_long& sum, cl_long& nsecFlow);
    void reduceHistogram(cl_int& maximum, cl_long& nsecHistogram);

    void loadMFI();
    void saveMFI();

    cl_uint getBrushingObject();
    cl_uint getRayCastingObject();

    // 2. Rendering
    // -->
public slots:
    void slotUpdateConnectionType();
    void slotUpdateTransferFunction();
    void slotLoadTransferFunctionClicked();
    void slotSaveTransferFunctionClicked();
    // <--
signals:
    void signalPartitionInitialized(::size_t partitionSize, float *partitionData);
    void signalHistogramInitialized(::size_t histogramSize, float *histogramData);
    void signalHistogramUpdated(int histogramID, float *histogramData);
public:
    void updateTransferFunction();
    void preInteration();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // QVRWIDGET