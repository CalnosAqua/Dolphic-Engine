/**	@file	math.cpp
 *	@brief	数学系関数群
 */
#include "math/math.hpp"
#include "math/intrin.hpp"
#include <vector>
#include <numeric>
#include <cfloat>

namespace dlph {
	template <>
	int const Math<float>::compare(float const& lhs, float const& rhs) noexcept {
		if (fabsf(lhs - rhs) < FLT_EPSILON * fmaxf(fmaxf(fabsf(lhs), fabsf(rhs)), 1.0f)) {
			return 0;
		}
		return (lhs < rhs) ? -1 : 1;
	}

	template <>
	float const Math<float>::sqrt(float const& arg, bool const& is_speedy) noexcept {
		float result = 0.0f;
		if (arg < 0.0f) {
			return result;
		}

		if (is_speedy) {
			//	高速逆平方根計算アルゴリズムを利用した方法
			float half = 0.5f * arg;
			int temp = 0x5F3759DF - ((*reinterpret_cast<int*>(&const_cast<float&>(arg)) >> 1));
			result = *reinterpret_cast<float*>(&temp);

			result *= 1.5f - half * result * result;
			result *= 1.5f - half * result * result;
			result *= 1.5f - half * result * result;
			result *= arg;
		}
		else {
			//	ニュートン法を利用した方法
			float temp = (arg + 1.0f) * 0.5f;
			while (true) {
				result = (temp + arg / temp) * 0.5f;
				if (compare(result, temp) == 0) {
					break;
				}
				temp = result;
			}
		}

		return result;
	}

	template <>
	float const Math<float>::sum(float const* const& ptr, size_t const& cnt, bool const& is_speedy) noexcept {
		float result = 0.0f;

		if (is_speedy) {
			//	単純に加算する方法
			for (size_t idx = 0U; idx < cnt; idx++) {
				result += *(ptr + idx);
			}
		}
		else {
			//	カハンの加算アルゴリズムを利用した方法
			volatile float y, c, t;
			c = 0.0f;

			for (size_t idx = 0U; idx < cnt; idx++) {
				y = *(ptr + idx) - c;
				t = result + y;
				c = (t - result) - y;
				result = t;
			}
		}

		return result;
	}

	template<>
	float const Math<float>::average(float const* const& ptr, size_t const& cnt, bool const& is_speedy) noexcept {
		return sum(ptr, cnt, is_speedy) / static_cast<float>(cnt);
	}

	template<>
	float const Math<float>::variance(float const* const& ptr, size_t const& cnt, bool const& is_speedy) noexcept {
		if (ptr == nullptr || cnt <= 0U) {
			return 0.0f;
		}

		std::vector<float> values;
		float result, average;
		average = Math::average(ptr, cnt, is_speedy);
		for (size_t idx = 0U; idx < cnt; ++idx) {
			result = sum({ *(ptr + idx), -average });
			values.emplace_back(result * result);
		}
		result = sum(values.data(), values.size(), is_speedy);
		result /= static_cast<float>(cnt);

		return result;
	}

	template <>
	float const Math<float>::clamp(float const& value, float const& min, float const& max) noexcept {
		float mn, mx;

		if (min > max) {
			mx = min;
			mn = max;
		}
		else {
			mx = max;
			mn = min;
		}

		float result = value;
		if (compare(result, mn) < 0) {
			result = mn;
		}
		if (compare(result, mx) > 0) {
			result = mx;
		}
		return result;
	}

	template <>
	float const Math<float>::loop(float const& value, float const& min, float const& max) noexcept {
		float mn, mx;

		if (min > max) {
			mx = min;
			mn = max;
		}
		else {
			mx = max;
			mn = min;
		}

		float result = value;
		float length = mx - mn;
		while (compare(result, mn) < 0) {
			result = sum({ length, result });
		}
		while (compare(result, mx) > 0) {
			result = sum({ -length, result });
		}
		return result;
	}

	template<>
	float const Math<float>::bern(size_t const& n, size_t const& k, float const& t) noexcept {
		float result = 1.0f;
		if (k <= n) {
			//	組み合わせを求める
			size_t tmp = 1U;
			for (size_t i = 1U; i < k; i++) {
				tmp *= (n + 1 - i) / i;
			}
			//	組み合わせからベルンシュタイン多項式を求める。
			float rate = clamp(t, 0.0f, 1.0f);
			result = static_cast<float>(tmp) * powf(rate, static_cast<float>(k)) * powf((1.0f - rate), static_cast<float>(n - k));
		}
		return result;
	}


	template <>
	int const Math<double>::compare(double const& lhs, double const& rhs) noexcept {
		if (fabs(lhs - rhs) < DBL_EPSILON * fmax(fmax(fabs(lhs), fabs(rhs)), 1.0)) {
			return 0;
		}
		return (lhs < rhs) ? -1 : 1;
	}

	template <>
	double const Math<double>::sqrt(double const& arg, bool const& is_speedy) noexcept {
		double result = 0.0;
		if (arg < 0.0) {
			return result;
		}

		if (is_speedy) {
			//	高速逆平方根計算アルゴリズムを利用した方法
			double half = 0.5 * arg;
			long long int temp = 0x5FE6EB50C7B537AAL - ((*reinterpret_cast<long long int*>(&const_cast<double&>(arg)) >> 1LL));
			result = *reinterpret_cast<double*>(&temp);

			result *= 1.5 - half * result * result;
			result *= 1.5 - half * result * result;
			result *= 1.5 - half * result * result;
			result *= arg;
		}
		else {
			//	ニュートン法を利用した方法
			double temp = (arg + 1.0) * 0.5;
			while (true) {
				result = (temp + arg / temp) * 0.5;
				if (compare(result, temp) == 0) {
					break;
				}
				temp = result;
			}
		}

		return result;
	}

	template <>
	double const Math<double>::sum(double const* const& ptr, size_t const& cnt, bool const& is_speedy) noexcept {
		double result = 0.0f;

		if (is_speedy) {
			//	単純に加算する方法
			for (size_t idx = 0U; idx < cnt; idx++) {
				result += *(ptr + idx);
			}
		}
		else {
			//	カハンの加算アルゴリズムを利用した方法
			volatile double y, c, t;
			c = 0.0;

			for (size_t idx = 0U; idx < cnt; idx++) {
				y = *(ptr + idx) - c;
				t = result + y;
				c = (t - result) - y;
				result = t;
			}
		}

		return result;
	}

	template<>
	double const Math<double>::average(double const* const& ptr, size_t const& cnt, bool const& is_speedy) noexcept {
		return sum(ptr, cnt, is_speedy) / static_cast<double>(cnt);
	}

	template<>
	double const Math<double>::variance(double const* const& ptr, size_t const& cnt, bool const& is_speedy) noexcept {
		if (ptr == nullptr || cnt <= 0U) {
			return 0.0;
		}

		std::vector<double> values;
		double result, average;
		average = Math::average(ptr, cnt, is_speedy);
		for (size_t idx = 0U; idx < cnt; ++idx) {
			result = sum({ *(ptr + idx), -average });
			values.emplace_back(result * result);
		}
		result = sum(values.data(), values.size(), is_speedy);
		result /= static_cast<double>(cnt);

		return result;
	}

	template <>
	double const Math<double>::clamp(double const& value, double const& min, double const& max) noexcept {
		double mn, mx;

		if (min > max) {
			mx = min;
			mn = max;
		}
		else {
			mx = max;
			mn = min;
		}

		double result = value;
		if (compare(result, mn) < 0) {
			result = mn;
		}
		if (compare(result, mx) > 0) {
			result = mx;
		}
		return result;
	}

	template <>
	double const Math<double>::loop(double const& value, double const& min, double const& max) noexcept {
		double mn, mx;

		if (min > max) {
			mx = min;
			mn = max;
		}
		else {
			mx = max;
			mn = min;
		}

		double result = value;
		double length = mx - mn;
		while (compare(result, mn) < 0) {
			result = sum({ length, result });
		}
		while (compare(result, mx) > 0) {
			result = sum({ -length, result });
		}
		return result;
	}

	template<>
	double const Math<double>::bern(size_t const& n, size_t const& k, double const& t) noexcept {
		double result = 1.0;
		if (k <= n) {
			//	組み合わせを求める
			size_t tmp = 1U;
			for (size_t i = 1U; i < k; i++) {
				tmp *= (n + 1 - i) / i;
			}
			//	組み合わせからベルンシュタイン多項式を求める。
			double rate = clamp(t, 0.0, 1.0);
			result = static_cast<double>(tmp) * pow(rate, static_cast<double>(k)) * pow((1.0f - rate), static_cast<double>(n - k));
		}
		return result;
	}

	template <>
	vctr const Math<vctr>::sum(vctr const* const& ptr, size_t const& cnt, bool const& is_speedy) noexcept {
		vctr result = set1(0.0f);

		if (is_speedy) {
			//	単純に加算する方法
			for (size_t idx = 0U; idx < cnt; idx++) {
				result = add(result, *(ptr + idx));
			}
		}
		else {
			//	カハンの加算アルゴリズムを利用した方法
			vctr y, c, t;
			c = set1(0.0f);

			for (size_t idx = 0U; idx < cnt; idx++) {
				y = sub(*(ptr + idx), c);
				t = add(result, y);
				c = sub(sub(t, result), y);
				result = t;
			}
		}

		return result;
	}
}
