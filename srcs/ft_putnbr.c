/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtai <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:07:18 by dtai              #+#    #+#             */
/*   Updated: 2020/01/27 23:11:54 by dtai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	find_size_nbr(long long nbr)
{
	int	ret;

	if (!nbr)
		return (1);
	ret = 0;
	while (nbr)
	{
		nbr /= 10;
		ret++;
	}
	return (ret);
}

static int	input_nbr(long long nbr, char *print_out, int size, t_info *info)
{
	int	ret;

	ret = nbr < 0 || info->f_plus ? 1 : 0;
	if (size == 1 && !info->s_precision && !nbr)
	{
		print_out[0] = info->f_plus ? '+' : ' ';
		return (info->f_plus ? 0 : -1);
	}
	while (--size >= 0)
	{
		print_out[size] = ((nbr % 10) * (nbr % 10 < 0 ? -1 : 1) + '0');
		nbr /= 10;
	}
	return (ret);
}

static int	ft_putnbr_i(long long nbr, t_info *info)
{
	int		ret;
	char	*print_out;
	int		prefix;
	int		pre_spaces;

	ret = find_size_nbr(nbr);
	ret = info->s_precision > ret ? info->s_precision : ret;
	print_out = (char *)malloc(sizeof(char) * (ret + 1));
	print_out[ret] = '\0';
	ret += (prefix = input_nbr(nbr, print_out, ret, info));
	pre_spaces = !info->f_dash && (!info->f_zero || info->s_precision != -1) ?
			ft_putnumchar(info->s_width - ret, ' ') : 0;
	ret += pre_spaces;
	write(1, " ", info->f_space && !info->f_plus && nbr >= 0 &&
			!pre_spaces && ++ret ? 1 : 0);
	write(1, (nbr < 0 ? "-" : "+"), prefix == 1 ? 1 : 0);
	ret += !info->f_dash && info->f_zero && info->s_precision == -1 ?
			ft_putnumchar(info->s_width - ret, '0') : 0;
	prefix != -1 ? ft_putstr(print_out) : 0;
	free(print_out);
	ret += info->f_dash ? ft_putnumchar(info->s_width - ret, ' ') : 0;
	free(info);
	return (ret);
}

int			ft_putnbr_p(va_list *argu, t_info *info)
{
	if (info->t_length == 'l')
		return (ft_putnbr_i((long)va_arg(*argu, long long int), info));
	if (info->t_length == 'l' * 2)
		return (ft_putnbr_i((long long)va_arg(*argu, long long int), info));
	if (info->t_length == 'h')
		return (ft_putnbr_i((short)va_arg(*argu, int), info));
	if (info->t_length == 'h' * 2)
		return (ft_putnbr_i((char)va_arg(*argu, int), info));
	return (ft_putnbr_i((int)va_arg(*argu, int), info));
}
