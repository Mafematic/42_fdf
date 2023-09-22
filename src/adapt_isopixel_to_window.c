/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapt_isopixel_to_window.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:43:06 by fszendzi          #+#    #+#             */
/*   Updated: 2023/09/22 16:43:17 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/fdf.h"

void	adapt_iso_pixel(t_prog_data *data)
{
	int		m;
	int		n;
	t_pixel	*cur_pixel;
	float	normalized_iso_x;
	float	normalized_iso_y;

	data->win->padding = 20;
	m = -1;
	while (++m < data->rows) 
	{
		n = 0;
		while (n < data->cols) 
		{
			cur_pixel = data->grid[m][n];
			normalized_iso_x = 2.0 * (cur_pixel->iso_x - data->iso->min_iso_x)
				/ (data->iso->max_iso_x - data->iso->min_iso_x) - 1.0;
			normalized_iso_y = 2.0 * (cur_pixel->iso_y - data->iso->min_iso_y) 
				/ (data->iso->max_iso_y - data->iso->min_iso_y) - 1.0;
			cur_pixel->w_x = data->win->padding + (normalized_iso_x + 1.0) 
				* ((data->win->width - 2 * data->win->padding) / 2.0);
			cur_pixel->w_y = data->win->padding + (normalized_iso_y + 1.0) 
				* ((data->win->height - 2 * data->win->padding) / 2.0);
			n++;
		}
	}
}
