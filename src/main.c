/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:44:25 by fszendzi          #+#    #+#             */
/*   Updated: 2023/09/22 16:44:29 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/fdf.h"

static int	initialize_data(t_prog_data *data, char *filename)
{
	if (!find_rows_cols(data, filename))
		return (0);
	data->win = open_window(800, 600, "Frido's Window");
	if (!data->win)
		return (0);
	data->grid = initialize_grid(data->rows, data->cols);
	if (!data->grid)
	{
		close_window_and_free(data->win);
		return (0);
	}
	return (1);
}

static int	process_file_and_setup_iso(t_prog_data *data, char *filename)
{
	if (!parse_file(data->grid, data, filename))
	{
		close_window_and_free(data->win);
		free_grid(data->grid, data->rows, data->cols);
		return (0);
	}
	data->iso = find_min_max_iso(data->grid, data);
	if (!data->iso)
	{
		printf("Failed to allocate memory for iso bounds\n");
		close_window_and_free(data->win);
		free_grid(data->grid, data->rows, data->cols);
		return (0);
	}
	return (1);
}

static void	setup_hooks_and_draw(t_prog_data *data)
{
	adapt_iso_pixel(data);
	draw_grid(data->grid, data->win, data);
	mlx_hook(data->win->win_ptr, 2, 1L << 0, handle_key, data);
	mlx_hook(data->win->win_ptr, 17, 1L << 17, handle_close, data);
	mlx_loop(data->win->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_prog_data	data;

	if (argc != 2)
	{
		write(1, "Usage: ./fdf <filename>\n", 24);
		return (1);
	}
	if (!initialize_data(&data, argv[1]))
		return (1);
	if (!process_file_and_setup_iso(&data, argv[1]))
		return (1);
	setup_hooks_and_draw(&data);
	return (0);
}
