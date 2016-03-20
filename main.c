/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 13:49:19 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/20 14:58:57 by cfelbacq         ###   ########.fr       */
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
	t_l *tmp;
	t_stat buf;
	int total;
	int count;

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

void	ls(t_l *data, t_option *opt)
{
	int i;
	int total_print;

	total_print = 0;
	i = 0;
	while (data != NULL)
	{
		if (!(opt->a == 0 && data->name[0] == '.'))
		{
			if(opt->l != 1)
				ft_putendl(data->name);
			else
			{
				if (i == 0)
				{
					total_print = total(data);
					ft_putstr("total ");
					ft_putnbr(total_print);
					ft_putchar('\n');
				}
				i++;
				print_l(data, opt);
			}
		}
		data = data->next;
	}
}

static t_l		*fill_c_t_data(DIR *rep, char *name, t_option *opt)
{
	t_dirent *ent;
	t_l *data;
	t_l *tmp;
	t_l *new;

	ent = readdir(rep);
	name = ft_strjoin(name, "/");
	data = fill_data(ft_strjoin(name, ent->d_name), ent->d_name, NULL, opt);
	tmp = data;
	while ((ent = readdir(rep)) != NULL)
	{
		new = fill_data(ft_strjoin(name, ent->d_name), ent->d_name, NULL, opt);
		if (sort_time(new, tmp) == 0)
			data = ins_start(data, new);
		else
		{
			while (tmp->next != NULL && sort_time(new, tmp->next) == 1)
				tmp = tmp->next;
			ins_middle(tmp, new, tmp->next);
		}
		tmp = data;
	}
	return (data);
}

static t_l		*fill_c_data(DIR *rep, char *name, t_option *opt)
{
	t_dirent *ent;
	t_l *data;
	t_l *tmp;
	t_l *new;

	ent = readdir(rep);
	name = ft_strjoin(name, "/");
	data = fill_data(ft_strjoin(name, ent->d_name), ent->d_name, NULL, opt);
	tmp = data;
	while ((ent = readdir(rep)) != NULL)
	{
		new = fill_data(ft_strjoin(name, ent->d_name), ent->d_name, NULL, opt);
			if ((ft_strcmp(new->name, tmp->name)) <= 0)
				data = ins_start(data, new);
			else
			{
				while (tmp->next != NULL && ft_strcmp(new->name, (tmp->next)->name) >= 0)
					tmp = tmp->next;
				ins_middle(tmp, new, tmp->next);
			}
			tmp = data;
	}
	return (data);
}

t_l		*create_data(char *name, t_option *opt)
{
	DIR *rep;
	t_l *data;

	if ((rep = opendir(name)) == NULL)
	{
		if (errno)
		{
			print_err(name);
			return (NULL);
		}
	}
	if (opt->t == 1)
		data = fill_c_t_data(rep, name, opt);
	else
		data = fill_c_data(rep, name, opt);
	closedir(rep);
	return (data);
}

t_l	*reverse(t_l *data)
{
	t_l *tmp1;
	t_l *tmp2;
	t_l *new;

	new = NULL;
	tmp1 = data;
	tmp2 = data;
	while (tmp1)
	{
		tmp1 = tmp1->next;
		tmp2->next = new;
		new = tmp2;
		tmp2 = tmp1;
	}
	return (new);
}

void	print_dir(char *name, t_option *opt)
{
	int i;
	t_l *data;
	t_l *tmp;

	i = 0;
	if ((data = create_data(name, opt)) == NULL)
		return ;
	if (name[ft_strlen(name) - 1] != '/')
	name = ft_strjoin(name, "/");
	if (opt->r == 1)
		data = reverse(data);
	tmp = data;
	ls(tmp, opt);
	while (tmp && opt->R == 1)
	{
		if (tmp->type == 'd' && ft_strcmp(".", tmp->name) != 0 &&\
				ft_strcmp("..", tmp->name) != 0)
		{
			if (!(opt->a == 0 && tmp->name[0] == '.'))
			{
				print_path(ft_strjoin(name, tmp->name));
				print_dir(ft_strjoin(name, tmp->name), opt);
			}
		}
		tmp = tmp->next;
	}
	free_data(&data, 1, opt);
}

void	check_len_ar(int argc, char **argv)
{
	int i;

	i = 0;
	while (i < argc)
	{
		if (ft_strlen(argv[i]) == 0)
		{
			ft_putendl("ls: fts_open: No such file or directory");
			exit (0);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_option opt;
	
	init_option(&opt);
	check_opt(argc ,&opt, argv);
	check_len_ar(argc, argv);
	if (argc == 1)
		print_dir(".", &opt);
	else
		start(argc, argv, &opt);
		//rep = opendir(argv[1]);
	//	printf("dernier changement d'etat : %s", ctime(&buf.st_ctime));
	//	printf("dernier acces au fichier : %s", ctime(&buf.st_atime));
	//	printf("derniere modification du fichier : %s\n", ctime(&buf.st_mtime));
	return (0);
}
