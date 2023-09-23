/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:47:29 by fszendzi          #+#    #+#             */
/*   Updated: 2023/09/22 16:47:33 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/fdf_bonus.h"

void	free_words(char **words)
{
	int	i;

	i = 0;
	while (words[i] != NULL)
	{
		free(words[i]);
		words[i] = NULL;
		i++;
	}
	free(words);
}
