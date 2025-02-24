/*
* Copyright (c) 2019-2023, NVIDIA CORPORATION.  All rights reserved.
*
* NVIDIA CORPORATION and its licensors retain all intellectual property
* and proprietary rights in and to this software, related documentation
* and any modifications thereto.  Any use, reproduction, disclosure or
* distribution of this software and related documentation without an express
* license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

#include "DDGIRootConstants.h"


VK_BINDING(1, 0) ConstantBuffer<DDGIRootConstants> DDGI : register(b1, space0);
uint GetDDGIVolumeIndex() { return DDGI.volumeIndex; }
uint3 GetReductionInputSize() { return uint3(DDGI.reductionInputSizeX, DDGI.reductionInputSizeY, DDGI.reductionInputSizeZ); }




uint GetDDGIVolumeConstantsIndex() { return DDGI.volumeConstantsIndex; }
uint GetDDGIVolumeResourceIndicesIndex() { return DDGI.volumeResourceIndicesIndex; }


