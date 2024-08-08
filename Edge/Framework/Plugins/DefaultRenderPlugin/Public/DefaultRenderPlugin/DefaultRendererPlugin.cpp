#include "DefaultRendererPlugin.h"

#include "EdgeFramework/Recources/AssetsDirectoryController/AssetsDirectoryController.h"
#include "EdgeFramework/Utils/XmlParser/NodeValueParserBase.h"
#include "EdgeFramework/Utils/XmlParser/XmlDocument.h"

#include "DefaultRenderer.h"

EDGE_MODULE_LOAD()
EDGE_PLUGIN(EdgeDefRender::DefaultRendererPlugin, EDGE_PLUGIN_TYPE_DECLARATION_RENDER)

void EdgeDefRender::DefaultRendererPlugin::onLoaded()
{
	const Edge::PluginModuleData& moduleData = Edge::PluginModuleCore::getInstance().getData();

	Edge::XmlDocument configFile;
	if (!configFile.loadFromFile(moduleData.m_modulePath + "/DefaultRenderPluginConfig.xml"))
	{
		assert(false && "Config file hasn't been found.");
		return;
	}

	Edge::XmlNode configFileRoot = configFile.getRootNode();
	Edge::XmlNode configNode = configFileRoot.getChild("CommonConfig");
	Edge::XmlNode assetsNode = configNode.getChild("Assets");

	auto assetsPathNodeRange = assetsNode.getChildren("AssetsPath");
	for (auto assetsPathNodeIter = assetsPathNodeRange.begin(); assetsPathNodeIter != assetsPathNodeRange.end(); ++assetsPathNodeIter)
	{
		Edge::XmlNode assetsPathNode = *assetsPathNodeIter;
		Edge::XmlNode aliasNode = assetsPathNode.getChild("AliasName");
		Edge::XmlNode rootPathNode = assetsPathNode.getChild("RootPath");

		std::string aliasName;
		Edge::XmlParserInterface::getValue(aliasNode, aliasName);

		Edge::FileName rootPath;
		Edge::XmlParserInterface::getValue(rootPathNode, rootPath);

		Edge::FrameworkCore::getInstance().getApplication().getAssetsDirectoryController().addAssetsRootPath(aliasName.c_str(), rootPath);
	}

}

Edge::Renderer* EdgeDefRender::DefaultRendererPlugin::createRenderer() const
{
	return new DefaultRenderer();
}
