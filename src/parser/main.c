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

static void printchain(t_chain *e)
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

int main(int args, char *argv[])
{
    t_chain *e;
    t_imgset *t;

    t = ft_calloc(1, sizeof(t_imgset));
    if (args != 2)
        return (255);
    else 
    {
        e = to_chain(argv[1]);
        printchain(e);
        remove_tail(e);
        int i = epure(e);
        //TODO:Gestion d'erreurs
        ft_printf("Retour : %d\n", i);
        printchain(e);
        i = generate_imgset(e, t);
        ft_printf("Retour : %d\n", i);
        readimgset(*t);
        free_chain(e);
        free_imgset(t);
    }
    return (0);
}
