/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:57:38 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/15 12:44:51 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static t_l		*fill_ar(int i, int argc, char **argv)
{
	t_l *ar;
	t_l *tmp;

	ar = fill_data(argv[i], argv[i], NULL);
	tmp = ar;
	while (i < argc - 1)
	{
		i++;
		t_l *new;
		new = fill_data(argv[i], argv[i], NULL);
			if ((ft_strcmp(new->name, tmp->name)) < 0)
				ar = ins_start(ar, new);
			else
			{
				while (tmp->next != NULL && ft_strcmp(new->name, (tmp->next)->name) > 0)
					tmp = tmp->next;
				ins_middle(tmp, new, tmp->next);
			}
			tmp = ar;
	}
	return (ar);
}


static void	init_rep(t_l *ar, t_option *opt, int nb_file, int nb_rep)
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
			if (nb_file > 0 || nb_rep > 0)
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

static void	init_file(t_l *ar, t_option *opt, int *nb_file, int *nb_rep)
{
	t_l *tmp;
	t_l *file;

	tmp = ar;
	file = NULL;
	while(tmp)
	{
		if (tmp->type != 'd')
		{
			*nb_file += 1;
			file = tmp;
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

t_l	*remove_link(t_l *ar, t_l *tmp, int i)
{
	t_l *tmp2;
	int j;

	j = 0;
	tmp2 = ar;
	if (i == 0)
	{
		ar = tmp->next;
		free(tmp);
		return (ar);
	}
	else
	{
		ft_putnbr(i);
		while (j < i - 1)
		{
			tmp2 = tmp2->next;
			j++;
		}
		tmp2->next = tmp->next;
		free(tmp);
	}
	return (NULL);
}

static void check_err(t_l *ar)
{
	int i;
	DIR *rep;
	t_l *tmp;
	struct stat buf;

	i = 0;
	tmp = ar;
	while (tmp)
	{
		i++;
		stat(tmp->name, &buf);
		if (errno == ENOENT)
		{
			if ((rep = opendir(tmp->name)) == NULL)
			{
				print_err(tmp->name);
				ar = remove_link(tmp, ar, i);
			}
		}
		tmp = tmp->next;
	}
}

static void	sort_ar(t_l *ar, t_option *opt)
{
	t_l *rep;
	int nb_file;
	int nb_rep;
	t_l *tmp;
	nb_file = 0;
	nb_rep = 0;
//	check_err(ar);
	init_file(ar, opt, &nb_file, &nb_rep);
	init_rep(ar, opt, nb_file, nb_rep);
}

void	start(int argc, char **argv, t_option *opt)
{
	int i;
	int j;
	DIR *rep;
	t_l *ar;

	j = argc;
	i = 1;
	while (argc > i && argv[i][0] == '-')
		i++;
	if (argc == i)
	{
		print_dir(".", opt);
		return ;
	}
	ar = fill_ar(i, argc, argv);
	sort_ar(ar, opt);
}
