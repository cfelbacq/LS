/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:54:18 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/18 15:20:07 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	print_err_ar(char *str)
{
	ft_putstr("ls: ");
	ft_putstr(str);
	ft_putstr(": ");
	perror("");
}

void	put_double_space(void)
{
	ft_putstr("  ");
}

void	print_l(t_l *data, t_option *opt)
{
	if (!(opt->a == 0 && data->name[0] == '.'))
	{
		ft_putchar(data->type);
		ft_putstr(data->mode);
		put_double_space();
		ft_putnbr(data->nb_link);
		ft_putchar(' ');
		ft_putstr(data->user);
		put_double_space();
		ft_putstr(data->group_name);
		put_double_space();
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
	ft_putnbr(opt->R);
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
	char **tab;
	int i;

	i = 0;
	tab = ft_strsplit(str, '/');
	while (tab[i] != NULL)
		i++;
	i--;
	ft_putstr("ls: ");
	ft_putstr(tab[i]);
	ft_putstr(": ");
	perror("");
	free_double(tab);
}
