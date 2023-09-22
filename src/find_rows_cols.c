#include "../includes/get_next_line.h"
#include "../includes/fdf.h"

static int	handle_error_and_close(int fd, char *message)
{
	perror(message);
	if (close_file(fd) == 0)
	{
		perror("Could not close file\n");
		return (-1);
	}
	return (-1);
}

static int	count_columns_and_free(char **numbers_in_line)
{
	int	y;

	y = 0;
	while (numbers_in_line[y] != NULL)
	{
		free(numbers_in_line[y]);
		y++;
	}
	free(numbers_in_line);
	return (y);
}

static int	process_line(char *line, int fd, int *max_columns)
{
	char	**numbers_in_line;
	int		current_columns;

	numbers_in_line = ft_split(line, ' ');
	if (!numbers_in_line)
	{
		free(line);
		handle_error_and_close(fd, "Memory allocation error.\n");
		return (-1);
	}
	current_columns = count_columns_and_free(numbers_in_line);
	if (current_columns > *max_columns)
		*max_columns = current_columns;
	free(line);
	return (1);
}

int	find_rows_cols(t_prog_data *data, char *filename)
{
	char	*line;
	int		fd;
	int		max_columns;

	max_columns = 0;
	data->rows = 0;
	fd = open_file(filename);
	if (fd <= 0)
	{
		perror("Could not open file!\n");
		return (-1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (process_line(line, fd, &max_columns) == -1)
			return (-1);
		data->rows++;
		line = get_next_line(fd);
	}
	data->cols = max_columns;
	if (close_file(fd) == 0)
		return (handle_error_and_close(fd, "Could not close file.\n"));
	return (1); 
}
