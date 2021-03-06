#include <stdio.h>
#include <string.h>
/* Exam A Question 7. */
struct Node{
	struct Node *next;
	int val;
};
int f(struct Node *n){
	if(n==NULL) return 0;
	return 1+f(n->next);
}
/* Question 8*/
struct{
	int one;
	union{
		char *uc;
		short us;
	} uni[2];
	char two, two1;
	short three;
} arr[3];

/* Question 17 */
int question17(){
	int i;
	int arr[] = {1,2,3,4};
	int *p = (&arr[0]);
	for(i=0;i<4;i++)
		printf("%d,", *(p+i));
		printf("\n");
	return 0;
}

/* Question 36 */
unsigned int foo(unsigned int n){
	int ret = n%10;
	while(n/=10){
		ret *= 10;
		ret += n%10;
	}
	return ret;
}

/* Question 39 */
int question39(){
	int x = -0xa9;
	printf("%x\n", (unsigned int) x);
	return 0;
}
/* Question 41 */
int question41(){
	int x,y;
	x = 2; y=4;
	if((x = 5) || (y = 8))
		printf("%d, %d\n", x, y);
	else
		printf("%d, %d\n", y, x);
}
/* Question 42 */
int question42(){
	int x, y;
	if (x == 1)
		if(y==2)
			x=6;
	else
		y=9;
}
/* Question 44 */
int question44(){
	char a[] = {'h', 'e', 'l', 'l', 'o'};
	char *b = "hello\0";
	printf("strlen a[] = %d\nstrlen *b = %d\n", strlen(a), strlen(b));
}

/* Question 45 */
int question45(){
	void *p;
	int *n;
	char *c;
	int *i;
	p = 0;
	i = (int *)p;
	i += 2;
	c = (char *)i;
	c += 5;
	p = (void *)c;
	printf("%u\n", (unsigned int)p);
}

int main(){
	question17();
	foo(17);
	question39();
	question41();
	question42();	
	question44();
}
