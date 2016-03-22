/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:57:24 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/22 13:59:06 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static	void	print_ill_opt(char c)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar(c);
	ft_putchar('\n');
	ft_putstr_fd("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1]", 2);
	ft_putendl_fd(" [file ...]", 2);
	exit(0);
}

static	int		flag_ls_ok(char c)
{
	if (c == 'A' || c == 'B' || c == 'C' || c == 'F' || c == 'G' || c == 'H' \
			|| c == 'L' || c == 'O' || c == 'P' || c == 'R' || c == 'S' \
			|| c == 'T' || c == 'U' || c == 'W' || c == 'a' || c == 'b' \
			|| c == 'c' || c == 'd' || c == 'e' || c == 'f' || c == 'g' \
			|| c == 'h' || c == 'i' || c == 'k' || c == 'l' || c == 'm' \
			|| c == 'n' || c == 'o' || c == 'p' || c == 'q' || c == 'r' \
			|| c == 's' || c == 't' || c == 'u' || c == 'w' || c == 'x' \
			|| c == '1' || c == '-')
		return (1);
	return (0);
}

static	void	check_char(t_option *opt, char c)
{
	if (c == 'l')
		opt->l = 1;
	else if (c == 'R')
		opt->re = 1;
	else if (c == 'a')
		opt->a = 1;
	else if (c == 'r')
		opt->r = 1;
	else if (c == 't')
		opt->t = 1;
	else if (c == '1')
		opt->un = 1;
	else if (flag_ls_ok(c) == 0)
		print_ill_opt(c);
}

void			check_opt(int argc, t_option *opt, char **str)
{
	int i;
	int j;
	int count;

	count = 0;
	j = 0;
	while (++j < argc)
	{
		count = 0;
		i = -1;
		if (str[j][1] == '-' && str[j][0] == '-' && str[j][2] != '\0')
			print_ill_opt('-');
		else if (str[j][1] == '-' || str[j][0] != '-')
			return ;
		else if (str[j][0] == '-' && str[j][1] == '\0')
			return ;
		while (str[j][++i] != '\0')
		{
			if (str[j][i] == '-')
				count++;
			if (count > 1)
				print_ill_opt('-');
			check_char(opt, str[j][i]);
		}
	}
}

void			init_option(t_option *opt)
{
	opt->l = 0;
	opt->re = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
	opt->err = 0;
	opt->un = 0;
}
