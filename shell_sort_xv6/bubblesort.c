#include "types.h"
#include "stat.h"
#include "user.h"

char buf[51200];

void swap(char* a, char* b){
	char temp[512];
	strcpy(temp,a);
	strcpy(a,b);
	strcpy(b,temp);

}

int convert_to_num(char* str){
	int num=0,i=0;
	int neg = 0;
	if(str[i] == '-'){
		neg = 1;
		i++;
	}
	while(str[i] && (str[i] >= '0' && str[i] <= '9')){
		num = num*10 + (str[i] - '0');
		i++;
	}
	if(neg) num = num * -1;
	return num;
}

int month[12];
int month_update(char* sentence){
	if(!strcmp(sentence,"january") || !strcmp(sentence,"January"))month[0]++;
	else if(!strcmp(sentence,"february") || !strcmp(sentence,"February"))month[1]++;
	else if(!strcmp(sentence,"march") || !strcmp(sentence,"March"))month[2]++;
	else if(!strcmp(sentence,"april") || !strcmp(sentence,"April"))month[3]++;
	else if(!strcmp(sentence,"may") || !strcmp(sentence,"May"))month[4]++;
	else if(!strcmp(sentence,"june") || !strcmp(sentence,"June"))month[5]++;
	else if(!strcmp(sentence,"july") || !strcmp(sentence,"July"))month[6]++;
	else if(!strcmp(sentence,"august") || !strcmp(sentence,"August"))month[7]++;
	else if(!strcmp(sentence,"september") || !strcmp(sentence,"September"))month[8]++;
	else if(!strcmp(sentence,"october") || !strcmp(sentence,"October"))month[9]++;
	else if(!strcmp(sentence,"november") || !strcmp(sentence,"November"))month[10]++;
	else if(!strcmp(sentence,"december") || !strcmp(sentence,"December"))month[11]++;
	else return 0;
	return 1;	
}


void print_month(){
	int i=0;
	while(i<12){
		while(month[i]){
			if(i == 0)printf(1,"January\n");
			else if(i == 1)printf(1,"February\n");
			else if(i == 2)printf(1,"March\n");
			else if(i == 3)printf(1,"April\n");
			else if(i == 4)printf(1,"May\n");
			else if(i == 5)printf(1,"June\n");
			else if(i == 6)printf(1,"July\n");
			else if(i == 7)printf(1,"August\n");
			else if(i == 8)printf(1,"September\n");
			else if(i == 9)printf(1,"October\n");
			else if(i == 10)printf(1,"November\n");
			else if(i == 11)printf(1,"December\n");
			month[i]--;
		}
		i++;
	}
}

void
sort(int fd,int argc, char* argv[])
{
 
  int n;
  int no_of_lines = 0;
  

  while((n = read(fd, buf, sizeof(buf))) > 0) {
    int k =0;
    //number = n;
    while(k<n){
    	if(buf[k] == '\n')no_of_lines++;
    	k++;
    }
    int z = 0;
    char* line_Array[no_of_lines];
    k=0;
    while(k<n){
  	int word_count = 0;
  	char sentence[1000] = {};
  	//int start_space_flag = 0;
  	while(buf[k] != '\n'){
  		if(strcmp(argv[1],"-b") == 0){
  			while(buf[k]==' ')k++;
  			sentence[word_count] = buf[k];
  			word_count++;
  			k++;
  		}
  		else{
  			sentence[word_count] = buf[k];
  			word_count++;
  			k++;
  		}
  	}
  	line_Array[z] = (char*)malloc((word_count+1)*sizeof(char)); 
  	strcpy(line_Array[z], sentence);
  	z++;
  	
  	//printf(1,"ended bitch\n");
  	k++;
     }   
     
     int i=0,j=0;
     while(i<no_of_lines){
	  j=0;
	  while(j<no_of_lines-i){
	  	if(strcmp(argv[1],"-n") == 0){
	  		int a = atoi(line_Array[j]);
	  		int b = atoi(line_Array[j+1]);
	  		
	  		if(a > b){
	     			swap(line_Array[j],line_Array[j+1]);
	     			
	     		}
	  	}
	  	else {
	  		if(strcmp(line_Array[j],line_Array[j+1])>0){
	     			swap(line_Array[j],line_Array[j+1]);
	     		}
	  	}    		
	     	
	     	j++;
	  }
	  
	  i++;
	  
     }
     
     
     
     
     if(argc <=2){
     	//Print the array
     	k = 0;
     	while(k<+no_of_lines){
  		printf(1,"%s\n",line_Array[k]);
  		k++;
     	}
     }
     else{
     	if(strcmp(argv[1],"-r") == 0){
     		printf(1,"printing in reverse\n");
	     	//Print the array
	     	k = no_of_lines-1;
	     	while(k>=0){
	  		printf(1,"%s\n",line_Array[k]);
	  		k--;
	     	}
     	}
        
        if(strcmp(argv[1],"-n") == 0){
     		printf(1,"printing numerical sort\n");
	     	//Print the array
	  	k = 0;
	     	while(k<=no_of_lines){
	  		printf(1,"%s\n",line_Array[k]);
	  		k++;
	     	}
     	}
     	
     	if(strcmp(argv[1],"-b") == 0){
     		
	     	//Print the array
	  	k = 0;
	     	while(k<no_of_lines){
	  		printf(1,"%s\n",line_Array[k]);
	  		k++;
	     	}
	     	printf(1,"%s\n",line_Array[k]);
     	}
     	
     	if(strcmp(argv[1],"-u") == 0){
     		printf(1,"printing uniq sort\n");
	     	//Print the array
	     	k = 0;
	     	while(k<no_of_lines){
	  		printf(1,"%s\n",line_Array[k]);
	  		while(k < no_of_lines && strcmp(line_Array[k],line_Array[k+1]) == 0)k++;
	  		k++;
	     	}
     	}
     	
     	if(strcmp(argv[1],"-M") == 0){
     		printf(1,"printing monthly sort\n");
	     	//Print the array
	     	k = 0;
	     	while(k< no_of_lines){
	  		if(!month_update(line_Array[k]))printf(1,"%s\n",line_Array[k]);
	  		k++;
	     	}
	     	print_month();
     	}
     
     }
       
  }
  
  
  
  
  
}

int
main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 1){
    printf(1,"no filename error\n");
    exit();
  }
  if(argc == 2)i=1;
  else if(argc>2)i=2; 
  
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "cat: cannot open %s\n", argv[i]);
      exit();
    }
    sort(fd,argc,argv);
    close(fd);
  
  exit();
}
