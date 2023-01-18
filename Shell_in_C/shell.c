#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<fcntl.h>

int cmd_len=0;
char* args="";
int flag = 0;
char* filename;

void shell_initialization(){
	printf("\033[H\033[J");
	printf("-------------------------------------------------------\n");
	printf("THis is a risky shell dude\n");
	printf("****************All the best*************\n");	
}

// function to read commands 
int getcmd_from_user(char* str){
	char* user = getenv("USER");
	printf("%s @ %s system >>",user,user);
	fgets(str,1024,stdin);
	//scanf("%s",str);
	if(strlen(str))return 1;
	else return 0;

}


// function to be used in uniq
int compare(char*a, char*b){
	int i=0;
	while(a[i] != '\0'){
		int c = a[i] - b[i];
		if(c != 0 && c != 32 && c!= -32)return 1;
		i++;
	}
	if(b[i]!='\0')return 1;
	return 0;
}



//function to parse commands from the user cmd input
void parsestring(char* str, char** cmd){
	int i=1;
	cmd[0] = strtok(str, " ");
	while(i<100){
		cmd[i] = strtok(NULL, " ");
		if(cmd[i] == NULL)break;
		if(strlen(cmd[i]) == 0)i--;
		i++;
	}
	cmd_len = i;
	
}

//function to parse pipes from the user input string
void parsepipes(char* str, char** cmd){
	int i=1;
	cmd[0] = strtok(str, "|");
	while(i<100){
		cmd[i] = strtok(NULL, "|");
		if(cmd[i] == NULL)break;
		if(strlen(cmd[i]) == 0)i--;
		i++;
	}
	cmd_len = i;
}

void make_end_null(int argc,char* argv[]){
	int len = strlen(argv[argc-1]);
	if(argv[argc-1][len-1] == '\n')
		argv[argc-1][strlen(argv[argc-1])-1] = '\0';

}


void system_func(int argc, char* argv[]){
	//printf("entered function\n");
	int len = strlen(argv[argc-1]);
	make_end_null(argc,argv);
	//if(argv[argc-1][len-1] == '\n')argv[argc-1][strlen(argv[argc-1])-1] = '\0';
	
	char sys_cmd[1024] = "/bin/";
	strcat(sys_cmd,argv[0]);
	int status;
	
	if(argc == 1){
		argv = NULL;
		//sys_cmd[strlen(sys_cmd) - 1] = '\0';
		//printf("test\n");
	}
	else {
		argv[argc] = NULL;
	}
	
	//printf("%s\n",sys_cmd);
	if(fork() ==0){
		
		if(filename){
			filename[strlen(filename)-1] = '\0';
			int fd = open(filename, O_RDWR | O_CREAT | S_IRUSR | S_IWUSR, 0644);
		
			dup2(fd,1);
			dup2(fd,2);
			close(fd);
			filename = NULL;
		
		}
		
		if(execvp(sys_cmd,argv) < 0){
			//printf("exec error\n");
			exit(1);
		}
		
	
	} 
	else wait(&status); 
	
	//printf("still working \n");
	
}
/*
void piped_func(int argc, char* argv[]){
	int fd[2];
	
	pid_t p1,p2,p3;
	char cmd[1024] = "/bin/";
	if(pipe(fd)<0){
		printf("Pipe avvale\n");
		return 0;
	}
	int i=0;
	while(i<argc){
		char* args[100];
		parsestring(argv[i],args);
		make_end_null(cmd_len,args);
		strcat(cmd,args[0]);
		
		p1 = fork();
		if(p1 < 0){
			printf("FOrk1 avvale\n");
			return 0;
		}
		else if(p1 == 0){
			close(fd[1]);
			dup2(fd[0],STDIN_FILENO);
			close(fd[0]);
			
			if(execvp(cmd1,args1)<0){
				printf("Couldn't execute cmd1\n");
				return 0;
			}
			exit(1);
		}
		else if (p1>0){
			
		}
			
			
			printf("first fork ayyindhi\n");
			if(!i){
				close(fd[0]);
				close(1);
				dup2(pipefd[1],STDOUT_FILENO);
				close(pipefd[1]);
				if(execvp(cmd1,args1)<0){
					printf("Couldn't execute cmd1\n");
					return 0;
				}
			}
			
			
			//execvp(cmd1,args1);
			exit(1);
		} 
		i++;
	}
	

}
*/

void piped_func(char cmd1[1024], char cmd2[1024]){
	
	char std_cmd1[1024] = "/bin/";
	char std_cmd2[1024] = "/bin/";

	char* parsed_cmd1[1024];
	char* parsed_cmd2[1024];
	
	parsestring(cmd1, parsed_cmd1);
	parsestring(cmd2++, parsed_cmd2);
	
	
	printf("commans is i%s\n",parsed_cmd1[0]);
	strcat(std_cmd1,parsed_cmd1[0]);
	strcat(std_cmd1,parsed_cmd1[0]);
	//parsed_cmd1
	
	parsed_cmd1[2] = NULL;
	parsed_cmd2[2] = NULL;

	
	
	int i=0;
	int p;
	int fd[2];
	pipe(fd);
	int status;
	//printf("loop %d\n",i);
	//p=fork();
	
	
	i=0;
	while(i<2){
		//pid_t p;
		//int fd[2];
		//pipe(fd);
		//int status;
		//printf("loop %d\n",i);
		p=fork();
		
		if(p==0){
			if(!i){
				//printf("process 1\n");
				printf("%s,%s\n",std_cmd1,parsed_cmd1[0]);
				dup2(fd[1],1);
				close(fd[0]);
				close(fd[1]);
				execvp(std_cmd1,parsed_cmd1);
				exit(1);
			}
			else {
				//printf("process 2\n");
				dup2(fd[0],0);
				close(fd[0]);
				close(fd[1]);
				execvp(std_cmd2,parsed_cmd2);
				exit(1);
			}	
		
		}
		/*else {
			//wait(NULL);
			close(fd[0]);
			close(fd[1]);
			printf("parent\n");
			
			waitpid(p,&status,0);
			//close(fd[0]);
			//close(fd[1]);
			//waitpid(p,&status,0);
			printf("after p\n");
			
		}*/
		else{
			close(fd[1]);
			waitpid(p,&status,0);
		
			i++;
		}
		
	}
	close(fd[0]);


}



//function to call head function from shell

int head(int argc, char* argv[]){
	int len=0,fd,i=0,linenum=0,j=0,sz=0;
	char line[1000];
	if(argc == 2){
		len = 10;
		argv[1][strlen(argv[1]) - 1] = '\0';
		fd = open(argv[1],0);	
		printf("---%s-----\n",argv[1]);
	}
	else if(argc > 2){
		len = atoi(argv[1]);
		len *= -1;
		argv[2][strlen(argv[2]) - 1] = '\0';
		fd = open(argv[2],0);
		printf("---%s-----\n",argv[2]);
	}
	else{
		fd = 0;
		
	}
	
	char*c = (char*) malloc(512000*sizeof(char));
	if(fd<0){
		printf("r1 .... %d\n",fd);
		close(fd);
	}
	sz = read(fd,c,512000);
	c[sz] = '\0';
	
	while(linenum<len && c[i] != '\0'){
		memset(line,0,1000);
		j=0;
		while(c[i]!= '\n'){
			line[j] = c[i];
			i++;
			j++;
		}
		printf("%s\n",line);
		linenum++;
		i++;
	}
	
	close(fd);
}

//function to call sort function from shell
int sort(int argc, char* argv[]){
	int fd,sz,flag=0;
	int fd2=0;
	if(argc <=2){
		argv[1][strlen(argv[1]) - 1] = '\0';
		fd = open(argv[1],0);
	}
	else{
		args = argv[1];
		//printf("args is %s\n",args);
		if(argc > 3) {
			argv[3][strlen(argv[3]) - 1] = '\0';
			argv[2][strlen(argv[2]) - 1] = '\0';
			fd = open(argv[3],0);
			fd2 = open(argv[2],1 | 3);
		}
		else{
			argv[2][strlen(argv[2]) - 1] = '\0';
			fd = open(argv[2],0);
		}	
		flag = 1;
	}
	
	char*c = (char*) malloc(51200*sizeof(char));
	char*d = (char*) malloc(51200*sizeof(char));
	if(fd<0){
		printf("r1\n");
		
	}
	sz = read(fd,c,51200);
	c[sz] = '\0';
	
	
	
	int i=0,linenum=0,j=0,linecount=0;
	
	while(c[i]!='\0'){
		if(c[i] == '\n')linecount++;
		i++;
	}
	char* linetexts[linecount];
	//printf(1,"%d\n",linecount);
	i=0;
	linenum=0;
	char line[1000];
	char temp[1000];
	while(c[i]!='\0'){
		j=0;
		while(c[i]!='\n'){
			line[j] = c[i];
			j++;
			i++;
		}
		line[j] = '\0';
		linetexts[linenum] = (char*)malloc((j+1)*sizeof(char));
		strcpy(linetexts[linenum],line);
		linenum++;
		i++;
		int k = linenum-1;
		while(k>0){
			//printf(1,"comparing %s and %s\n",linetexts[k-1],linetexts[k]);
			if(strcmp(linetexts[k],linetexts[k-1])<0){
				strcpy(temp,linetexts[k]);
				strcpy(linetexts[k],linetexts[k-1]);
				strcpy(linetexts[k-1],temp);
				//printf(1,"after comparing %s and %s\n",linetexts[k-1],linetexts[k]);
			}
			else{
				//printf(1,"after comparing %s and %s\n",linetexts[k-1],linetexts[k]);
				break;
			} 
			//printf(1,"%d,%s\n",k,linetexts[k]);
			k--;
		}
		
		if(linenum == linecount){
			//printf(1,"printing sorted array\n");
			j=0;
			if(!flag){
				while(j<linenum){
					printf("%s\n",linetexts[j]);
					j++;
				}
			
			}
			else if(strcmp(args,"-r")==0 || strcmp(args,"-R")==0){
				j = linenum;
				while(j>=0){
					printf("%s\n",linetexts[j]);
					j--;
				}
				
			}
			else if(strcmp(args,"-o")==0 || strcmp(args,"-O")==0){
				while(j<linenum){
					write(fd2,linetexts[j],10);
					j++;
				}
				printf("%s\n",d);
				
			}
					
			
		}
	}
	i=0;
	
	close(fd);
	

}


void uniq(int argc,char* argv[]){
	int fd;
	int i=0,sz,count=0,linenum=0,record_index=1;
	char line[1000];
	char prevline[1000];
	if(argc <=2){
		argv[1][strlen(argv[1]) - 1] = '\0';
		fd = open(argv[1],0);
		flag = 1;
	}
	else {
		args = argv[1];
		argv[2][strlen(argv[2]) - 1] = '\0';
		fd = open(argv[2],0);
	}
	//uniq(fd);
	
	
	
	//Reading the file content into a string
	char*c = (char*) malloc(512000*sizeof(char));
	if(fd<0){
		printf("r1\n");
		//exit(1);
	}
	sz = read(fd,c,512000);
	c[sz] = '\0';
	
	
	i=0;
	while(c[i]!='\0'){
		count=0;
		while(c[i]!= '\n'){
			line[count] = c[i];
			count++;
			i++;
		
		}
		
		line[count] = '\0';
		i++;
		strcpy(prevline, line);
		while(c[i] != '\0'){
			count=0;
			
			while(c[i] != '\n'){
				line[count] = c[i];
				i++;
				count++;
				
			}
			line[count] = '\0';
			i++;
			if(strcmp(args,"-c")==0){
				if(strcmp(prevline,line)!=0){
					printf("%d, %s\n",record_index,prevline);
					strcpy(prevline,line);
					record_index = 1;
				}
				else record_index++;
				linenum++;
				flag = 2;
			}
			else if(strcmp(args,"-i")==0){
				int z = compare(prevline,line);
				if(z!=0){
					printf(" %s\n",prevline);
					strcpy(prevline,line);
				}
				linenum++;
			}
			else if(strcmp(args,"-d")==0){
				flag = 4;
				if(strcmp(prevline,line)!=0){
					if(record_index>1)printf("%s\n",prevline);
					strcpy(prevline,line);
					record_index = 1;
				}
				else record_index++;
				linenum++;
			}
			else{
				if(strcmp(prevline,line)!=0){
					printf(" %s\n",prevline);
					strcpy(prevline,line);
					
				}
				linenum++;
			}
			
			
			
		}
		if(flag==2)printf("%d,%s\n",record_index,prevline);
		else if(flag==4){
			if(record_index > 1)printf("%s\n",prevline);
		}
		else printf("%s\n",prevline);
	}
	//exit(1);
	close(fd);

}



void func_init(char* cmd[]){
	
	if(!strcmp(cmd[0],"head")){
		head(cmd_len,cmd);
	}
	else if(!strcmp(cmd[0],"sort"))sort(cmd_len,cmd);
	else if(!strcmp(cmd[0],"uniq"))uniq(cmd_len,cmd);
	else system_func(cmd_len,cmd);
}

int main(){
	char input[1024];
	char* cmd[100];
	char* parsed_cmd[100];
	
	int output_fd;
	shell_initialization();
	while(1){
		int a = getcmd_from_user(input);
		
		int i=1;
		filename = strtok(input,">");
		strcpy(input,filename);
		filename = strtok(NULL,">");
		
		parsed_cmd[0] = strtok(input, "|");
		while(i<100){
			parsed_cmd[i] = strtok(NULL, "|");
			if(parsed_cmd[i] == NULL)break;
			if(strlen(parsed_cmd[i]) == 0)i--;
			i++;
		}
		
		
		if(i==1){
			parsestring(input,cmd);
			func_init(cmd);
		}
		else{
			int j = 0;
			char* cmd2[100];
			char* cmd3[100];
			
			//printf("%s\n",parsed_cmd[0]);
			//printf("%s\n",parsed_cmd[1]);
			
			//char* cmd_args2[1024];
			//char* cmd_args3[1024];
			
			//parsestring(parsed_cmd[0],cmd_args2);
			//parsestring(parsed_cmd[1],cmd_args3);
			//printf("%s\n",cmd_args2[0]);
			
			
			piped_func(parsed_cmd[0],parsed_cmd[1]);
			/*while(j<i){
				char* cmd2[100];
				char* cmd3[100];
				parsestring(parsed_cmd[j],cmd2);
				parsestring(parsed_cmd[j])
				piped_func(i,parsed_cmd);
				//func_init(cmd2);
				j++;
			}*/
			
		}
		
		
		
		
		
		
	}
	return 0;

}



