/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 14:14:16 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/20 15:46:30 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	init_rep(t_l *ar, t_option *opt, int nb_file, int nb_rep)
{
	t_l *tmp;
	t_l *rep;
	int i;

	i = 0;
	tmp = ar;
	rep = NULL;
	while(tmp)
	{
		if (tmp->type == 'd')
		{
			if (nb_file > 0 || nb_rep > 1 || opt->err > 0)
			{
				if (nb_file > 0 || i > 0)
					ft_putchar('\n');
				ft_putstr(tmp->name);
				ft_putendl(":");
			}
			if (tmp->type == 'd')
				print_dir(tmp->name, opt);
			i++;
		}
		tmp = tmp->next;
	}
}

void	init_file(t_l *ar, t_option *opt, int *nb_file, int *nb_rep)
{
	t_l *tmp;

	tmp = ar;
	while(tmp)
	{
		if (tmp->type != 'd')
		{
			*nb_file += 1;
			if (opt->l == 1)
				print_l(tmp, opt);
			else
				ft_putendl(tmp->name);
		}
		else
			*nb_rep += 1;
		tmp = tmp->next;
	}
}
