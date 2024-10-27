#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main()
{	int fd1 = open("my_details.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    	int fd2 = open("friend_details.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    	if (fd1 < 0 || fd2 < 0)
{	printf("Failed to open or create files.\n");
        		return 1;
    	}
    	char my_details[] = "Name: Alice\nAge: 20\nCity: New York\n";
    	char friend_details[] = "Name: Bob\nAge: 21\nCity: New York\n";
write(fd1, my_details, strlen(my_details));
    	write(fd2, friend_details, strlen(friend_details));
close(fd1);
    	close(fd2);
    	fd1 = open("my_details.txt", O_RDONLY);
    	fd2 = open("friend_details.txt", O_RDONLY);
if (fd1 < 0 || fd2 < 0)
{	printf("Failed to open files for reading.\n");
        		return 1;
    	}
    	char buffer1[100], buffer2[100];
    	int bytes_read1 = read(fd1, buffer1, sizeof(buffer1));
    	int bytes_read2 = read(fd2, buffer2, sizeof(buffer2));
    	buffer1[bytes_read1] = '\0';
    	buffer2[bytes_read2] = '\0';
    	printf("Matching lines:\n");
    	char *line1 = strtok(buffer1, "\n");
   	char *line2 = strtok(buffer2, "\n");
    	while (line1 != NULL && line2 != NULL)
{	if (strcmp(line1, line2) == 0)
{	printf("%s\n", line1);
       		}
        		line1 = strtok(NULL, "\n");
        		line2 = strtok(NULL, "\n");
    	}
close(fd1);
    	close(fd2);
printf("\nhello...this os program to check matched lines");
    	return 0;

