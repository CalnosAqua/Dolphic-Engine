/**	@file	math.hpp
 *	@brief	数学系関数群
 */
#pragma once
#include <initializer_list>

namespace dlph {
	//! @brief 円周率
	template <typename T>
	static T constexpr PI = static_cast<T>(3.141592653589793238462643383279L);

	//! @brief ネイピア数
	template <typename T>
	static T constexpr NAPIER = static_cast<T>(2.718281828459045235360287471352L);

	/**	@class	Math
	 *	@brief	数学系関数クラス
	 */
	template <typename T>
	class Math final {
	public	:
		/**	@brief 平方根関数
		 *	@param[in] lhs 左辺の値
		 *	@param[in] rhs 右辺の値
		 *	@retval  0 共に同じ位の大きさ
		 *	@retval +1 左辺の値の方が大きい
		 *	@retval -1 左辺の値の方が小さい
		 */
		static int const compare(T const& lhs, T const& rhs) noexcept;
		/**	@brief 平方根関数
		 *	@param[in] arg 対象データ
		 *	@param[in] mode 計算モード
		 *	@return 計算結果
		 */
		static T const sqrt(T const& arg, bool const& is_speedy = false) noexcept;
		/**	@brief 総和関数
		 *	@param[in] args 対象データ
		 *	@param[in] is_speedy 高速計算モード
		 *	@return 計算結果
		 */
		static T const sum(std::initializer_list<T> const& args, bool const& is_speedy = false) noexcept;
		/**	@brief 総和関数
		 *	@param[in] ptr 配列の先頭へのポインタ
		 *	@param[in] cnt 配列長
		 *	@param[in] is_speedy 高速計算モード
		 *	@return 計算結果
		 */
		static T const sum(T const* const& ptr, size_t const& cnt, bool const& is_speedy = false) noexcept;
		/**	@brief 平均関数
		 *	@param[in] args 対象データ
		 *	@param[in] is_speedy 高速計算モード
		 *	@return 計算結果
		 */
		static T const average(std::initializer_list<T> const& args, bool const& is_speedy = false) noexcept;
		/**	@brief 平均関数
		 *	@param[in] ptr 配列の先頭へのポインタ
		 *	@param[in] cnt 配列長
		 *	@param[in] is_speedy 高速計算モード
		 *	@return 計算結果
		 */
		static T const average(T const* const& ptr, size_t const& cnt, bool const& is_speedy = false) noexcept;
		/**	@brief	クランプ関数
		 *	@param[in] value 左辺の値
		 *	@param[in] min 右辺の値
		 *	@param[in] max 右辺の値
		 *	@return 計算結果
		 */
		static T const clamp(T const& value, T const& min, T const& max) noexcept;
		/**	@brief	ラップ関数
		 *	@param[in] value 左辺の値
		 *	@param[in] min 右辺の値
		 *	@param[in] max 右辺の値
		 *	@return 計算結果
		 */
		static T const loop(T const& value, T const& min, T const& max) noexcept;
	};

	template<typename T>
	inline T const Math<T>::sum(std::initializer_list<T> const& args, bool const& is_speedy) noexcept {
		return sum(args.begin(), args.size(), is_speedy);
	}

	template<typename T>
	inline T const Math<T>::average(std::initializer_list<T> const& args, bool const& is_speedy) noexcept {
		return average(args.begin(), args.size(), is_speedy);
	}
}
