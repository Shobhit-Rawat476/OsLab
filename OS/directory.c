#include <stdio.h>
#include <dirent.h>
int main()
{	// Open the directory
    	DIR *dir = opendir(".");
    	if (dir == NULL)
{	printf("Could not open current directory.\n");
        		return 1;
    	}
    	// Read and print directory contents
    	struct dirent *entry;
    	while ((entry = readdir(dir)) != NULL)
{	printf("%s\n", entry->d_name);
    	}
    	// Close the directory
    	closedir(dir);
printf("\n");
    	return 0;
}
