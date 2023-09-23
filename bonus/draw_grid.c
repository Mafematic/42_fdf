/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:44:36 by fszendzi          #+#    #+#             */
/*   Updated: 2023/09/22 16:44:40 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/fdf_bonus.h"

void put_pixel_to_image(t_image *img, t_window *win, int x, int y, int color)
{
    int index;

    if (x < 0 || y < 0 || x >= win->width || y >= win->height)
        return;

    index = y * img->size_line + x * 4;
    *(int *)(img->data + index) = color;
}

static int	get_color(int value)
{
	if (value <= -6) 
		return (0x00008B);
	else if (value <= 0)
		return (0x007FFF);
	else if (value <= 5)
		return (0x228B22);
	else if (value <= 10)
		return (0x808000);
	else if (value <= 15)
		return (0xFFD700);
	else if (value <= 30)
		return (0x9ACD32);
	else if (value <= 60)
		return (0xFFFF00);
	else if (value <= 90)
		return (0xFFA500);
	else if (value <= 120)
		return (0xFF4500);
	return (0x8B0000);
}

static void	draw_segment(t_image *i, t_window *w, t_pixel *start, t_pixel *end, int color)
{
	put_pixel_to_image(i, w, start->w_x, start->w_y, color);
	put_pixel_to_image(i, w, end->w_x, end->w_y, color);
	draw_line(i, w, start, end, color);
}

void	draw_grid(t_pixel ***grid, t_window *w, t_prog_data *data)
{
	t_image	i;
	void	*img_ptr;
	int		row;
	int		col;
	int		color;

	img_ptr = mlx_new_image(w->mlx_ptr, w->width, w->height);
	i.data = mlx_get_data_addr(img_ptr, &i.bits_pixel, &i.size_line, &i.endian);
	row = 0;
	while (row < data->rows)
	{
		col = 0;
		while (col < data->cols)
		{
			color = get_color(grid[row][col]->z);
			if (col < data->cols - 1)
				draw_segment(&i, w, grid[row][col], grid[row][col + 1], color);
			if (row < data->rows - 1)
				draw_segment(&i, w, grid[row][col], grid[row + 1][col], color);
			col++;
		}
		row++;
	}
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, img_ptr, 0, 0);
	mlx_destroy_image(w->mlx_ptr, img_ptr);
}
