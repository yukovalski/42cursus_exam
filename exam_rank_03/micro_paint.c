/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:19:44 by sgath             #+#    #+#             */
/*   Updated: 2021/03/14 14:42:20 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

typedef struct s_bg
{
	char	c;
	int		w;
	int		h;
}			t_bg;

typedef struct s_rtn
{
	char	type;
	float	x;
	float	y;
	float	w;
	float	h;
	char	c;
}			t_rtn;

int
	end_prog(int rez, char *str, char *map, FILE *file)
{
	if (str)
		while (*str)
			write(1, &(*str++), 1);
	if (map)
		free(map);
	if (file)
		fclose(file);
	return (rez);
}

int
	in_rectangle(int x, int y, t_rtn rct)
{
	if ((rct.x <= x && (rct.x + rct.h) >= x) && (rct.y <= y &&
	(rct.y + rct.w) >= y))
	{
		if (rct.x + rct.h - x < 1 || x - rct.x < 1 || rct.y +
		rct.w - y < 1 || y - rct.y < 1)
			return (2);
		return (1);
	}
	return (0);
}

int
	draw_rectangle(char **map, t_bg bgc, FILE *file)
{
	int x, y, i;
	int ret;
	t_rtn rct;

	memset((*map), bgc.c, bgc.w * bgc.h);
	while ((ret = fscanf(file, "%c %f %f %f %f %c\n", &rct.type,
		&rct.x, &rct.y, &rct.w, &rct.h, &rct.c)) == 6)
	{
		if (rct.w <= 0 || rct.h <= 0)
			return (-1);
		if (rct.type != 'R' && rct.type != 'r')
			return (-1);
		x = -1;
		while (++x < bgc.w)
		{
			y = -1;
			while (++y < bgc.h)
			{
				i = in_rectangle(x, y, rct);
				if ((i == 2 && rct.type == 'r') || (i && rct.type == 'R'))
					(*map)[bgc.w * y + x] = rct.c;
			}
		}
	}
	return(ret == -1 ? 0 : -1);
}

int
	print_map(char *map, t_bg bgc, FILE *file)
{
	int i, count;

	i = -1;
	count = 1;
	while (map[++i])
	{
		if (i == bgc.w * count)
		{
			write(1, "\n", 1);
			count++;
		}
		write(1, &map[i], 1);
	}
	return (0);
}

int
	main(int av, char **ac)
{
	FILE	*file;
	t_bg	bgc;
	char	*map;

	if (av != 2)
		return (end_prog(1, "Error: argument\n", NULL, NULL));
	if ((file = fopen(ac[1], "r")) == NULL)
		return (end_prog(1, "Error: Operation file corrupted\n",NULL, NULL));
	if (fscanf(file, "%d %d %c\n", &bgc.w, &bgc.h, &bgc.c) != 3)
		return (end_prog(1, "Error: Operation file corrupted\n",NULL, file));
	if (bgc.w < 0 || bgc.w >= 300 || bgc.h < 0 || bgc.h >= 300)
		return (end_prog(1, "Error: Operation file corrupted\n",NULL, file));
	if ((map = calloc(sizeof(char), (bgc.w * bgc.h + 1))) == NULL)
		return (end_prog(1, "Error: Operation file corrupted\n",NULL, file));
	if (draw_rectangle(&map, bgc, file) == -1)
		return (end_prog(1, "Error: Operation file corrupted\n",map, file));
	print_map(map, bgc, file);
	return (end_prog(0, NULL,map, file));
}