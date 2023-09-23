/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:46:21 by fszendzi          #+#    #+#             */
/*   Updated: 2023/09/22 16:46:23 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/fdf_bonus.h"

void	free_numbers_from_index(char **numbers_in_line, int start_idx)
{
	int	i;

	i = start_idx;
	while (numbers_in_line[i] != NULL)
	{
		free(numbers_in_line[i]);
		i++;
	}
}

int	handle_overflow_columns(char **numbers_in_line, int y)
{
	free_numbers_from_index(numbers_in_line, y);
	return (-1);
}

int	handle_fail(char **line_num, t_pixel ***grid, int x, int y)
{
	int	prev_y;

	prev_y = 0;
	while (prev_y < y)
	{
		free(grid[x][prev_y]);
		prev_y++;
	}
	free_numbers_from_index(line_num, y);
	return (-1);
}
