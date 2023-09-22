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

static int	handle_col(char **line_num, t_pixel ***grid, t_window *w, t_program_data *data, int x)
{
	t_pixel	p;
	int		y;

	y = 0;
	while (line_num[y] != NULL && y < data->cols)
	{
		if (y >= data->cols)
		{
			return (handle_overflow_columns(line_num, y));
		}
		p.x = x;
		p.y = y;
		p.z = ft_atoi(line_num[y]);
		grid[x][y] = create_element(p, w->win_width, w->win_height);
		if (!grid[x][y])
		{
			return (handle_fail_creation(line_num, grid, x, y));
		}
		free(line_num[y]);
		y++;
	}
	return (1);
}

static int	process_line(char *line, t_pixel ***grid, t_window *w, t_program_data *data, int x)
{
	char 	**numbers_in_line;
	int		result;

	numbers_in_line = ft_split(line, ' ');
    if (!numbers_in_line) 
        return (-1);
    result = handle_col(numbers_in_line, grid, w, data, x);
    free(numbers_in_line);
    return result;
}

int parse_file(t_pixel ***grid, t_window *w, t_program_data *data)
{
    char	*line;
    int		fd;
    int		x;
	
	x = 0;
    fd = open_file("pylone.fdf");
    if (fd <= 0)
    {
        perror("Could not open file!");
        return (-1);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        if (x >= data->rows)
        {
            perror("Too many rows in the input file!");
            free(line);
            close_file(fd);
            return (-1);
        }
        if (process_line(line, grid, w, data, x) == -1)
        {
            free(line);
            close_file(fd);
            return (-1);
        }
        free(line);
        x++;
    }
    if (close_file(fd) == 0)
    {
        perror("Could not close file.");
        return (-1);
    }
    return (1); 
}
