/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtai <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:54:07 by dtai              #+#    #+#             */
/*   Updated: 2020/01/27 22:43:36 by dtai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct	s_info
{
	char		param;
	int			f_dash;
	int			f_zero;
	int			f_space;
	int			f_plus;
	int			f_hash;
	int			s_width;
	int			s_precision;
	int			t_length;
}				t_info;

/*
** LEGEND
** _p = Percent
** _wp = Width/Precision
** _i = Info
** _r = Recursion
*/

/*
**	ft_printf.c
*/

int				ft_printf(char *str, ...);

/*
**	read_arg.c
*/

int				check_percent(char **str, va_list *argu);

/*
**	add_w_p.c
**		extra credit: * - wildcard
*/

char			add_width_precision(t_info *ret, char **str,
						char width_precision, va_list *argu);
/*
**	ft_putchar.c
*/

int				ft_putnumchar(int num, char c);
int				ft_putchar(char c);
int				ft_putchar_p(char c, t_info *info);

/*
**	ft_putstr.c
*/

int				ft_strlen(char *str);
int				ft_putstr_i(char *str, int to_free, t_info *info);
int				ft_putstr(char *str);
int				ft_putstr_p(char *str, t_info *info);

/*
**	ft_putpoi.c
*/

int				ft_putpoi_p(unsigned long nbr, t_info *info);

/*
**	ft_putnbr.c
*/

int				ft_putnbr_p(va_list *argu, t_info *info);

/*
**	ft_putoct.c
*/

int				ft_putoct_p(va_list *argu, t_info *info);

/*
**	ft_putuint.c
*/

int				ft_putuint_p(va_list *argu, t_info *info);

/*
**	ft_puthex.c
*/

int				ft_puthex_p(va_list *argu, t_info *info);

/*
**	ft_putflo.c
*/

int				ft_putflo_p(va_list *argu, t_info *info);

/*
**	ft_putbin.c
**		extra credit: %b - binary, behaves like %o
*/

int				ft_putbin_p(va_list *argu, t_info *info);

/*
**	ft_putiso.c
**	ft_putiso_set.c
**		extra credit: %k - prints ISO dates in YYYY-MM-DD or YYYY.MM.DD format
*/

int				ft_putiso_p(char *str, t_info *info);
int				iso_set(char *ret, int itr, char input);

#endif
