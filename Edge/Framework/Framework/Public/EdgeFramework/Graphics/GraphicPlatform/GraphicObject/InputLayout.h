#pragma once

#include "EdgeCommon/HashFunctions/StdHashCombine.h"

#include "GraphicObject.h"

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

			HashCombine(result, m_semanticName);
			HashCombine(result, m_index);
			HashCombine(result, m_slot);
			HashCombine(result, m_offset);
			HashCombine(result, m_componentsCount);
			HashCombine(result, m_type);

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

			HashCombine(result, m_slot);
			HashCombine(result, m_stride);
			HashCombine(result, m_type);

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
				HashCombine(result, element.getHash());
			}

			for (const auto& binding : m_bindings)
			{
				HashCombine(result, binding.getHash());
			}

			return result;
		}
	};

	class InputLayout : public GraphicObject
	{
	private:
		const InputLayoutDesc m_desc;

	public:
		InputLayout(const InputLayoutDesc& desc)
			: m_desc(desc) {}

		const InputLayoutDesc& getDesc() const { return m_desc; }
	};
}
