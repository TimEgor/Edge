#pragma once

#include <unordered_map>

namespace Edge
{
	class FileName;

	class AssetsDirectoryController final
	{
	private:
		using PathID = uint32_t;
		using PathContainer = std::unordered_map<PathID, FileName>;

		PathContainer m_paths;

	public:
		AssetsDirectoryController() = default;

		void addAssetsRootPath(const char* aliasName, const FileName& rootPath);
		const FileName* getAssetsRootPath(const char* aliasName) const;

		void prepareAssetPath(const char* aliasName, const FileName& assetPath, FileName& resultPath) const;
		FileName prepareAssetPath(const char* aliasName, const FileName& assetPath) const;
	};
}
