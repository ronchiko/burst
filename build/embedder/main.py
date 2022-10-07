import os
import argparse
import sys

from embed import embed

def parse_arguments():
	"""
	Parses the command line arguments
	"""
	parser = argparse.ArgumentParser(description="Generates C files from binary files")

	parser.add_argument(
		dest='source_file', 
		type=str,
		action='store')
	parser.add_argument(
		dest='target_file',
		type=str,
		action='store',
		default=""
	)
	parser.add_argument(
		'--name',
		dest='target_name',
		type=str,
		action='store',
		default="",
		help='The base name of the generated variable'
	)

	args = parser.parse_args()
	return args

def main() -> None:
	try:
		args = parse_arguments()
		print("{} -> {}".format(args.source_file, args.target_file))
		embed(args)

	except Exception as e:
		print('Error: {}'.format(e), file=sys.stderr)
		sys.exit(-1)
	
	sys.exit(0)

if __name__ == '__main__':
	main()