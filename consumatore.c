#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_STRING_LENGTH 256

// consumatore.c e' un filtro
int main(int argc, char* argv[]){

	char *file_in, read_char, buf[MAX_STRING_LENGTH];
	int nread, fd,i ,j=0,k=0;
    char prefix[MAX_STRING_LENGTH];
	//controllo numero argomenti
	if (argc != 3 ){ 
		perror(" numero di argomenti sbagliato"); exit(1);
	} 
	strcpy(prefix,argv[1]);
    //strcpy(prefix,argv[1]);
    /*if(argc == 3){
        
    }*/
	file_in = argv[2];
    printf("prefix = %s\n",prefix);
	fd = open(file_in, O_RDONLY);
	if (fd<0){
		perror("P0: Impossibile aprire il file.");
		exit(2);
	}

	while(nread = read(fd, &read_char, sizeof(char))) /* Fino ad EOF*/{
		if(nread>=0){
            int len_prefix=strlen(prefix);
                if(read_char==prefix[k] && k<len_prefix){
                    
                    
                    if(k+1==len_prefix || read_char=='\n') k=0;
                    else {
                        buf[k]=read_char;
                        k++;
                    }
                    /*else{
                        write(1, read_char, sizeof(char));
                        printf("%c",read_char);
                    }*/
                }
                else if(read_char!=prefix[k] && k!=0){
                    buf[k+1]='\0';
                    k=0;
                    //write(1, buf, sizeof(char)*strlen(buf));
                    printf("%s",buf);
                    
                   // write(1, read_char, sizeof(char));
                    printf("%c",read_char);
                }
                else if(read_char!=prefix[k] && k==0){
                    k=0;
                   // write(1, read_char, sizeof(char));
                    printf("%c",read_char);
                }
        }
		else{
			printf("(PID %d) impossibile leggere dal file %s", getpid(), file_in);
			perror("Errore!");
			close(fd);
			exit(3);
		}
	}
	
	close(fd);
}
