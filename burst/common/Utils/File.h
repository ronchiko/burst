#pragma once

#include <vector>

#include "../Types.h"

namespace burst::file {
	
	Vector<u8> readToBuffer(const std::string& path);
}
