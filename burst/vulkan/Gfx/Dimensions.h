#pragma once

#include <burst/common/Types.h>

namespace burst::vulkan {

	/**
	 * An error that occur when a dimension is not present in a Dimensions object.
	 */
	class DimensionUnavailable : public Error
	{};

	struct Dimensions
	{
	public:
		/**
		 * An object with one dimension.
		 * 
		 * \param w: The first dimension
		 */
		explicit Dimensions(u32 w);

		/**
		 * An object with two dimensions.
		 * 
		 * \param w: The first dimension
		 * \param h: The second dimension
		 */
		explicit Dimensions(u32 w, u32 h);

		/**
		 * An objec the three dimensions.
		 * 
		 * \param w: The first dimension
		 * \param h: The second dimension
		 * \param d: The third dimension
		 */
		explicit Dimensions(u32 w, u32 h, u32 d);

		/**
		 * The amount of dimension in this object.
		 */
		u32 count() const;

		/**
		 * The first dimension of this object.
		 */
		u32 width() const;

		/**
		 * The second dimension of this object.
		 * 
		 * \note: Throws an DimensionUnavailable when dimension not present
		 */
		u32 height() const;

		/**
		 * The third dimension of this object.
		 * 
		 * \note: Throws an DimensionUnavailable when dimension not present
		 */
		u32 depth() const;

	private:
		u32 m_Size;

		u32 m_Width;
		u32 m_Height;
		u32 m_Depth;
	};
}
