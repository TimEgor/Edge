#include "XmlDocument.h"

#include "EdgeCommon/FileName/FileName.h"

bool Edge::XmlDocument::loadFromFile(const FileName& file)
{
	return m_xmlDocument.load_file(file.c_str());
}

bool Edge::XmlDocument::loadFromBuffer(const void* data, size_t dataSize)
{
	return m_xmlDocument.load_buffer(data, dataSize);
}

bool Edge::XmlDocument::loadFromString(const char* str)
{
	return m_xmlDocument.load_string(str);
}

Edge::XmlNode Edge::XmlDocument::getRootNode() const
{
	return m_xmlDocument;
}