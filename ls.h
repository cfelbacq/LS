/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 13:27:10 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/03 13:41:51 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LS_H
# define LS_H

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>
#include "../fdf/libft/libft.h"
#include <stdio.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

typedef	struct	s_l
{
	char	*mode;
	long	nb_link;
	char	*name;
	char	*user;
	char	*group_name;
	int	nb_octet;
	char	*time;
	char	type;
	struct s_l *next;
}				t_l;

#endif

