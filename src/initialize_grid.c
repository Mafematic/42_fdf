/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_grid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:43:43 by fszendzi          #+#    #+#             */
/*   Updated: 2023/09/22 16:43:45 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/fdf.h"

t_pixel	***initialize_grid(int num_rows, int num_columns)
{
	t_pixel	***grid;
	int		row;

	grid = (t_pixel ***)malloc(num_rows * sizeof(t_pixel **));
	if (!grid)
	{
		printf("Memory allocation failed!\n");
		return (NULL);
	}
	row = 0;
	while (row < num_rows)
	{
		grid[row] = (t_pixel **)malloc(num_columns * sizeof(t_pixel *));
		if (!grid[row])
		{
			printf("Memory allocation failed!\n");
			free_grid(grid, row, num_columns);
			return (NULL);
		}
		row++;
	}
	return (grid);
}
