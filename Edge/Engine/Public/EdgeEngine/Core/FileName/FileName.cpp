#include "FileName.h"

#include "EdgeEngine/Core/HashFunctions/CRC32.h"

void Edge::FileName::assign(const ResourceNameCharType* newName)
{
	m_name = newName;

#if EDGE_FILE_NAME_LOWERCASE
	size_t newSize = m_name.size();
	for (size_t i = 0; i < newSize; ++i)
	{
		m_name[i] = std::tolower(m_name[i]);
	}
#endif
}

Edge::FileName::FileName(const ResourceNameCharType* newName)
{
	assign(newName);
}

Edge::FileName::FileName(ResourceNameCharType ch)
{
#if EDGE_FILE_NAME_LOWERCASE
	ch = std::tolower(ch);
#endif

	m_name = ch;
}

Edge::FileName::FileName(const std::string& str)
	: FileName(str.c_str())
{}

Edge::FileName::FileName(const FileName& newName)
	: FileName(newName.m_name)
{}

Edge::FileName& Edge::FileName::operator=(const ResourceNameCharType* newName)
{
	assign(newName);
	return *this;
}

Edge::FileName& Edge::FileName::operator=(ResourceNameCharType ch)
{
#if EDGE_FILE_NAME_LOWERCASE
	m_name[0] = tolower(ch);
#else
	m_name[0] = ch;
#endif
	m_name[1] = '\0';

	return *this;
}

Edge::FileName& Edge::FileName::operator=(const std::string& str)
{
	return operator=(str.c_str());
}

Edge::FileName& Edge::FileName::operator=(const FileName& newName)
{
	return operator=(newName.m_name.c_str());
}

Edge::FileName& Edge::FileName::operator+=(const ResourceNameCharType* name)
{
#if EDGE_FILE_NAME_LOWERCASE
	size_t baseIndex = m_name.size();

	m_name += name;

	size_t newSize = m_name.size();
	for (size_t i = baseIndex; i < newSize; ++i)
	{
		m_name[i] = std::tolower(newName[i]);
	}

#else
	m_name += name;
#endif

	return *this;
}

Edge::FileName& Edge::FileName::operator+=(ResourceNameCharType ch)
{
	m_name += ch;
	return *this;
}

Edge::FileName& Edge::FileName::operator+=(const std::string& str)
{
	return operator+=(str.c_str());
}

Edge::FileName& Edge::FileName::operator+=(const FileName& name)
{
	return operator+=(name.m_name);
}

bool Edge::FileName::operator==(const ResourceNameCharType* name) const
{
	return m_name == name;
}

bool Edge::FileName::operator==(const std::string& str) const
{
	return m_name == str;
}

bool Edge::FileName::operator==(const FileName& name) const
{
	return m_name == name.m_name;
}

bool Edge::FileName::operator!=(const ResourceNameCharType* name) const
{
	return m_name != name;
}

bool Edge::FileName::operator!=(const std::string& str) const
{
	return m_name != str;
}

bool Edge::FileName::operator!=(const FileName& name) const
{
	return m_name != name.m_name;
}

const Edge::FileName::ResourceNameCharType& Edge::FileName::operator[](size_t index) const
{
	return m_name[index];
}

Edge::FileName::ResourceNameCharType& Edge::FileName::operator[](size_t index)
{
	return m_name[index];
}

size_t Edge::FileName::length() const
{
	return m_name.size();
}

Edge::FileNameID Edge::FileName::hash() const
{
	return Crc32(m_name.c_str());
}

void Edge::FileName::clear()
{
	m_name.clear();
}

void Edge::FileName::release()
{
	m_name = ResourceNameContainerType();
}

Edge::FileName Edge::operator+(const FileName& resName, const FileName::ResourceNameCharType* name)
{
	FileName newName(resName);
	newName += name;
	return newName;
}

Edge::FileName Edge::operator+(const FileName::ResourceNameCharType* name, const FileName& resName)
{
	FileName newName(name);
	newName += resName;
	return newName;
}

Edge::FileName Edge::operator+(const FileName& resName, FileName::ResourceNameCharType ch)
{
	FileName newName(resName);
	newName += ch;
	return newName;
}

Edge::FileName Edge::operator+(FileName::ResourceNameCharType ch, const FileName& resName)
{
	FileName newName(ch);
	newName += resName;
	return newName;
}

Edge::FileName Edge::operator+(const FileName& resName, const std::string& str)
{
	FileName newName(resName);
	newName += str;
	return newName;
}

Edge::FileName Edge::operator+(const std::string& str, const FileName& resName)
{
	FileName newName(str);
	newName += resName;
	return newName;
}

Edge::FileName Edge::operator+(const FileName& resName1, const FileName& resName2)
{
	FileName newName(resName1);
	newName += resName2;
	return newName;
}

void parseValue(const char* strVal, Edge::FileName& value)
{
	value = strVal;
}