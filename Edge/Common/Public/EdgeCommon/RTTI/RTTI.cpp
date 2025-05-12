#include "RTTI.h"

#include "EdgeCommon/Assert/AssertCore.h"

Edge::RTTI::TypeMetaInfo::TypeMetaInfo(TypeMetaInfoID id, size_t size, ParentTypeMetaInfoCollection&& parentTypeMetaInfos)
	: m_parentTypeMetaInfos(std::move(parentTypeMetaInfos)),
	m_size(size),
	m_id(id)
{
	EDGE_ASSERT(size);
	EDGE_ASSERT(id);

	for (const ParentTypeMetaInfoContext& parentTypeMetaInfo : m_parentTypeMetaInfos)
	{
		EDGE_ASSERT(parentTypeMetaInfo.m_info);
		EDGE_ASSERT(parentTypeMetaInfo.m_typeOffset < m_size);
	}
}

bool Edge::RTTI::TypeMetaInfo::isBasedOn(TypeMetaInfoID baseTypeID) const
{
	if (baseTypeID == m_id)
	{
		return true;
	}

	for (const ParentTypeMetaInfoContext& parentContext : m_parentTypeMetaInfos)
	{
		const TypeMetaInfo* parentInfo = parentContext.m_info;
		if (parentInfo->isBasedOn(baseTypeID))
		{
			return true;
		}
	}

	return false;
}

void* Edge::RTTI::TypeMetaInfo::castTo(void* object, TypeMetaInfoID baseTypeID) const
{
	if (baseTypeID == m_id)
	{
		return object;
	}

	for (const ParentTypeMetaInfoContext& parentContext : m_parentTypeMetaInfos)
	{
		const TypeMetaInfo* parentInfo = parentContext.m_info;
		void* parentObject = static_cast<uint8_t*>(object) + parentContext.m_typeOffset;

		void* baseCast = parentInfo->castTo(parentObject, baseTypeID);
		if (baseCast)
		{
			return baseCast;
		}
	}

	return nullptr;
}
