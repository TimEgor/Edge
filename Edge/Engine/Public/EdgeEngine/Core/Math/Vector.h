#pragma once

#include <type_traits>

namespace Edge
{
	template <typename T>
	struct Vector2Base final
	{
		using ValueType = T;
		static_assert(std::is_arithmetic_v<ValueType>);

		static constexpr ValueType DefaultValue = 0;

		union
		{
			ValueType m_values[2];

			struct
			{
				ValueType m_x;
				ValueType m_y;
			};
		};

		constexpr Vector2Base() = default;
		constexpr Vector2Base(ValueType val) : Vector2Base(val, val) {}
		constexpr Vector2Base(ValueType x, ValueType y) : m_x(x), m_y(y) {}
		constexpr Vector2Base(const Vector2Base& vector) : m_x(vector.m_x), m_y(vector.m_y) {}

		Vector2Base& operator=(const Vector2Base& vector);
		ValueType operator[](size_t index) const;
		ValueType& operator[](size_t index);

		ValueType getElement(size_t index) const;
		ValueType& getElement(size_t index);

		void setElement(size_t index, ValueType value);
	};

	template <typename T>
	struct Vector3Base final
	{
		using ValueType = T;
		static_assert(std::is_arithmetic_v<ValueType>);

		static constexpr ValueType DefaultValue = 0;

		union
		{
			ValueType m_values[3];

			Vector2Base<ValueType> m_xy;

			struct
			{
				ValueType m_x;
				ValueType m_y;
				ValueType m_z;
			};
		};

		constexpr Vector3Base() = default;
		constexpr Vector3Base(ValueType val) : Vector3Base(val, val, val) {}
		constexpr Vector3Base(ValueType x, ValueType y, ValueType z) : m_x(x), m_y(y), m_z(z) {}
		constexpr Vector3Base(const Vector2Base<ValueType>& vector) : m_x(vector.m_x), m_y(vector.m_y), m_z(DefaultValue) {}
		constexpr Vector3Base(const Vector3Base& vector) : m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z) {}

		Vector3Base& operator=(const Vector2Base<ValueType>& vector);
		Vector3Base& operator=(const Vector3Base& vector);
		ValueType operator[](size_t index) const;
		ValueType& operator[](size_t index);
		
		ValueType getElement(size_t index) const;
		ValueType& getElement(size_t index);

		void setElement(size_t index, ValueType value);
	};

	template <typename T>
	struct Vector4Base final
	{
		using ValueType = T;
		static_assert(std::is_arithmetic_v<ValueType>);

		static constexpr ValueType DefaultValue = 0;

		union
		{
			ValueType m_values[4];

			struct
			{
				Vector2Base<ValueType> m_xy;
				Vector2Base<ValueType> m_zw;
			};

			Vector3Base<ValueType> m_xyz;

			struct
			{
				ValueType m_x;
				ValueType m_y;
				ValueType m_z;
				ValueType m_w;
			};
		};

		constexpr Vector4Base() = default;
		constexpr Vector4Base(ValueType val) : Vector4Base(val, val, val, val) {}
		constexpr Vector4Base(ValueType x, ValueType y, ValueType z, ValueType w) : m_x(x), m_y(y), m_z(z), m_w(w) {}
		constexpr Vector4Base(const Vector2Base<ValueType>& vector) : m_x(vector.m_x), m_y(vector.m_y), m_z(DefaultValue), m_w(DefaultValue) {}
		constexpr Vector4Base(const Vector3Base<ValueType>& vector) : m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z), m_w(DefaultValue) {}
		constexpr Vector4Base(const Vector4Base& vector) : m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z), m_w(vector.m_w) {}

		Vector4Base& operator=(const Vector2Base<ValueType>& vector);
		Vector4Base& operator=(const Vector3Base<ValueType>& vector);
		Vector4Base& operator=(const Vector4Base& vector);
		ValueType operator[](size_t index) const;
		ValueType& operator[](size_t index);

		ValueType getElement(size_t index) const;
		ValueType& getElement(size_t index);

		void setElement(size_t index, ValueType value);
	};

	using FloatVector2 = Vector2Base<float>;
	using FloatVector3 = Vector3Base<float>;
	using FloatVector4 = Vector4Base<float>;

	using UInt8Vector2 = Vector2Base<uint8_t>;
	using UInt8Vector3 = Vector3Base<uint8_t>;
	using UInt8Vector4 = Vector4Base<uint8_t>;

	using Int8Vector2 = Vector2Base<int8_t>;
	using Int8Vector3 = Vector3Base<int8_t>;
	using Int8Vector4 = Vector4Base<int8_t>;

	using UInt16Vector2 = Vector2Base<uint16_t>;
	using UInt16Vector3 = Vector3Base<uint16_t>;
	using UInt16Vector4 = Vector4Base<uint16_t>;

	using Int16Vector2 = Vector2Base<int16_t>;
	using Int16Vector3 = Vector3Base<int16_t>;
	using Int16Vector4 = Vector4Base<int16_t>;

	using UInt32Vector2 = Vector2Base<uint32_t>;
	using UInt32Vector3 = Vector3Base<uint32_t>;
	using UInt32Vector4 = Vector4Base<uint32_t>;

	using Int32Vector2 = Vector2Base<int32_t>;
	using Int32Vector3 = Vector3Base<int32_t>;
	using Int32Vector4 = Vector4Base<int32_t>;

	constexpr FloatVector2 FloatVector2Zero = FloatVector2(0.0f);
	constexpr FloatVector3 FloatVector3Zero = FloatVector3(0.0f);
	constexpr FloatVector4 FloatVector4Zero = FloatVector4(0.0f);

	constexpr FloatVector2 FloatVector2One = FloatVector2(1.0f);
	constexpr FloatVector3 FloatVector3One = FloatVector3(1.0f);
	constexpr FloatVector4 FloatVector4One = FloatVector4(1.0f);

	constexpr FloatVector2 FloatVector2NegativeOne = FloatVector2(-1.0f);
	constexpr FloatVector3 FloatVector3NegativeOne = FloatVector3(-1.0f);
	constexpr FloatVector4 FloatVector4NegativeOne = FloatVector4(-1.0f);

	constexpr UInt8Vector2 UInt8Vector2Zero = UInt8Vector2(0);
	constexpr UInt8Vector3 UInt8Vector3Zero = UInt8Vector3(0);
	constexpr UInt8Vector4 UInt8Vector4Zero = UInt8Vector4(0);

	constexpr Int8Vector2 Int8Vector2Zero = Int8Vector2(0);
	constexpr Int8Vector3 Int8Vector3Zero = Int8Vector3(0);
	constexpr Int8Vector4 Int8Vector4Zero = Int8Vector4(0);

	constexpr UInt16Vector2 UInt16Vector2Zero = UInt16Vector2(0);
	constexpr UInt16Vector3 UInt16Vector3Zero = UInt16Vector3(0);
	constexpr UInt16Vector4 UInt16Vector4Zero = UInt16Vector4(0);

	constexpr Int16Vector2 Int16Vector2Zero = Int16Vector2(0);
	constexpr Int16Vector3 Int16Vector3Zero = Int16Vector3(0);
	constexpr Int16Vector4 Int16Vector4Zero = Int16Vector4(0);

	constexpr UInt32Vector2 UInt32Vector2Zero = UInt32Vector2(0);
	constexpr UInt32Vector3 UInt32Vector3Zero = UInt32Vector3(0);
	constexpr UInt32Vector4 UInt32Vector4Zero = UInt32Vector4(0);

	constexpr Int32Vector2 Int32Vector2Zero = Int32Vector2(0);
	constexpr Int32Vector3 Int32Vector3Zero = Int32Vector3(0);
	constexpr Int32Vector4 Int32Vector4Zero = Int32Vector4(0);

	constexpr FloatVector3 FloatVector3UnitX = FloatVector3(1.0f, 0.0f, 0.0f);
	constexpr FloatVector3 FloatVector3UnitY = FloatVector3(0.0f, 1.0f, 0.0f);
	constexpr FloatVector3 FloatVector3UnitZ = FloatVector3(0.0f, 0.0f, 1.0f);
	constexpr FloatVector3 FloatVector3NegativeUnitX = FloatVector3(-1.0f, 0.0f, 0.0f);
	constexpr FloatVector3 FloatVector3NegativeUnitY = FloatVector3(0.0f, -1.0f, 0.0f);
	constexpr FloatVector3 FloatVector3NegativeUnitZ = FloatVector3(0.0f, 0.0f, -1.0f);
}

#include "Vector.hpp"