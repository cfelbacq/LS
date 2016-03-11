/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:54:18 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/11 15:19:21 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	print_l(t_l *data, t_option *opt)
{
	if (!(opt->a == 0 && data->name[0] == '.'))
	{
	ft_putchar(data->type);
	ft_putstr(data->mode);
	ft_putchar(' ');
	ft_putnbr(data->nb_link);
	ft_putchar(' ');
	ft_putstr(data->user);
	ft_putchar(' ');
	ft_putstr(data->group_name);
	ft_putchar(' ');
	ft_putnbr(data->nb_octet);
	ft_putchar(' ');
	ft_putstr(data->name);
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
