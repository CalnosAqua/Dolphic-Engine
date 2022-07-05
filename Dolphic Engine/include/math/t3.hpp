/**	@file	t3.hpp
 *	@brief	三成分構造体
 */
#pragma once
#pragma warning(disable : 4201)
#include "const.hpp"
#include <initializer_list>

namespace dlph {
	/**	@struct	Element3
	 *	@brief	三成分構造体
	 */
	template <typename T>
	struct Element3 {
		union {
			//!	@brief	成分数
			T p[T3_CNT];
			struct {
				//!	@brief	第一成分
				T x;
				//!	@brief	第二成分
				T y;
				//!	@brief	第三成分
				T z;
			};
		};
		//!	@brief	ムーブコンストラクタ
		Element3(Element3<T>&& arg) noexcept = default;
		//!	@brief	コピーコンストラクタ
		Element3(Element3<T> const& arg) noexcept = default;
		//!	@brief	ムーブ代入演算子
		Element3<T>& operator=(Element3<T>&& rhs) & noexcept = default;
		//!	@brief	コピー代入演算子
		Element3<T>& operator=(Element3<T> const& rhs) & noexcept = default;

		//!	@brief	初期化子コンストラクタ
		explicit Element3(std::initializer_list<T> const& args) noexcept;
		//!	@brief	コンストラクタ
		constexpr Element3(T const& x, T const& y, T const& z) noexcept;

		//!	@brief	デフォルトコンストラクタ
		Element3() noexcept;
		//!	@brief	デストラクタ
		~Element3() noexcept = default;
	};

	//!	@brief	単精度浮動小数点数型三成分構造体
	using Float3 = Element3<float>;
	//!	@brief	自然数型三成分構造体
	using UInt3 = Element3<unsigned int>;

	template<typename T>
	inline Element3<T>::Element3(std::initializer_list<T> const& args) noexcept :
		Element3()
	{
		size_t idx = 0U;
		for (T const& arg : args) {
			if (idx > T3_CNT) {
				break;
			}
			p[idx] = arg;
			++idx;
		}
	}

	template<typename T>
	inline constexpr Element3<T>::Element3(T const& x, T const& y, T const& z) noexcept :
		p{ x, y, z }
	{}

	template<typename T>
	inline Element3<T>::Element3() noexcept :
		p()
	{}
}
