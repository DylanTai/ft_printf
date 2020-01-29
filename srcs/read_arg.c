/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtai <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:27:01 by dtai              #+#    #+#             */
/*   Updated: 2020/01/27 23:13:23 by dtai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		is_param(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'o'
			|| c == 'u' || c == 'x' || c == 'X' || c == 'f' || c == '%'
			|| c == 'b' || c == 'k')
		return (1);
	if (c == '-' || c == '0' || c == ' ' || c == '+'
			|| c == '#' || c == '.' || (c >= '0' && c <= '9')
			|| c == '*' || c == 'l' || c == 'h' || c == 'L')
		return (0);
	return (-1);
}

static t_info	*init_info(void)
{
	t_info	*ret;

	ret = (t_info *)malloc(sizeof(t_info));
	ret->f_dash = 0;
	ret->f_zero = 0;
	ret->f_space = 0;
	ret->f_plus = 0;
	ret->f_hash = 0;
	ret->s_width = -1;
	ret->s_precision = -1;
	ret->t_length = -1;
	ret->param = 0;
	return (ret);
}

static t_info	*create_info(char **str, va_list *argu)
{
	t_info	*ret;
	char	width_precision;

	ret = init_info();
	width_precision = 'w';
	while (is_param(**str) == 0)
	{
		ret->f_dash = (**str == '-' ? 1 : ret->f_dash);
		ret->f_zero = (**str == '0' ? 1 : ret->f_zero);
		ret->f_space = (**str == ' ' ? 1 : ret->f_space);
		ret->f_plus = (**str == '+' ? 1 : ret->f_plus);
		ret->f_hash = (**str == '#' ? 1 : ret->f_hash);
		width_precision = (**str == '.' ? 'p' : width_precision);
		if ((**str >= '0' && **str <= '9') || **str == '*')
			width_precision = add_width_precision(ret, str, width_precision,
					argu);
		if (**str == 'l' || **str == 'L' || **str == 'h')
			ret->t_length = (ret->t_length == -1 ? **str : ret->t_length * 2);
		(*str)++;
	}
	width_precision == 'p' && ret->s_precision == -1 ? ret->s_precision = 0 : 0;
	ret->param = **str;
	return (ret);
}

static int		check_param(t_info *info, va_list *argu)
{
	if (info->param == '%')
		return (ft_putchar_p('%', info));
	if (info->param == 'c')
		return (ft_putchar_p((char)va_arg(*argu, int), info));
	if (info->param == 's')
		return (ft_putstr_p(va_arg(*argu, char *), info));
	if (info->param == 'p')
		return (ft_putpoi_p(va_arg(*argu, unsigned long int), info));
	if (info->param == 'd' || info->param == 'i')
		return (ft_putnbr_p(argu, info));
	if (info->param == 'o')
		return (ft_putoct_p(argu, info));
	if (info->param == 'u')
		return (ft_putuint_p(argu, info));
	if (info->param == 'x' || info->param == 'X')
		return (ft_puthex_p(argu, info));
	if (info->param == 'f')
		return (ft_putflo_p(argu, info));
	if (info->param == 'b')
		return (ft_putbin_p(argu, info));
	if (info->param == 'k')
		return (ft_putiso_p(va_arg(*argu, char *), info));
	free(info);
	return (0);
}

int				check_percent(char **str, va_list *argu)
{
	t_info	*info;

	++(*str);
	info = create_info(str, argu);
	is_param(**str) == 1 ? ++(*str) : 0;
	return (check_param(info, argu));
}
