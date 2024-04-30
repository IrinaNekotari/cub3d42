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

t_anim	*create_sprite(int delay)
{
	t_anim	*sprite;
	int		i;

	i = 0;
	sprite = ft_calloc(1, sizeof(t_anim));
	while (i < IMAGES_IN_SPRITES)
		sprite->sprites[i++] = NULL;
	sprite->current = NULL;
	sprite->delay = delay;
	sprite->index = 0;
	return (sprite);
}

void	add_to_set(t_anim *s, char *tex)
{
	int	i;

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

t_contr	*init_controller(void)
{
	t_contr	*contr;
	int		i;

	i = 0;
	contr = ft_calloc(1, sizeof(t_contr));
	while (i < MAX_ANIMATIONS)
		contr->sprite_set[i++] = NULL;
	contr->frame = 0;
	contr->frame_max = 0;
	return (contr);
}

void	add_to_control(t_contr *a, t_anim *s)
{
	int	i;

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
