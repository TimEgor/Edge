#include "AssetsDirectoryController.h"

#include "EdgeCommon/FileName/FileName.h"
#include "EdgeCommon/HashFunctions/CRC32.h"

void Edge::AssetsDirectoryController::addAssetsRootPath(const char* aliasName, const FileName& rootPath)
{
	m_paths.insert(std::make_pair(Crc32(aliasName), rootPath));
}

const Edge::FileName* Edge::AssetsDirectoryController::getAssetsRootPath(const char* aliasName) const
{
	auto findPathIter = m_paths.find(Crc32(aliasName));
	if (findPathIter != m_paths.end())
	{
		return &findPathIter->second;
	}

	return nullptr;
}

void Edge::AssetsDirectoryController::prepareAssetPath(const char* aliasName, const FileName& assetPath, FileName& resultPath) const
{
	resultPath.clear();

	const FileName* rootPath = getAssetsRootPath(aliasName);
	if (rootPath)
	{
		resultPath = *rootPath + "/" + assetPath;
	}
}

Edge::FileName Edge::AssetsDirectoryController::prepareAssetPath(const char* aliasName, const FileName& assetPath) const
{
	FileName result;
	prepareAssetPath(aliasName, assetPath, result);

	return result;
}
