#pragma once

#include "EdgeCommon/CommonMacros.h"
#include "EdgeCommon/HashFunctions/CRC32.h"

#include <vector>

namespace Edge
{
	namespace RTTI
	{
		using TypeMetaInfoID = uint32_t;
		inline constexpr TypeMetaInfoID InvalidTypeMetaInfoID = 0;

		class TypeMetaInfo final
		{
		public:
			struct ParentTypeMetaInfoContext final
			{
				const TypeMetaInfo* m_info = nullptr;
				size_t m_typeOffset = 0;

				ParentTypeMetaInfoContext() = default;
				ParentTypeMetaInfoContext(const TypeMetaInfo* info, size_t offset)
					: m_info(info),
					m_typeOffset(offset) {
				}
			};

			using ParentTypeMetaInfoCollection = std::vector<ParentTypeMetaInfoContext>;

		private:
			ParentTypeMetaInfoCollection m_parentTypeMetaInfos;
			const size_t m_size = 0;
			const TypeMetaInfoID m_id = 0;

		public:
			TypeMetaInfo(TypeMetaInfoID id, size_t size,
				ParentTypeMetaInfoCollection&& parentTypeMetaInfos = ParentTypeMetaInfoCollection());
			TypeMetaInfo(const TypeMetaInfo&) = default;
			TypeMetaInfo(TypeMetaInfo&&) = default;

			bool isBasedOn(const TypeMetaInfo& baseType) const;
			void* castTo(void* object, const TypeMetaInfo& baseType) const;
		};

		template <typename T>
		constexpr TypeMetaInfoID GetTypeMetaInfoID()
		{
			return T::GetMetaInfoID();
		}

		template <typename T>
		const TypeMetaInfo& GetTypeMetaInfo()
		{
			return T::GetMetaInfo();
		}

		template<typename Type, typename Base>													
		size_t GetBaseTypeOffset()
		{
			static_assert(std::is_base_of_v<Base, Type>);
			return reinterpret_cast<uint8_t*>(static_cast<Base*>(reinterpret_cast<Type*>(0x10000))) -
				reinterpret_cast<uint8_t*>(reinterpret_cast<Type*>(0x10000));
		}

		template<typename Type, typename ...Bases>
		TypeMetaInfo RegistryTypeMetaInfo()
		{
			return std::move(TypeMetaInfo(GetTypeMetaInfoID<Type>(), sizeof(Type),
		{{&(GetTypeMetaInfo<Bases>()), GetBaseTypeOffset<Type, Bases>()}...}));
		}

		template<typename Type, typename Base>
		bool IsBasedOn()
		{
			return GetTypeMetaInfo<Type>().isBasedOn(GetTypeMetaInfo<Base>());
		}

		template<typename Base, typename Type>
		bool IsObjectBasedOn(const Type& object)
		{
			return object.GetObjectTypeMetaInfo().isBasedOn(GetTypeMetaInfo<Base>());
		}

		template<typename Type, typename Base>
		Type* CastTo(const Base* object)
		{
			return GetTypeMetaInfo<Type>().castTo(object, GetTypeMetaInfoID<Base>());
		}
	}
}

#define EDGE_RTTI(TYPE, ...)												\
static constexpr Edge::RTTI::TypeMetaInfoID GetMetaInfoID()					\
{																			\
	return Edge::Crc32(#TYPE);												\
}																			\
																			\
static const Edge::RTTI::TypeMetaInfo& GetMetaInfo()						\
{																			\
	static const Edge::RTTI::TypeMetaInfo TypeMetaInfo =					\
		std::move(Edge::RTTI::RegistryTypeMetaInfo<TYPE, __VA_ARGS__>());	\
	return TypeMetaInfo;													\
}

#define EDGE_RTTI_OBJECT(TYPE, PRE_MODIFIER, POST_MODIFIER)										\
	PRE_MODIFIER Edge::RTTI::TypeMetaInfoID GetObjectTypeMetaInfoID() const POST_MODIFIER		\
	{																							\
		return GetMetaInfoID();																	\
	}																							\
																								\
	PRE_MODIFIER const Edge::RTTI::TypeMetaInfo& GetObjectTypeMetaInfo() const POST_MODIFIER	\
	{																							\
		return GetMetaInfo();																	\
	}																							

#define EDGE_RTTI_VIRTUAL(TYPE, ...)			\
	EDGE_RTTI(TYPE, __VA_ARGS__)				\
	EDGE_RTTI_OBJECT(TYPE, virtual, override)

#define EDGE_RTTI_VIRTUAL_BASE(TYPE)			\
	EDGE_RTTI(TYPE)								\
	EDGE_RTTI_OBJECT(TYPE, virtual, )

#define EDGE_RTTI_TYPE_ID(TYPE) (Edge::RTTI::GetTypeMetaInfoID<TYPE>())
#define EDGE_RTTI_TYPE_META_INFO(TYPE) (Edge::RTTI::GetTypeMetaInfo<TYPE>())