import os
from dataclasses import dataclass

from serialized_buffer import SerializedBuffer

NAME_REPLACER = "%NAME%"
BUFFER_REPLACER = "%BUFFER%"
LENGTH_REPLACER = "%SIZE%"

EMBEDDED_FILE_FORMAT: str = f"""
/**
 * This is an auto generated file, DON'T EDIT!
 */

#include <stddef.h>

char {NAME_REPLACER}_BUFFER[] = {'{' + BUFFER_REPLACER + '}'};
size_t {NAME_REPLACER}_SIZE = {LENGTH_REPLACER}; 
"""


@dataclass
class EmbedInfo:
	buffer: SerializedBuffer
	name: str


def _generate_c_file_contents(info: EmbedInfo) -> str:
	content = EMBEDDED_FILE_FORMAT
	replacers= {
		LENGTH_REPLACER: info.buffer.length,
		BUFFER_REPLACER: info.buffer.as_c_buffer,
		NAME_REPLACER: info.name 
	} 

	for keyword, value in replacers.items():
		content = content.replace(keyword, str(value))

	return content

def _load_info(args) -> EmbedInfo:
	name = args.target_name
	if len(name) == 0:
		name = os.path.basename(args.target_file).replace('.', '_')

	with open(args.source_file, "rb") as source:
		return EmbedInfo(
			buffer=SerializedBuffer(source.read()),
			name=name
		)


def embed(args) -> None:
	"""
	Embeds a shader file into a c file
	"""
	info = _load_info(args)
	contents = _generate_c_file_contents(info)
	with open(args.target_file, "w+") as target:
		target.write(contents)