/**	@file	fpln3.hpp
 *	@brief	平面クラス
 */
#pragma once
#include "structs/flt2.hpp"
#include "structs/flt3.hpp"
#include "structs/flt4.hpp"

#include "structs/uint2.hpp"

#include "math/fvec3.hpp"
#include "math/fquat.hpp"

namespace dlph {
	/**	@class	FPlane3
	 *	@brief	平面クラス
	 */
	class FPlane3 final {
	public	:
		//!	@brief	ムーブコンストラクタ
		FPlane3(FPlane3&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		FPlane3(FPlane3 const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		FPlane3& operator=(FPlane3&&) & noexcept = default;
		//!	@brief	コピー代入演算子
		FPlane3& operator=(FPlane3 const&) & noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		FPlane3() noexcept;
		//!	@brief	デストラクタ
		~FPlane3() noexcept = default;

		//!	@brief	初期化関数
		FPlane3& init(
			FVector3 const& center,
			FQuaternion const& posture,
			Float2 const& size,
			UInt2 const& partial_count
		) noexcept;
		//!	@brief	終了関数
		void exit() noexcept;

	private	:
		//!	@brief	中心点
		Float3 m_center;
		//!	@brief	姿勢
		Float4 m_posture;
		//!	@brief	横幅
		float m_width;
		//!	@brief	縦幅
		float m_height;
		//!	@brief	横分割数
		size_t m_horizontal;
		//!	@brief	縦分割数
		size_t m_vertical;
	};
}
