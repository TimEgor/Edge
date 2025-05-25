#include "Color.shader"
#include "Camera.shader"

struct VertexInput
{
	float3 position : POSITION;
	uint color : COLOR;
};

struct VertexOutput
{
	float4 position : SV_Position;
	float4 color : COLOR;
};

VertexOutput VS(VertexInput input)
{
	float4 vertPosition = float4(input.position, 1.0);
	vertPosition = mul(viewTransform, vertPosition);
	vertPosition = mul(projTransform, vertPosition);

	VertexOutput output;

	output.position = vertPosition;
	output.color = unpackColor(input.color);

	return output;
}