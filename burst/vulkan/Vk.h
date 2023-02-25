/*****************************************************************//**
 * \file   Vk.h
 * \brief  Header file for using vulkan
 * 
 * \author ronmh
 * \date   February 2023
 *********************************************************************/
#pragma once

#include <vulkan/vulkan.hpp>

/**
 * Calls a vulkan function, and returns a vk::Result object.
 */
#define VK_CALL(expr) (static_cast<vk::Result>(expr))
