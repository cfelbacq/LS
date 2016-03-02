/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 13:49:19 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/02 16:49:33 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ls.h"

void	fill_data(struct passwd *get, char *name, struct group	 *getgrp\
		,struct stat *buf, t_l *data)
{
	data = (t_l *)ft_memalloc(sizeof(t_l));
	data->name = (char *)ft_memalloc(sizeof(char) * ft_strlen(name) + 1);
	data->user = (char *)ft_memalloc(sizeof(char) * ft_strlen(get->pw_name));
	data->group_name = (char *)ft_memalloc(sizeof(char) *\
			ft_strlen(getgrp->gr_name + 1));
	data->nb_link = buf->st_nlink;
	data->nb_octet = buf->st_mode;
	ft_strcpy(data->name, name);
	ft_strcpy(data->user, get->pw_name);
	ft_strcpy(data->group_name, getgrp->gr_name);
	ft_putendl(data->name);
	ft_putnbr(data->nb_link);
	ft_putendl(data->user);
	ft_putendl(data->group_name);
	printf("%o \n", data->nb_octet);
}

void	print_dir(char *name)
{
	struct stat buf;
	struct dirent *ent;
	struct passwd *get;
	DIR *rep;
	t_l *data;
	char start[1] = ".";

	rep = opendir(name);
	name = ft_strjoin(name, "/");
	while ((ent = readdir(rep)) != NULL)
	{
		if ((ft_strcmp(".", ent->d_name) != 0) && (ft_strcmp("..", ent->d_name) != 0))
		{
			stat(ent->d_name, &buf);
			if(S_ISDIR(buf.st_mode))
			{
				ft_putendl(ft_strjoin(name, ent->d_name));
				print_dir((ft_strjoin(name, ent->d_name)));
			}
			else
			{
				ft_putendl(ent->d_name);
			}
		}
	}
}

int	main(int argc, char **argv)
{
	DIR * rep;
	struct stat buf;

	int a;
	a = 0;
	t_l *data;
	rep = NULL;
	if (argc == 1)
		print_dir(".");
		//rep = opendir(".");
	else if(argc == 2)
		print_dir(argv[1]);
		//rep = opendir(argv[1]);
	struct passwd *get;
	struct dirent *ent;
	struct group *getgrp;
	/*while ((ent = readdir(rep)) != NULL)
	{
		stat(ent->d_name, &buf);
		getgrp = getgrgid(buf.st_gid);
		get = getpwuid(buf.st_uid);
		fill_data(get, ent->d_name, getgrp, &buf, data);
		if (buf.st_mode == S_IFDIR || buf.st_mode >= 40000)
			ft_putendl("rep");
		fprintf(stdout, "ID PROPIETAIRE(%s) : %d\n",get->pw_name, buf.st_uid);
		fprintf(stdout, "ID DU GROUPE(%s) : %d\n",getgrp->gr_name, buf.st_gid);
		fprintf(stdout, "Protection : %o\n", buf.st_mode);
		fprintf(stdout, "taille : %lld octets\n ", (long long)buf.st_size);
		fprintf(stdout, "NB LIEN : %ld \n", (long)buf.st_nlink);
		printf("dernier changement d'etat : %s", ctime(&buf.st_ctime));
		printf("dernier acces au fichier : %s", ctime(&buf.st_atime));
		printf("derniere modification du fichier : %s\n", ctime(&buf.st_mtime));
	}*/
	return (0);
}
