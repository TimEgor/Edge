#include "FontController.h"

#include "EdgeCommon/HashFunctions/CRC32.h"
#include "EdgeCommon/HashFunctions/StdHashCombine.h"

#include "EdgeFramework/FrameworkCore.h"
#include "EdgeFramework/Platform/Platform.h"
#include "EdgeFramework/Visualizer/FontProvider.h"

void EdgeDefRender::FontController::release()
{
	m_fonts = FontCollection();
}

void EdgeDefRender::FontController::update()
{
	
}

const EdgeDefRender::Font* EdgeDefRender::FontController::getFont(const char* fontName, uint32_t fontHeight)
{
	return nullptr;

	//if (!fontName || fontHeight == 0)
	//{
	//	return nullptr;
	//}

	//const Edge::Application& application = Edge::FrameworkCore::getInstance().getApplication();

	//const uint32_t currentFrame = application.getCurrentFrameNum();

	//FontID fontID = Edge::Crc32(fontName);
	//Edge::HashCombine(fontID, fontHeight);

	//const auto findFontIter = m_fonts.find(fontID);
	//if (findFontIter != m_fonts.end())
	//{
	//	findFontIter->second.m_lastUsingFrame = currentFrame;
	//	return &findFontIter->second.m_font;
	//}

	//Edge::FontProvider& fontProvider = application.getPlatform().getFontProvider();
	//Edge::FontProvider::GlyphDataCollection glyphData = fontProvider.getFontGlyphsData(fontName, fontHeight);

	//if (!glyphData.m_data)
	//{
	//	return nullptr;
	//}

	//FontData& fontData = m_fonts[fontID];
	//fontData.m_font.init(glyphData);
	//fontData.m_lastUsingFrame = currentFrame;

	//EDGE_SAFE_DESTROY_ARRAY(glyphData.m_data);

	//return &fontData.m_font;
}
