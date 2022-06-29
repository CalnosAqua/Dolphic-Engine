/**	@file	VKDevice.hpp
 *	@brief	Direct3D12 用のデバイスクラス
 */
#pragma	once
#include "ifs/singleton.hpp"
#include <vulkan/vulkan.h>

namespace dlph {
	/**	@file	VKDevice
	 *	@brief	Direct3D12 用のデバイスクラス
	 */
	class VKDevice final : public ISingleton<VKDevice> {
	public:
		//!	@brief	デフォルトコンストラクタ
		VKDevice() noexcept;
		//!	@brief	デストラクタ
		virtual ~VKDevice() noexcept;

		//!	@brief	初期化関数
		bool const init() noexcept;
		//!	@brief	終了関数
		virtual void exit() noexcept;

		//!	@brief	ポインタ取得関数
		VkDevice_T* get() const noexcept;
		//!	@brief	メンバアクセス演算子
		VkDevice_T* operator->() const noexcept;

	private:
		//!	@brief	デバイス
		VkDevice_T* m_device;
	};
}
