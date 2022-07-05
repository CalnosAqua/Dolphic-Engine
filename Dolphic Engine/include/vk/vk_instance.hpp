/**	@file	vk_instance.hpp
 *	@brief	Vulkan のインスタンスクラス
 */
#pragma once
#include "util/singleton.hpp"
#include <string>
#include <vulkan/vulkan.h>

namespace dlph {
	/**	@class	VKInstance
	 *	@brief	Vulkan のインスタンスクラス
	 */
	class VKInstance final : public ISingleton<VKInstance> {
	public	:
		//!	@brief	デフォルトコンストラクタ
		VKInstance() noexcept;
		//!	@brief	デストラクタ
		~VKInstance() noexcept;

		//!	@brief	初期化関数
		bool const init(std::string const& name) noexcept;

	private	:
		//!	@brief	Vulkan インスタンス
		VkInstance m_instance;
	};
}
