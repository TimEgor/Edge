#include "XmlNode.h"

bool Edge::XmlNodeIterator::operator==(const XmlNodeIterator& iter) const
{
	return m_xmlNodeIterator == iter.m_xmlNodeIterator;
}

bool Edge::XmlNodeIterator::operator!=(const XmlNodeIterator& iter) const
{
	return m_xmlNodeIterator != iter.m_xmlNodeIterator;
}

Edge::XmlNode Edge::XmlNodeIterator::operator*() const
{
	return m_xmlNodeIterator.operator*();
}

Edge::XmlNodeIterator& Edge::XmlNodeIterator::operator++()
{
	m_xmlNodeIterator = m_xmlNodeIterator.operator++();
	return *this;
}

Edge::XmlNodeIterator Edge::XmlNodeIterator::operator++(int)
{
	const XmlNodeIterator tmp = *this;
	m_xmlNodeIterator = m_xmlNodeIterator.operator++();
	return tmp;
}

Edge::XmlNodeIterator& Edge::XmlNodeIterator::operator--()
{
	m_xmlNodeIterator = m_xmlNodeIterator.operator--();
	return *this;
}

Edge::XmlNodeIterator Edge::XmlNodeIterator::operator--(int)
{
	const XmlNodeIterator tmp = *this;
	m_xmlNodeIterator = m_xmlNodeIterator.operator--();
	return tmp;
}

bool Edge::XmlNamedNodeIterator::operator==(const XmlNamedNodeIterator& iter) const
{
	return m_xmlNodeIterator == iter.m_xmlNodeIterator;
}

bool Edge::XmlNamedNodeIterator::operator!=(const XmlNamedNodeIterator& iter) const
{
	return m_xmlNodeIterator != iter.m_xmlNodeIterator;
}

Edge::XmlNode Edge::XmlNamedNodeIterator::operator*() const
{
	return m_xmlNodeIterator.operator*();
}

Edge::XmlNamedNodeIterator& Edge::XmlNamedNodeIterator::operator++()
{
	m_xmlNodeIterator = m_xmlNodeIterator.operator++();
	return *this;
}

Edge::XmlNamedNodeIterator Edge::XmlNamedNodeIterator::operator++(int)
{
	const XmlNamedNodeIterator tmp = *this;
	m_xmlNodeIterator = m_xmlNodeIterator.operator++();
	return tmp;
}

Edge::XmlNamedNodeIterator& Edge::XmlNamedNodeIterator::operator--()
{
	m_xmlNodeIterator = m_xmlNodeIterator.operator--();
	return *this;
}

Edge::XmlNamedNodeIterator Edge::XmlNamedNodeIterator::operator--(int)
{
	const XmlNamedNodeIterator tmp = *this;
	m_xmlNodeIterator = m_xmlNodeIterator.operator--();
	return tmp;
}

Edge::XmlNode Edge::XmlNode::getChild(const char* name) const
{
	return m_xmlNode.child(name);
}

Edge::XmlNodeRange<Edge::XmlNodeIterator> Edge::XmlNode::getAllChildren() const
{
	pugi::xml_object_range<pugi::xml_node_iterator> xmlRange = m_xmlNode.children();
	return XmlNodeRange{ XmlNodeIterator(xmlRange.begin()), XmlNodeIterator(xmlRange.end()) };
}

Edge::XmlNodeRange<Edge::XmlNamedNodeIterator> Edge::XmlNode::getChildren(const char* name) const
{
	pugi::xml_object_range<pugi::xml_named_node_iterator> xmlRange = m_xmlNode.children(name);
	return XmlNodeRange{ XmlNamedNodeIterator(xmlRange.begin()), XmlNamedNodeIterator(xmlRange.end()) };
}

Edge::XmlNode Edge::XmlNode::getFirstChild() const
{
	return m_xmlNode.first_child();
}

Edge::XmlNode Edge::XmlNode::getLastChild() const
{
	return m_xmlNode.last_child();
}

Edge::XmlNode Edge::XmlNode::getNextSibling() const
{
	return m_xmlNode.next_sibling();
}

Edge::XmlNode Edge::XmlNode::getPrevSibling() const
{
	return m_xmlNode.previous_sibling();
}

const char* Edge::XmlNode::getName() const
{
	return m_xmlNode.name();
}

bool Edge::XmlNode::setName(const char* name)
{
	return m_xmlNode.set_name(name);
}

Edge::XmlNodeValue Edge::XmlNode::getValue() const
{
	return m_xmlNode.text();
}
