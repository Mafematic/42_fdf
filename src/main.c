#include "../includes/get_next_line.h"
#include "../includes/fdf.h"

int	handle_key(int keycode, void *param)
{
	t_prog_data	*data;

	data = (t_prog_data *)param;
	if (keycode == 65307)
	{
		close_window_and_free(data->win);
		free_grid(data->grid, data->rows, data->cols);
		free(data->iso);
		exit(0);
	}
	return (0);
}

int	handle_close(void *param)
{
	t_prog_data	*data;

	data = (t_prog_data *)param;
	close_window_and_free(data->win);
	free_grid(data->grid, data->rows, data->cols);
	free(data->iso);
	exit(0);
	return (0);
}

void	close_window_and_free(t_window *window)
{
	t_xvar	*xvar;

	if (window)
	{
		if (window->win_ptr)
		{
			mlx_destroy_window(window->mlx_ptr, window->win_ptr);
		}
		if (window->mlx_ptr)
		{
			xvar = (t_xvar *)window->mlx_ptr;
			if (xvar && xvar->display)
			{
				XCloseDisplay(xvar->display);
			}
			free(window->mlx_ptr);
		}
		free(window);
	}
}

int main(int argc, char **argv)
{
	t_prog_data	data;

	if (argc != 2)
    {
        write(1, "Usage: ./fdf <filename>\n", 24);
        return (1);
    }

	if (!find_rows_cols(&data, argv[1]))
		return (1);
	data.win = open_window(800, 600, "Frido's Window");
	if (!data.win)
		return (1);
	data.grid = initialize_grid(data.rows, data.cols);
	if (!data.grid)
	{
		close_window_and_free(data.win);
		return (1);
	}
	if (!parse_file(data.grid, &data, argv[1]))
	{
		close_window_and_free(data.win);
		free_grid(data.grid, data.rows, data.cols);
		return (1);
	}
	data.iso = find_min_max_iso(data.grid, &data);
	if (!data.iso)
	{
		printf("Failed to allocate memory for iso bounds\n");
		close_window_and_free(data.win);
		free_grid(data.grid, data.rows, data.cols);
		return (1);
	}
	isopixel(data.grid, data.win, data.iso, &data);
	draw_grid(data.grid, data.win, &data);
	mlx_hook(data.win->win_ptr, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win->win_ptr, 17, 1L << 17, handle_close, &data);
	mlx_loop(data.win->mlx_ptr);
	return (0);
}
