/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:54:18 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/22 11:13:14 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	print_l(t_l *data, t_option *opt)
{
	if (!(opt->a == 0 && data->name[0] == '.'))
	{
		ft_putchar(data->type);
		ft_putstr(data->mode);
		ft_putstr("  ");
		ft_putnbr(data->nb_link);
		ft_putchar(' ');
		ft_putstr(data->user);
		ft_putstr("  ");
		ft_putstr(data->group_name);
		ft_putstr("  ");
		if (data->type == 'c' || data->type == 'b')
			print_maj_min(data);
		else
			ft_putnbr(data->nb_octet);
		ft_putstr(data->time);
		ft_putchar(' ');
		ft_putstr(data->name);
		if (data->type == 'l')
		{
			ft_putstr(" -> ");
			ft_putstr(data->link);
		}
		ft_putchar('\n');
	}
}

void	print_path(char *path)
{
	ft_putchar('\n');
	ft_putstr(path);
	ft_putchar(':');
	ft_putchar('\n');
}

void	print_opt(t_option *opt)
{
	ft_putstr("l : ");
	ft_putnbr(opt->l);
	ft_putchar('\n');
	ft_putstr("R : ");
	ft_putnbr(opt->re);
	ft_putchar('\n');
	ft_putstr("a : ");
	ft_putnbr(opt->a);
	ft_putchar('\n');
	ft_putstr("r : ");
	ft_putnbr(opt->r);
	ft_putchar('\n');
	ft_putstr("t : ");
	ft_putnbr(opt->t);
	ft_putchar('\n');
}

void	print_err(char *str)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_strsplit(str, '/');
	while (tab[i] != NULL)
		i++;
	i--;
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(tab[i], 2);
	ft_putstr_fd(": ", 2);
	perror("");
	free_double(tab);
}
