/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:47:39 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/21 16:58:58 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static	char	*fill_hour(char *time, char *time_print, int j, int i)
{
	int count;

	count = 0;
	while (time[i] != '\n' && count < 2)
	{
		if (time[i] == ':')
			count++;
		time_print[j] = time[i];
		j++;
		i++;
	}
	time_print[j - 1] = '\0';
	return (time_print);
}

static	char	*fill_year(char *ttime, char *time_print, int j, int i)
{
	int k;

	k = 0;
	while (ttime[i] != ' ')
	{
		time_print[j] = ttime[i];
		j++;
		i++;
	}
	while (ttime[k] != '\n')
		k++;
	while (ttime[k] != ' ')
		k--;
	while (ttime[k] != '\n')
	{
		time_print[j] = ttime[k];
		j++;
		k++;
	}
	time_print[j] = '\0';
	return (time_print);
}

static	char	*get_time(char *ttime, t_stat *buf)
{
	char	*time_print;
	int		i;
	int		count;
	int		j;

	j = 0;
	count = 0;
	i = 0;
	time_print = (char *)malloc(ft_strlen(ttime) + 1);
	while (ttime[i] != ' ')
		i++;
	while (ttime[i] < '0' || ttime[i] > '9')
	{
		time_print[j] = ttime[i];
		i++;
		j++;
	}
	if (time(NULL) - buf->st_mtime > 15552000 \
			|| time(NULL) - buf->st_mtime < -15552000)
		time_print = fill_year(ttime, time_print, j, i);
	else
		time_print = fill_hour(ttime, time_print, j, i);
	return (time_print);
}

t_l				*fill_data(char *path, char *name, t_l *next, t_option *opt)
{
	t_l			*data;
	t_stat		buf;

	data = (t_l *)ft_memalloc(sizeof(t_l));
	lstat(path, &buf);
	get_path_name(data, path, name);
	fill_type(&buf, data);
	if (data->type == 'l')
		data->link = ft_readlink(path, buf.st_size);
	if (opt->l == 1)
	{
		data->time = (char *)ft_memalloc((ft_strlen(ctime(&buf.st_mtime))) + 1);
		data->time = get_time(ft_strcpy(data->time, (ctime(&buf.st_mtime))),\
				&buf);
		if (data->type == 'c' || data->type == 'b')
			get_major_minor(data, buf);
		get_user_grp(data, buf);
		fill_mod(&buf, data);
		data->nb_octet = buf.st_size;
		data->nb_link = buf.st_nlink;
	}
	get_time_sec(data, buf);
	data->next = next;
	return (data);
}
