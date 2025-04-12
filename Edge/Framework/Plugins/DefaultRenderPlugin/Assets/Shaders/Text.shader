#ifndef TEXT_SHADER_INCLUDE
#define TEXT_SHADER_INCLUDE

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

#endif //TEXT_SHADER_INCLUDE