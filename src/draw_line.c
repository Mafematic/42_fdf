#include "../includes/get_next_line.h"
#include "../includes/fdf.h"

static void	initialize_line_vars(t_pixel *start, t_pixel *end, t_line_vars *v)
{
	v->x0 = start->wX;
	v->y0 = start->wY;
	v->x1 = end->wX;
	v->y1 = end->wY;
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
