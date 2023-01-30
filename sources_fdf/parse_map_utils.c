/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:16:48 by lwidmer           #+#    #+#             */
/*   Updated: 2023/01/30 15:39:55 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	abs_f(float x)
{
	if (x < 0)
		return (-x);
	else
		return (x);
}

void	free_map_int(int **map, int num_lines)
{
	int	i;

	i = 0;
	while (i < num_lines)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_map_struct(t_point **map_struct, int num_lines)
{
	int	i;

	i = 0;
	while (i < num_lines)
	{
		free(map_struct[i]);
		i++;
	}
	free(map_struct);
}

int	**free_line(char **line_split, char *line, int **map, int **map_t)
{
	int	i;

	i = 0;
	while (line_split[i])
	{
		free (line_split[i]);
		i++;
	}
	free(line);
	free(line_split);
	free(map);
	return (map_t);
}
