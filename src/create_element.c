#include "../includes/get_next_line.h"
#include "../includes/fdf.h"

t_pixel	*create_element(t_pixel pt, int width, int height)
{
	t_pixel	*new_pixel;

	new_pixel = (t_pixel *)malloc(sizeof(t_pixel));
	if (new_pixel == NULL) 
	{
		perror("Failed to create new grid element");
		return (NULL);
	}
	new_pixel->x = pt.x;
	new_pixel->y = pt.y;
	new_pixel->z = pt.z;
	new_pixel->isoX = (pt.x - pt.y) * cos(M_PI / 4);
	new_pixel->isoY = (pt.x + pt.y - pt.z) * sin(M_PI / 4);
	new_pixel->wX = 0;
	new_pixel->wY = 0;
	return (new_pixel);
}
