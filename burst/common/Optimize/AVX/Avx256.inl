#pragma once

#include "../Avx.h"

#include <zmmintrin.h>

namespace burst {

	// AVX256f
	template<>
	struct AvxWorkset<float, __m256>
	{
		using Mm = __m256;
		using R = float;

		static constexpr u32 SIZE_IN_RESULTION = 32 / sizeof(R);

		static inline Mm load(R buffer[SIZE_IN_RESULTION])
		{
			return _mm256_load_ps(buffer);
		}

		static inline Mm broadcast(const R& value)
		{
			return _mm256_broadcast_ss(&value);
		}

		static inline void store(R buffer[SIZE_IN_RESULTION], const Mm& value)
		{
			_mm256_store_ps(buffer, value);
		}

		// AVX Addition
		static Mm add(const Mm& first, const Mm& second)
		{
			return _mm256_add_ps(first, second);
		}

		// AVX Subtraction
		static inline Mm sub(const Mm& first, const Mm& second)
		{
			return _mm256_sub_ps(first, second);
		}

		// AVX multiplacation
		static Mm mul(const Mm& first, const Mm& second)
		{
			return _mm256_mul_ps(first, second);
		}

		// AVX division
		static Mm div(const Mm& first, const Mm& second)
		{
			return _mm256_div_ps(first, second);
		}
	};

	// AVX256d
	template<>
	struct AvxWorkset<double, __m256d>
	{
		using Mm = __m256d;
		using R = double;

		static constexpr u32 SIZE_IN_RESULTION = 32 / sizeof(R);

		static inline Mm load(R buffer[SIZE_IN_RESULTION])
		{
			return _mm256_load_pd(buffer);
		}

		static inline Mm broadcast(const R& value)
		{
			return _mm256_broadcast_sd(&value);
		}

		static inline void store(R buffer[SIZE_IN_RESULTION], const Mm& value)
		{
			_mm256_store_pd(buffer, value);
		}

		// AVX Addition
		static Mm add(const Mm& first, const Mm& second)
		{
			return _mm256_add_pd(first, second);
		}

		// AVX Subtraction
		static Mm sub(const Mm& first, const Mm& second)
		{
			return _mm256_sub_pd(first, second);
		}

		// AVX multiplacation
		static Mm mul(const Mm& first, const Mm& second)
		{
			return _mm256_mul_pd(first, second);
		}

		// AVX division
		static Mm div(const Mm& first, const Mm& second)
		{
			return _mm256_div_pd(first, second);
		}
	};
}
