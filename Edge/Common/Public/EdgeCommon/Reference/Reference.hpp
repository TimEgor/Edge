#pragma region CONST_REFERENCE_IMPL
template<typename T>
void Edge::ConstReference<T>::release()
{
	if (m_object)
	{
		const_cast<T*>(m_object)->releaseReferenceObject();
		m_object = nullptr;
	}
}

template <typename T>
void Edge::ConstReference<T>::assign(const T* object)
{
	static_assert(std::is_base_of_v<MTCountableObjectBase, T>);

	release();

	if (object)
	{
		const_cast<T*>(object)->addReferenceCounter();
		m_object = object;
	}
}

template<typename T>
Edge::ConstReference<T>::ConstReference(const T* object)
{
	static_assert(std::is_base_of_v<MTCountableObjectBase, T>);

	if (object)
	{
		const_cast<T*>(object)->addReferenceCounter();
		m_object = object;
	}
}

template<typename T>
Edge::ConstReference<T>::ConstReference(const ConstReference<T>& reference)
{
	static_assert(std::is_base_of_v<MTCountableObjectBase, T>);

	if (reference.m_object)
	{
		const_cast<T*>(reference.m_object)->addReferenceCounter();
		m_object = reference.m_object;
	}
}

template<typename T>
Edge::ConstReference<T>::ConstReference(ConstReference<T>&& reference)
{
	if (reference.m_object)
	{
		m_object = reference.m_object;
		reference.m_object = nullptr;
	}
}

template<typename T>
Edge::ConstReference<T>::ConstReference(const Reference<T>& reference)
{
	static_assert(std::is_base_of_v<MTCountableObjectBase, T>);

	if (reference.m_object)
	{
		const_cast<T*>(reference.m_object)->addReferenceCounter();
		m_object = reference.m_object;
	}
}

template<typename T>
template<typename U, typename>
Edge::ConstReference<T>::ConstReference(Edge::ConstReference<U>&& reference)
	: Edge::ConstReference(std::move(ConstReference(reference.getObject()))) {}

template<typename T>
template<typename U, typename>
Edge::ConstReference<T>::ConstReference(const Edge::Reference<U>& reference)
	: Edge::ConstReference(reference.getObject()) {}

template<typename T>
Edge::ConstReference<T>& Edge::ConstReference<T>::operator=(const ConstReference<T>& reference)
{
	assign(reference.m_object);
	return *this;
}

template<typename T>
Edge::ConstReference<T>& Edge::ConstReference<T>::operator=(ConstReference<T>&& reference)
{
	assign(reference.m_object);
	return *this;
}

template<typename T>
bool Edge::ConstReference<T>::operator==(const ConstReference<T>& reference) const
{
	return m_object == reference.m_object;
}

template<typename T>
bool Edge::ConstReference<T>::operator!=(const ConstReference<T>& reference) const
{
	return m_object != reference.m_object;
}

template <typename T1, typename T2>
bool operator<(Edge::ConstReference<T1> ref1, Edge::ConstReference<T2> ref2)
{
	return ref1->getObject() < ref2->getObject();
}

template <typename T1, typename T2>
bool operator>(Edge::ConstReference<T1> ref1, Edge::ConstReference<T2> ref2)
{
	return ref1->getObject() > ref2->getObject();
}
#pragma endregion

#pragma region REFERENCE_IMPL
template <typename T>
template <typename U, typename>
Edge::Reference<T>::Reference(const Reference<U>& reference)
	: ConstReference<T>(reference.getObject()) {}

template <typename T>
template <typename U, typename>
Edge::Reference<T>::Reference(Reference<U>&& reference)
	: ConstReference<T>(std::move(Reference(reference.getObject()))) {}

template <typename T>
Edge::Reference<T>& Edge::Reference<T>::operator=(const Reference<T>& reference)
{
	ConstReference<T>::assign(const_cast<const T*>(reference.m_object));
	return *this;
}

template <typename T>
Edge::Reference<T>& Edge::Reference<T>::operator=(Reference<T>&& reference)
{
	ConstReference<T>::assign(const_cast<const T*>(reference.m_object));
	return *this;
}
#pragma endregion