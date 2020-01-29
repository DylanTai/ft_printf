/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putflo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtai <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:07:18 by dtai              #+#    #+#             */
/*   Updated: 2020/01/27 23:11:42 by dtai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	find_size_flo(long double flo, int p)
{
	int	decimals;
	int ret;

	decimals = p == -1 ? 6 : p;
	flo *= flo < 0 ? -1 : 1;
	ret = 1;
	while (flo >= 1)
	{
		flo /= 10;
		ret++;
	}
	ret += decimals ? 1 + decimals : 0;
	return (ret);
}

static void	round_flo(int check, char *print_out, int size)
{
	if (check < 5)
		return ;
	while (print_out[--size] == '9' || print_out[size] == '.')
	{
		if (print_out[size] == '.')
			continue ;
		print_out[size] = '0';
	}
	print_out[size]++;
}

static int	input_flo(long double flo, char *print_out, int size, t_info *info)
{
	int	ret;
	int	decimals;
	int	itr;

	ret = flo < 0 || info->f_plus ? 1 : 0;
	print_out[0] = '0';
	decimals = info->s_precision == -1 ? 6 : info->s_precision;
	itr = 1;
	while (flo < 0 || flo >= 10)
		flo /= flo < 0 ? -1 : 10;
	!((int)flo) ? flo *= 10 : 0;
	while (itr < size - (decimals ? decimals + 1 : 0))
	{
		print_out[itr++] = (int)flo + '0';
		flo = (flo - (int)flo) * 10;
	}
	decimals ? print_out[itr++] = '.' : 0;
	while (itr < size)
	{
		print_out[itr++] = (int)flo + '0';
		flo = (flo - (int)flo) * 10;
	}
	round_flo((int)flo, print_out, size);
	return (ret);
}

static int	ft_putflo_i(long double flo, t_info *info)
{
	int		ret;
	char	*print_out;
	int		prefix;
	int		pre_spaces;
	int		start;

	ret = find_size_flo(flo, info->s_precision);
	print_out = (char *)malloc(sizeof(char) * (ret + 1));
	print_out[ret] = '\0';
	ret += (prefix = input_flo(flo, print_out, ret, info));
	ret -= (start = print_out[0] == '0' &&
			print_out[1] != '.' && print_out[1] != '\0' ? 1 : 0);
	ret += (pre_spaces = !info->f_dash && (!info->f_zero || info->s_precision
			!= -1) ? ft_putnumchar(info->s_width - ret, ' ') : 0);
	write(1, " ", info->f_space && !info->f_plus && flo >= 0 &&
			!pre_spaces && ++ret ? 1 : 0);
	write(1, (flo < 0 ? "-" : "+"), prefix == 1 ? 1 : 0);
	ret += !info->f_dash && info->f_zero && info->s_precision == -1 ?
			ft_putnumchar(info->s_width - ret, '0') : 0;
	prefix != -1 ? ft_putstr(print_out + start) : 0;
	ret += info->f_hash && !info->s_precision ? ft_putchar('.') : 0;
	free(print_out);
	ret += info->f_dash ? ft_putnumchar(info->s_width - ret, ' ') : 0;
	free(info);
	return (ret);
}

int			ft_putflo_p(va_list *argu, t_info *info)
{
	if (info->t_length == 'L')
		return (ft_putflo_i((long double)va_arg(*argu, long double), info));
	return (ft_putflo_i((double)va_arg(*argu, double), info));
}
