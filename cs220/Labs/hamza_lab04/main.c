#include <stdio.h>
#include "secret.h"

unsigned int extract_secret(struct secret_keeper *);

int main()
{
	struct secret_keeper *k;
	unsigned int secret;
	k = get_keeper();
	secret = extract_secret(k);
	printf("Secret is %s\n", verify_secret(secret) == 1 ?  "correct" : "wrong");
	return 0;
}

unsigned int extract_secret(struct secret_keeper *k)
{	
	int i;
	union secret *s = (union secret *) k->ptr;
	for(i = 1; i <	k->count; i++){
		s = (union secret *) s->ptr; 
	}	 	
/*	printf("%d\n", s->secret); */
	return s->secret;
}

