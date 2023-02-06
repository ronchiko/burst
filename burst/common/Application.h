#pragma once

#include "Types.h"

namespace burst {

	/**
	 * Defines a version.
	 * 
	 * \note: Sometime libraries have their own version formatting (like vulkan)
	 *		  In that case, use the librarys version fomrat.
	 */
	struct Version
	{
		u8 major; // Major version
		u8 minor; // Minor version
		u16 fix;  // Subfix

		/**
		 * Defines a new version struct.
		 *
		 * \param major: The major version
		 * \param minor: The minor version
		 * \param fix: The fix version
		 */
		constexpr Version(u8 major, u8 minor = 0, u16 fix = 0)
			: major(major)
			, minor(minor)
			, fix(fix)
		{}

		/**
		 * Converts a version to u32.
		 *
		 * \return The version represented as u32
		 */
		constexpr u32 to_u32() const
		{
			return (major << 24) | (minor << 16) | fix;
		}

		/**
		 * Creates a version from a u32 (inversion of Version::to_u32).
		 * 
		 * \param version: The version represented as an integer
		 */
		constexpr static Version from_u32(u32 version)
		{
			return Version{
				static_cast<u8>((version & 0xFF000000) >> 24),
				static_cast<u8>((version & 0xFF0000) >> 16),
				static_cast<u8>(version & 0xFFFF),
			};
		}

		constexpr bool operator==(const Version& other) noexcept {
			return to_u32() == other.to_u32();
		}
	};

	struct ApplicationInfo
	{
		// The name of the application
		String application_name;
		// The version of the application
		Version application_version;
	};
}
