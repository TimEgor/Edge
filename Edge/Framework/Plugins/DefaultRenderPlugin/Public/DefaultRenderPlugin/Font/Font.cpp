#include "Font.h"

#include "EdgeCommon/UtilsMacros.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicDevice.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/Texture.h"

EdgeDefRender::Font::~Font()
{
	release();
}

bool EdgeDefRender::Font::init(const Edge::FontProvider::GlyphDataCollection& glyphData, Edge::GraphicDevice& device)
{
	Edge::Texture2DDesc textureDesc{};
	textureDesc.m_format = Edge::GraphicResourceFormat::R8_UNORM;
	textureDesc.m_size.m_x = glyphData.m_atlasWidth;
	textureDesc.m_size.m_y = glyphData.m_atlasHeight;
	textureDesc.m_access = Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ;
	textureDesc.m_usage = Edge::GRAPHIC_RESOURCE_USAGE_SHADER_RESOURCE;

	const Edge::InitialGraphicResourceData atlasData(glyphData.m_data, glyphData.m_dataSize);
	m_atlas = device.createTexture2D(textureDesc, &atlasData);

	EDGE_CHECK_INITIALIZATION(m_atlas);

	m_height = glyphData.m_height;

	memcpy(m_widths, glyphData.m_widths, sizeof(glyphData.m_widths));
	memcpy(m_heights, glyphData.m_heights, sizeof(glyphData.m_heights));
	memcpy(m_spacing, glyphData.m_spacing, sizeof(glyphData.m_spacing));
	memcpy(m_x, glyphData.m_x, sizeof(glyphData.m_x));

	return true;
}

void EdgeDefRender::Font::release()
{
	EDGE_SAFE_DESTROY(m_atlas);
}

Edge::Texture2D* EdgeDefRender::Font::getAtlas() const
{
	return m_atlas;
}

uint16_t EdgeDefRender::Font::getHeight() const
{
	return m_height;
}

uint16_t EdgeDefRender::Font::getGlyphWidth(uint32_t index) const
{
	return m_widths[index];
}

uint16_t EdgeDefRender::Font::getGlyphHeight(uint32_t index) const
{
	return m_heights[index];
}

uint16_t EdgeDefRender::Font::getGlyphPairSpacing(uint32_t index1, uint32_t index2) const
{
	return m_spacing[index1][index2];
}

uint16_t EdgeDefRender::Font::getGlyphPosition(uint32_t index) const
{
	return m_x[index];
}
