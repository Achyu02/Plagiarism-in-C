char* string_Conversion(char *ch)
{
	/* To remove the special characters and lower 
		the characters in the string and returns the modified string
	*/
	char* data = (char *) malloc(sizeof(char) * 10000);
	strlwr(ch);
	int i=0,j=0;
	int a = strlen(ch);
	while(i!=a)
	{
		if (ch[i]==32||ch[i]>96&&ch[i]<123)
		{
			data[j]=ch[i];
			j++;
		}
		i+=1;
	}
	data[i]='\0';
	return data;
	
}
int fcmp_txt(char *file_name)
{
	/* To compare two strings with txt format and returns 
		the obtained result value
	*/

	char *cmp = (char *) malloc(sizeof(char) * 1000);
	cmp = "txt";
	char *r;
	int a;
	r = strstr(file_name,cmp);
	if(r == NULL)
	{
		r="EMPTY";
	}
	a=strcmp(r,cmp);
	return a;
}
char* file_open(char *file_name)
{
	/*for opening file and copying to string 
		and to move multiple lines in a single line
	*/
	
	FILE * fp;											
	FILE * fp1;
	char *s = (char*)malloc(sizeof(char)*10000);
	char *s2 = (char*)malloc(sizeof(char)*10000);
	char *d = (char*)malloc(sizeof(char)*10000);
	int i=0,j=0;
	fp = fopen(file_name, "r");
  if(!fp) 
  	{
  		// strcat(s,"0.0");
  		return NULL;  
  		}
  	else
  	{ 
  		strcpy(s,"");
  		strcpy(s2,"");
  while (fgets(s2,1000,fp)!=NULL) {				
  	int temp2=strlen(s2);
  		if (s2[temp2-1]=='\n'){
  			s2[temp2-1]=' ';
  		}
  	  strcat(s,s2);
}
          }
          d=string_Conversion(s);
          return d; 	
}