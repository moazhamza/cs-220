/* Prog.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bad(int dummy){
	char sentence[] = "Quick brown fox jumped over the lazy dog";
	char *sentenceHolder = (char *)malloc(sizeof(sentence));
	strcpy(sentenceHolder, "Quick brown fox jumped over the lazy dog");
	int *studentPtr = &dummy;
	while(*studentPtr != 22){
		studentPtr++;
	}
	*studentPtr = 1000;
	studentPtr -= 2;
	*studentPtr = sentenceHolder;
}
int main(){
	struct{
		char *name;
		int age;
	} student = { .name="John", 
			.age = 22};
	bad(sizeof(student));
	printf("student.name = %s\nstudent.age = %d\n", student.name, student.age);
	return 0;
	
}
