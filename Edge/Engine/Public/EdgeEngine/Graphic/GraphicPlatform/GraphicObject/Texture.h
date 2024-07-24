#pragma once

#include "EdgeEngine/Core/Math/Vector.h"

#include "Format.h"
#include "IGraphicResource.h"

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

	class ITexture : public IGraphicResource
	{
	public:
		ITexture() = default;

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

	class ITexture1D : public ITexture
	{
	public:
		ITexture1D() = default;

		virtual const Texture1DDesc& getDesc() const = 0;

		virtual TextureDimension getDimension() const override { return TextureDimension::D1D; }
	};

	class Texture1DBase : public ITexture1D
	{
	private:
		const Texture1DDesc m_desc;

	public:
		Texture1DBase(const Texture1DDesc& desc)
			: m_desc(desc) {}

		virtual const Texture1DDesc& getDesc() const override { return m_desc; }
	};

	using Texture2DSize = UInt32Vector2;

	struct Texture2DDesc final
	{
		Texture2DSize m_size = UInt32Vector2Zero;
		GraphicResourceFormat m_format = GraphicResourceFormat::Undefined;
		GraphicResourceUsageValueType m_usage = GRAPHIC_RESOURCE_USAGE_UNDEFINED;
		GraphicResourceAccessValueType m_access = GRAPHIC_RESOURCE_ACCESS_UNDEFINED;
	};

	class ITexture2D : public ITexture
	{
	public:
		ITexture2D() = default;

		virtual const Texture2DDesc& getDesc() const = 0;

		virtual TextureDimension getDimension() const override { return TextureDimension::D2D; }
	};

	class Texture2DBase : public ITexture2D
	{
	private:
		const Texture2DDesc m_desc;

	public:
		Texture2DBase(const Texture2DDesc& desc)
			: m_desc(desc) {}

		virtual const Texture2DDesc& getDesc() const override { return m_desc; }
	};

	using Texture3DSize = UInt32Vector3;

	struct Texture3DDesc final
	{
		Texture3DSize m_size = UInt32Vector3Zero;
		GraphicResourceFormat m_format = GraphicResourceFormat::Undefined;
		GraphicResourceUsageValueType m_usage = GRAPHIC_RESOURCE_USAGE_UNDEFINED;
		GraphicResourceAccessValueType m_access = GRAPHIC_RESOURCE_ACCESS_UNDEFINED;
	};

	class ITexture3D : public ITexture
	{
	public:
		ITexture3D() = default;

		virtual const Texture3DDesc& getDesc() const = 0;

		virtual TextureDimension getDimension() const override { return TextureDimension::D3D; }
	};

	class Texture3DBase : public ITexture3D
	{
	private:
		const Texture3DDesc m_desc;

	public:
		Texture3DBase(const Texture3DDesc& desc)
			: m_desc(desc) {}

		virtual const Texture3DDesc& getDesc() const override { return m_desc; }
	};
}
