#pragma once

// Safe include for vulkan windows

#include <Windows.h>
#include <vulkan/vulkan_win32.h>

// Undef problematic macros
#undef min
#undef max
#undef ERROR
