#include "../includes/get_next_line.h"
#include "../includes/fdf.h"

static void	free_numbers_from_index(char **numbers_in_line, int start_idx)
{
	int	i;

	i = start_idx;
	while (numbers_in_line[i] != NULL)
	{
		free(numbers_in_line[i]);
		i++;
	}
}

static int	handle_overflow_columns(char **numbers_in_line, int y)
{
	free_numbers_from_index(numbers_in_line, y);
	return (-1);
}

static int	handle_fail_creation(char **line_num, t_pixel ***grid, int x, int y)
{
	int	prev_y;

	prev_y = 0;
	while (prev_y < y)
	{
		free(grid[x][prev_y]);
		prev_y++;
	}
	free_numbers_from_index(line_num, y);
	return (-1);
}

static int	handle_col(char **line, t_pixel ***grid, t_prog_data *data, int x)
{
	t_pixel	p;
	int		y;

	y = 0;
	while (line[y] != NULL && y < data->cols)
	{
		if (y >= data->cols)
		{
			return (handle_overflow_columns(line, y));
		}
		p.x = x;
		p.y = y;
		p.z = ft_atoi(line[y]);
		grid[x][y] = create_element(p);
		if (!grid[x][y])
		{
			return (handle_fail_creation(line, grid, x, y));
		}
		free(line[y]);
		y++;
	}
	return (1);
}

static int	process_line(char *line, t_pixel ***grid, t_prog_data *data, int x)
{
	char	**numbers_in_line;
	int		result;

	numbers_in_line = ft_split(line, ' ');
	if (!numbers_in_line)
		return (-1);
	result = handle_col(numbers_in_line, grid, data, x);
	free(numbers_in_line);
	return (result);
}

static int	initialize_parsing(int *fd, char *filename)
{
	*fd = open_file(filename);
	if (*fd <= 0)
	{
		perror("Could not open file!");
		return (-1);
	}
	return (1);
}

static int	process_lines(int fd, t_pixel ***grid, t_prog_data *data)
{
	char	*line;
	int		x;

	x = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (x >= data->rows)
		{
			perror("Too many rows in the input file!");
			free(line);
			return (-1);
		}
		if (process_line(line, grid, data, x) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
		x++;
		line = get_next_line(fd);
	}
	return (1);
}

int	parse_file(t_pixel ***grid, t_prog_data *data, char *filename)
{
	int	fd;

	if (initialize_parsing(&fd, filename) == -1)
	{
		close_file(fd);
		return (-1);
	}
	if (process_lines(fd, grid, data) == -1)
	{
		close_file(fd);
		return (-1);
	}
	if (close_file(fd) == 0)
	{
		perror("Could not close file.");
		return (-1);
	}
	return (1);
}
