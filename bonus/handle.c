/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:47:40 by fszendzi          #+#    #+#             */
/*   Updated: 2023/09/22 16:47:43 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/fdf.h"

int	handle_key(int keycode, void *param)
{
	t_prog_data	*data;
	// Print the keycode to the console
    printf("Keycode: %d\n", keycode);

	data = (t_prog_data *)param;
	if (keycode == 65307)
	{
		close_window_and_free(data->win);
		free_grid(data->grid, data->rows, data->cols);
		free(data->iso);
		exit(0);
	}
    if (keycode == 49)
    {
        if (data->current_projection == PROJECTION_ISO)
        {
            data->current_projection = PROJECTION_ORTHO;
        }
        else
        {
            data->current_projection = PROJECTION_ISO;
        }
        project_new(data);
        draw_grid(data->grid, data->win, data);
    }
	return (0);
}

int	handle_close(void *param)
{
	t_prog_data	*data;

	data = (t_prog_data *)param;
	close_window_and_free(data->win);
	free_grid(data->grid, data->rows, data->cols);
	free(data->iso);
	exit(0);
	return (0);
}
