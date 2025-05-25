#include "Color.shader"
#include "Camera.shader"
#include "Text.shader"

PixelInput VS(VertexInput input)
{
	float4 vertPosition = float4(input.position, 1.0);
	vertPosition = mul(projTransform, vertPosition);

	PixelInput output;

	output.position = vertPosition;
	output.uv = input.uv;
	output.color = unpackColor(input.color);

	return output;
}