/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:45:49 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/24 09:58:57 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_is_space(int c)
{
	if((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

int	ft_is_start_map(char *line)
{
	int	i;
	
	if (!line)
		return (0);
	i = 0;
	while(line[i] && ft_is_space(line[i]) == 1)
		i++;
	if(line[i] != '1')
		return (0);
	else
	{
		while(line[i] && (line[i] == '1' || line[i] == ' ' || line[i] == '\t'))
			i++;
//			printf("%c", line[i++]);
		// printf("PFV---%c\n",line[i]);
		if(line[i] != '\n')
			return (0);
		else
			return (1);
	}
}
