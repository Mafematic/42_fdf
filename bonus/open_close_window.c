/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:45:40 by fszendzi          #+#    #+#             */
/*   Updated: 2023/09/22 16:45:43 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

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

void	close_window_and_free(t_window *window)
{
	t_xvar	*xvar;

	if (window)
	{
		if (window->win_ptr)
		{
			mlx_destroy_window(window->mlx_ptr, window->win_ptr);
		}
		if (window->mlx_ptr)
		{
			xvar = (t_xvar *)window->mlx_ptr;
			if (xvar && xvar->display)
			{
				XCloseDisplay(xvar->display);
			}
			free(window->mlx_ptr);
		}
		free(window);
	}
}
