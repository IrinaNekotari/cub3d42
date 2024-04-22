/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <nmascrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 00:41:33 by nmascrie          #+#    #+#             */
/*   Updated: 2024/04/22 00:41:35 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

t_sprite *create_sprite(int delay)
{
    t_sprite    *sprite;
    int         i;

    i = 0;
    sprite = ft_calloc(1, sizeof(t_sprite));
    while (i < IMAGES_IN_SPRITES)
        sprite->sprites[i++] = NULL;
    sprite->current = NULL;
    sprite->delay = delay;
    sprite->index = 0;
    return (sprite);
}

void    add_to_set(t_sprite *s, char *tex)
{
    int i;

    if (!tex || !s)
        return ;
    i = 0;
    while (s->sprites[i])
        i++;
    if (i >= IMAGES_IN_SPRITES)
        return ;
    s->sprites[i] = mlx_load_png(tex);
    if (!s->current)
        s->current = s->sprites[0];
}

void    tick_sprite(t_sprite *s)
{
    if (s->index + 1 > 9 || !s->sprites[s->index + 1])
        s->index = 0;
    else
        s->index++;
    s->current = s->sprites[s->index];
}

t_animation_controller    *init_controller(void)
{
    t_animation_controller  *contr;
    int                     i;

    i = 0;
    contr = ft_calloc(1, sizeof(t_animation_controller));
    while (i < MAX_ANIMATIONS)
        contr->sprite_set[i++] = NULL;
    contr->frame = 0;
    contr->frame_max = 0;
    return (contr);
}

int ppcm(int a, int b)
{
    int i;
    int j;

    if (!a || !b)
        return (0);
    i = a;
    j = b;
    while (a != b)
    {
        if (a > b)
            b += j;
        else if (a < b)
            a += i;
    }
    return (a);
}

void    add_to_control(t_animation_controller *a, t_sprite *s)
{
    int i;

    i = 0;
    while (a->sprite_set[i])
        i++;
    if (i > MAX_ANIMATIONS)
        return ;
    a->sprite_set[i] = s;
    if (a->frame_max == 0)
        a->frame_max = s->delay;
    else
        a->frame_max = ppcm(s->delay, a->frame_max);
}

void    tick_sprites(t_animation_controller *a)
{
    int i;

    i = 0;
    while (i < MAX_ANIMATIONS)
    {
        if ((a->frame % a->sprite_set[i]->delay) == 0)
            tick_sprite(a->sprite_set[i]);
        i++;
        if (!a->sprite_set[i])
            break ;
    }
    a->frame++;
    if (a->frame >= a->frame_max)
        a->frame = 0;
}