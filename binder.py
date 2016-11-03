import sys

def createHeader():
	with open('codearray.h', 'w') as fp:
		fp.write("#include <string>\n\nusing namespace std;\n\nunsigned char* codeArray[] = {\n")

def createFooter(programLengths):
	with open('codearray.h', 'w') as fp:
		fb.write("\n\nunsigned programLengths[] = {")
		for i in range(len(programLengths)):
			if i == len(programLengths) - 1:
				fp.write(str(programLengths[i]) + "}\n")
			else:
				fp.write(str(programLengths[i]) + ", ")
			

def writeBytes(bytes_to_write, numFiles):
	with open('codearray.h', 'w') as fp:
		fp.write("new unsigned char[" + numFiles + "]{")
		for i in range(len(bytes_to_write)):
			if i != len(bytes_to_write) - 2:
				fb.write(byte_to_write[i] + ", ")
			else:
				fb.write(byte_to_write[i] + "},\n")
				
# Will return the array of bytes
def getBytes(fileName):
	byte = bytearray(open(fileName, 'rb').read())
	return byte


# Main execution
def main(args):
	print("Binding the %d files together!!!!" %(len(args)))
	createHeader()
	programLengths = []
	for i in args:
		bytes_of_file = getBytes(i)
		programLengths.append(len(bytes_of_file))
		writeBytes(byte_of_file, len(args))
	createFooter(programLengths)


if __name__ == '__main__':
	main(sys.argv[1:])
