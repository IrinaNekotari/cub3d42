/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <nmascrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 01:09:37 by nmascrie          #+#    #+#             */
/*   Updated: 2024/03/29 01:09:54 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Tu peux dégager ce fichier, c'était juste pour les tests

#include "parser.h"

void printchain(t_chain *e)
{
    if (!e)
        ft_printf("NULLLL\n");
    else
    while (e)
    {
        ft_printf("%s", e->line);
        if (!e->next)
            return ;
        e = e->next;
    }
}

static void readimgset(t_imgset t)
{
    ft_printf("NO = %s\n", t.no);
    ft_printf("SO = %s\n", t.so);
    ft_printf("WE = %s\n", t.we);
    ft_printf("EA = %s\n", t.ea);
    ft_printf("F = %s\n", t.floor_img);
    ft_printf("C = %s\n", t.ceiling_img);
    ft_printf("F (rgb) = %d\n", t.floor_color);
    ft_printf("C (rgb) = %d\n", t.ceiling_color);
}

static void print_map(char **m)
{
    int i = 0;
    while (m[i])
    {
        ft_printf("## %s\n", m[i]);
        i++;
    }
}

static void print_data(t_data *d)
{
    ft_printf("## IMGSET DATA ##\n");
    readimgset(*(d->img));
    ft_printf("##SIZE OF MAP : %dx%d ##\n", d->map_height, d->map_width);
    ft_printf("## PLAYER DATA : START AT %dx%d, orientation %c ##", d->player_x, d->player_y, d->player_orientation);
    ft_printf("## MAP ##\n");
    print_map(d->map);
}

int main(int args, char *argv[])
{
    t_data *d;

    if (args != 2)
        return (255);
    else 
    {
        d = generate_data(argv[1]);
        if (!d)
            return (1);
        print_data(d);
        free_data(d, NULL);
    }
    return (0);
}
