#ifndef ENVIRONMENT_SHADER_INCLUDE
#define ENVIRONMENT_SHADER_INCLUDE

struct DirectionLight
{
	float3 dir;
	float3 color;
};

struct LightEnvironment
{
	DirectionLight light;
	float3 color;
	float intensity;
};

static LightEnvironment lightEnvironment = {
	{
		{ -1.0, -0.5, 0.5 },
		{ 1.0, 1.0, 1.0 }
	},
	{ 1.0, 1.0, 1.0 },
	0.3
};

#endif //ENVIRONMENT_SHADER_INCLUDE