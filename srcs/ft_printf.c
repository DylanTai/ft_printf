/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtai <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:38:04 by dtai              #+#    #+#             */
/*   Updated: 2020/01/27 23:09:41 by dtai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(char *str, ...)
{
	int		ret;
	va_list	argu;

	ret = 0;
	va_start(argu, str);
	while (*str)
	{
		if (*str != '%')
		{
			write(1, str++, 1);
			ret++;
		}
		else
			ret += check_percent(&str, &argu);
	}
	va_end(argu);
	return (ret);
}
