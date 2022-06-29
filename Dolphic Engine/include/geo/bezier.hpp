/**	@file	avbezier.hpp
 *	@brief	ベジエ曲線テンプレートクラス
 */
#pragma once
#include <vector>
#include <numeric>

namespace dlph {
	/* 宣言 */

	/**	@struct WData<T>
	 *	@brief 重み付きのデータテンプレート構造体
	 */
	template <typename T>
	struct WData {
		//! @brief データ
		T data;
		//! @brief 重み
		float weight;
	};

	/**	@class BezierCurve<T>
	 *	@brief ベジエ曲線テンプレート
	 */
	template <typename T>
	class BezierCurve {
	public	:
		//!	@brief	型情報
		using type_t = T;

		//! @brief 要素
		std::vector<WData<T>> mContents;

		//! @brief デフォルトコンストラクタ
		BezierCurve() noexcept;
		//! @brief デストラクタ
		~BezierCurve() noexcept = default;

		//! @brief 補間関数
		T const interpolate(const float& t, bool const& useBern = true) noexcept;

	private:
		//! @brief バーンシュタイン関数
		float const bern(const unsigned int& n, const unsigned int& k, const float& t) noexcept;
	};
}
