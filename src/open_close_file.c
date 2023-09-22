#include "../includes/get_next_line.h"
#include "../includes/fdf.h"

int	open_file(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		return (0);
	}
	return (fd);
}

int	close_file(int fd)
{
	if (close(fd) == -1)
	{
		return (0);
	}
	return (1);
}
