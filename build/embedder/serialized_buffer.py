

class SerializedBuffer:
	"""
	A serialized buffer that can be easly exported.
	"""
	def __init__(self, contents: bytes) -> None:
		self._content = contents

	@property
	def length(self) -> int:
		return len(self._content)
	
	@property
	def as_c_buffer(self) -> str:
		"""
		Exports the buffer into a C style buffer
		"""
		return ", ".join(hex(byte) for byte in self._content)

	def __repr__(self) -> str:
		return "SerialziedBuffer(len={})".format(self.length)
