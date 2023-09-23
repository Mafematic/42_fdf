/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:45:11 by fszendzi          #+#    #+#             */
/*   Updated: 2023/09/22 16:45:13 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/fdf.h"

static void	initialize_line_vars(t_pixel *start, t_pixel *end, t_line_vars *v)
{
	v->x0 = start->w_x;
	v->y0 = start->w_y;
	v->x1 = end->w_x;
	v->y1 = end->w_y;
	v->dx = abs(v->x1 - v->x0);
	v->dy = abs(v->y1 - v->y0);
	if (v->x0 < v->x1)
		v->sx = 1;
	else
		v->sx = -1;
	if (v->y0 < v->y1)
		v->sy = 1;
	else
		v->sy = -1;
	v->err = v->dx - v->dy;
}

void	draw_line(t_image *img, t_pixel *start, t_pixel *end, int color)
{
	t_line_vars	v;
	int			e2;

	initialize_line_vars(start, end, &v);
	while (1) 
	{
		put_pixel_to_image(img, v.x0, v.y0, color);
		if (v.x0 == v.x1 && v.y0 == v.y1)
			break ;
		e2 = 2 * v.err;
		if (e2 > -v.dy)
		{
			v.err -= v.dy;
			v.x0 += v.sx;
		}
		if (e2 < v.dx)
		{
			v.err += v.dx;
			v.y0 += v.sy;
		}
	}
}
