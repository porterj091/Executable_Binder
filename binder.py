import sys
from subprocess import call
from subprocess import Popen, PIPE

# Make the header for the cpp file
# Input: 
def createHeader():
	with open('codearray.h', 'w') as fp:
		fp.write("#include <string>\n\nusing namespace std;\n\nunsigned char* codeArray[] = {\n")


# Make the footer for the cpp file
def createFooter(programLengths, numFiles):
	with open('codearray.h', 'a') as fp:
		fp.write("\n\nunsigned programLengths[] = {")
		for i in range(len(programLengths)):
			if i == len(programLengths) - 1:
				fp.write(str(programLengths[i] - 1) + "};\n")
			else:
				fp.write(str(programLengths[i] - 1) + ", ")
		fp.write("#define NUM_BINARIES " + str(numFiles) + "\n") 
			
# Writes the bytes into the codeArray variable
# Input:  byte string, num of total files, currfile we are working on
def writeBytes(bytes_to_write, numFiles, currFile):
	with open('codearray.h', 'a') as fp:
		fp.write("new unsigned char[" + str(len(bytes_to_write) - 1) + "] {")
		for i in range(len(bytes_to_write) - 1):
			if i != len(bytes_to_write) - 2:
				fp.write(bytes_to_write[i] + ", ")
			elif currFile != numFiles:
				fp.write(bytes_to_write[i] + "},\n")
			else:
				fp.write(bytes_to_write[i] + "}\n};")
				
# Will return the array of bytes
def getBytes(fileName):
	process = Popen(["hexdump", "-v", "-e", '"0x" 1/1 "%02X" ","', fileName], stdout=PIPE)
	(output, err) = process.communicate()
	exit_code = process.wait()
	if exit_code == 0:
		byte = output.split(',')
		return byte
	else:
		print("Problem with getting the bytes")
		sys.exit(1)

# Compile the cpp backend program that will create the bound executable
def compileCpp():
	call(["g++", "binderbackend.cpp", "-o" "bound", "-std=gnu++11"])

# Main execution
def main(args):
	print("######### Binding the %d files together!!!! ########" %(len(args)))
	createHeader()
	programLengths = []
	currFile = 1
	for i in args:
		bytes_of_file = getBytes(i)
		print("========= Adding %s to binder with size: %d bytes ======" %(i, len(bytes_of_file)))
		programLengths.append(len(bytes_of_file))
		writeBytes(bytes_of_file, len(args), currFile)
		currFile += 1
	createFooter(programLengths, len(args))
	print("============= Starting the compile the executable!! ===============\n")
	compileCpp()
	print("\n============= Finished Compiling the bound executable!! ==============\n")


if __name__ == '__main__':
	main(sys.argv[1:])
