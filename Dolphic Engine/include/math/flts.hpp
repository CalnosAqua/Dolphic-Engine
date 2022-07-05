/**	@file	flts.hpp
 *	@brief	テンソル便利関数群
 */
#pragma once

#include "math/t2.hpp"
#include "math/t3.hpp"
#include "math/t4.hpp"

#include "math/flt2x2.hpp"
#include "math/flt3x3.hpp"
#include "math/flt4x4.hpp"

namespace dlph {
	/**	@brief	設定関数
	 *	@param[in] 設定用の値
	 *	@return	設定した値
	 */
	Float2 constexpr set_vt(float const& x, float const& y) noexcept;

	/**	@brief	設定関数
	 *	@param[in] 設定用の値
	 *	@return	設定した値
	 */
	Float3 constexpr set_vt(float const& x, float const& y, float const& z) noexcept;

	/**	@brief	設定関数
	 *	@param[in] 設定用の値
	 *	@return	設定した値
	 */
	Float4 constexpr set_vt(float const& x, float const& y, float const& z, float const& w) noexcept;

	/**	@brief	設定関数
	 *	@param[in] 設定用の値
	 *	@return	設定した値
	 */
	Float2x2 constexpr set_mtx(
		float const& m00, float const& m01,
		float const& m10, float const& m11
	) noexcept;

	/**	@brief	設定関数
	 *	@param[in] 設定用の値
	 *	@return	設定した値
	 */
	Float3x3 constexpr set_mtx(
		float const& m00, float const& m01, float const& m02,
		float const& m10, float const& m11, float const& m12,
		float const& m20, float const& m21, float const& m22
	) noexcept;

	/**	@brief	設定関数
	 *	@param[in] 設定用の値
	 *	@return	設定した値
	 */
	Float4x4 constexpr set_mtx(
		float const& m00, float const& m01, float const& m02, float const& m03,
		float const& m10, float const& m11, float const& m12, float const& m13,
		float const& m20, float const& m21, float const& m22, float const& m23,
		float const& m30, float const& m31, float const& m32, float const& m33
	) noexcept;

	/**	@brief	列成分設定関数
	 *	@param[in] mtx	設定先
	 *	@param[in] vt	設定元
	 *	@param[in] idx	設定インデックス
	 */
	void set_mtx_column(Float2x2& mtx, Float2 const& vt, unsigned int const& idx) noexcept;

	/**	@brief	列成分設定関数
	 *	@param[in] mtx	設定先
	 *	@param[in] vt	設定元
	 *	@param[in] idx	設定インデックス
	 */
	void set_mtx_column(Float3x3& mtx, Float3 const& vt, unsigned int const& idx) noexcept;

	/**	@brief	列成分設定関数
	 *	@param[in] mtx	設定先
	 *	@param[in] vt	設定元
	 *	@param[in] idx	設定インデックス
	 */
	void set_mtx_column(Float4x4& mtx, Float4 const& vt, unsigned int const& idx) noexcept;

	/**	@brief	行成分設定関数
	 *	@param[in] mtx	設定先
	 *	@param[in] vt	設定元
	 *	@param[in] idx	設定インデックス
	 */
	void set_mtx_row(Float2x2& mtx, Float2 const& vt, unsigned int const& idx) noexcept;

	/**	@brief	行成分設定関数
	 *	@param[in] mtx	設定先
	 *	@param[in] vt	設定元
	 *	@param[in] idx	設定インデックス
	 */
	void set_mtx_row(Float3x3& mtx, Float3 const& vt, unsigned int const& idx) noexcept;

	/**	@brief	行成分設定関数
	 *	@param[in] mtx	設定先
	 *	@param[in] vt	設定元
	 *	@param[in] idx	設定インデックス
	 */
	void set_mtx_row(Float4x4& mtx, Float4 const& vt, unsigned int const& idx) noexcept;

	/**	@brief	転置関数
	 *	@param[in] mtx	対象
	 */
	void trns_mtx(Float2x2& mtx) noexcept;

	/**	@brief	転置関数
	 *	@param[in] mtx	対象
	 */
	void trns_mtx(Float3x3& mtx) noexcept;

	/**	@brief	転置関数
	 *	@param[in] mtx	対象
	 */
	void trns_mtx(Float4x4& mtx) noexcept;

	/**	@brief	列成分抽出関数
	 *	@param[in] mtx	抽出元
	 *	@param[in] idx	抽出インデックス
	 *	@return	抽出した値
	 */
	Float2 const sep_column(Float2x2 const& mtx, unsigned int const& idx) noexcept;

	/**	@brief	列成分抽出関数
	 *	@param[in] mtx	抽出元
	 *	@param[in] idx	抽出インデックス
	 *	@return	抽出した値
	 */
	Float3 const sep_column(Float3x3 const& mtx, unsigned int const& idx) noexcept;

	/**	@brief	列成分抽出関数
	 *	@param[in] mtx	抽出元
	 *	@param[in] idx	抽出インデックス
	 *	@return	抽出した値
	 */
	Float4 const sep_column(Float4x4 const& mtx, unsigned int const& idx) noexcept;

	/**	@brief	行成分抽出関数
	 *	@param[in] mtx	抽出元
	 *	@param[in] idx	抽出インデックス
	 *	@return	抽出した値
	 */
	Float2 const sep_row(Float2x2 const& mtx, unsigned int const& idx) noexcept;

	/**	@brief	行成分抽出関数
	 *	@param[in] mtx	抽出元
	 *	@param[in] idx	抽出インデックス
	 *	@return	抽出した値
	 */
	Float3 const sep_row(Float3x3 const& mtx, unsigned int const& idx) noexcept;

	/**	@brief	行成分抽出関数
	 *	@param[in] mtx	抽出元
	 *	@param[in] idx	抽出インデックス
	 *	@return	抽出した値
	 */
	Float4 const sep_row(Float4x4 const& mtx, unsigned int const& idx) noexcept;
}
