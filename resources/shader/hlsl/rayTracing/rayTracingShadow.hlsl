// Copyright 2020 Google LLC
#include "base.hlsl"


struct UBO
{
	float4x4 viewInverse;
	float4x4 projInverse;
	float4 lightPos;
	int vertexSize;
	uint frame;
};




struct GeometryNode {
	float4 color;
	uint vertexOffset;
    uint indexOffset;
	int textureIndexBaseColor;
	int textureIndexOcclusion;
	uint alphaMode;
    float alphaMaskCutoff;
	uint padding[2];
};


RaytracingAccelerationStructure topLevelAS VKBINDING(0, 0): register(t0);
RWTexture2D<float4> image VKBINDING(1, 0): register(u1);
RES(CBUFFER(UBO), ubo, UPDATE_FREQ_NONE, b2, VKBINDING(2, 0));

VKBINDING(5, 0) StructuredBuffer<GeometryNode> geometryNodes: register(t5, space0);

VKBINDING(6, 0) ByteAddressBuffer     vertexDataBuffer[]    : register(t6, space0);

VKBINDING(7, 0) ByteAddressBuffer     indexDataBuffer[]    : register(t7, space0);


struct Payload
{
	VKLOCATION(0) float4 hitValue;
	VKLOCATION(2) bool shadowed;
};

struct Attributes
{
  float2 bary;
};

[shader("raygeneration")]
void rayGenMain()
{
	uint3 LaunchID = DispatchRaysIndex();
	uint3 LaunchSize = DispatchRaysDimensions();

	const float2 pixelCenter = float2(LaunchID.xy) + float2(0.5, 0.5);
	const float2 inUV = pixelCenter/float2(LaunchSize.xy);
	float2 d = inUV * 2.0 - 1.0;
	float4 target = mul(ubo.projInverse, float4(d.x, d.y, 1, 1));

	RayDesc rayDesc;
	rayDesc.Origin = mul(ubo.viewInverse, float4(0,0,0,1)).xyz;
	rayDesc.Direction = mul(ubo.viewInverse, float4(normalize(target.xyz), 0)).xyz;
	rayDesc.TMin = 0.001;
	rayDesc.TMax = 10000.0;

	Payload payload;
	TraceRay(topLevelAS, RAY_FLAG_FORCE_OPAQUE, 0xff, 0, 0, 0, rayDesc, payload);

	image[int2(LaunchID.xy)] = payload.hitValue;
}


struct Vertex
{
  float3 position;
  float3 normal;
  float4 tangent;
  float2 uv;
  float4 color;
};

struct Triangle {
	Vertex vertices[3];
	float3 normal;
	float2 uv;
};

uint3 LoadIndices(uint geometryIndex, uint primitiveIndex)
{
    GeometryNode geometry = geometryNodes[geometryIndex];
    uint index = primitiveIndex * 3 + geometry.indexOffset;
    return indexDataBuffer[geometryIndex].Load3(index * 4); 
}

void LoadVertices(uint geometryIndex, uint primitiveIndex, out Vertex vertices[3])
{
    // Get the indices
	GeometryNode geometry = geometryNodes[geometryIndex];
    uint3 indices = LoadIndices(geometryIndex, primitiveIndex);

    // Load the vertices
    uint address;
	
	ByteAddressBuffer vertexBuffer = vertexDataBuffer[geometryIndex];
    for (uint i = 0; i < 3; i++)
    {
        vertices[i] = (Vertex)0;
        address = (indices[i] + geometry.vertexOffset) * ubo.vertexSize;

        // Load the position
        vertices[i].position = asfloat(vertexBuffer.Load3(address));
        address += 12;

        // Load the normal
        vertices[i].normal = asfloat(vertexBuffer.Load3(address));
        address += 12;

        // Load the tangent
        vertices[i].tangent = asfloat(vertexBuffer.Load4(address));
        address += 16;

        // Load the texture coordinates
        vertices[i].uv = asfloat(vertexBuffer.Load2(address));
    }
}

Triangle unpackTriangle(uint index, Attributes attribs) {
	Triangle tri;

    uint geometryIndex = GeometryIndex();
	uint primitiveIndex = PrimitiveIndex();

	LoadVertices(geometryIndex, primitiveIndex, tri.vertices);

	// Calculate values at barycentric coordinates
	float3 barycentricCoords = float3(1.0f - attribs.bary.x - attribs.bary.y, attribs.bary.x, attribs.bary.y);
	tri.uv = tri.vertices[0].uv * barycentricCoords.x + tri.vertices[1].uv * barycentricCoords.y + tri.vertices[2].uv * barycentricCoords.z;
	tri.normal = tri.vertices[0].normal * barycentricCoords.x + tri.vertices[1].normal * barycentricCoords.y + tri.vertices[2].normal * barycentricCoords.z;
	
	GeometryNode geometry = geometryNodes[geometryIndex];
	
	tri.vertices[0].color = geometry.color;
	return tri;
}

[shader("closesthit")]
void closethitMain(inout Payload payload, in Attributes attribs)
{
    Triangle tri = unpackTriangle(PrimitiveIndex(), attribs);
	
	
	Vertex v0 = tri.vertices[0];


	// Basic lighting
	float3 lightVector = normalize(ubo.lightPos.xyz);
	float dot_product = max(dot(lightVector, tri.normal), 0.2);
	payload.hitValue = float4(v0.color.rgb * dot_product, 0.0f);
	
	return;
	RayDesc rayDesc;
	rayDesc.Origin = WorldRayOrigin() + WorldRayDirection() * RayTCurrent();
	rayDesc.Direction = lightVector;
	rayDesc.TMin = 0.001;
	rayDesc.TMax = 100.0;

	payload.shadowed = true;
	// Offset indices to match shadow hit/miss index
	TraceRay(topLevelAS, RAY_FLAG_ACCEPT_FIRST_HIT_AND_END_SEARCH | RAY_FLAG_FORCE_OPAQUE | RAY_FLAG_SKIP_CLOSEST_HIT_SHADER, 0xff, 0, 0, 1, rayDesc, payload);
	if (payload.shadowed) {
		payload.hitValue *= 0.3;
	}
}

[shader("miss")]
void missMain(inout Payload p)
{
    p.hitValue = float4(0.0, 0.2, 0.2, 0.0f);
}

//[shader("miss")]
//void shadowMissmain(inout Payload payload)
//{
//	payload.shadowed = false;
//}