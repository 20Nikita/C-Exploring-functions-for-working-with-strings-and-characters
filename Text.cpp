#include <locale.h>	
#include <stdio.h>	
#include <string.h>	
#define буфер 500
int main()
{
	setlocale(LC_ALL, "Russian");	
	char s[буфер] = { 0 };			
	char * q, * w;					
	FILE* in = NULL;				
	FILE* out = NULL;				
	int	i = 0;						
	int	j = 0;						
	int quoted = 0;					
	int comment = 0;				
	int comment2 = 0;				

	in = fopen("Source.cpp", "r");	
	if (!in) {						
		printf(" Не удалось открыть файл. \n");
		return 1;
	}

	out = fopen("Text.cpp", "w");	
	
	while (fgets(s, буфер, in) != NULL) {
		q = strstr(s, "/*");
		w = strstr(s, "//");
		
		if (!q && !w && !comment && !comment2)
			fprintf(out, s);
		else
			while (s[i]) {
				
				if (s[i - 2] != '/' && s[i - 1] == '*' && s[i] == '/')
					comment = 0, i++;	
				
				if (s[i] == '\n')
					comment2 = 0;		
				
				if (!comment && !comment2 && !quoted && s[i] == '"' && s[i - 1] != '\'' && s[i - 1] != '\\')
				{
					quoted = 1;			
					fputc(s[i], out);	
					i++;				
				}
				
				while (quoted && s[i] == '\\')
				{
					fputc(s[i], out);	
					j++;				
					i++;				
				}
				
				if (s[i] == '"' && j  == 0)
					quoted = 0;			
				
				else if (!comment2 && s[i] == '/' && s[i + 1] == '*' && !quoted)
					comment = 1;		
				
				else if (s[i] == '/' && s[i + 1] == '/' && !quoted && !comment)
					comment2 = 1;		
				
				if (!comment && !comment2)
					fputc(s[i], out);	
				i++;					
				j = 0;					
			}
		quoted = 0;
		i = 0;
	}
	printf("\tПрограмма сработала корректно, ошибок не обнаружено.\n\tОбработанный текст содержится в файле \"Text.cpp\"\n");
}