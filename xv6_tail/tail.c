#include "types.h"
#include "stat.h"
#include "user.h"




int main(int argc, char *argv[]){
	int len=0,fd,i=0,linenum=0,j=0,sz=0;
	char line[1000];
	if(argc == 2){
		len = 10;
		fd = open(argv[1],0);	
	}
	else if(argc > 2){
		len = atoi(argv[1]+1);
		//printf(1,"%s,%s\n",argv[1],argv[2]);
		fd = open(argv[2],0);
	}
	else{
		fd = 0;
		exit();
	}
	char*c = (char*) malloc(512000*sizeof(char));
	if(fd<0){
		printf(1,"r1\n");
		exit();
	}
	//printf(1,"%d\n",len);
	sz = read(fd,c,512000);
	c[sz] = '\0';
	int total = 0;
	
	while( c[i] != '\0'){
		
		while(c[i]!= '\n')i++;
		total++;
		//printf(1,"%s\n",line);
		
		i++;
	}
	//printf(1,"%d\n",total);
	
	i=0;
	while( c[i] != '\0'){
		memset(line,0,1000);
		j=0;
		while(c[i]!= '\n'){
			line[j] = c[i];
			i++;
			j++;
		}
		if(total<len || linenum >= total-len)printf(1,"%s\n",line);
		//printf(1,"%s\n",line);
		//strcpy(words[linenum],line);
		linenum++;
		i++;
	}
	
	
	
	
	exit();
}
