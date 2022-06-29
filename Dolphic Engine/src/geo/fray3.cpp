/**	@file	avfray3.hpp
 *	@brief	三次元光線クラス
 */

#include "geo/fray3.hpp"

namespace dlph {
	FRay3::FRay3() noexcept :
		position(FVT3_ZERO),
		direction(FVector3(1.0f, 0.0f, 0.0f))
	{}

	FRay3::FRay3(FVector3 const& pos, FVector3 const& dir) noexcept :
		position(pos),
		direction(normalize(dir))
	{}

	FVector3 const FRay3::operator[](float const& rate) noexcept {
		return position + direction * rate;
	}
}
