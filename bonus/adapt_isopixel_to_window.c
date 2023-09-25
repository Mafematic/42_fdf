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
#include "../includes/fdf_bonus.h"

static void	normalize_coordinates(t_pixel *pixel, t_prog_data *data)
{
	pixel->normal_iso_x = 2.0 * (pixel->iso_x - data->iso->min_iso_x)
		/ (data->iso->max_iso_x - data->iso->min_iso_x) - 1.0;
	pixel->normal_iso_y = 2.0 * (pixel->iso_y - data->iso->min_iso_y)
		/ (data->iso->max_iso_y - data->iso->min_iso_y) - 1.0;
}

static void	updt_wndw(t_pixel *p, t_prog_data *d, float zm_c_x, float zm_c_y)
{
	float	half_width;
	float	half_height;

	half_width = (d->win->width - 2 * d->win->padding) / 2.0;
	half_height = (d->win->height - 2 * d->win->padding) / 2.0;
	p->w_x = d->win->padding + (p->normal_iso_x + 1.0)
		* half_width + d->trans_x;
	p->w_y = d->win->padding + (p->normal_iso_y + 1.0)
		* half_height + d->trans_y;
	p->w_x = (p->w_x - zm_c_x) * d->scale_factor + zm_c_x;
	p->w_y = (p->w_y - zm_c_y) * d->scale_factor + zm_c_y;
}

void	adapt_iso_pixel(t_prog_data *data)
{
	float	zoom_cen_x;
	float	zoom_cen_y;
	int		m;
	int		n;
	t_pixel	*cur_pixel;

	zoom_cen_x = data->win->width / 2.0;
	zoom_cen_y = data->win->height / 2.0;
	data->win->padding = 20;
	m = -1;
	while (++m < data->rows)
	{
		n = 0;
		while (n < data->cols)
		{
			cur_pixel = data->grid[m][n];
			normalize_coordinates(cur_pixel, data);
			updt_wndw(cur_pixel, data, zoom_cen_x, zoom_cen_y);
			n++;
		}
	}
}

void	adapt_ortho_pixel(t_prog_data *data)
{
	int		m;
	int		n;
	t_pixel	*cur_pixel;
	float	normalized_x;
	float	normalized_y;

	data->win->padding = 20;
	m = -1;
	while (++m < data->rows)
	{
		n = 0;
		while (n < data->cols)
		{
			cur_pixel = data->grid[m][n];
			normalized_x = 2.0 * (cur_pixel->x - data->ortho->min_ortho_x)
				/ (data->ortho->max_ortho_x - data->ortho->min_ortho_x) - 1.0;
			normalized_y = 2.0 * (cur_pixel->y - data->ortho->min_ortho_y)
				/ (data->ortho->max_ortho_y - data->ortho->min_ortho_y) - 1.0;
			cur_pixel->w_x = data->win->padding + (normalized_x + 1.0)
				* ((data->win->width - 2 * data->win->padding) / 2.0);
			cur_pixel->w_y = data->win->padding + (normalized_y + 1.0)
				* ((data->win->height - 2 * data->win->padding) / 2.0);
			n++;
		}
	}
}
