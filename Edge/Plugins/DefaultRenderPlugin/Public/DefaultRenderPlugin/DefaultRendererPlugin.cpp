#include "DefaultRendererPlugin.h"

#include "TinySimFramework/Recources/AssetsDirectoryController/AssetsDirectoryController.h"
#include "TinySimFramework/Utils/XmlParser/XmlDocument.h"
#include "TinySimFramework/Utils/XmlParser/NodeValueParserBase.h"

#include "DefaultRenderer.h"

TS_MODULE_LOAD()
TS_PLUGIN(TS_DEF_RENDERER::DefaultRendererPlugin, TS_PLUGIN_TYPE_DECLARATION_RENDERER)

void TS_DEF_RENDERER::DefaultRendererPlugin::onLoaded()
{
	const TS::PluginModuleData& moduleData = TS::PluginModuleCore::getInstance().getData();

	TS::XmlDocument configFile;
	if (!configFile.loadFromFile(moduleData.m_modulePath + "/DefaultRendererPluginConfig.xml"))
	{
		assert(false && "Config file hasn't been found.");
		return;
	}

	TS::XmlNode configFileRoot = configFile.getRootNode();
	TS::XmlNode configNode = configFileRoot.getChild("CommonConfig");
	TS::XmlNode assetsNode = configNode.getChild("Assets");

	auto assetsPathNodeRange = assetsNode.getChildren("AssetsPath");
	for (auto assetsPathNodeIter = assetsPathNodeRange.begin(); assetsPathNodeIter != assetsPathNodeRange.end(); ++assetsPathNodeIter)
	{
		TS::XmlNode assetsPathNode = *assetsPathNodeIter;
		TS::XmlNode aliasNode = assetsPathNode.getChild("AliasName");
		TS::XmlNode rootPathNode = assetsPathNode.getChild("RootPath");

		std::string aliasName;
		TS::XmlParserInterface::getValue(aliasNode, aliasName);

		TS::FileName rootPath;
		TS::XmlParserInterface::getValue(rootPathNode, rootPath);

		TS::FrameworkCore::getInstance().getApplication().getAssetsDirectoryController().addAssetsRootPath(aliasName.c_str(), rootPath);
	}

}

TS::Renderer* TS_DEF_RENDERER::DefaultRendererPlugin::createRenderer() const
{
	return new DefaultRenderer();
}
