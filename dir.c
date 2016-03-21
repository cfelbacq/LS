/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 16:45:50 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/21 17:00:58 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static t_l		*fill_c_t_data(DIR *rep, char *name, t_option *opt)
{
	t_dirent	*ent;
	t_l			*data;
	t_l			*tmp;
	t_l			*new;

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
	t_dirent	*ent;
	t_l			*data;
	t_l			*tmp;
	t_l			*new;

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
			while (tmp->next != NULL \
					&& ft_strcmp(new->name, (tmp->next)->name) >= 0)
				tmp = tmp->next;
			ins_middle(tmp, new, tmp->next);
		}
		tmp = data;
	}
	return (data);
}

static	t_l		*check_date_create(t_l *data, t_option *opt)
{
	t_l		*tmp;
	t_stat	buf;

	tmp = data;
	while (tmp)
	{
		if (!(opt->a == 0 && tmp->name[0] == '.'))
		{
			if (lstat(tmp->path, &buf) == -1)
			{
				print_err(tmp->path);
				data = remove_link(data, tmp->name, opt);
			}
		}
		tmp = tmp->next;
	}
	return (data);
}

static	t_l		*create_data(char *name, t_option *opt)
{
	DIR		*rep;
	t_l		*data;

	if ((rep = opendir(name)) == NULL)
	{
		print_err(name);
		return (NULL);
	}
	if (opt->t == 1)
		data = fill_c_t_data(rep, name, opt);
	else
		data = fill_c_data(rep, name, opt);
	data = check_date_create(data, opt);
	closedir(rep);
	return (data);
}

void			print_dir(char *name, t_option *opt)
{
	t_l *data;
	t_l *tmp;

	if ((data = create_data(name, opt)) == NULL)
		return ;
	if (ft_strcmp(name, "/") != 0)
		name = ft_strjoin(name, "/");
	if (opt->r == 1)
		data = reverse(data);
	tmp = data;
	ls(tmp, opt);
	while (tmp && opt->re == 1)
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
