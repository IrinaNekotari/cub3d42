/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <nmascrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 02:06:09 by nmascrie          #+#    #+#             */
/*   Updated: 2024/03/29 02:06:10 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
* A réecrire avec les >> 16
*/
int	colorpicker(int r, int g, int b)
{
	int	color;
	
	color = 0;
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		return (-1);
    color = color | (r << 16);
    color = color | (g << 8);
	color = color | (b << 0);
	return (color);
}

int is_rgb(char *a)
{
    int count;
    int i;

    i = 0;
    count = 0;
    while (a[i])
    {
        if (a[i] == ',' && a[i + 1] && a[i + 1] != ',')
            count++;
        i++;
    }
    if (count == 2)
        return (1);
    else 
        return (0);
}

int get_rgb(char *a)
{
    int     color;
    char **split;

    split = ft_split(a, ',');
    color = colorpicker(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2])
    );
    free(split[0]);
    free(split[1]);
    free(split[2]);
    free(split);
    return (color);
}