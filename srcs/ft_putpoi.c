/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtai <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:11:34 by dtai              #+#    #+#             */
/*   Updated: 2020/01/27 23:12:57 by dtai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			g_size;

static int	find_size_poi(unsigned long nbr)
{
	int ret;

	if (!nbr)
		return (3);
	ret = 2;
	while (nbr)
	{
		nbr /= 16;
		ret++;
	}
	return (ret);
}

static void	ft_putpoi_r(unsigned long nbr, t_info *info)
{
	char temp;

	temp = nbr % 16;
	if (temp > 9)
		temp += 'a' - ('0' + 10);
	temp += '0';
	if (nbr >= 16 || info->s_precision >= 0)
	{
		info->s_precision--;
		ft_putpoi_r(nbr / 16, info);
	}
	g_size++;
	ft_putchar(temp);
}

static int	ft_putpoi_zero(t_info *info)
{
	int	ret;
	int	size;

	if (!info->s_precision)
	{
		free(info);
		return (ft_putstr("0x"));
	}
	ret = 0;
	size = (info->s_precision > 1 ? info->s_precision : 1) + 2;
	while (!info->f_dash && info->s_width-- > size)
		ret += ft_putchar(' ');
	ret += ft_putstr("0x");
	ret += info->s_precision == -1 ? ft_putchar('0') : 0;
	while (info->s_precision-- >= 1)
		ret += ft_putchar('0');
	while (info->f_dash && info->s_width-- > size)
		ret += ft_putchar(' ');
	free(info);
	return (ret);
}

int			ft_putpoi_p(unsigned long nbr, t_info *info)
{
	int size;
	int itr;

	if (!nbr)
		return (ft_putpoi_zero(info));
	size = find_size_poi(nbr);
	itr = info->s_width;
	g_size = 0;
	while (!info->f_dash && info->s_width > size && itr-- > size)
		write(1, " ", ++g_size ? 1 : 0);
	g_size += ft_putstr("0x");
	info->s_precision -= 2;
	ft_putpoi_r(nbr, info);
	while (info->f_dash && info->s_width > size && itr-- > size)
		write(1, " ", ++g_size ? 1 : 0);
	free(info);
	return (g_size);
}
