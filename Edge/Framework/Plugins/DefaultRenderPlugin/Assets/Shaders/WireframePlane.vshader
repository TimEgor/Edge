#include "Color.shader"
#include "Camera.shader"
#include "WireframePixelInput.shader"

static float2 planeBaseVertexPositions[4] =
{
	{ 0.5, -0.5 },
	{ 0.5, 0.5 },
	{ -0.5, -0.5 },
	{ -0.5, 0.5 }
};

static uint planeBaseVertexPositionIndices[5] =
{
	0, 1, 3, 2, 0
};

struct VertexInput
{
	float3 instancePosition : INST_POSITION;
	float instanceSizeX : INST_SIZE0;
	float3 instanceNormal : INST_NORMAL;
	float instanceSizeY : INST_SIZE1;
	float3 instanceDirX : INST_DIR;
	uint instanceColor : INST_COLOR;
};


PixelInput VS(VertexInput input, uint vertexID : SV_VertexID)
{
	float3 dirY = cross(input.instanceNormal, input.instanceDirX);
	float2 localPlaneVertexPosition = planeBaseVertexPositions[planeBaseVertexPositionIndices[vertexID]] * float2(input.instanceSizeX, input.instanceSizeY);
	float3 planeVertexPosition = localPlaneVertexPosition.x * input.instanceDirX + localPlaneVertexPosition.y * dirY;

	float4 vertPosition = float4(input.instancePosition + planeVertexPosition, 1.0);
	vertPosition = mul(viewTransform, vertPosition);
	vertPosition = mul(projTransform, vertPosition);

	PixelInput output;

	output.position = vertPosition;
	output.color = unpackColor(input.instanceColor);

	return output;
}