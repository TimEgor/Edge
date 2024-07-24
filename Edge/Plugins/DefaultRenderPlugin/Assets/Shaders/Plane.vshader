#include "Color.shader"
#include "SolidPixelInput.shader"

static float2 planeBaseVertexPositions[4] =
{
	{ 0.5, -0.5 },
	{ 0.5, 0.5 },
	{ -0.5, -0.5 },
	{ -0.5, 0.5 }
};

cbuffer CameraTransforms : register(b0)
{
	float4x4 viewTransform;
	float4x4 projTransform;
	uint2 screenSpaceSize;
};

struct VertexInput
{
	float3 instancePosition : INST_POSITION;
	float instanceSizeX : INST_SIZE0;
	float3 instanceNormal : INST_NORMAL;
	float instanceSizeY : INST_SIZE1;
	float3 instanceDirRight : INST_DIR;
	uint instanceColor : INST_COLOR;
};


PixelInput VS(VertexInput input, uint vertexID : SV_VertexID)
{
	float3 directionUp = cross(input.instanceNormal, input.instanceDirRight);
	float2 localPlaneVertexPosition = planeBaseVertexPositions[vertexID] * float2(input.instanceSizeX, input.instanceSizeY);
	float3 planeVertexPosition = localPlaneVertexPosition.x * input.instanceDirRight + localPlaneVertexPosition.y * directionUp;

	float4 vertPosition = float4(input.instancePosition + planeVertexPosition, 1.0);
	vertPosition = mul(viewTransform, vertPosition);
	vertPosition = mul(projTransform, vertPosition);

	PixelInput output;

	output.position = vertPosition;
	output.normal = float4(input.instanceNormal, 0.0);
	output.color = unpackColor(input.instanceColor);

	return output;
}