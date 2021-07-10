#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <unistd.h>
#include <sys/stat.h> 
#include <errno.h> 
int charsize = 1e6; 
char str[1000001];
char path[1000000];
char fname[1000000]; 
void reverse(char *exp,int st,int end) 
{
	char re[1000000];
	for(int i=st;i<=end;i++)re[i] = *(exp+i);
	for(int i=st;i<=end;i++)*(exp+i) = re[end-i];
} 
int main(int argc,char* args[]) 
{ 
	int fd = open(args[1], O_RDONLY); 
	char ch; 
	int point=0;
	for(int i=0;i<strlen(args[1]);i++) { 
		ch = *(args[1] + i); 
		if(ch=='/')point=i;
	} 
	if(point == 0){ 
		for(int i=0;i<strlen(args[1]);i++)fname[i] = *(args[1]+i);
	}
	else { 
		for(int i=(point+1);i<strlen(args[1]);i++)fname[i-(point+1)] = *(args[1]+i);  
		for(int i=0;i<=point;i++)path[i] = *(args[1]+i);
	}
	if(fd==-1)perror("Program: "); 
	else{ 
		int end = lseek(fd,0,SEEK_END); 
		int rem = end%charsize; 
		int extra = -rem; 
		int exseek = lseek(fd,extra,SEEK_END); 
		int exread = read(fd,str,rem); 
		int dir = mkdir("Assignment", 0777); 
		if(dir==-1)perror("Program: ");
		char string[] = "./Assignment/"; 
		strcat(string,fname); 
		int fd2 = open(string,O_RDWR | O_CREAT,0644); 
		reverse(str,0,rem-1); 
		int exwr = write(fd2,str,rem); 
		char strper[16]; 
		float percent = rem; 
		sprintf(strper, "\rProgress: %0.2f",(percent*100)/(float)end); 
		int out = write(1,strper,16); 
		int exend = rem;
		int exchsz; 
		while(exend<end) 
		{ 
			exend +=charsize;
			exchsz = -exend;
			exseek = lseek(fd,exchsz,SEEK_END);  
			exread = read(fd,str,charsize); 
			reverse(str,0,charsize-1); 
			exwr = write(fd2,str,charsize); 
			percent+=charsize; 
			sprintf(strper, "\rProgress: %0.2f",(percent*100)/(float)end); 
			exseek = lseek(1,0,SEEK_SET); 
			out =write(1,strper,16); 
		} 
		close(fd); 
		close(fd2);		 
	} 
	return 0; 
}