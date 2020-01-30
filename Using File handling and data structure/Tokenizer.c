#include <stdio.h>
#include <string.h>

int main()
{
    char str[100];
    printf("Enter SQL commands: ");
	scanf("%[^\n]",str);//^\n tells to take input until newline doesn’t get encountered

	int init_size = strlen(str);
	char delim[] = " ,;()";// can add  more than one delimiter

	char *ptr = strtok(str, delim);

	while (ptr != NULL)
	{
		printf("%s\n", ptr);
		ptr = strtok(NULL, delim);
	}

	return 0;
}