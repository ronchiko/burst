#pragma once

#include "../Types.h"

namespace burst {

	/**
	 * An work set for an AVX of type and integral type.
	 * 
	 * \tparam AvxMm: The root AVX type (_m256 etc...)
	 * \tparam Resultion: The Resulution of the operation set (ie float, double)
	 */
	template<typename Resultion, typename AvxMm>
	struct AvxWorkset
	{
		/**
		 * The size of the AVX value in bytes.
		 */
		static constexpr u32 SIZE_IN_RESULTION = 0;

		/**
		 * Load a buffer in an AVX.
		 */
		static AvxMm load(Resultion buffer[SIZE_IN_RESULTION]) = 0;

		/**
		 * Loads a single value into the AVX.
		 * 
		 * \param value to load
		 */
		static AvxMm load_single(const Resultion& value) = 0;

		/**
		 * Stores the the avx into a buffer.
		 * 
		 * \param buffer: The buffer to set
		 * \param value: The avx to set
		 */
		static void store(Resultion buffer[SIZE_IN_RESULTION], const AvxMm& value) = 0;

		// AVX Addition
		static AvxMm add(const AvxMm& first, const AvxMm& second) = 0;

		// AVX Subtraction
		static AvxMm sub(const AvxMm& first, const AvxMm& second) = 0;
		
		// AVX multiplacation
		static AvxMm mul(const AvxMm& first, const AvxMm& second) = 0;

		// AVX division
		static AvxMm div(const AvxMm& first, const AvxMm& second) = 0;
	};

}

// Worksets
#include "AVX/Avx256.inl"
