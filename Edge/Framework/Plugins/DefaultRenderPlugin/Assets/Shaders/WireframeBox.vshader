#include "Color.shader"
#include "WireframePixelInput.shader"

cbuffer CameraTransforms : register(b0)
{
	float4x4 viewTransform;
	float4x4 projTransform;
	uint2 screenSpaceSize;
};

struct VertexInput
{
	float3 position : POSITION;
	float4x4 instanceTransform : INST_TRANSFORM;
};

PixelInput VS(VertexInput input)
{
	uint color = asuint(input.instanceTransform[3][3]);
	input.instanceTransform[3][3] = 1.0;

	float4 vertPosition = float4(input.position, 1.0);
	vertPosition = mul(input.instanceTransform, vertPosition);
	vertPosition = mul(viewTransform, vertPosition);
	vertPosition = mul(projTransform, vertPosition);

	PixelInput output;

	output.position = vertPosition;
	output.color = unpackColor(color);

	return output;
}