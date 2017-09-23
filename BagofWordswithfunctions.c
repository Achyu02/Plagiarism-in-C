#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>
#include "files.h"
struct function
{
	char * words;
	int count;
};
int char_split(char* s,struct function f1[]);
int dot_product(int len,int len2,struct function f[],struct function f2[]);
float euclidean_norm(int len,struct function f[]);

int main(int argc, char const *argv[])
{
	struct dirent *de; 
	char folder[1000];
	DIR *dr ;					// To open files from directory
	if (argc==2){
		dr=opendir(argv[1]);
		strcpy(folder,argv[1]);	//To give input from command line directory
		strcat(folder,"\\");
	}
	else 
	{
		dr= opendir(".");
		strcpy(folder,".");	 //Points to current path if no path is declared
		strcat(folder,"\\");
	}
	
	char *Filesnums[100];
	if (dr == NULL) 
	{
		perror(" wrong path : ");
	}
	int a;
	int i=0;
	while ((de = readdir(dr)) != NULL)	//To read files from directory  
	{
		if (strlen(de->d_name)>2) 		//	copy files into an array
		{
	   		a = fcmp_txt(de->d_name);
	   		if(a==0)
	   			{
					Filesnums[i]=malloc(strlen(de->d_name));
					strcpy(Filesnums[i],de->d_name);
					i=i+1;
	   			}	
	    }
	 }
	  for (int z = 0; z < i; ++z)			//To print the file names in
	{
		printf("  \t\t%s",Filesnums[z]);	//column format			
	}
	printf("\n");
	 char *s = (char*)malloc(sizeof(char)*100);
	 char *s1 = (char*)malloc(sizeof(char)*100);
	 int len,len2;
	 float result;
	 float plagiarism[10];	// Declaration of variables of different data types
	 int temp=0;
	 struct function f[100];
 	struct function f2[100];
	 for (int j = 0; j < i; j++)
	 {
			printf("%s",Filesnums[j]);

	 	for (int k = 0; k < i; k++)
	 	{
				if(j!=k)
	 		{
	 			char filepath1[1000];
	 			char filepath2[1000];
	 			strcpy(filepath1,folder);
	 			strcpy(filepath2,folder);			
	 			strcat(filepath1,Filesnums[j]);
	 			strcat(filepath2,Filesnums[k]);	 											
	 			s=file_open(filepath1);
	 			s1=file_open(filepath2);	// To open the files from the folder
	 			len=char_split(s,f);
				len2=char_split(s1,f2);
				int num=0;
				float den1,den2=0.0;
				num=dot_product(len,len2,f,f2);	
				den1=euclidean_norm(len,f);
				den2=euclidean_norm(len2,f2);
				float den=(den1*den2);
				result=(num/den)*100;
				plagiarism[temp]=result;
	 			
				temp++;
			}
			else{
				result=100.0;
			}
			printf("     \t%.2f",result);
	 	}
	 	printf("\n");
	 }
	 return 0;
}
int dot_product(int len,int len2,struct function f[],struct function f2[]){

	/* To calculate the dot product 
		of two files consisting the strings
	*/
	int num=0;
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len2;j++)
	{
		if(strcmp(f[i].words,f2[j].words)==0){
			num=num+(f[i].count*f2[j].count);
		}
	}
	}
	return num;
}
float euclidean_norm(int len,struct function f[]){

	/* To calculate the Euclidean norm 
		for two files and result is returned 
	*/

	float den1=0.0;
for (int i = 0; i < len; i++)
	{
		den1=den1+pow(f[i].count,2);
	}
	den1=sqrt(den1);
	return den1;
}
int rem_dup(int k,struct function f1[]){

	/* To remove the duplicates from the array
		and the length is returned
	*/

	int len=0;
	for(int j=0;j<k;j++){
			for(int y=j+1;y<k;){
				if(strcmp(f1[j].words,f1[y].words)==0){
					for (int z = y; z < k; z++)
					{
						f1[z].words=f1[y+1].words;
							
					} 
					k=k-1;
				}
				else{
				y++;
				
			}
			}
			len=len+1;
		}
	return len;		
}
void freq_count(int i,char * a[],int c[],struct function f1[]){

	/* frequency count for the all the strings are 
		calculated 
	*/

	int j1=0;
		for(int j=0;j<i;j++){
		 int count=1;
		for(int l=j+1;l<i;l++){
			int r=strcmp(a[j],a[l]);
				if(r==0){
				count=count+1;
			}
		}
		c[j1]=count;
		f1[j1].count=count;
		j1=j1+1;
	}
}
int char_split(char* s,struct function f1[]){

	/* To split the characters from the string duplicates are removed
		and frequencies are calculated and the length is returned
	*/

	char b[100];
	char * a[10];
	int i=0,j=0;
	int c[100];
	char * token=strtok(s," ");
	while(token!=NULL){
		a[i]=token;
		f1[i].words=token;
		i++;
		token=strtok(NULL," ");
	}
		int k=i,count=1,j1=0,len;
		len=rem_dup(k,f1);
		freq_count(i,a,c,f1);
	return len;
	}