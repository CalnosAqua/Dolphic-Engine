/**	@file	array_builder.inl
 *	@brief	配列生成クラス
 */
#pragma once
#include "array_builder.hpp"

namespace dlph {
	template<typename T>
	inline ArrayBuilder<T>::ArrayBuilder(ArrayBuilder<T>&& arg) noexcept :
		ArrayBuilder()
	{
		this->Array(arg);
	}

	template<typename T>
	inline ArrayBuilder<T>::ArrayBuilder(ArrayBuilder<T> const& arg) noexcept :
		ArrayBuilder()
	{
		this->Array(arg);
	}

	template<typename T>
	inline ArrayBuilder<T>& ArrayBuilder<T>::operator=(ArrayBuilder<T>&& rhs) & noexcept {
		return this->Array(rhs);
	}

	template<typename T>
	inline ArrayBuilder<T>& ArrayBuilder<T>::operator=(ArrayBuilder<T> const& rhs) & noexcept {
		return this->Array(rhs);
	}

	template<typename T>
	inline ArrayBuilder<T>::ArrayBuilder() noexcept :
		Array<T>()
	{}

	template<typename T>
	inline ArrayBuilder<T>::~ArrayBuilder() noexcept {
		this->~Array();
	}

	template<typename T>
	inline ArrayBuilder<T>::ArrayBuilder(std::initializer_list<T> const& args) noexcept :
		ArrayBuilder()
	{
		this->Array(args);
	}

	template<typename T>
	inline ArrayBuilder<T>::ArrayBuilder(size_t const& size) noexcept :
		ArrayBuilder()
	{
		this->Array(size);
	}
}
