/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtai <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:41:32 by dtai              #+#    #+#             */
/*   Updated: 2020/01/27 23:09:51 by dtai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnumchar(int num, char c)
{
	int ret;

	if (num <= 0)
		return (0);
	ret = num;
	while (num--)
		write(1, &c, 1);
	return (ret);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putchar_p(char c, t_info *info)
{
	int	ret;

	ret = (info->s_width > 0 ? info->s_width : 1) - 1;
	ret += info->f_dash ? ft_putchar(c) : 0;
	while (--info->s_width > 0)
		write(1, " ", 1);
	ret += !info->f_dash ? ft_putchar(c) : 0;
	free(info);
	return (ret);
}
