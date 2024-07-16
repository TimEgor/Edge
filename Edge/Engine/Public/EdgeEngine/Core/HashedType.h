#pragma once

#include "HashFunctions/CRC32.h"

namespace Edge
{
	class HashedType
	{
	public:
		using Type = uint32_t;

		static constexpr Type InvalidType = 0;

	public:
		HashedType() = default;
		virtual ~HashedType() = default;

		static constexpr Type calcType(const char* type) { return Crc32(type); }
	};
}

#define EDGE_HASH_TYPE(TYPE_VAL, TYPE, NAME)											\
	static constexpr TYPE NAME##Type = calcType(TYPE_VAL);								\
	static constexpr TYPE get##NAME##Type() { return NAME##Type; }						\
	virtual TYPE getType() const override { return get##NAME##Type(); }

#define EDGE_SPECIAL_NAMED_HASH_TYPE(NAME_TYPE_VAL, TYPE_VAL, TYPE, NAME)				\
	EDGE_HASH_TYPE(TYPE_VAL, TYPE, NAME)												\
																						\
	static constexpr const char* NAME##TypeName = NAME_TYPE_VAL;						\
	static constexpr const char* get##NAME##TypeName() { return NAME##TypeName ; }		\
	virtual const char* getTypeName() const override { return get##NAME##TypeName(); }

#define EDGE_NAMED_HASH_TYPE(TYPE_VAL, TYPE, NAME)										\
	EDGE_SPECIAL_NAMED_HASH_TYPE(TYPE_VAL, TYPE_VAL, TYPE, NAME)