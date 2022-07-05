/**	@file	random.hpp
 *	@brief	ランダム管理クラス
 */
#pragma once
#include <random>

namespace dlph {
#	if defined(_M_ARM) || defined(_M_IX86)
	//!	@brief	32-bit 版メルセンヌツイスタ
	using MTwister = std::mt19937;
#	elif defined(_M_ARM64) || defined(_M_X64)
	//!	@brief	64-bit 版メルセンヌツイスタ
	using MTwister = std::mt19937_64;
#	endif

	/**	@file	Random
	 *	@brief	ランダム管理クラス
	 */
	class Random final {
	public	:
		//!	@brief	ムーブコンストラクタ
		Random(Random&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		Random(Random const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		Random& operator=(Random&&) & noexcept = default;
		//!	@brief	コピー代入演算子
		Random& operator=(Random const&) & noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		Random() noexcept;
		//!	@brief	デストラクタ
		~Random() noexcept = default;

		//!	@brief	最小値取得関数
		float const min() const noexcept;
		//!	@brief	最大値取得関数
		float const max() const noexcept;

		//!	@brief	最小値設定関数
		Random& min(float const&) noexcept;
		//!	@brief	最大値設定関数
		Random& max(float const&) noexcept;

		//!	@brief	乱数生成関数
		float const generate() noexcept;

	private	:
		//!	@brief	ランダムデヴァイス
		std::random_device m_device;
		//!	@brief	メルセンヌツイスタ
		MTwister m_twister;
		//!	@brief	最小値
		double m_min;
		//!	@brief	最大値
		double m_max;
	};
}
