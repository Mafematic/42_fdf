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
#include "../includes/fdf_bonus.h"

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

static void	update_ortho_bounds(t_ortho *ortho, t_pixel *current_pixel)
{
	if (current_pixel->x < ortho->min_ortho_x)
		ortho->min_ortho_x = current_pixel->x;
	if (current_pixel->x > ortho->max_ortho_x)
		ortho->max_ortho_x = current_pixel->x;
	if (current_pixel->y < ortho->min_ortho_y)
		ortho->min_ortho_y = current_pixel->y;
	if (current_pixel->y > ortho->max_ortho_y)
		ortho->max_ortho_y = current_pixel->y;
}

t_ortho	*find_min_max_ortho(t_pixel ***grid, t_prog_data *data)
{
	t_ortho	*ortho;
	int		i;
	int		j;

	ortho = (t_ortho *)malloc(sizeof(t_ortho));
	if (ortho == NULL)
		return (NULL);
	ortho->min_ortho_x = MY_FLOAT_MAX;
	ortho->max_ortho_x = MY_FLOAT_MIN;
	ortho->min_ortho_y = MY_FLOAT_MAX;
	ortho->max_ortho_y = MY_FLOAT_MIN;
	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			update_ortho_bounds(ortho, grid[i][j]);
			j++;
		}
		i++;
	}
	return (ortho);
}
