#include "../includes/get_next_line.h"
#include "../includes/fdf.h"

void	update_iso_bounds(t_iso_bounds *iso, t_pixel *current_pixel)
{
	if (current_pixel->isoX < iso->min_iso_x)
		iso->min_iso_x = current_pixel->isoX;
	if (current_pixel->isoX > iso->max_iso_x)
		iso->max_iso_x = current_pixel->isoX;
	if (current_pixel->isoY < iso->min_iso_y)
		iso->min_iso_y = current_pixel->isoY;
	if (current_pixel->isoY > iso->max_iso_y)
		iso->max_iso_y = current_pixel->isoY;
}

t_iso_bounds	*find_min_max_iso(t_pixel ***grid, t_program_data *data)
{
	t_iso_bounds	*iso;
	int				i;
	int				j;
	t_pixel			*current_pixel;

	iso = malloc(sizeof(t_iso_bounds));
	if (iso == NULL)
		return (NULL);
	iso->min_iso_x = FLT_MAX;
	iso->max_iso_x = FLT_MIN;
	iso->min_iso_y = FLT_MAX;
	iso->max_iso_y = FLT_MIN;
	i = 0;
	while (i < data->rows) 
	{
		j = 0;
		while (j < data->cols)
		{
			current_pixel = grid[i][j];
			update_iso_bounds(iso, grid[i][j]);
			j++;
		}
		i++;
	}
	return (iso);
}
