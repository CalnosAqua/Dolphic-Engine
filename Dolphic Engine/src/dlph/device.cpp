/**	@file	device.cpp
 *	@brief	抽象デバイスクラス
 */
#include "dlph/device.hpp"

namespace dlph {
	Device::Device() noexcept :
		ISingleton()
	{}

	Device::~Device() noexcept {
		exit();
	}
}
