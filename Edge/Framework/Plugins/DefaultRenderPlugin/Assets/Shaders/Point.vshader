#include "Color.shader"
#include "Camera.shader"

static float2 pointScreenPositions[4] =
{
	{ 0.5, -0.5 },
	{ 0.5, 0.5 },
	{ -0.5, -0.5 },
	{ -0.5, 0.5 }
};

static uint pointSize = 12;

struct VertexInput
{
	float3 instancePosition : INST_POSITION;
	uint instanceColor : INST_COLOR;
};

struct VertexOutput
{
	float4 position : SV_Position;
	float4 color : COLOR;
};

VertexOutput VS(VertexInput input, uint vertexID : SV_VertexID)
{
	float4 vertPosition = float4(input.instancePosition, 1.0);
	vertPosition = mul(viewTransform, vertPosition);
	vertPosition = mul(projTransform, vertPosition);
	
	const float2 screenSpacePoinPosition = vertPosition.xy / vertPosition.w;

	const float2 pointPositionSizeScale = 1.0 / (screenSpaceSize / pointSize * 2.0);
	const float2 pointVertexOffset = pointScreenPositions[vertexID] * pointPositionSizeScale;

	VertexOutput output;
	output.position = vertPosition + float4(pointVertexOffset * vertPosition.w, 0.0, 0.0);
	output.color = unpackColor(input.instanceColor);

	return output;
}