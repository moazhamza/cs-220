#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

char **set_up_args(char *str, char **args){
    int i, numArgs = 1, j=0;
    i = 0;
    while(str[i] != '\n' && str[i] != '\0'){
        if(str[i] == ' ') {
            str[i] = '\0';
            args[j] = str;
            str = &(str[i+1]);
            j++; i=0;
        }
        else{
            i++;
        }
    }
    args[j] = str;
    args[j+1] = NULL;
    return args;
}
/* Returns the second argument if it exists,
 * returns 0 if there is no second argument.
 */
char *set_up_second_command(char *line, char *secondCommand){
    int i;
    for (i=0; i< strlen(line); i++) {
        if(line[i] == '&' && line[i+1] == '&'){
            line[i-1] = '\0';
            secondCommand = &line[i+3];
            return secondCommand;
        }
    }
    return 0;
}

int main(){
    char line[1024];
    int pid, pid2, i, error;
    char *secondCommand = 0; 
    char **args = (char **) malloc(1024);
    char **args2 = (char **) malloc(1024);
    while(1){
        printf("Hello!!>");
        if(!fgets(line, 1023, stdin)){
            break;
        }
        if(strcmp(line, "exit\n")  == 0) break;
        for (i=0; i< strlen(line); i++) {
            if(line[i] == '\n') line[i] = '\0';
        }
	
       	secondCommand = set_up_second_command(line, secondCommand);
        args = set_up_args(line, args);
        
        pid = fork();
        if(pid == 0) { /* This is the child */ 	
		execvp(line, args);
		fprintf(stderr, "Hello!!: %s\n", strerror(errno));
		exit(errno);
	} else {
            wait(&error);
        }
	if(secondCommand && !error){
		pid2 = fork();
		if(pid2 == 0){ /*This is another child */
			if(errno == 0){		 	
				args2 = set_up_args(secondCommand, args2);
				execvp(secondCommand, args2);
				fprintf(stderr, "Hello!!: %s\n", strerror(errno));
				exit(errno);
			}
		}else wait(NULL);
	}
    }
    
    return 0;
}
