#ifndef CAMERA_SHADER_INCLUDE
#define CAMERA_SHADER_INCLUDE

cbuffer CameraTransforms : register(b0)
{
	float4x4 viewTransform;
	uint2 screenSpaceSize;
};

cbuffer CameraTransforms : register(b1)
{
	float4x4 projTransform;
};

#endif //CAMERA_SHADER_INCLUDE