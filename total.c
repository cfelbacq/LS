/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   total.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 16:37:24 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/21 16:39:26 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int	round_total(float nb)
{
	int nb_div;

	nb_div = nb / 512;
	if (nb / 512 > nb_div)
		return (nb / 512 + 1);
	return (nb / 512);
}

int	total(t_l *data)
{
	t_l		*tmp;
	t_stat	buf;
	int		total;
	int		count;

	count = 0;
	total = 0;
	tmp = data;
	while (tmp)
	{
		lstat(tmp->path, &buf);
		total = total + round_total(buf.st_size);
		tmp = tmp->next;
	}
	return (total);
}
