#include "Color.shader"

cbuffer CameraTransforms : register(b0)
{
	float4x4 viewTransform;
	float4x4 projTransform;
	uint2 screenSpaceSize;
};

struct VertexInput
{
	float3 position : POSITION;
    float2 uv : TEXCOORD;
	uint color : COLOR;
};

struct PixelInput
{
	float4 position : SV_Position;
	float2 uv : TEXCOORD;
	float4 color : COLOR;
};

PixelInput VS(VertexInput input)
{
	float4 vertPosition = float4(input.position, 1.0);
	vertPosition = mul(viewTransform, vertPosition);
	vertPosition = mul(projTransform, vertPosition);

	PixelInput output;

	output.position = vertPosition;
    output.uv = input.uv;
	output.color = unpackColor(input.color);

	return output;
}