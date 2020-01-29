/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_w_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtai <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:10:10 by dtai              #+#    #+#             */
/*   Updated: 2020/01/27 23:09:37 by dtai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_atoi_wp(char **str)
{
	int ret;

	ret = 0;
	while (**str >= '0' && **str <= '9')
	{
		ret = ret * 10 + (**str - '0');
		(*str)++;
	}
	(*str)--;
	return (ret);
}

static int		star_wp(t_info *info, char width_precision, va_list *argu)
{
	int	ret;

	ret = va_arg(*argu, int);
	if (ret < 0)
	{
		if (width_precision == 'p')
			return (-1);
		ret *= -1;
		info->f_dash = 1;
	}
	return (ret);
}

char			add_width_precision(t_info *info, char **str,
		char width_precision, va_list *argu)
{
	int i;

	i = **str == '*' ? star_wp(info, width_precision, argu) : ft_atoi_wp(str);
	width_precision == 'w' ? info->s_width = i : 0;
	width_precision == 'p' ? info->s_precision = i : 0;
	if (width_precision == 'p' && info->s_precision == -1)
		return ('w');
	return (width_precision);
}
