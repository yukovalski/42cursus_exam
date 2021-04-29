/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:13:26 by sgath             #+#    #+#             */
/*   Updated: 2021/03/13 14:49:25 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_bc
{
	int		w;
	int		h;
	char	c;
}			t_bc;

typedef struct s_crcl
{
	char	type;
	float	x;
	float	y;
	float	r;
	char	c;
}			t_crcl;

int
	end_prog(char *str, FILE *file, char * map, int rez)
{
	if (str)
		while (*str)
			write(1, &(*str++), 1);
	if (file)
		fclose(file);
	if (map)
		free(map);
	return(rez);
}

int
	check_crcl(int x, int y, t_crcl crcl)
{
	float r;

	r = sqrtf(powf(x - crcl.x, 2) + powf(y - crcl.y, 2));
	if (r <= crcl.r)
	{
		if ((crcl.r - r) < 1)
			return(2);
		return (1);
	}
	return (0);
}

int
	draw_zone(t_bc bgc, char **map, FILE *file)
{
	t_crcl	crcl;
	int x, y;
	int	i, ret;

	while ((ret = fscanf(file, "%c %f %f %f %c\n", &crcl.type, &crcl.x, &crcl.y,
		&crcl.r, &crcl.c)) == 5)
	{
		if (crcl.type != 'C' && crcl.type != 'c')
			return(-1);
		x = -1;
		while (++x < bgc.w)
		{
			y = -1;
			while (++y < bgc.h)
			{
				i = check_crcl(x, y, crcl);
				if ((i == 2 && crcl.type == 'c') || (crcl.type == 'C' && i))
					(*map)[bgc.w * y + x] = crcl.c;
			}
		}
	}
	return (ret == -1 ? 0 : -1);
}

void
	print_map(char *map, t_bc bgc)
{
	int count, i;
	
	count = 1;
	i = -1;
	while (map[++i])
	{
		if (i == count * bgc.w)
		{
			write(1, "\n", 1);
	 		count++;
		}
	 	write(1, &map[i], 1);
	}
	write(1, "\n", 1);
}

int
	main(int av, char **ac)
{
	FILE	*file;
	char	*map;
	t_bc	bgc;


	if (av == 2)
	{
		if ((file = fopen(ac[1], "r")) == NULL)
			return (end_prog("Error: Operation file corrupted\n", NULL, NULL, 1));
		if ((fscanf(file, "%d %d %c\n", &bgc.w, &bgc.h, &bgc.c) != 3)
			|| (bgc.h < 1 || bgc.h > 300 || bgc.w < 1 || bgc.w > 300))
			return (end_prog("Error: Operation file corrupted\n", file, NULL, 1));
		if (!(map = calloc(sizeof(char) , (bgc.w * bgc.h + 1))))
			return (end_prog("Error: Operation file corrupted\n", file, map, 1));
		memset(map, bgc.c, bgc.h * bgc.w);
		if (draw_zone(bgc, &map, file) < 0)
			return (end_prog("Error: Operation file corrupted\n", file, map, 1));
		print_map(map, bgc);
		return(end_prog(NULL, file, map, 0));
	}
	else
		return (end_prog("Error: argument\n", NULL, NULL, 1));
}