/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 14:14:16 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/22 13:35:01 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static	void	print_link(t_l *tmp, t_option *opt, int mode, t_nb *nb)
{
	if (mode == 0 && opt->l == 1)
	{
		print_l(tmp, opt);
		nb->file += 1;
		return ;
	}
	else if (mode == 0 && opt->l == 0 && opendir(tmp->link) == NULL)
	{
		ft_putendl(tmp->name);
		nb->file += 1;
	}
	if (mode == 1 && opt->l != 1)
	{
		if (nb->file > 0 || nb->rep > 1 || opt->err > 0)
		{
			if (nb->file > 0 || nb->i > 0)
				ft_putchar('\n');
			ft_putstr(tmp->name);
			ft_putendl(":");
		}
		print_dir(tmp->link, opt);
		nb->i += 1;
	}
}

void			init_rep(t_l *ar, t_option *opt, t_nb *nb)
{
	t_l *tmp;

	nb->i = 0;
	tmp = ar;
	while (tmp)
	{
		if (tmp->type == 'l' && opendir(tmp->link) != NULL)
			print_link(tmp, opt, 1, nb);
		if (tmp->type == 'd')
		{
			if (nb->file > 0 || nb->rep > 1 || opt->err > 0)
			{
				if (nb->file > 0 || nb->i > 0)
					ft_putchar('\n');
				ft_putstr(tmp->name);
				ft_putendl(":");
			}
			if (tmp->type == 'd')
				print_dir(tmp->name, opt);
			nb->i++;
		}
		tmp = tmp->next;
	}
}

void			init_file(t_l *ar, t_option *opt, t_nb *nb)
{
	t_l *tmp;

	tmp = ar;
	while (tmp)
	{
		if (tmp->type == 'l')
			print_link(tmp, opt, 0, nb);
		if (tmp->type != 'd' && tmp->type != 'l')
		{
			nb->file += 1;
			if (opt->l == 1)
				print_l(tmp, opt);
			else
				ft_putendl(tmp->name);
		}
		else if (tmp->type == 'd' \
				|| (tmp->type == 'l' && opendir(tmp->link) != NULL))
			nb->rep += 1;
		tmp = tmp->next;
	}
}
