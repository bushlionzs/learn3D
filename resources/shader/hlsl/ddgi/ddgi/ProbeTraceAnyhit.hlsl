/*
* Copyright (c) 2019-2023, NVIDIA CORPORATION.  All rights reserved.
*
* NVIDIA CORPORATION and its licensors retain all intellectual property
* and proprietary rights in and to this software, related documentation
* and any modifications thereto.  Any use, reproduction, disclosure or
* distribution of this software and related documentation without an express
* license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

#include "ddgiDescriptors.hlsl"
#include "ddgiRayTracing.hlsl"


[shader("anyhit")]
void AHS_GI(inout PackedPayload payload, BuiltInTriangleIntersectionAttributes attrib)
{
    // Load the intersected mesh geometry's data
    GeometryData geometry;
    GetGeometryData(GeometryIndex(), geometry);

    // Load the surface material
    Material material = GetMaterial(GeometryIndex());

    float alpha = material.opacity;
    if (material.alphaMode == 2)
    {
        // Load the vertices
        Vertex vertices[3];
        LoadVerticesPosUV0(InstanceID(), PrimitiveIndex(), geometry, vertices);

        // Interpolate the triangle's texture coordinates
        float3 barycentrics = float3((1.f - attrib.barycentrics.x - attrib.barycentrics.y), attrib.barycentrics.x, attrib.barycentrics.y);
        Vertex v = InterpolateVertexUV0(vertices, barycentrics);

        // Sample the texture
        if (material.albedoTexIdx > -1)
        {
            // Get the number of mip levels
            uint width, height, numLevels;
            GetTex2D(material.albedoTexIdx).GetDimensions(0, width, height, numLevels);

            // Sample the texture
            alpha *= GetTex2D(material.albedoTexIdx).SampleLevel(GetBilinearWrapSampler(), v.uv0, numLevels * 0.6667f).a;
        }
    }

    if (alpha < material.alphaCutoff) IgnoreHit();
}
