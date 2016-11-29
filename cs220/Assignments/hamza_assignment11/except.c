#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <stdlib.h>

#define intSize sizeof(int)
#define charSize sizeof(char)
#define floatSize sizeof(float)
#define longSize sizeof(long)
#define doubleSize sizeof(double)
#define shortSize sizeof(short)
#define longDoubleSize sizeof(long double)

#define ARRAY_SIZE 100
/* g is a global variabl */

jmp_buf buf;

int g = 10;

/* Declare struct var_state here */

struct var_state {
    void *address;
    unsigned int size;
    char * data;
    struct var_state *next;
};

struct var_state *var_state_head;

/* Implement save_state() */
void save_state(void *addr, unsigned int size){
    int i;
    /* Create element */
    struct var_state *new_elem = malloc(sizeof(struct var_state));
    /* Set the address and size of the saved variable*/
    new_elem->address = addr;
    new_elem->size = size;
    
    char *temp_data_addr = (char *) addr;
    new_elem->data = (char *) malloc(size);
    char *current = (char *) new_elem->data;
    
    for(i=0; i < size; i++){
		*current = *temp_data_addr;
		current++; temp_data_addr++;
    }
    new_elem->next = var_state_head;
    var_state_head = new_elem;
}


/* Implement restore_state() */
void restore_state(){
    int i;
    struct var_state *variable = var_state_head;
    while(variable){
    	   	char *variable_addr = (char *) variable->address;
		char *saved_data_addr = (char *) variable->data;
		for(i=0;i<variable->size; i++){
		    	*variable_addr = *saved_data_addr;
			variable_addr++; saved_data_addr++;  
	    }
	free(variable->data);
	free(variable);
	variable = variable->next;
    }
}

void signalHandler(int signal){
    longjmp(buf, signal);
}

void f(){
    int x, i;
    char *p;
    x = 11;
    p = (char *) malloc(100);
    p[0] = p[1] = 'x';
    
    /* Register signal handler */
    for (i=1; i<31; i++) signal(i, signalHandler);
    
    /* Save x, g, p, *p */
    save_state(&x, sizeof(x));
    save_state(&g, sizeof(g));
    save_state(p, sizeof(p));
    save_state(&p, sizeof(&p));
    
    int a = setjmp(buf);
    if (a == 0){
        g = 30;
        x = 100;
        p = 0;
        p[0] = p[1] = p[2] = 'x';
    } else{
        restore_state();
        printf("%d, %d, %c, %c\n", g, x, p[0], p[1]);
    }
}

int main(){
    f();
}
