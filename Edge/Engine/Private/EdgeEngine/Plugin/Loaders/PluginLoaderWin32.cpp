#if defined(WIN32) || defined(_WIN32)

#include "PluginLoaderWin32.h"

#include "EdgeEngine/Core/FileName/FileNameUtils.h"
#include "EdgeEngine/Core/String/Format.h"
#include "EdgeEngine/Plugin/ExternalPluginCore.h"

#include "EdgeEngine/EngineCore.h"

#include <cassert>

void outputError(const Edge::FileName& name)
{
	LPVOID lpMsgBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&lpMsgBuf,
		0, NULL);

#ifdef _MSC_VER
	OutputDebugStringA(Edge::StringFormat("Plugin issue (\"%s\") error message:\n %s\n", name.c_str(), lpMsgBuf).c_str());
#endif // _MSC_VER

	if (lpMsgBuf)
	{
		LocalFree(lpMsgBuf);
	}
}

EDGE_PLATFORM_MODULE_HANDLE Edge::PluginLoaderWin32::loadModule(PluginModuleID moduleID, const FileName& moduleName)
{
	FileName dirPath;
	FileNameUtils::getFileDirPath(moduleName, dirPath);

	SetDllDirectory(dirPath.c_str());

	EDGE_PLATFORM_MODULE_HANDLE moduleHandle = LoadLibrary(moduleName.c_str());
	if (moduleHandle == EDGE_INVALID_PLATFORM_MODULE_HANDLE)
	{
		outputError(moduleName);
		return EDGE_INVALID_PLATFORM_MODULE_HANDLE;
	}

	const PluginModuleLoadFunctionPtr loadingFunction = reinterpret_cast<PluginModuleLoadFunctionPtr>(
		GetProcAddress(moduleHandle, EDGE_TO_STRING_DEF(EDGE_PLUGIN_MODULE_LOAD_FUNC)));

	if (loadingFunction)
	{
		IEngine& engine = EngineCore::getInstance().getEngine();
		loadingFunction(moduleID, &engine, dirPath);
	}
	else
	{
		FreeLibrary(moduleHandle);
		return EDGE_INVALID_PLATFORM_MODULE_HANDLE;
	}

	return moduleHandle;
}

void Edge::PluginLoaderWin32::unloadModule(EDGE_PLATFORM_MODULE_HANDLE moduleHandle)
{
	assert(moduleHandle != EDGE_INVALID_PLATFORM_MODULE_HANDLE);
	if(!FreeLibrary(moduleHandle))
	{
		outputError("");
	}
}

Edge::IPlugin* Edge::PluginLoaderWin32::loadPlugin(EDGE_PLATFORM_MODULE_HANDLE moduleHandle, PluginModuleID moduleID, const char* typeName)
{
	const std::string functionName = StringFormat("%s%s", EDGE_TO_STRING_DEF(EDGE_PLUGIN_CREATE_FUNC_BASE), typeName);
	const PluginCreatingFunctionPtr creatingFunction = reinterpret_cast<PluginCreatingFunctionPtr>(
		GetProcAddress(moduleHandle, functionName.c_str()));

	if (!creatingFunction)
	{
		return nullptr;
	}

	return creatingFunction(moduleID);
}

void Edge::PluginLoaderWin32::unloadPlugin(EDGE_PLATFORM_MODULE_HANDLE moduleHandle, IPlugin* plugin)
{
	const std::string functionName = StringFormat("%s%s", EDGE_TO_STRING_DEF(EDGE_PLUGIN_RELEASE_FUNC_BASE), plugin->getModuleGeneratorName());
	const PluginReleasingFunctionPtr releaseFunction = reinterpret_cast<PluginReleasingFunctionPtr>(
		GetProcAddress(moduleHandle, functionName.c_str()));

	if (releaseFunction)
	{
		releaseFunction(plugin);
	}
}

void Edge::PluginLoaderWin32::getNativePluginModulePath(const char* title, FileName& outPath) const
{
	outPath.clear();

	char tmpPathBuffer[512] = "\0";

	OPENFILENAME openFileName;
	ZeroMemory(&openFileName, sizeof(openFileName));
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.lpstrFile = tmpPathBuffer;
	openFileName.nMaxFile = sizeof(tmpPathBuffer);
	openFileName.lpstrFilter = "Plugin Module (.dll)\0*.dll\0";
	openFileName.nFilterIndex = 1;
	openFileName.lpstrTitle = title ? title : "Plugin module";
	openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&openFileName))
	{
		outPath = tmpPathBuffer;
	}
}

#endif