/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:23:07 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/04 17:05:17 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int main(int ac, char **av)
{
	int i;

	i = 0;
	t_parcing p;
	initial(&p);
	ft_parse(&p, ac, av);
	printf("R: %d\t%d\nsouth:\t%s\nwest:\t%s\neast:\t%s\nnorth:\t%s\ns_path:"
			"\t%s\n"
			"C=> R: %d\tG: %d\tB: %d\t\tRGB: %d\n"
			"F=> R: %d\tG: %d\tB: %d\t\tRGB: %d\n",
			p.p_w, p.p_h,
	p.south, p.west, p.east, p.north, p.s_path,
	p.c[C].r, p.c[C].g, p.c[C].b, p.c[C].color,
	p.c[F].r, p.c[F].g, p.c[F].b, p.c[F].color);
	puts("MAP");
	puts("\n\n");

	i = -1;
	while (p.map.map[++i])
		printf("[%s]\n", p.map.map[i]);

	printf("%d\t%d\t\t%d\n", p.map.nbr_rows, p.map.nbr_cols, p.file_args);
	return (0);
}
