/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:57:38 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/20 16:20:04 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static t_l		*fill_ar(int i, int argc, char **argv, t_option *opt)
{
	t_l *ar;
	t_l *tmp;
	//struc timespec tmp1;
	//struc timespec tmp2;
	ar = fill_data(argv[i], argv[i], NULL, opt);
	tmp = ar;
	while (i < argc - 1)
	{
		i++;
		t_l *new;
		new = fill_data(argv[i], argv[i], NULL, opt);
			if ((ft_strcmp(new->name, tmp->name)) <= 0)
				ar = ins_start(ar, new);
			else
			{
				while (tmp->next != NULL && ft_strcmp(new->name, (tmp->next)->name) >= 0)
					tmp = tmp->next;
				ins_middle(tmp, new, tmp->next);
			}
			tmp = ar;
	}
	return (ar);
}

int sort_time(t_l *new, t_l *tmp)
{
	t_l	*tmp1;
	t_l *tmp2;

	tmp1 = new;
	tmp2 = tmp;
	if ((tmp1->time_sec).tv_sec == (tmp2->time_sec).tv_sec)
	{
		if ((tmp1->time_sec).tv_nsec > (tmp2->time_sec).tv_nsec)
			return (0);
		if ((tmp1->time_sec).tv_nsec < (tmp2->time_sec).tv_nsec)
			return (1);
		if (ft_strcmp(new->name, tmp->name) < 0)
			return (0);
		return (1);
	}
	if ((tmp1->time_sec).tv_sec > (tmp2->time_sec).tv_sec)
		return (0);
	return (1);
}

static	t_l	*fill_t_ar(int i, int argc, char **argv, t_option *opt)
{
	t_l	*ar;
	t_l *tmp;
	t_l *new;

	new = NULL;
	ar = fill_data(argv[i], argv[i], NULL, opt);
	tmp = ar;
	while (i < argc - 1)
	{
		i++;
		new = fill_data(argv[i], argv[i], NULL, opt);
			if (sort_time(new, tmp) == 0)
				ar = ins_start(ar, new);
		else
		{
			while (tmp->next != NULL && sort_time(new, tmp->next) == 1)
				tmp = tmp->next;
			ins_middle(tmp, new, tmp->next);
		}
		tmp = ar;
	}
	return (ar);
}

static	t_l	*remove_link(t_l *ar, char *name, t_option *opt)
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

t_l	*check_file(t_l *ar, t_option *opt)
{
	t_l *tmp;
	struct stat buf;

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

static void	sort_ar(t_l *ar, t_option *opt)
{
	int nb_file;
	int nb_rep;

	nb_file = 0;
	nb_rep = 0;
	ar = check_file(ar, opt);
	if (opt->r == 1)
		ar = reverse(ar);
	if (ar == NULL)
		exit(0) ;
	init_file(ar, opt, &nb_file, &nb_rep);
	init_rep(ar, opt, nb_file, nb_rep);
}

static	int		check_flag(char *str)
{
	if(str[0] == '-' && str[1] != '\0')
		return (1);
	else
		return (0);
}

void	start(int argc, char **argv, t_option *opt)
{
	int i;

	i = 1;
	while (argc > i && argv[i][0] == '-' && argv[i][1] != '-' &&\
			check_flag(argv[i]) == 1)
		i++;
	if (i < argc && ft_strcmp("--", argv[i]) == 0)
		i++;
	if (argc == i)
	{
		print_dir(".", opt);
		return ;
	}
	if (opt->t == 1)
		sort_ar(fill_t_ar(i, argc, argv, opt), opt);
	else
		sort_ar(fill_ar(i, argc, argv,opt), opt);
}
