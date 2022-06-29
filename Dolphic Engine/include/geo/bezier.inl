/**	@file	avbezier.inl
 *	@brief	ベジエ曲線テンプレートクラス
 */
#pragma once

#include "bezier.hpp"

namespace dlph {
	template<typename T>
	BezierCurve<T>::BezierCurve() noexcept :
		mContents()
	{}

	template<typename T>
	T const BezierCurve<T>::interpolate(const float& t, bool const& useBern) noexcept {
		T result = T();
		WData<T> tmp;
		if (t <= 0.0f) {
			result = mContents[0].point;
			return result;
		}
		if (t >= 1.0f) {
			result = mContents[mContents.size() - 1].point;
			return result;
		}
		if (useBern) {
			//	ベルンシュタイン多項式を利用して座標を求める。
			WData<T> arg = WData<T>();
			for (unsigned int idx = 0; idx < mContents.size(); idx++) {
				arg = mContents[idx];
				tmp.data += arg.point * arg.weight * bern(mContents.size(), idx, t);
				tmp.weight += arg.weight * bern(mContents.size(), idx, t);
			}
			result = tmp.data / tmp.weight;
		}
		else {
			//	初期化リスト内の内容を複製
			for (WData<T> arg : mContents) {
				tmp.push_back(arg.point);
			}
			//	ベルンシュタイン多項式を利用して座標を求める。
			for (unsigned int idx = 0; idx < mContents.size(); idx++) {
				tmp.data += tmp[idx] * bern(mContents.size(), idx, t);
			}
			//	完成品の代入
			result = tmp.data;
		}
		return result;
	}

	template<typename T>
	float const BezierCurve<T>::bern(const unsigned int& n, const unsigned int& k, const float& t) noexcept {
		float result;
		if (k > n) {
			result = 1.0f;
			return result;
		}

		//	組み合わせを求める
		unsigned int tmp = 1U;
		for (unsigned int i = 1U; i < k; i++) {
			tmp *= (n + 1 - i) / i;
		}

		//	組み合わせからベルンシュタイン多項式を求める。
		result =
			static_cast<float>(tmp)
			* powf(t, static_cast<float>(k))
			* powf((1.0f - t), static_cast<float>(n - k));

		return result;
	}
}
