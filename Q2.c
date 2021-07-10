#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <unistd.h>
#include <sys/stat.h> 
#include <errno.h> 
int charsize = 1e6; 
char stro[1000001];
char strn[1000001];
int check = 0;
void reverse(char *exp,int st,int end) 
{
	char re[1000000];
	for(int i=st;i<=end;i++)re[i] = *(exp+i);
	for(int i=st;i<=end;i++)*(exp+i) = re[end-i];
} 
void stringchecking(char *exp1,char *exp2,int end)
{
	for(int i=0;i<=end;i++){
		if(*(exp1+i) != *(exp2+i)){
			check = 1;
			break;
		}
	}
}
int main(int argc, char* args[])
{
	int fdn = open(args[1],O_RDONLY);
	int fdo = open(args[2],O_RDONLY);
	int endn = lseek(fdn,0,SEEK_END);
	int endo = lseek(fdo,0,SEEK_END);
	if(endo != endn)check=1;
	else{
		int exseek = lseek(fdo,0,SEEK_SET);
		int rem = endn%charsize;
		int exread = read(fdo,stro,rem);
		exseek = lseek(fdn,-rem,SEEK_END);
		exread = read(fdn,strn,rem);
		reverse(strn,0,rem-1);
		stringchecking(strn,stro,rem-1);
		int exend = rem;
		if(check==0){
			while(exend < endn)
			{
				exend+=charsize;
				exread = read(fdo,stro,charsize);
				lseek(fdn,-exend,SEEK_END);
				exread = read(fdn,strn,charsize);
				reverse(strn,0,charsize-1);
				stringchecking(strn,stro,charsize-1);
				if(check==1)break;
			}
		}
	}
	struct stat status;
	char stp[50];
	if(stat(args[3],&status)==0){
		mode_t nperm = status.st_mode;
		if(nperm & S_IFDIR){
			sprintf(stp, "Directory is created: Yes\n");
			write(1,stp,strlen(stp));
		}
		else{
			sprintf(stp, "Directory is created: No\n");
			write(1,stp,strlen(stp));
		}
	}
	else perror("Program: ");
	if(check==1){
		char ans[] = "Whether file contents are reversed in newfile: No\n";
		write(1,ans,strlen(ans));
	}
	else if(check==0){
		char ans[] = "Whether file contents are reversed in newfile: Yes\n";
		write(1,ans,strlen(ans));		
	}
	if(stat(args[1], &status)==0){
		mode_t nperm = status.st_mode;
		if(nperm & S_IRUSR){
			sprintf(stp,"User has read permissions on new file: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"User has read permissions on new file: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IWUSR){
			sprintf(stp,"User has write permissions on new file: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"User has write permissions on new file: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IXUSR){
			sprintf(stp,"User has execute permissions on new file: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"User has read permissions on new file: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IRGRP){
			sprintf(stp,"Group has read permissions on new file: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"Group has read permissions on new file: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IWGRP){
			sprintf(stp,"Group has write permissions on new file: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"Group has write permissions on new file: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IXGRP){
			sprintf(stp,"Group has execute permissions on new file: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"Group has execute permissions on new file: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IROTH){
			sprintf(stp,"Others has read permissions on new file: Yes\n");
			write(1,stp,strlen(stp));
		}
		else{
			sprintf(stp,"Others has read permissions on new file: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IWOTH){
			sprintf(stp,"Others has write permissions on new file: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"Others has write permissions on new file: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IXOTH){
			sprintf(stp,"Others has execute permissions on new file: Yes\n");
			write(1,stp,strlen(stp));
		}
		else{
			sprintf(stp,"Others has execute permissions on new file: No\n");
			write(1,stp,strlen(stp));
		}

	}
	else perror("Program: ");
	if(stat(args[2], &status)==0){
		mode_t nperm = status.st_mode;
		if(nperm & S_IRUSR){
			sprintf(stp,"User has read permissions on old file: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"User has read permissions on old file: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IWUSR){
			sprintf(stp,"User has write permissions on old file: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"User has write permissions on old file: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IXUSR){
			sprintf(stp,"User has execute permissions on old file: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"User has read permissions on old file: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IRGRP){
			sprintf(stp,"Group has read permissions on old file: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"Group has read permissions on old file: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IWGRP){
			sprintf(stp,"Group has write permissions on old file: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"Group has write permissions on old file: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IXGRP){
			sprintf(stp,"Group has execute permissions on old file: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"Group has execute permissions on old file: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IROTH){
			sprintf(stp,"Others has read permissions on old file: Yes\n");
			write(1,stp,strlen(stp));
		}
		else{
			sprintf(stp,"Others has read permissions on old file: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IWOTH){
			sprintf(stp,"Others has write permissions on old file: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"Others has write permissions on old file: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IXOTH){
			sprintf(stp,"Others has execute permissions on old file: Yes\n");
			write(1,stp,strlen(stp));
		}
		else{
			sprintf(stp,"Others has execute permissions on old file: No\n");
			write(1,stp,strlen(stp));
		}
	}
	else perror("Program: ");
	if(stat(args[3], &status)==0){
		mode_t nperm = status.st_mode;
		if(nperm & S_IRUSR){
			sprintf(stp,"User has read permissions on directory: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"User has read permissions on directory: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IWUSR){
			sprintf(stp,"User has write permissions on directory: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"User has write permissions on directory: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IXUSR){
			sprintf(stp,"User has execute permissions on directory: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"User has read permissions on directory: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IRGRP){
			sprintf(stp,"Group has read permissions on directory: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"Group has read permissions on directory: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IWGRP){
			sprintf(stp,"Group has write permissions on directory: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"Group has write permissions on directory: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IXGRP){
			sprintf(stp,"Group has execute permissions on directory: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"Group has execute permissions on directory: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IROTH){
			sprintf(stp,"Others has read permissions on directory: Yes\n");
			write(1,stp,strlen(stp));
		}
		else{
			sprintf(stp,"Others has read permissions on directory: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IWOTH){
			sprintf(stp,"Others has write permissions on directory: Yes\n");
			write(1,stp,strlen(stp));
		}
		else {
			sprintf(stp,"Others has write permissions on directory: No\n");
			write(1,stp,strlen(stp));
		}
		if(nperm & S_IXOTH){
			sprintf(stp,"Others has execute permissions on directory: Yes\n");
			write(1,stp,strlen(stp));
		}
		else{
			sprintf(stp,"Others has execute permissions on directory: No\n");
			write(1,stp,strlen(stp));
		}
	}
	else perror("Program: ");
	close(fdo);
	close(fdn);
	return 0;
}