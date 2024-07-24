#ifndef COLOR_SHADER_INCLUDE
#define COLOR_SHADER_INCLUDE

float4 unpackColor(uint color)
{
	float4 result;

	result.r = (color & 255) / 255.0;
	result.g = ((color & (255 << 8)) >> 8) / 255.0;
	result.b = ((color & (255 << 16)) >> 16) / 255.0;
	result.a = ((color & (255 << 24)) >> 24) / 255.0;

	return result;
}

#endif //COLOR_SHADER_INCLUDE