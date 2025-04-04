#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


int	main()
{
	int fd = open("1.txt", O_RDONLY);
	char buffer[45000];
	
	read(fd, buffer, 45000);
	printf("%s", buffer);
	return 0;
}

