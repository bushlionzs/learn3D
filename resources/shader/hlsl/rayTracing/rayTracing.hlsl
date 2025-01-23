#include "base.hlsl"
#include "random.hlsl"

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
};


VKBINDING(0, 0) ConstantBuffer<UBO>   ubo: register(b0, space0);
VKBINDING(1, 0) StructuredBuffer<GeometryNode> geometryNodes: register(t0, space0);
VKBINDING(2, 0) SamplerState texSampler: register(s0, space0);
VKBINDING(3, 0) RaytracingAccelerationStructure topLevelAS: register(t3);
VKBINDING(4, 0) RWTexture2D<float4> image : register(u0);
VKBINDING(5, 0) Texture2D<float4> textures[] : register(t4);
VKBINDING(6, 0) ByteAddressBuffer     vertexDataBuffer[]    : register(t5, space1);

VKBINDING(7, 1) ByteAddressBuffer     indexDataBuffer[]    : register(t5, space2);

struct RayPayload
{
    VKLOCATION(0) float4 hitValue;
	VKLOCATION(2) uint payloadSeed;
};

struct Attributes
{
  float2 bary;
};

// Ray Generation Shader
[shader("raygeneration")]
void rayGenMain()
{
    uint2 gl_LaunchID = DispatchRaysIndex().xy;
	uint2 gl_LaunchSize = DispatchRaysDimensions().xy;
    uint seed = tea(gl_LaunchID.y * gl_LaunchSize.x + gl_LaunchID.x, ubo.frame);


    float r1 = rnd(seed);
    float r2 = rnd(seed);


    float2 subpixel_jitter = ubo.frame == 0 ? float2(0.5f, 0.5f) : float2(r1, r2);
    const float2 pixelCenter = float2(gl_LaunchID.xy) + subpixel_jitter;
    const float2 inUV = pixelCenter / float2(gl_LaunchSize.xy);
    float2 d = inUV * 2.0f - 1.0f;


    float4 origin = mul(ubo.viewInverse, float4(0,0,0,1));
    float4 target = mul(ubo.projInverse, float4(d.x, d.y, 1, 1));
    float4 direction = mul(ubo.viewInverse, float4(normalize(target.xyz), 0));

    float tmin = 0.001f;
    float tmax = 10000.0f;

    float4 hitValues = float4(0, 0, 0, 0);
    const int samples = 1;
	RayPayload payload;
	payload.hitValue = float4(0.0, 0.0, 0.0, 0.0);
    for (int smpl = 0; smpl < samples; ++smpl)
    {
        payload.payloadSeed = tea(gl_LaunchID.y * gl_LaunchSize.x + gl_LaunchID.x, ubo.frame);
		RayDesc ray;
		ray.Origin = origin.xyz;
		ray.Direction = direction.xyz;
		ray.TMin = tmin;
		ray.TMax = tmax;
        TraceRay(topLevelAS, RAY_FLAG_NONE, 0xFF, 0, 0, 0, ray, payload);
        hitValues += payload.hitValue;
    }

    float4 hitVal = hitValues / float(samples);

    if (ubo.frame > 0)
    {

        float a = 1.0f / float(ubo.frame + 1);
        float4 image_color = image.Load(gl_LaunchID.xy);
		float3 old_color = image_color.xyz;
        image[int2(gl_LaunchID.xy)] = float4(lerp(old_color, hitVal.rgb, a), 1.0f);
    }
    else
    {
        image[int2(gl_LaunchID.xy)] = hitVal;
    }
}

[shader("miss")]
void missMain(inout RayPayload payload)
{
    payload.hitValue = float4(0.2f, 0.0f, 0.0f, 1.0f);
}

struct Vertex
{
  float3 position;
  float3 normal;
  float4 tangent;
  float2 uv;
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



Triangle unpackTriangle(Attributes attribs) {
	Triangle tri;

    uint geometryIndex = GeometryIndex();
	uint primitiveIndex = PrimitiveIndex();

	LoadVertices(geometryIndex, primitiveIndex, tri.vertices);

	// Calculate values at barycentric coordinates
	float3 barycentricCoords = float3(1.0f - attribs.bary.x - attribs.bary.y, attribs.bary.x, attribs.bary.y);
	tri.uv = tri.vertices[0].uv * barycentricCoords.x + tri.vertices[1].uv * barycentricCoords.y + tri.vertices[2].uv * barycentricCoords.z;
	tri.normal = tri.vertices[0].normal * barycentricCoords.x + tri.vertices[1].normal * barycentricCoords.y + tri.vertices[2].normal * barycentricCoords.z;
	return tri;
}

[shader("closesthit")]
void closesthitMain(inout RayPayload payload, in Attributes attr)
{
	Triangle tri = unpackTriangle(attr);

	GeometryNode geometryNode = geometryNodes[GeometryIndex()];
	
	float4 color = geometryNode.color;
	if(geometryNode.textureIndexBaseColor > -1)
	{
	    color = textures[geometryNode.textureIndexBaseColor].SampleLevel(texSampler, tri.uv, 0);
	}
	
	if (geometryNode.textureIndexOcclusion > -1) {
		float occlusion = textures[geometryNode.textureIndexOcclusion].SampleLevel(texSampler, tri.uv, 0).r;
		color *= occlusion;
	}

	payload.hitValue = color;
}

[shader("anyhit")]
void anyhitMain(inout RayPayload payload, in Attributes attr)
{
	Triangle tri = unpackTriangle(attr);
	GeometryNode geometryNode = geometryNodes[GeometryIndex()];
	float4 color = geometryNode.color;
	IgnoreHit();
	return;
	if(geometryNode.textureIndexBaseColor > -1)
	{
	    color = textures[geometryNode.textureIndexBaseColor].SampleLevel(texSampler, tri.uv, 0);
		
		if(geometryNode.alphaMode == 2)
		{
		    IgnoreHit();
			return;
		    if (color.a < geometryNode.alphaMaskCutoff)
			{
				IgnoreHit();
			}
		}
	}
	
}