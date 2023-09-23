/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_min_max_iso.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:45:55 by fszendzi          #+#    #+#             */
/*   Updated: 2023/09/22 16:45:57 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/fdf.h"

static void	update_iso_bounds(t_iso *iso, t_pixel *current_pixel)
{
	if (current_pixel->iso_x < iso->min_iso_x)
		iso->min_iso_x = current_pixel->iso_x;
	if (current_pixel->iso_x > iso->max_iso_x)
		iso->max_iso_x = current_pixel->iso_x;
	if (current_pixel->iso_y < iso->min_iso_y)
		iso->min_iso_y = current_pixel->iso_y;
	if (current_pixel->iso_y > iso->max_iso_y)
		iso->max_iso_y = current_pixel->iso_y;
}

t_iso	*find_min_max_iso(t_pixel ***grid, t_prog_data *data)
{
	t_iso	*iso;
	int		i;
	int		j;

	iso = malloc(sizeof(t_iso));
	if (iso == NULL)
		return (NULL);
	iso->min_iso_x = MY_FLOAT_MAX;
	iso->max_iso_x = MY_FLOAT_MIN;
	iso->min_iso_y = MY_FLOAT_MAX;
	iso->max_iso_y = MY_FLOAT_MIN;
	i = 0;
	while (i < data->rows) 
	{
		j = 0;
		while (j < data->cols)
		{
			update_iso_bounds(iso, grid[i][j]);
			j++;
		}
		i++;
	}
	return (iso);
}
