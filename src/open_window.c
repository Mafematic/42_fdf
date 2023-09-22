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
	w->win_width = width;
	w->win_height = height;
	w->win_ptr = mlx_new_window(w->mlx_ptr, w->win_width, w->win_height, title);
	if (!w->win_ptr)
	{
		free(w);
		return (NULL);
	}
	return (w); 
}
