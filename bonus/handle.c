/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:47:40 by fszendzi          #+#    #+#             */
/*   Updated: 2023/09/22 16:47:43 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/fdf_bonus.h"

int	handle_key_bonus(int key, t_prog_data *data)
{
	if (key == 61)
	{
		data->scale_factor += 0.1;
		apply_zoom(data, data->scale_factor);
	}
	else if (key == 45)
	{
		data->scale_factor -= 0.1;
		apply_zoom(data, data->scale_factor);
	}
	if (data->iso)
		free(data->iso);
	data->iso = find_min_max_iso(data->grid, data);
	adapt_iso_pixel(data);
	draw_grid(data->grid, data->win, data);
	return (0);
}

int	handle_key(int keycode, t_prog_data *data)
{
	handle_key_bonus(keycode, data);
	if (keycode == 65307)
	{
		close_window_and_free(data->win);
		free_grid(data->grid, data->rows, data->cols);
		free(data->iso);
		free(data->ortho);
		exit(0);
	}
	if (keycode == 49)
	{
		if (data->current_projection == PROJECTION_ISO)
			data->current_projection = PROJECTION_ORTHO;
		else
			data->current_projection = PROJECTION_ISO;
		project_new(data);
		draw_grid(data->grid, data->win, data);
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
	free(data->ortho);
	exit(0);
	return (0);
}
