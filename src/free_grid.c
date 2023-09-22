#include "../includes/get_next_line.h"
#include "../includes/fdf.h"

void	free_grid(t_pixel ***grid, int num_rows, int num_columns)
{
	int	row;
	int	col;

	row = 0;
	while (row < num_rows)
	{
		col = 0;
		while (col < num_columns)
		{
			if (grid[row][col])
			{
				free(grid[row][col]);
			}
			col++;
		}
		free(grid[row]);
		row++;
	}
	free(grid);
}
