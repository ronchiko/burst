#include "Dimensions.h"

#define ASSERT_DIMENSION_PRESENT(index)                                             \
	if(m_Size < (index)) {                                                          \
		throw ::burst::vulkan::DimensionUnavailable();                              \
	}

namespace burst::vulkan {
	Dimensions::Dimensions(u32 w)
		: m_Size(1)
		, m_Width(w)
		, m_Height(0)
		, m_Depth(0)
	{}

	Dimensions::Dimensions(u32 w, u32 h)
		: m_Size(2)
		, m_Width(w)
		, m_Height(h)
		, m_Depth(0)
	{}

	Dimensions::Dimensions(u32 w, u32 h, u32 d)
		: m_Size(3)
		, m_Width(w)
		, m_Height(h)
		, m_Depth(d)
	{}

	u32 Dimensions::count() const {
		return m_Size;
	}

	u32 Dimensions::width() const {
		// Width is always present
		return m_Width;
	}

	u32 Dimensions::height() const {
		ASSERT_DIMENSION_PRESENT(2);
		return m_Height;
	}

	u32 Dimensions::depth() const
	{
		ASSERT_DIMENSION_PRESENT(3);
		return m_Depth;
	}
}
