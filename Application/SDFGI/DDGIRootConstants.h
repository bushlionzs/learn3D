/*
* Copyright (c) 2019-2023, NVIDIA CORPORATION.  All rights reserved.
*
* NVIDIA CORPORATION and its licensors retain all intellectual property
* and proprietary rights in and to this software, related documentation
* and any modifications thereto.  Any use, reproduction, disclosure or
* distribution of this software and related documentation without an express
* license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

#ifndef RTXGI_DDGI_ROOT_CONSTANTS_H
#define RTXGI_DDGI_ROOT_CONSTANTS_H


#include "ddgiTypes.h"


struct DDGIRootConstants
{
    uint32_t volumeIndex;
    uint32_t volumeConstantsIndex;
    uint32_t volumeResourceIndicesIndex;
    // Split uint3 into three uints to prevent internal padding
    // while keeping these values at the end of the struct
    uint32_t  reductionInputSizeX;
    uint32_t  reductionInputSizeY;
    uint32_t  reductionInputSizeZ;


    static uint32_t GetAlignedSizeInBytes() 
    { 
        uint32_t size = sizeof(DDGIRootConstants);

        uint32_t alignmentSize = CalcConstantBufferByteSize(size);

        return alignmentSize;
    }
};

#endif // RTXGI_DDGI_ROOT_CONSTANTS_H
