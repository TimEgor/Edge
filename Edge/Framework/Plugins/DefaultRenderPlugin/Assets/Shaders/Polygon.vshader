#include "Color.shader"
#include "SolidPixelInput.shader"

cbuffer CameraTransforms : register(b0)
{
	float4x4 viewTransform;
	float4x4 projTransform;
	uint2 screenSpaceSize;
};

struct VertexInput
{
	float3 position : POSITION;
	uint color : COLOR;
	float3 normal : NORMAL;
};

PixelInput VS(VertexInput input)
{
	float4 vertPosition = float4(input.position, 1.0);
	vertPosition = mul(viewTransform, vertPosition);
	vertPosition = mul(projTransform, vertPosition);

	PixelInput output;

	output.position = vertPosition;
	output.color = unpackColor(input.color);
	output.normal = float4(input.normal, 0.0);

	return output;
}