#include "File.h"

#include <fstream>

#include "Error.h"

std::vector<burst::u8> burst::read_file(const std::string& path) {
	std::fstream stream(path, std::ios::ate | std::ios::binary);

	if (!stream.is_open() || stream.bad()) {
		throw burst::RuntimeError::make("Failed to open file: ", path);
	}

	size_t size = stream.tellg();
	std::vector<burst::u8> data(size);
	
	stream.read(reinterpret_cast<char*>(data.data()), size);
	return data;
}
