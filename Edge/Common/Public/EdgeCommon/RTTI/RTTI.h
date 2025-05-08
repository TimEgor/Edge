#pragma once

#include <vector>

namespace Edge
{
	namespace RTTI
	{
		using TypeInfoID = uint32_t;

		class TypeInfo final
		{
		private:
			struct ParentTypeInfoContext final
			{
				const TypeInfo* m_type = nullptr;
				size_t m_typeOffset = 0;

				ParentTypeInfoContext() = default;
				ParentTypeInfoContext(const TypeInfo* type, size_t offset)
					: m_type(type), m_typeOffset(offset) {
				}
			};

			std::vector<ParentTypeInfoContext> m_parentTypeInfos;
			const size_t m_size = 0;
			const TypeInfoID m_id = 0;

		public:
			TypeInfo(TypeInfoID id, size_t size);

			void addBaseType(const TypeInfo* info, size_t offset);

			bool isBasedOn(TypeInfoID baseTypeID) const;
			void* castTo(void* object, TypeInfoID baseTypeID) const;
		};
	}
}


#define EDGE_RTTI_TYPE_INFO_GETTER(TYPE)										\
	static Edge::RTTI::TypeInfo& GetRuntimeTimeTypeInfo()						\
	{																			\
		static Edge::RTTI::TypeInfo	typeInfo(Edge::Crc32(#TYPE), sizeof(TYPE));	\
		return typeInfo;														\
	}
