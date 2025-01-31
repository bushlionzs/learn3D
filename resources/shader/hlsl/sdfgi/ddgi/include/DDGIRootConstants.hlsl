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

#ifndef __spirv__ // D3D12

   

#else // VULKAN

   

	VK_BINDING(1, 0) ConstantBuffer<DDGIRootConstants> DDGI : register(b1, space0);
	uint GetDDGIVolumeIndex() { return DDGI.volumeIndex; }
	uint3 GetReductionInputSize() { return uint3(DDGI.reductionInputSizeX, DDGI.reductionInputSizeY, DDGI.reductionInputSizeZ); }

    

    // These functions are not relevant in Vulkan since descriptor heap style bindless is not available
    uint GetDDGIVolumeConstantsIndex() { return 0; }
    uint GetDDGIVolumeResourceIndicesIndex() { return 0; }

#endif
