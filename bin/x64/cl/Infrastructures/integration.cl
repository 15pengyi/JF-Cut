/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    *.cl
 * @brief   * functions definition.
 * 
 * This file defines *.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2012/06/12
 */

constant sampler_t sampler = CLK_NORMALIZED_COORDS_TRUE | CLK_ADDRESS_CLAMP_TO_EDGE | CLK_FILTER_LINEAR;

__kernel void pre_integration(
    __read_only image2d_t transferFunction,
    __write_only image2d_t integrationTable,
    const uint stepBias, const uint stepScale
    )
{
    int x = get_global_id(0);
    int y = get_global_id(1);
    int width = get_image_width(integrationTable);
    int height = get_image_height(integrationTable);
    if (x >= width || y >= height) return;
    
    // Compute the step number for color integration
    const float2 scalar = (float2)((float)x / (width - 1), (float)y / (height - 1));
    const uint stepNumber = (uint)(fabs(scalar.x - scalar.y) * stepScale) + stepBias;
    const float stepSize = 1.0f / stepNumber;
    const float scalarStepSize = (scalar.y - scalar.x) * stepSize;
    
    // Do color integration
    float4 color = (float4)(0.0f);
    for (int i = 0; i < stepNumber; i++)
    {
        const float4 sample = read_imagef(transferFunction, sampler, (float2)(scalar.x + scalarStepSize * i, 0.5f));
        const float alpha = sample.w * stepSize;
        color.xyz += sample.xyz * exp(-color.w) * alpha;
        color.w += alpha;
    }
    write_imagef(integrationTable, (int2)(x, y), (float4)(color.xyz, 1.0f - exp(-min(color.w, 1.0f))));
}