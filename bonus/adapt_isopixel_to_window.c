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

void adapt_ortho_pixel(t_prog_data *data)
{
    int m, n;
    t_pixel *cur_pixel;
    float normalized_x, normalized_y;

    data->win->padding = 20;

    // The range of x and y in orthographic projection will likely be the raw x and y.
    // Thus, we can use data->iso->max_iso_x and its companions as our bounds.
    float max_x = data->ortho->max_ortho_x;
    float min_x = data->ortho->min_ortho_x;
    float max_y = data->ortho->max_ortho_y;
    float min_y = data->ortho->min_ortho_y;

    m = -1;
    while (++m < data->rows) 
    {
        n = 0;
        while (n < data->cols) 
        {
            cur_pixel = data->grid[m][n];
            normalized_x = 2.0 * (cur_pixel->x - min_x) / (max_x - min_x) - 1.0;
            normalized_y = 2.0 * (cur_pixel->y - min_y) / (max_y - min_y) - 1.0;

            cur_pixel->w_x = data->win->padding + (normalized_x + 1.0) 
                * ((data->win->width - 2 * data->win->padding) / 2.0);
            cur_pixel->w_y = data->win->padding + (normalized_y + 1.0) 
                * ((data->win->height - 2 * data->win->padding) / 2.0);
            n++;
        }
    }
}


