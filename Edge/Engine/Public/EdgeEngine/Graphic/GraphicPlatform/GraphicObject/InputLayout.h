#pragma once

#include "EdgeEngine/Core/HashFunctions/StdHashCombine.h"

#include "IGraphicObject.h"

#include <cstdint>
#include <vector>


namespace Edge
{
	using InputLayoutElementNameHash = uint32_t;
	using InputLayoutElementHash = uint32_t;

	enum class InputLayoutElementType
	{
		Int8,
		Int16,
		Int32,
		UInt8,
		UInt16,
		UInt32,
		Float16,
		Float32,

		Undefined
	};

	using InputLayoutElementHash = uint32_t;
	using InputLayoutElementSemanticNameType = const char*;

	struct InputLayoutElementDesc final
	{
		InputLayoutElementSemanticNameType m_semanticName;
		uint32_t m_index = 0;
		uint32_t m_slot = 0;
		uint32_t m_offset = 0;
		uint32_t m_componentsCount = 0;
		InputLayoutElementType m_type = InputLayoutElementType::Undefined;

		InputLayoutElementHash getHash() const
		{
			InputLayoutElementHash result = 0;

			hashCombine(result, m_semanticName);
			hashCombine(result, m_index);
			hashCombine(result, m_slot);
			hashCombine(result, m_offset);
			hashCombine(result, m_componentsCount);
			hashCombine(result, m_type);

			return result;
		}
	};

	enum class InputLayoutBindingType
	{
		VertexBinding,
		InstanceBinding
	};

	using InputLayoutBindingHash = uint32_t;

	struct InputLayoutBindingDesc final
	{
		uint32_t m_slot = 0;
		uint32_t m_stride = 0;
		InputLayoutBindingType m_type = InputLayoutBindingType::VertexBinding;


		InputLayoutBindingHash getHash() const
		{
			InputLayoutBindingHash result = 0;

			hashCombine(result, m_slot);
			hashCombine(result, m_stride);
			hashCombine(result, m_type);

			return result;
		}
	};

	using InputLayoutHash = uint32_t;

	struct InputLayoutDesc final
	{
		using ElementDescContainer = std::vector<InputLayoutElementDesc>;
		using BindingDescContainer = std::vector<InputLayoutBindingDesc>;

		ElementDescContainer m_elements;
		BindingDescContainer m_bindings;

		InputLayoutHash getHash() const
		{
			InputLayoutHash result = 0;

			for (const auto& element : m_elements)
			{
				hashCombine(result, element.getHash());
			}

			for (const auto& binding : m_bindings)
			{
				hashCombine(result, binding.getHash());
			}

			return result;
		}
	};

	class IInputLayout : public IGraphicObject
	{
	public:
		IInputLayout() = default;

		virtual const InputLayoutDesc& getDesc() const = 0;
	};

	class InputLayoutBase : public IInputLayout
	{
	private:
		const InputLayoutDesc m_desc;

	public:
		InputLayoutBase(const InputLayoutDesc& desc)
			: m_desc(desc) {}

		virtual const InputLayoutDesc& getDesc() const override { return m_desc; }
	};
}
