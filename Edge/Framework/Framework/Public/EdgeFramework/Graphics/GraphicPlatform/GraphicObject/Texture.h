#pragma once

#include "EdgeCommon/Math/Vector.h"

#include "Format.h"
#include "GraphicResource.h"

#define EDGE_GRAPHIC_RESOURCE_TEXTURE_TYPE

namespace Edge
{
	enum TextureUsage : GraphicResourceUsageValueType
	{
		TEXTURE_USAGE_RENDER_TARGET = GRAPHIC_RESOURCE_MAX_USAGE << 1,
		TEXTURE_USAGE_DEPTH_STENCIL = GRAPHIC_RESOURCE_MAX_USAGE << 2
	};

	enum class TextureDimension
	{
		D1D,
		D2D,
		D3D
	};

	class Texture : public GraphicResource
	{
	public:
		Texture() = default;

		virtual TextureDimension getDimension() const = 0;

		EDGE_GRAPHIC_RESOURCE_TYPE(EDGE_GRAPHIC_RESOURCE_TEXTURE_TYPE)
	};

	using Texture1DSize = uint32_t;

	struct Texture1DDesc final
	{
		Texture1DSize m_size = 0;
		GraphicResourceFormat m_format = GraphicResourceFormat::Undefined;
		GraphicResourceUsageValueType m_usage = GRAPHIC_RESOURCE_USAGE_UNDEFINED;
		GraphicResourceAccessValueType m_access = GRAPHIC_RESOURCE_ACCESS_UNDEFINED;
	};

	class Texture1D : public Texture
	{
	private:
		const Texture1DDesc m_desc;

	public:
		Texture1D(const Texture1DDesc& desc)
			: m_desc(desc) {}

		const Texture1DDesc& getDesc() const { return m_desc; }

		virtual TextureDimension getDimension() const override { return TextureDimension::D1D; }
	};

	using Texture2DSize = UInt32Vector2;
	constexpr Texture2DSize Texture2DSizeZero = UInt32Vector2Zero;

	struct Texture2DDesc final
	{
		Texture2DSize m_size = Texture2DSizeZero;
		GraphicResourceFormat m_format = GraphicResourceFormat::Undefined;
		GraphicResourceUsageValueType m_usage = GRAPHIC_RESOURCE_USAGE_UNDEFINED;
		GraphicResourceAccessValueType m_access = GRAPHIC_RESOURCE_ACCESS_UNDEFINED;
	};

	class Texture2D : public Texture
	{
	private:
		const Texture2DDesc m_desc;

	public:
		Texture2D(const Texture2DDesc& desc)
			: m_desc(desc) {}

		const Texture2DDesc& getDesc() const { return m_desc; }

		virtual TextureDimension getDimension() const override { return TextureDimension::D2D; }
	};

	using Texture3DSize = UInt32Vector3;
	constexpr Texture3DSize Texture3DSizeZero = UInt32Vector3Zero;

	struct Texture3DDesc final
	{
		Texture3DSize m_size = Texture3DSizeZero;
		GraphicResourceFormat m_format = GraphicResourceFormat::Undefined;
		GraphicResourceUsageValueType m_usage = GRAPHIC_RESOURCE_USAGE_UNDEFINED;
		GraphicResourceAccessValueType m_access = GRAPHIC_RESOURCE_ACCESS_UNDEFINED;
	};

	class Texture3D : public Texture
	{
	private:
		const Texture3DDesc m_desc;

	public:
		Texture3D(const Texture3DDesc& desc)
			: m_desc(desc) {}

		const Texture3DDesc& getDesc() const { return m_desc; }

		virtual TextureDimension getDimension() const override { return TextureDimension::D3D; }
	};
}
