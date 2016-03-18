/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 14:20:25 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/18 14:21:04 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_l		*ins_start(t_l *begin, t_l *new)
{
	new->next = begin;
	begin = new;
	return (begin);
}

void	ins_middle(t_l *prev, t_l *new, t_l *next)
{
	prev->next = new;
	if (next != NULL)
	new->next = next;
}
