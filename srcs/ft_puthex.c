/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtai <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 23:57:45 by dtai              #+#    #+#             */
/*   Updated: 2020/01/27 23:10:28 by dtai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	find_size_hex(unsigned long long nbr)
{
	int	ret;

	if (!nbr)
		return (1);
	ret = 0;
	while (nbr)
	{
		nbr /= 16;
		ret++;
	}
	return (ret);
}

static void	input_hex(unsigned long long nbr, char *print_out,
		int size, char input)
{
	char	alpha[16];
	int		itr;

	itr = -1;
	while (++itr < 10)
		alpha[itr] = itr + '0';
	itr--;
	while (++itr < 16)
		alpha[itr] = itr - 10 + (input == 'x' ? 'a' : 'A');
	while (--size >= 0)
	{
		print_out[size] = alpha[nbr % 16];
		nbr /= 16;
	}
}

static void	print_hash_hex(char param)
{
	write(1, "0", 1);
	write(1, param == 'x' ? "x" : "X", 1);
}

static int	ft_puthex_i(unsigned long long nbr, t_info *info)
{
	int		ret;
	char	*print_out;

	ret = find_size_hex(nbr);
	ret = info->s_precision > ret ? info->s_precision : ret;
	print_out = (char *)malloc(sizeof(char) * (ret + 1));
	print_out[ret] = '\0';
	input_hex(nbr, print_out, ret, info->param);
	ret += info->f_hash && info->s_precision && nbr ? 2 : 0 -
			!info->s_precision;
	ret += !info->f_dash && (!info->f_zero || info->s_precision != -1) ?
			ft_putnumchar(info->s_width - ret, ' ') : 0;
	info->f_hash && info->s_precision && nbr ? print_hash_hex(info->param) : 0;
	ret += !info->f_dash && info->f_zero && info->s_precision == -1 ?
			ft_putnumchar(info->s_width - ret, '0') : 0;
	info->s_precision ? ft_putstr(print_out) : 0;
	free(print_out);
	ret += info->f_dash ? ft_putnumchar(info->s_width - ret, ' ') : 0;
	free(info);
	return (ret);
}

int			ft_puthex_p(va_list *argu, t_info *info)
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
	return (ft_puthex_i(nbr, info));
}
