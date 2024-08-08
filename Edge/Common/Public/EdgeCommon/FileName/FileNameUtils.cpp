#include "FileNameUtils.h"

#include <filesystem>


void Edge::FileNameUtils::getFileName(const FileName& path, FileName& resultName)
{
	const std::filesystem::path tmpPath(path.c_str());
	resultName = tmpPath.filename().string();
}

Edge::FileName Edge::FileNameUtils::getFileName(const FileName & path)
{
	const std::filesystem::path tmpPath(path.c_str());
	return tmpPath.filename().string();
}

void Edge::FileNameUtils::getFileDirPath(const FileName& path, FileName& resultPath)
{
	const std::filesystem::path tmpPath(path.c_str());
	resultPath = tmpPath.parent_path().string();
}

Edge::FileName Edge::FileNameUtils::getFileDirPath(const FileName & path)
{
	const std::filesystem::path tmpPath(path.c_str());
	return tmpPath.parent_path().string();
}

void Edge::FileNameUtils::getFileExtension(const FileName& path, FileName& resultExtension)
{
	const std::filesystem::path tmpPath(path.c_str());
	resultExtension = tmpPath.extension().string();
}

Edge::FileName Edge::FileNameUtils::getFileExtension(const FileName& path)
{
	const std::filesystem::path tmpPath(path.c_str());
	return tmpPath.extension().string();
}

void Edge::FileNameUtils::removeExtension(FileName& name)
{
	std::filesystem::path tmpPath(name.c_str());
	name = tmpPath.replace_extension().string();
}

Edge::FileName Edge::FileNameUtils::removeExtension(const FileName& name)
{
	std::filesystem::path tmpPath(name.c_str());
	return tmpPath.replace_extension().string();
}