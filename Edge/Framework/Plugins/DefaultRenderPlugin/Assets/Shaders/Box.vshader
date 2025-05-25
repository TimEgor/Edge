#include "Color.shader"
#include "Camera.shader"
#include "SolidPixelInput.shader"

struct VertexInput
{
	float3 position : POSITION;
	float3 normal : NORMAL;
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

	float4 vertNormal = float4(input.normal, 0.0);
	vertNormal = mul(input.instanceTransform, vertNormal);
	vertNormal = float4(normalize(vertNormal.xyz), 0.0);

	PixelInput output;

	output.position = vertPosition;
	output.normal = vertNormal;
	output.color = unpackColor(color);

	return output;
}