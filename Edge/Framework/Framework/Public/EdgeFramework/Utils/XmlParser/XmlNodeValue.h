#pragma once

#include "pugixml.hpp"

namespace Edge
{
	class XmlNodeValue final
	{
	private:
		pugi::xml_text m_xmlText;

	public:
		XmlNodeValue() = default;
		XmlNodeValue(pugi::xml_text pugiXmlText)
			: m_xmlText(pugiXmlText) {}

		template<typename T>
		T get() const;

		const char* getRaw() const { return m_xmlText.get(); }

		template<typename T>
		void set(T val);
	};

	template <typename T>
	T XmlNodeValue::get() const
	{
		static_assert(false && "Inalid XML Value type");
		return T();
	}

	template <>
	inline bool XmlNodeValue::get() const
	{
		return m_xmlText.as_bool();
	}

	template <>
	inline unsigned XmlNodeValue::get() const
	{
		return m_xmlText.as_uint();
	}

	template <>
	inline int XmlNodeValue::get() const
	{
		return m_xmlText.as_int();
	}

	template <>
	inline float XmlNodeValue::get() const
	{
		return m_xmlText.as_float();
	}

	template <>
	inline double XmlNodeValue::get() const
	{
		return m_xmlText.as_double();
	}

	template <>
	inline const char* XmlNodeValue::get() const
	{
		return m_xmlText.as_string();
	}

	template <typename T>
	void XmlNodeValue::set(T val)
	{
		m_xmlText.set(val);
	}
}
