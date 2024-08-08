#pragma once

#include <string>

namespace Edge
{
	std::wstring ConvertStringToWString(const std::string& str);
	std::string ConvertWStringToString(const std::wstring& wstr);

	template <typename T>
	std::string convertToString(T val)
	{
		return std::to_string(val);
	}
}
