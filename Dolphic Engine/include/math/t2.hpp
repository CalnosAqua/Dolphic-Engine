/**	@file	t2.hpp
 *	@brief	二成分構造体
 */
#pragma once
#pragma warning(disable : 4201)
#include "const.hpp"
#include <initializer_list>

namespace dlph {
	/**	@struct	Element2
	 *	@brief	二成分構造体
	 */
	template <typename T>
	struct Element2 {
		union {
			//!	@brief	成分数
			T p[T2_CNT];
			struct {
				//!	@brief	第一成分
				T x;
				//!	@brief	第二成分
				T y;
			};
		};
		//!	@brief	ムーブコンストラクタ
		Element2(Element2<T>&& arg) noexcept = default;
		//!	@brief	コピーコンストラクタ
		Element2(Element2<T> const& arg) noexcept = default;
		//!	@brief	ムーブ代入演算子
		Element2<T>& operator=(Element2<T>&& rhs) & noexcept = default;
		//!	@brief	コピー代入演算子
		Element2<T>& operator=(Element2<T> const& rhs) & noexcept = default;

		//!	@brief	初期化子コンストラクタ
		explicit Element2(std::initializer_list<T> const& args) noexcept;
		//!	@brief	コンストラクタ
		constexpr Element2(T const& x, T const& y) noexcept;

		//!	@brief	デフォルトコンストラクタ
		Element2() noexcept;
		//!	@brief	デストラクタ
		~Element2() noexcept = default;
	};

	//!	@brief	単精度浮動小数点数型二成分構造体
	using Float2 = Element2<float>;
	//!	@brief	自然数型二成分構造体
	using UInt2 = Element2<unsigned int>;

	template<typename T>
	inline Element2<T>::Element2(std::initializer_list<T> const& args) noexcept :
		Element2()
	{
		size_t idx = 0U;
		for (T const& arg : args) {
			if (idx > T2_CNT) {
				break;
			}
			p[idx] = arg;
			++idx;
		}
	}

	template<typename T>
	inline constexpr Element2<T>::Element2(T const& x, T const& y) noexcept :
		p{ x, y }
	{}

	template<typename T>
	inline Element2<T>::Element2() noexcept :
		p()
	{}
}
