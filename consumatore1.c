#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAX_STRING_LENGTH 256

char maiusc_minusc(char c);
char maiusc_minusc(char c){
    if((int)c>=(int)'A' && (int)c<='Z')
        return (c+32);
    else if((int)c>='a' && (int)c<='z')
        return c-32;
    else return -1;
}
// consumatore.c e' un filtro
int main(int argc, char* argv[]){

	char *file_in, read_char, buf[MAX_STRING_LENGTH];
	int nread, fd,i ,j=0,k=0;
    char prefix[MAX_STRING_LENGTH];
	//controllo numero argomenti
	if (argc != 3 && argc!=2){ 
		perror(" numero di argomenti sbagliato"); exit(1);
	} 
	strcpy(prefix,argv[1]);
    //strcpy(prefix,argv[1]);
    if(argc == 3){
        
        file_in = argv[2];
        
        fd = open(file_in, O_RDONLY);
    
        if (fd<0){
            perror("P0: Impossibile aprire il file.");
            exit(2);
        }
    }
    else fd=0;
    printf("prefix = %s\n",prefix);
    
    int len_prefix=strlen(prefix);
    int ok=1; //se ok=1 non ho trovato un carattere della stringa filtro 
	while(nread = read(fd, &read_char, sizeof(char))) /* Fino ad EOF*/{
        ok=1;
		if(nread>=0){
            k=0;
	    //ciclo di controllo sul carattere letto
            while(k<len_prefix && ok){
                if(read_char==prefix[k] || prefix[k]==maiusc_minusc(read_char)) // ho trovato un carattere da eliminare
			ok=0; // esco dal ciclo e non scrivo il carattere
                k++;
            }
            if(ok!=0) write(1,&read_char,sizeof(char)); //il carattere non è contenuto nella stringa filtro
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
