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

			bool isBasedOn(TypeMetaInfoID baseTypeID) const;
			void* castTo(void* object, TypeMetaInfoID baseTypeID) const;
		};

		template <typename T>
		constexpr TypeMetaInfoID GetTypeMetaInfoID()
		{
			static_assert(false && "Should be redefined with the particular specialization.");
			return InvalidTypeMetaInfoID;
		}

		template <typename T>
		const TypeMetaInfo& GetTypeMetaInfo()
		{
			static_assert(false && "Should be redefined with the particular specialization.");
			static TypeMetaInfo InvalidTypeMetaInfo(0, 0);
			return InvalidTypeMetaInfo;
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
			return GetTypeMetaInfo<Type>().isBasedOn(GetTypeMetaInfoID<Base>());
		}

		template<typename Type, typename Base>
		Type* CastTo(const Base* object)
		{
			return GetTypeMetaInfo<Type>().castTo(object, GetTypeMetaInfoID<Base>());
		}
	}
}

#define EDGE_RTTI(TYPE, ...)																			\
template<>																								\
constexpr Edge::RTTI::TypeMetaInfoID Edge::RTTI::GetTypeMetaInfoID<TYPE>()								\
{																										\
	return Edge::Crc32(#TYPE);																			\
}																										\
																										\
template<>																								\
inline const Edge::RTTI::TypeMetaInfo& Edge::RTTI::GetTypeMetaInfo<TYPE>()								\
{																										\
	static const TypeMetaInfo TypeMetaInfo =															\
		std::move(RegistryTypeMetaInfo<TYPE, __VA_ARGS__>());											\
	return TypeMetaInfo;																				\
}																							