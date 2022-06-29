/**	@file	clock.hpp
 *	@brief	汎用時計クラス
 */
#pragma once
#include <chrono>

using namespace std::chrono;
namespace dlph {
	/**	@class Clock
	 *	@brief 汎用時計
	 */
	class Clock final {
	public:
		//!	@brief ムーブコンストラクタ
		Clock(Clock&&) noexcept = default;
		//!	@brief コピーコンストラクタ
		Clock(Clock const&) noexcept = default;
		//!	@brief ムーブ代入演算子
		Clock& operator=(Clock&&) & noexcept = default;
		//!	@brief コピー代入演算子
		Clock& operator=(Clock const&) & noexcept = default;

		//!	@brief デフォルトコンストラクタ
		Clock() noexcept;
		//!	@brief デストラクタ
		~Clock() noexcept = default;

		//!	@brief 初期化関数
		void init() noexcept;
		//!	@brief 終了関数
		void exit() noexcept;
		//!	@brief 更新関数
		void update() noexcept;

		//!	@brief デルタ時間取得関数
		float const delta_time() const noexcept;
		//!	@brief 経過時間取得関数
		float const difference_time() const noexcept;

	private:
		//!	@brief	初期時間
		time_t m_begin;
		//!	@brief	現在時間
		time_t m_current;
		//!	@brief	最新時間
		time_t m_latest;
		//!	@brief	初期化状態
		bool m_inited;
	};
}
