#pragma region CONST_REFERENCE_IMPL
template<typename T>
void Edge::MTConstReference<T>::releaseReference()
{
	if (m_object)
	{
		const_cast<T*>(m_object)->releaseReferenceObject();
		m_object = nullptr;
	}
}

template <typename T>
void Edge::MTConstReference<T>::assign(const T* object)
{
	static_assert(std::is_base_of_v<MTCountableObjectBase, T>);

	releaseReference();

	if (object && const_cast<T*>(object)->addReferenceCounter())
	{
		m_object = object;
	}
}

template<typename T>
Edge::MTConstReference<T>::MTConstReference(const T* object)
{
	static_assert(std::is_base_of_v<MTCountableObjectBase, T>);

	if (object && const_cast<T*>(object)->addReferenceCounter())
	{
		m_object = object;
	}
}

template<typename T>
Edge::MTConstReference<T>::MTConstReference(const MTConstReference<T>& reference)
{
	static_assert(std::is_base_of_v<MTCountableObjectBase, T>);

	if (reference.m_object && const_cast<T*>(reference.m_object)->addReferenceCounter())
	{
		m_object = reference.m_object;
	}
}

template<typename T>
Edge::MTConstReference<T>::MTConstReference(MTConstReference<T>&& reference)
{
	if (reference.m_object)
	{
		m_object = reference.m_object;
		reference.m_object = nullptr;
	}
}

template<typename T>
Edge::MTConstReference<T>::MTConstReference(const MTReference<T>& reference)
{
	static_assert(std::is_base_of_v<MTCountableObjectBase, T>);

	if (reference.m_object && const_cast<T*>(reference.m_object)->addReferenceCounter())
	{
		m_object = reference.m_object;
	}
}

template<typename T>
template<typename U, typename>
Edge::MTConstReference<T>::MTConstReference(Edge::MTConstReference<U>&& reference)
	: Edge::MTConstReference(std::move(MTConstReference(reference.getObject()))) {}

template<typename T>
template<typename U, typename>
Edge::MTConstReference<T>::MTConstReference(const Edge::MTReference<U>& reference)
	: Edge::MTConstReference(reference.getObject()) {}

template<typename T>
Edge::MTConstReference<T>& Edge::MTConstReference<T>::operator=(const T* objectRef)
{
	assign(objectRef);
	return *this;
}

template<typename T>
Edge::MTConstReference<T>& Edge::MTConstReference<T>::operator=(const MTConstReference<T>& reference)
{
	assign(reference.m_object);
	return *this;
}

template<typename T>
Edge::MTConstReference<T>& Edge::MTConstReference<T>::operator=(MTConstReference<T>&& reference)
{
	assign(reference.m_object);
	return *this;
}

template<typename T>
bool Edge::MTConstReference<T>::operator==(const MTConstReference<T>& reference) const
{
	return m_object == reference.m_object;
}

template<typename T>
bool Edge::MTConstReference<T>::operator!=(const MTConstReference<T>& reference) const
{
	return m_object != reference.m_object;
}

template <typename T1, typename T2>
bool operator<(Edge::MTConstReference<T1> ref1, Edge::MTConstReference<T2> ref2)
{
	return ref1->getObject() < ref2->getObject();
}

template <typename T1, typename T2>
bool operator>(Edge::MTConstReference<T1> ref1, Edge::MTConstReference<T2> ref2)
{
	return ref1->getObject() > ref2->getObject();
}
#pragma endregion

#pragma region REFERENCE_IMPL
template <typename T>
template <typename U, typename>
Edge::MTReference<T>::MTReference(const MTReference<U>& reference)
	: MTConstReference<T>(reference.getObject()) {}

template <typename T>
template <typename U, typename>
Edge::MTReference<T>::MTReference(MTReference<U>&& reference)
	: MTConstReference<T>(std::move(MTReference(reference.getObject()))) {}

template <typename T>
Edge::MTReference<T>& Edge::MTReference<T>::operator=(T* object)
{
	MTConstReference<T>::assign(const_cast<const T*>(object));
	return *this;
}

template <typename T>
Edge::MTReference<T>& Edge::MTReference<T>::operator=(const MTReference<T>& reference)
{
	MTConstReference<T>::assign(const_cast<const T*>(reference.m_object));
	return *this;
}

template <typename T>
Edge::MTReference<T>& Edge::MTReference<T>::operator=(MTReference<T>&& reference)
{
	MTConstReference<T>::assign(const_cast<const T*>(reference.m_object));
	return *this;
}
#pragma endregion