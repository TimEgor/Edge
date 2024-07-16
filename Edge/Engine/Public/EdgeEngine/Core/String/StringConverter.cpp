#include "StringConverter.h"

#include <codecvt>
#include <locale>

std::wstring Edge::ConvertStringToWString(const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	return converter.from_bytes(str);
}

std::string Edge::ConvertWStringToString(const std::wstring& wstr)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	return converter.to_bytes(wstr);
}
