/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtai <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 23:49:01 by dtai              #+#    #+#             */
/*   Updated: 2020/01/27 23:13:16 by dtai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	find_size_uint(unsigned long long nbr)
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

static void	input_uint(unsigned long long nbr, char *print_out, int size)
{
	while (--size >= 0)
	{
		print_out[size] = nbr % 10 + '0';
		nbr /= 10;
	}
}

static int	ft_putuint_i(unsigned long long nbr, t_info *info)
{
	int		size;
	int		ret;
	char	*print_out;

	size = find_size_uint(nbr);
	ret = info->s_precision > size ? info->s_precision : size;
	print_out = (char *)malloc(sizeof(char) * (ret + 1));
	print_out[ret] = '\0';
	input_uint(nbr, print_out, ret);
	ret += info->f_hash - (info->s_precision || nbr ? 0 : 1);
	ret += !info->f_dash && (!info->f_zero || info->s_precision != -1) ?
			ft_putnumchar(info->s_width - ret, ' ') : 0;
	write(1, "0", info->f_hash);
	ret += !info->f_dash && info->f_zero && info->s_precision == -1 ?
			ft_putnumchar(info->s_width - ret, '0') : 0;
	info->s_precision || nbr ? ft_putstr(print_out) : 0;
	free(print_out);
	ret += info->f_dash ? ft_putnumchar(info->s_width - ret, ' ') : 0;
	free(info);
	return (ret);
}

int			ft_putuint_p(va_list *argu, t_info *info)
{
	unsigned long long	nbr;

	if (info->t_length == 'l')
		nbr = (unsigned long)va_arg(*argu, unsigned long long int);
	else if (info->t_length == 'l' * 2)
		nbr = (unsigned long long)va_arg(*argu, unsigned long long int);
	else if (info->t_length == 'h')
		nbr = (unsigned short)va_arg(*argu, unsigned int);
	else if (info->t_length == 'h' * 2)
		nbr = (unsigned char)va_arg(*argu, unsigned int);
	else
		nbr = (unsigned int)va_arg(*argu, unsigned int);
	return (ft_putuint_i(nbr, info));
}
