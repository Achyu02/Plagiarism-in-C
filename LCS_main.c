#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>
#include "files.h"
char * substrng(char * s,int i,int n);
int  split(char * s,char * s2[]);
char * substrng(char * s,int i,int n)
	{

  /* To obtain substring from the string and 
    returns substring
  */

  char* substr=(char*)malloc(sizeof(char)*1000);
  int p=0;
  strcpy(substr,"");
  for (int j = i; j <= n;j++)
	 {
     substr[p] = s[j]; 
     p++; 
 
   }
    substr[p] = '\0'; 
    return substr;
  }

int  split(char * s,char * s2[]){

  /* It splits the string and returns the
    length of the substrings
  */
  
  	char * s1;
  	int l=strlen(s);
   	int i=0,n=2,j=0,l1=0;
	 for (int i = 0; i<l;i++)
	 {
		  for (int j=i;j<l; j++)
		  {
		   s1=substrng(s,i,j);
		   s2[l1]=s1;
		   l1++;
		  }
	 }
	return l1;
  }
int main(int argc, char const *argv[])
{
	char *s = (char*)malloc(sizeof(char)*1000);
  char *t = (char*)malloc(sizeof(char)*1000);
	int l1,l2;
	int c[100];
	int n;
	char LCS[10];               // Declaration of different strings 
	char * s2[1000];
	char * s3[1000];
	char * str[1000];
	char * stemp;
  struct dirent *de; 
  char folder[1000];
  float result;
  DIR *dr;
  if (argc==2){
    dr=opendir(argv[1]);		//Opens the files through command prompt
    strcpy(folder,argv[1]);                     
    strcat(folder,"\\");
  }
  else                           //Opening the files from current directory
  {
    dr= opendir(".");
    strcpy(folder,".");
    strcat(folder,"\\");
  }
  char *Filesnums[1000];
  if (dr == NULL) 
  {
    perror(" wrong path : ");
  }
  int a;
  int i=0;
  while ((de = readdir(dr)) != NULL)
  {
    if (strlen(de->d_name)>2)//directory containing txt files are copied into an array
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
    for (int z = 0; z < i; ++z)
    {
      printf("  \t\t%s",Filesnums[z]);  //To print the filenames in matrix format
    }									                  //in columns
    printf("\n");
  for (int j = 0; j < i; j++)
    {
      printf("%s ",Filesnums[j]);
      for (int k = 0; k < i; k++)
        {
          if(j!=k)
        {
          char filepath1[1000];
          char filepath2[1000];                      // For opening of txt files 
          strcpy(filepath1,folder);
          strcpy(filepath2,folder);
          strcat(filepath1,Filesnums[j]);
          strcat(filepath2,Filesnums[k]);
          s=file_open(filepath1);
          t=file_open(filepath2);
          int length1=strlen(s);
          int length2=strlen(t);
        	l1=split(s,s2);
	        l2=split(t,s3);      //Split function splits the string to substring
          int z=0,count=0;
          char temp[100];
          strcpy(temp," ");
          for (int i = 0; i < l1;i++)
          {
       	    for (int j = 0; j < l2; j++) //It compares two files and copies into another array
       	    {
       		   if(strcmp(s2[i],s3[j])==0){
       			  count=count+1;
       			  str[z]=s2[i];
       			  strcpy(temp,s2[i]);
       			  int x=strlen(temp);
       			  c[z]=x;
       			  z++;
       	      }
       	    }
          }
        int m=c[0];
        strcpy(LCS,str[0]);
        for (int i = 1; i < z; i++)//To calculate maximum length from common substrings 
        {
       	  if(m<c[i]){
       		 m=c[i];
       		 strcpy(LCS,str[i]);
       	  }
        }
       float num=(m*2);
       float den=(length1+length2);   //To calculate the plagiarism percentage
       result=(num/den)*100;
      }
    else
    {
      strcpy(LCS,"SAME");
    result=100.00;
    }
    printf("   \t%s,%0.2f",LCS,result);
  }
    printf("\n");
}
return 0;
}
