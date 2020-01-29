/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtai <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:11:58 by dtai              #+#    #+#             */
/*   Updated: 2020/01/27 23:13:04 by dtai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen(char *str)
{
	int ret;

	ret = 0;
	while (str[ret])
		ret++;
	return (ret);
}

int	ft_putstr_i(char *str, int to_free, t_info *info)
{
	int str_size;
	int space_itr;
	int str_itr;

	str_size = ft_strlen(str);
	space_itr = info->s_width;
	while (!info->f_dash && info->s_width > str_size && space_itr-- > str_size)
		write(1, " ", 1);
	str_itr = 0;
	while (str[str_itr])
		write(1, str + str_itr++, 1);
	while (info->f_dash && info->s_width > str_size && space_itr-- > str_size)
		write(1, " ", 1);
	if (to_free)
		free(str);
	free(info);
	return (info->s_width > str_size ? info->s_width : str_size);
}

int	ft_putstr(char *str)
{
	int ret;

	ret = 0;
	while (str[ret])
		write(1, str + ret++, 1);
	return (ret);
}

int	ft_putstr_p(char *str, t_info *info)
{
	char	*new_str;
	int		str_size;

	str = !str ? "(null)" : str;
	str_size = ft_strlen(str);
	if (str_size < info->s_precision || info->s_precision == -1)
		return (ft_putstr_i(str, 0, info));
	new_str = (char *)malloc(sizeof(char) * (info->s_precision + 1));
	new_str[info->s_precision] = '\0';
	while (--info->s_precision >= 0)
		new_str[info->s_precision] = str[info->s_precision];
	return (ft_putstr_i(new_str, 1, info));
}
