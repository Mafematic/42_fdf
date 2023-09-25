/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:00:39 by fszendzi          #+#    #+#             */
/*   Updated: 2023/09/25 20:00:42 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/fdf_bonus.h"

static int	handle_key_zoom(int key, t_prog_data *data)
{
	if (key == 61)
	{
		data->scale_factor += SCALE;
		apply_zoom(data, data->scale_factor);
	}
	else if (key == 45)
	{
		data->scale_factor -= SCALE;
		apply_zoom(data, data->scale_factor);
	}
	return (0);
}

static int	handle_key_translation(int key, t_prog_data *data)
{
	if (key == 65363)
	{
		data->trans_x += TRANSLATION;
		apply_translation(data, TRANSLATION, 0);
	}
	else if (key == 65361)
	{
		data->trans_x -= TRANSLATION;
		apply_translation(data, -TRANSLATION, 0);
	}
	else if (key == 65362)
	{
		data->trans_y -= TRANSLATION;
		apply_translation(data, 0, -TRANSLATION);
	}
	else if (key == 65364)
	{
		data->trans_y += TRANSLATION;
		apply_translation(data, 0, TRANSLATION);
	}
	return (0);
}

static int	handle_key_rotation(int key, t_prog_data *data)
{
	if (key == 114)
	{
		apply_rotation(data, ROTATION);
	}
	else if (key == 108)
	{
		apply_rotation(data, -ROTATION);
	}
	return (0);
}

int	handle_key_bonus(int key, t_prog_data *data)
{
	handle_key_zoom(key, data);
	handle_key_translation(key, data);
	handle_key_rotation(key, data);
	if (data->iso)
		free(data->iso);
	data->iso = find_min_max_iso(data->grid, data);
	adapt_iso_pixel(data);
	draw_grid(data->grid, data->win, data);
	return (0);
}
