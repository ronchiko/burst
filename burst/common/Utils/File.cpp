#include "File.h"

#include <fstream>

#include "Error.h"

using namespace burst;

Vector<u8> burst::file::readToBuffer(const String& path) {
	std::fstream stream(path, std::ios::ate | std::ios::binary);

	if (!stream.is_open() || stream.bad()) {
		throw burst::RuntimeError::make("Failed to open file: ", path);
	}

	size_t size = stream.tellg();
	Vector<u8> data(size);
	
	stream.read(reinterpret_cast<char*>(data.data()), size);
	return data;
}
