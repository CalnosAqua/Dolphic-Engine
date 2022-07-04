/**	@file	t4.hpp
 *	@brief	四成分構造体
 */
#pragma once
#pragma warning(disable : 4201)
#include "const.hpp"
#include <initializer_list>

namespace dlph {
	/**	@struct	Element4
	 *	@brief	四成分構造体
	 */
	template <typename T>
	struct Element4 {
		union {
			//!	@brief	成分数
			T p[T4_CNT];
			struct {
				//!	@brief	第一成分
				T x;
				//!	@brief	第二成分
				T y;
				//!	@brief	第三成分
				T z;
				//!	@brief	第四成分
				T w;
			};
		};
		//!	@brief	ムーブコンストラクタ
		Element4(Element4<T>&& arg) noexcept = default;
		//!	@brief	コピーコンストラクタ
		Element4(Element4<T> const& arg) noexcept = default;
		//!	@brief	ムーブ代入演算子
		Element4<T>& operator=(Element4<T>&& rhs) & noexcept = default;
		//!	@brief	コピー代入演算子
		Element4<T>& operator=(Element4<T> const& rhs) & noexcept = default;

		//!	@brief	初期化子コンストラクタ
		explicit Element4(std::initializer_list<T> const& args) noexcept;
		//!	@brief	コンストラクタ
		constexpr Element4(T const& x, T const& y, T const& z, T const& w) noexcept;

		//!	@brief	デフォルトコンストラクタ
		Element4() noexcept;
		//!	@brief	デストラクタ
		~Element4() noexcept = default;
	};

	//!	@brief	単精度浮動小数点数型四成分構造体
	using Float4 = Element4<float>;
	//!	@brief	自然数型四成分構造体
	using UInt4 = Element4<unsigned int>;

	template<typename T>
	inline Element4<T>::Element4(std::initializer_list<T> const& args) noexcept :
		Element4()
	{
		size_t idx = 0U;
		for (T const& arg : args) {
			if (idx > T4_CNT) {
				break;
			}
			p[idx] = arg;
			++idx;
		}
	}

	template<typename T>
	inline constexpr Element4<T>::Element4(T const& x, T const& y, T const& z, T const& w) noexcept :
		p{ x, y, z, w }
	{}

	template<typename T>
	inline Element4<T>::Element4() noexcept :
		p()
	{}
}
