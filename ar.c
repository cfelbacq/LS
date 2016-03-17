/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:57:38 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/17 15:52:58 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static t_l		*fill_ar(int i, int argc, char **argv, t_option *opt)
{
	t_l *ar;
	t_l *tmp;
	t_l *new;

	ar = fill_data(argv[i], argv[i], NULL, opt);
	tmp = ar;
	while (i < argc - 1)
	{
		i++;
		new = fill_data(argv[i], argv[i], NULL, opt);
		if ((ft_strcmp(new->name, tmp->name)) < 0)
			ar = ins_start(ar, new);
		else
		{
			while (tmp->next != NULL &&\
				ft_strcmp(new->name, (tmp->next)->name) > 0)
			tmp = tmp->next;
			ins_middle(tmp, new, tmp->next);
		}
		tmp = ar;
	}
	return (ar);
}

static void		init_rep(t_l *ar, t_option *opt, int nb_file, int nb_rep)
{
	t_l *tmp;
	t_l *rep;
	int i;

	i = 0;
	tmp = ar;
	rep = NULL;
	while (tmp)
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
			print_dir(tmp->name, opt);
			i++;
		}
		tmp = tmp->next;
	}
}

static void		init_file(t_l *ar, t_option *opt, int *nb_file, int *nb_rep)
{
	t_l *tmp;

	tmp = ar;
	while (tmp)
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

static	t_l		*remove_link(t_l *ar, char *name, t_option *opt)
{
	t_l *tmp1;
	t_l *tmp2;

	tmp2 = NULL;
	tmp1 = ar;
	while (tmp1 != NULL && ft_strcmp(tmp1->name, name) != 0)
	{
		tmp2 = tmp1;
		tmp1 = tmp1->next;
	}
	if (tmp2 == NULL)
	{
		tmp2 = ar;
		ar = ar->next;
		free_data(&tmp2, 0, opt);
	}
	else
	{
		tmp2->next = tmp1->next;
		free_data(&tmp1, 0, opt);
	}
	return (ar);
}

static	void	print_err_ar(char *str)
{
	ft_putstr("ls : ");
	ft_putstr(str);
	ft_putstr(": ");
	perror("");
}

static	t_l		*check_file(t_l *ar, t_option *opt)
{
	t_l		*tmp;
	t_stat	buf;

	tmp = ar;
	while (tmp != NULL)
	{
		if (lstat(tmp->name, &buf) == -1)
		{
			opt->err += 1;
			print_err_ar(tmp->name);
			ar = remove_link(ar, tmp->name, opt);
		}
		tmp = tmp->next;
	}
	return (ar);
}

static void		sort_ar(t_l *ar, t_option *opt)
{
	int nb_file;
	int nb_rep;

	nb_file = 0;
	nb_rep = 0;
	ar = check_file(ar, opt);
	if (ar == NULL)
		exit(0) ;
	init_file(ar, opt, &nb_file, &nb_rep);
	init_rep(ar, opt, nb_file, nb_rep);
}

void			start(int argc, char **argv, t_option *opt)
{
	int i;

	i = 1;
	while (argc > i && argv[i][0] == '-')
		i++;
	if (argc == i)
	{
		print_dir(".", opt);
		return ;
	}
	sort_ar(fill_ar(i, argc, argv, opt), opt);
}
