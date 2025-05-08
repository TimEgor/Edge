#include "RTTI.h"

#include "EdgeCommon/Assert/AssertCore.h"

Edge::RTTI::TypeInfo::TypeInfo(TypeInfoID id, size_t size)
	: m_size(size), m_id(id)
{
	EDGE_ASSERT(size);
	EDGE_ASSERT(id);
}

void Edge::RTTI::TypeInfo::addBaseType(const TypeInfo* info, size_t offset)
{
	EDGE_ASSERT(info);
	EDGE_ASSERT(offset < m_size);

	m_parentTypeInfos.emplace_back(info, offset);
}

bool Edge::RTTI::TypeInfo::isBasedOn(TypeInfoID baseTypeID) const
{
	if (baseTypeID == m_id)
	{
		return true;
	}

	for (const ParentTypeInfoContext& parentContext : m_parentTypeInfos)
	{
		const TypeInfo* parentInfo = parentContext.m_type;
		if (parentInfo->isBasedOn(baseTypeID))
		{
			return true;
		}
	}

	return false;
}

void* Edge::RTTI::TypeInfo::castTo(void* object, TypeInfoID baseTypeID) const
{
	if (baseTypeID == m_id)
	{
		return object;
	}

	for (const ParentTypeInfoContext& parentContext : m_parentTypeInfos)
	{
		const TypeInfo* parentInfo = parentContext.m_type;
		void* parentObject = static_cast<uint8_t*>(object) + parentContext.m_typeOffset;

		void* baseCast = parentInfo->castTo(parentObject, baseTypeID);
		if (baseCast)
		{
			return baseCast;
		}
	}

	return nullptr;
}
