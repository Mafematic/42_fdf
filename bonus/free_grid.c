/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:47:07 by fszendzi          #+#    #+#             */
/*   Updated: 2023/09/22 16:47:09 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/fdf_bonus.h"

void	free_grid(t_pixel ***grid, int num_rows, int num_columns)
{
	int	row;
	int	col;

	row = 0;
	while (row < num_rows)
	{
		col = 0;
		while (col < num_columns)
		{
			if (grid[row][col])
			{
				free(grid[row][col]);
			}
			col++;
		}
		free(grid[row]);
		row++;
	}
	free(grid);
}
