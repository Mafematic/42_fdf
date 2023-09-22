#include "../includes/get_next_line.h"
#include "../includes/fdf.h"

void	isopixel(t_pixel ***g, t_window *w, t_iso *i, t_prog_data *d)
{
	int		m;
	int		n;
	t_pixel	*current_pixel;
	float	normalized_iso_x;
	float	normalized_iso_y;

	w->padding = 20;
	m = -1;
	while (++m < d->rows) 
	{
		n = 0;
		while (n < d->cols) 
		{
			current_pixel = g[m][n];
			normalized_iso_x = 2.0 * (current_pixel->isoX - i->min_iso_x) 
				/ (i->max_iso_x - i->min_iso_x) - 1.0;
			normalized_iso_y = 2.0 * (current_pixel->isoY - i->min_iso_y) 
				/ (i->max_iso_y - i->min_iso_y) - 1.0;
			current_pixel->wX = w->padding + (normalized_iso_x + 1.0) 
				* ((w->width - 2 * w->padding) / 2.0);
			current_pixel->wY = w->padding + (normalized_iso_y + 1.0) 
				* ((w->height - 2 * w->padding) / 2.0);
			n++;
		}
	}
}
