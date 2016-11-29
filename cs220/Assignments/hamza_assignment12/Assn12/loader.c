#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	/* Declare an array large enough to hold the raw bytes. Raw bytes are best stored in byte-addressable arrays. Pick the appropriate type. Call it "raw_bytes" */
	unsigned char raw_bytes[99];
 	/* Declare a function pointer type that matches the calc function's type. Call it "Calc_fptr" */
	typedef int (*Calc_fptr)(char, int, int);	
	FILE *fp;
	unsigned int i;
	Calc_fptr calculator;

	/* TODO if number of arguments is not 4 (5 including program name) 
	 * print ("Usage %s <filename><uint><operation><uint>\n", argv[0]) and exit
	 */
	if(argc != 5){
		printf("Usage %s <filename><uint><operation><uint>\n", argv[0]);
		exit(0);
	}
	/* TODO: Open and read the binary file into raw_bytes. Use fopen and fread.
	 */	
	fp = fopen(argv[1], "rb");
	fread(raw_bytes, 99, 1, fp);

	calculator = (Calc_fptr) raw_bytes;

	unsigned int arg1 = atoi(argv[2]);
	unsigned int arg2 = atoi(argv[4]);
	char sign = (char) *argv[3];

	int result = calculator(sign, arg1, arg2);
	/* TODO: Print the result. Refer to sample input and output. */
	printf("%d %c %d = %d\n", arg1, sign, arg2,  result);
	return 0;
}
