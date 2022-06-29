/**	@file	device.hpp
 *	@brief	抽象デバイスクラス
 */
#pragma once
#include "ifs/singleton.hpp"

namespace dlph {
	/**	@class	Device
	 *	@brief	抽象デバイスクラス
	 */
	class Device : public ISingleton<Device> {
	public	:
		//!	@brief	デフォルトコンストラクタ
		Device() noexcept;
		//!	@brief	デストラクタ
		virtual ~Device() noexcept;

		//!	@brief	初期化関数
		virtual bool const init() noexcept = 0;
		//!	@brief	終了関数
		virtual void exit() noexcept = 0;
	};
}
