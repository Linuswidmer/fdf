/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:16:48 by lwidmer           #+#    #+#             */
/*   Updated: 2023/01/30 11:20:51 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	free_line(char **line_split, char *line)
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
}

void	print_map_int(int **map, int num_lines, int line_len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < num_lines)
	{
		while (j < line_len)
		{
			ft_printf("%i", map[i][j]);
			j++;
		}
		j = 0;
		ft_printf("\n");
		i++;
	}
}
