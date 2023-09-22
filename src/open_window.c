#include "../includes/fdf.h"

t_window	*open_window(int width, int height, char *title)
{
	t_window	*w;

	w = malloc(sizeof(t_window));
	if (!w)
		return (NULL);
	w->mlx_ptr = mlx_init();
	if (!w->mlx_ptr)
	{
		free(w);
		return (NULL);
	}
	w->width = width;
	w->height = height;
	w->win_ptr = mlx_new_window(w->mlx_ptr, w->width, w->height, title);
	if (!w->win_ptr)
	{
		free(w);
		return (NULL);
	}
	return (w); 
}
