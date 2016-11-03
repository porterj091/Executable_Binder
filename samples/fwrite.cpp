#include <stdio.h>
#include <stdlib.h>

int main()
{
	
	/* An array of bytes */
	char bytes[] = {0x12, 0x34, 0x45, 0xfd};
	
	/* Open the file for writing binary values */
	FILE* fp = fopen("bytefile.bin", "wb");
	
	/* Make sure the file was opened */
	if(!fp)
	{
		perror("fopen");
		exit(-1);
	}
	
	/* The arguments are as follows:
 	 * @arg1 - the array containing the elements we would like to write to the file.
 	 * @arg2 - the size of a single element.
 	 * @arg3 - the number of elements to write to the file
 	 * @arg4 - the file to which to write the bytes
 	 * The function returns the number of bytes written to the file or -1 on error
 	 */
	if(fwrite(bytes, sizeof(char), 4, fp) < 0)
	{
		perror("fwrite");
		exit(-1);
	}
	
	/* Close the file */
	fclose(fp);
	
	return 0;
	
}
