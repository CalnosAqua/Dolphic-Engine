/**	@file	mathutil.hpp
 *	@brief	便利な数学関数群
 */
#pragma once

#include "math/math.hpp"

#include "math/fcomp.hpp"
#include "math/fquat.hpp"
#include "math/frot.hpp"
#include "math/ferot.hpp"
#include "math/fvec4.hpp"
#include "math/fvec3.hpp"
#include "math/fvec2.hpp"
#include "math/fmtx4x4.hpp"
#include "math/fmtx3x3.hpp"
#include "math/fmtx2x2.hpp"

#include <numeric>

namespace dlph {
	template <typename T>
	T const lerp(T const& begin, T const& end, float const& rate) noexcept {
		return (end - begin) * rate + begin;
	}

	template <typename T>
	T const slerp(T const& begin, T const& end, float const& rate) noexcept {
		FRotation th, thr;
		th = angle(begin, end);
		thr = th * rate;
		return (begin * sin(th) * cos(thr) - (begin * cos(th) + end) * sin(thr)) / sin(th);
	}

	template <typename T>
	T const bounce(T const& dir, T const& nor, float const& rate) noexcept {
		T n = normalize(nor);
		float tmp = rate;
		if (tmp < 2.0f) {
			tmp = 2.0f;
		}
		if (tmp < -2.0f) {
			tmp = -2.0f;
		}
		return dir - tmp * dot(-dir, n) * n;
	}

	template <typename T>
	FRotation const angle(T const& base, T const& tar) noexcept {
		FRotation result;
		result = acos(dot(normalize(base), normalize(tar)));
		return result;
	}
}
