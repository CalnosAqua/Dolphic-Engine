/**	@file	mathutil.cpp
 *	@brief	便利な数学関数群
 */
#include "math/mathutil.hpp"
#include "math/math.hpp"
#include <cfloat>

namespace dlph {
	FMatrix3x3 const toMtx(FComplex const& arg) noexcept {
		FMatrix3x3 result;
		float sin, cos;

		sin = arg.y;
		cos = arg.x;

		result.m00 = result.m11 = cos;
		result.m01 = -sin;
		result.m10 = +sin;

		return result;
	}

	FMatrix4x4 const toMtx(FQuaternion const& arg) noexcept {
		FMatrix4x4 result;

		result.m00 = Math<float>::sum({ arg.x * arg.x, -(arg.y * arg.y), -(arg.z * arg.z), arg.w * arg.w });
		result.m11 = Math<float>::sum({ -(arg.x * arg.x), arg.y * arg.y, -(arg.z * arg.z), arg.w * arg.w });
		result.m22 = Math<float>::sum({ -(arg.x * arg.x), -(arg.y * arg.y), arg.z * arg.z, arg.w * arg.w });

		result.m21 = 2.0f * Math<float>::sum({ arg.y * arg.z, arg.x * arg.w });
		result.m10 = 2.0f * Math<float>::sum({ arg.x * arg.y, arg.z * arg.w });
		result.m02 = 2.0f * Math<float>::sum({ arg.x * arg.z, arg.y * arg.w });

		result.m01 = 2.0f * Math<float>::sum({ arg.x * arg.y, -(arg.z * arg.w) });
		result.m12 = 2.0f * Math<float>::sum({ arg.y * arg.z, -(arg.x * arg.w) });
		result.m20 = 2.0f * Math<float>::sum({ arg.x * arg.z, -(arg.y * arg.w) });

		return result;
	}

	FMatrix3x3 const toMtx(FRotation const& arg) noexcept {
		static FMatrix3x3 result;
		float s, c;

		s = sin(arg);
		c = cos(arg);

		result.m00	= result.m11	= c;
		result.m01	= -s;
		result.m10	= s;

		return result;
	}

	FMatrix4x4 const toMtx(FEulerRotation const& arg) noexcept {
		FMatrix4x4 pitch, yaw, roll;

		pitch.m11	= pitch.m22	= cos(arg.x);
		yaw.m00		= yaw.m22	= cos(arg.y);
		roll.m00	= roll.m11	= cos(arg.z);

		pitch.m12	= pitch.m12	= sin(arg.x);
		yaw.m02		= yaw.m20	= sin(arg.y);
		roll.m01	= roll.m10	= sin(arg.z);

		pitch.m12	*= -1.0f;
		yaw.m20		*= -1.0f;
		roll.m01	*= -1.0f;

		return pitch * yaw * roll;
	}

	FRotation const toRot(FComplex const& arg) noexcept {
		FRotation result;
		result = atan(arg.x, arg.y);
		return result;
	}

	FEulerRotation const toRot(FQuaternion const&) noexcept {
		// TODO : 変換式を調べて実装する。
		return FEulerRotation();
	}

	FRotation const toRot(FMatrix3x3 const&) noexcept {
		// TODO : 変換式を調べて実装する。
		return FRotation();
	}

	FEulerRotation const toRot(FMatrix4x4 const&) noexcept {
		// TODO : 変換式を調べて実装する。
		return FEulerRotation();
	}

	FComplex const toCmp(FMatrix3x3 const&) noexcept {
		// TODO : 変換式を調べて実装する。
		return FComplex();
	}

	FQuaternion const toQt(FMatrix4x4 const& arg) noexcept {
		float mult, v, biggest = FLT_MIN;
		unsigned long int i = 0U;
		FQuaternion result = FQTR_ZERO;
		FVector4 tmp = FVT4_ZERO;

		tmp.x = Math<float>::sum({ arg.m00, -arg.m11, -arg.m22, 1.0f });
		tmp.y = Math<float>::sum({ -arg.m00,  arg.m11, -arg.m22, 1.0f });
		tmp.z = Math<float>::sum({ -arg.m00, -arg.m11,  arg.m22, 1.0f });
		tmp.w = Math<float>::sum({ arg.m00,  arg.m11,  arg.m22, 1.0f });

		for (unsigned long int idx = 0U; idx < 4U; idx++) {
			if (biggest > tmp.p[idx]) {
				biggest = tmp.p[idx];
				i = idx;
			}
		}
		if (tmp.p[i] < 0.0f) {
			return result;
		}

		v = Math<float>::sqrt(tmp.p[i]) * 0.5f;
		mult = 0.25f / v;
		result.p[i] = v;
		switch (i) {
		case 0:
			result.y = Math<float>::sum({ arg.m01,  arg.m10 }) * mult;
			result.z = Math<float>::sum({ arg.m20,  arg.m02 }) * mult;
			result.w = Math<float>::sum({ arg.m12, -arg.m21 }) * mult;
			break;
		case 1:
			result.x = Math<float>::sum({ arg.m01,  arg.m10 }) * mult;
			result.z = Math<float>::sum({ arg.m12,  arg.m21 }) * mult;
			result.w = Math<float>::sum({ arg.m20, -arg.m02 }) * mult;
			break;
		case 2:
			result.x = Math<float>::sum({ arg.m20,  arg.m02 }) * mult;
			result.y = Math<float>::sum({ arg.m12,  arg.m21 }) * mult;
			result.w = Math<float>::sum({ arg.m01, -arg.m10 }) * mult;
			break;
		case 3:
			result.x = Math<float>::sum({ arg.m12, -arg.m21 }) * mult;
			result.y = Math<float>::sum({ arg.m20, -arg.m02 }) * mult;
			result.z = Math<float>::sum({ arg.m01, -arg.m10 }) * mult;
			break;
		}

		return result;
	}

	FComplex const toCmp(FRotation const& arg) noexcept {
		FComplex result;
		result.x = cos(arg);
		result.y = sin(arg);
		return result;
	}

	FQuaternion const toQt(FEulerRotation const& arg) noexcept {
		FQuaternion pitch, yaw, roll;

		pitch.w	= cos(arg.x);
		pitch.x	= sin(arg.x);
		yaw.w	= cos(arg.y);
		yaw.y	= sin(arg.y);
		roll.w	= cos(arg.z);
		roll.z	= sin(arg.z);

		return pitch * yaw * roll;
	}

	FMatrix3x3 const makeTransit(HandSide const& hs, FVector2 const& vt) noexcept {
		FMatrix3x3 result = FMTX3x3_UNIT;

		switch (hs) {
		case HandSide::LHS:
			result.m02 = vt.x;
			result.m12 = vt.y;
			break;
		case HandSide::RHS:
			result.m20 = vt.x;
			result.m21 = vt.y;
			break;
		}

		return result;
	}

	FMatrix4x4 const makeTransit(HandSide const& hs, FVector3 const& vt) noexcept {
		FMatrix4x4 result = FMTX4x4_UNIT;
		switch (hs) {
		case HandSide::LHS:
			result.m03 = vt.x;
			result.m13 = vt.y;
			result.m23 = vt.z;
			break;
		case HandSide::RHS:
			result.m30 = vt.x;
			result.m31 = vt.y;
			result.m32 = vt.z;
			break;
		}
		return result;
	}

	FMatrix4x4 const makeRotate(HandSide const& hs, FQuaternion const& qt) noexcept {
		FMatrix4x4 result = FMTX4x4_UNIT;

		result.m00 = Math<float>::sum({ qt.x * qt.x, -(qt.y * qt.y), -(qt.z * qt.z), qt.w * qt.w });
		result.m11 = Math<float>::sum({ -(qt.x * qt.x), qt.y * qt.y, -(qt.z * qt.z), qt.w * qt.w });
		result.m22 = Math<float>::sum({ -(qt.x * qt.x), -(qt.y * qt.y), qt.z * qt.z, qt.w * qt.w });

		result.m21 = 2.0f * Math<float>::sum({ qt.y * qt.z, qt.x * qt.w });
		result.m10 = 2.0f * Math<float>::sum({ qt.x * qt.y, qt.z * qt.w });
		result.m02 = 2.0f * Math<float>::sum({ qt.x * qt.z, qt.y * qt.w });

		result.m01 = 2.0f * Math<float>::sum({ qt.x * qt.y, -(qt.z * qt.w) });
		result.m12 = 2.0f * Math<float>::sum({ qt.y * qt.z, -(qt.x * qt.w) });
		result.m20 = 2.0f * Math<float>::sum({ qt.x * qt.z, -(qt.y * qt.w) });

		switch (hs) {
		case HandSide::LHS:
			return transpose(result);
		default:
			return result;
		}
	}

	FMatrix3x3 const makeRotate(HandSide const& hs, FRotation const& rot) noexcept {
		FMatrix3x3 result = FMTX3x3_UNIT;

		result.m11 = result.m00 = cos(rot);
		result.m01 = result.m10 = sin(rot);
		result.m01 *= -1.0f;

		switch (hs) {
		case HandSide::LHS:
			return transpose(result);
		default:
			return result;
		}
	}

	FMatrix4x4 const makeRotate(HandSide const& hs, FVector3 const& axis, FRotation const& rot) noexcept {
		FMatrix4x4 result = FMTX4x4_UNIT;

		float s = sin(rot);
		float c = cos(rot);
		FVector3 n = normalize(axis);

		result.m00 = c + n.x * n.x * (1.0f - c);
		result.m11 = c + n.y * n.y * (1.0f - c);
		result.m22 = c + n.z * n.z * (1.0f - c);

		result.m01 = n.x * n.y * (1.0f - c) - n.z * s;
		result.m12 = n.y * n.z * (1.0f - c) - n.x * s;
		result.m20 = n.x * n.z * (1.0f - c) - n.y * s;

		result.m10 = n.x * n.y * (1.0f - c) + n.z * s;
		result.m21 = n.y * n.z * (1.0f - c) + n.x * s;
		result.m02 = n.x * n.z * (1.0f - c) + n.y * s;

		switch (hs) {
		case HandSide::LHS:
			return transpose(result);
		default:
			return result;
		}
	}

	FMatrix3x3 const makeScaler(FVector2 const& vt) noexcept {
		FMatrix3x3 tmp = FMTX3x3_UNIT;
		tmp.m00 = vt.x;
		tmp.m11 = vt.y;
		return tmp;
	}

	FMatrix4x4 const makeScaler(FVector3 const& vt) noexcept {
		FMatrix4x4 tmp = FMTX4x4_UNIT;
		tmp.m00 = vt.x;
		tmp.m11 = vt.y;
		tmp.m22 = vt.z;
		return tmp;
	}

	FMatrix3x3 const makeSkew(HandSide const& hs, SkewType2 const& st, FRotation const& rot) noexcept {
		FMatrix3x3 tmp = FMTX3x3_UNIT;
		switch (hs) {
		case HandSide::LHS:
			switch (st) {
			case SkewType2::PRI:
				tmp.m10 = tan(rot);
				break;
			case SkewType2::SEC:
				tmp.m01 = tan(rot);
				break;
			}
			break;
		case HandSide::RHS:
			switch (st) {
			case SkewType2::PRI:
				tmp.m01 = tan(rot);
				break;
			case SkewType2::SEC:
				tmp.m10 = tan(rot);
				break;
			}
		}
		return tmp;
	}

	FMatrix4x4 const makeSkew(HandSide const& hs, SkewType3 const& st, FRotation const& rot) noexcept {
		FMatrix4x4 tmp = FMTX4x4_UNIT;
		switch (hs) {
		case HandSide::LHS:
			switch (st) {
			case SkewType3::XYP:
				tmp.m10 = tan(rot);
				break;
			case SkewType3::XYS:
				tmp.m01 = tan(rot);
				break;
			case SkewType3::XZP:
				tmp.m20 = tan(rot);
				break;
			case SkewType3::XZS:
				tmp.m02 = tan(rot);
				break;
			case SkewType3::YZP:
				tmp.m12 = tan(rot);
				break;
			case SkewType3::YZS:
				tmp.m21 = tan(rot);
				break;
			}
			break;
		case HandSide::RHS:
			switch (st) {
			case SkewType3::XYP:
				tmp.m01 = tan(rot);
				break;
			case SkewType3::XYS:
				tmp.m10 = tan(rot);
				break;
			case SkewType3::XZP:
				tmp.m02 = tan(rot);
				break;
			case SkewType3::XZS:
				tmp.m20 = tan(rot);
				break;
			case SkewType3::YZP:
				tmp.m21 = tan(rot);
				break;
			case SkewType3::YZS:
				tmp.m12 = tan(rot);
				break;
			}
			break;
		}
		return tmp;
	}
}
