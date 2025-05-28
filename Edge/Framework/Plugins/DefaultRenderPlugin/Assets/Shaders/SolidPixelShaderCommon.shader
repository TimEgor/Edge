#ifndef SOLID_PIXEL_SHADER_COMMON_SHADER_INCLUDE
#define SOLID_PIXEL_SHADER_COMMON_SHADER_INCLUDE

#include "Environment.shader"
#include "SolidPixelInput.shader"

static uint polyGridSegmentCount = 6;
static float polyGridSegmentStep = 1.0 / polyGridSegmentCount;

float4 PS(PixelInput input) : SV_Target0
{
	const float lightIntensity = saturate(dot(input.normal.xyz, -lightEnvironment.light.dir)) * 0.5;
	const float3 lightColor = lightEnvironment.light.color * lightIntensity;

	const uint2 polyGridSegemntIndex = uint2(input.uv / polyGridSegmentStep) % 2;
	const float polyGridSegemntColorCoef = 1.0 - ((polyGridSegemntIndex.x != polyGridSegemntIndex.y) * 0.25);

	const float3 environmentColor = lightEnvironment.color * lightEnvironment.intensity * polyGridSegemntColorCoef;

	return input.color * float4(lightColor + environmentColor, 1.0);
}

#endif //SOLID_PIXEL_SHADER_COMMON_SHADER_INCLUDE