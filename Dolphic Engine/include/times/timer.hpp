/**	@file	timer.hpp
 *	@brief	汎用タイムスイッチクラス
 */
#pragma once
#include "clock.hpp"

namespace dlph {
	/**	@class	Timer
	 *	@brief	汎用タイムスイッチ
	 */
	class Timer final {
	public	:
		//!	@brief	ムーブコンストラクタ
		Timer(Timer&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		Timer(Timer const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		Timer& operator=(Timer&&) noexcept = default;
		//!	@brief	コピー代入演算子
		Timer& operator=(Timer const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		Timer() noexcept;
		//!	@brief	デストラクタ
		~Timer() noexcept = default;

		//!	@brief	更新関数
		void update(Clock const&) noexcept;
		//!	@brief	再設定関数
		void reset() noexcept;

		//!	@brief	目標時間設定関数
		void  target_time(float const&) noexcept;

		//!	@brief	完了状態調査関数
		bool const is_finished() const noexcept;
		//!	@brief	目標時間取得関数
		float const target_time() const noexcept;
		//!	@brief	現在時間取得関数
		float const current_time() const noexcept;

		//!	@brief	経過時間率取得関数
		float const progress_rate() const noexcept;
		//!	@brief	経過時間差分取得関数
		float const progress_difference() const noexcept;

	private	:
		/**	@enum	TimerState
		 *	@brief	汎用タイムスイッチの状態
		 */
		enum class TimerState : unsigned char {
			//!	@brief	待機状態
			Wait,
			//!	@brief	計測状態
			Progress,
			//!	@brief	完了状態
			Finish
		};

		//!	@brief	状態
		TimerState m_state;
		//!	@brief	目標経過時間
		float m_target;
		//!	@brief	現在経過時間
		float m_current;
	};
}
