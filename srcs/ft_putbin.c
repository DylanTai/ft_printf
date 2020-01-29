/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtai <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 22:51:40 by dtai              #+#    #+#             */
/*   Updated: 2020/01/27 23:09:47 by dtai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	find_size_bin(unsigned long long nbr)
{
	int	ret;

	if (!nbr)
		return (1);
	ret = 0;
	while (nbr)
	{
		nbr /= 2;
		ret++;
	}
	return (ret);
}

static void	input_bin(unsigned long long nbr, char *print_out, int size)
{
	while (--size >= 0)
	{
		print_out[size] = nbr % 2 + '0';
		nbr /= 2;
	}
}

static int	ft_putbin_i(unsigned long long nbr, t_info *info)
{
	int		ret;
	char	*print_out;

	ret = find_size_bin(nbr);
	ret = info->s_precision > ret ? info->s_precision : ret;
	print_out = (char *)malloc(sizeof(char) * (ret + 1));
	print_out[ret] = '\0';
	input_bin(nbr, print_out, ret);
	ret += (print_out[0] != '0' || !info->s_precision ? info->f_hash : 0)
			- (info->s_precision || nbr ? 0 : 1);
	ret += !info->f_dash && (!info->f_zero || info->s_precision != -1) ?
			ft_putnumchar(info->s_width - ret, ' ') : 0;
	print_out[0] != '0' || !info->s_precision ? write(1, "0", info->f_hash) : 0;
	ret += !info->f_dash && info->f_zero && info->s_precision == -1 ?
			ft_putnumchar(info->s_width - ret, '0') : 0;
	info->s_precision || nbr ? ft_putstr(print_out) : 0;
	free(print_out);
	ret += info->f_dash ? ft_putnumchar(info->s_width - ret, ' ') : 0;
	free(info);
	return (ret);
}

int			ft_putbin_p(va_list *argu, t_info *info)
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
	return (ft_putbin_i(nbr, info));
}
