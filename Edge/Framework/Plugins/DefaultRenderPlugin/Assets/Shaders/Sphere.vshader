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
	float3 normal : NORMAL;
	float3 instancePosition : INST_POSITION;
	float3 instanceDirectionForward : INST_DIR0;
	float3 instanceDirectionUp : INST_DIR1;
	float instanceRadius : INST_RADIUS;
	uint instanceColor : INST_COLOR;
};

PixelInput VS(VertexInput input)
{
	float4x4 transform;
	transform[0] = float4(cross(input.instanceDirectionUp, input.instanceDirectionForward), 0.0);
	transform[1] = float4(input.instanceDirectionUp, 0.0);
	transform[2] = float4(input.instanceDirectionForward, 0.0);
	transform[3] = float4(input.instancePosition, 1.0);

	transform = transpose(transform);

	float4 vertPosition = float4(input.position * input.instanceRadius, 1.0);
	vertPosition = mul(transform, vertPosition);
	vertPosition = mul(viewTransform, vertPosition);
	vertPosition = mul(projTransform, vertPosition);

	float4 vertNormal = float4(input.normal, 0.0);
	vertNormal = mul(transform, vertNormal);
	vertNormal = float4(normalize(vertNormal.xyz), 0.0);

	PixelInput output;

	output.position = vertPosition;
	output.normal = vertNormal;
	output.color = unpackColor(input.instanceColor);

	return output;
}