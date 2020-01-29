/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putiso.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtai <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:11:58 by dtai              #+#    #+#             */
/*   Updated: 2020/01/27 23:52:30 by dtai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*concat_date(char *yr, char *month, char *day, int bc)
{
	char	*ret;
	int		temp_itr;
	int		itr;

	if (!day)
	{
		free(yr);
		return (NULL);
	}
	ret = (char *)malloc(sizeof(char) * (ft_strlen(yr) + ft_strlen(month) +
			(day[0] == '0' ? 1 : 2) + (bc ? 3 : 0 + 3) + 1));
	itr = 0;
	temp_itr = 0;
	while (temp_itr < ft_strlen(month))
		ret[itr++] = month[temp_itr++];
	!(temp_itr *= 0) ? ret[itr++] = ' ' : 0;
	ret[itr++] = day[0] != '0' ? day[0] : day[1];
	day[0] != '0' ? ret[itr++] = day[1] : 0;
	itr = iso_set(ret, itr, ',');
	while (temp_itr < ft_strlen(yr))
		ret[itr++] = yr[temp_itr++];
	itr = bc ? iso_set(ret, itr, 'b') : itr;
	ret[itr] = '\0';
	free(day);
	return (ret);
}

static char	*get_day(char *yr, char *str, int day_itr, int month_itr)
{
	char	*ret;

	if (str[day_itr] == '3' && str[day_itr + 1] > '1')
		return (NULL);
	if (str[day_itr] == '3' && str[day_itr + 1] == '1' &&
			((str[month_itr] == '0' && (str[month_itr + 1] == '2' ||
			str[month_itr + 1] == '4' || str[month_itr + 1] == '6' ||
			str[month_itr + 1] == '9')) || (str[month_itr] == '1' &&
			str[month_itr + 1] == '1')))
		return (NULL);
	if (str[day_itr] == '3' && str[day_itr + 1] == '0' &&
			str[month_itr] == '0' && str[month_itr + 1] == '2')
		return (NULL);
	if (str[day_itr] == '2' && str[day_itr + 1] == '9' && str[month_itr] == '0'
			&& str[month_itr + 1] == '2' && (((yr[ft_strlen(yr) - 2] - '0') * 10
			+ yr[ft_strlen(yr) - 1] - '0') % 4))
		return (NULL);
	ret = (char *)malloc(sizeof(char) * 3);
	ret[0] = str[day_itr];
	ret[1] = str[day_itr + 1];
	ret[2] = '\0';
	return (ret);
}

static char	*get_yr(char *str, int *start, int *end)
{
	char	*ret;
	int		size;
	int		itr;

	while (str[*end] && str[*end] != '-' && str[*end] != '.' &&
			str[*end] >= '0' && str[*end] <= '9')
		(*end)++;
	if (str[*end] != '-' && str[*end] != '.')
		return (NULL);
	size = *end - *start;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	ret[size] = '\0';
	itr = 0;
	while (itr < size)
		ret[itr++] = str[(*start)++];
	return (ret);
}

static char	*get_month(char *str)
{
	if (str[0] == '0' && str[1] == '1')
		return ("January");
	if (str[0] == '0' && str[1] == '2')
		return ("February");
	if (str[0] == '0' && str[1] == '3')
		return ("March");
	if (str[0] == '0' && str[1] == '4')
		return ("April");
	if (str[0] == '0' && str[1] == '5')
		return ("May");
	if (str[0] == '0' && str[1] == '6')
		return ("June");
	if (str[0] == '0' && str[1] == '7')
		return ("July");
	if (str[0] == '0' && str[1] == '8')
		return ("August");
	if (str[0] == '0' && str[1] == '9')
		return ("September");
	if (str[0] == '1' && str[1] == '0')
		return ("October");
	if (str[0] == '1' && str[1] == '1')
		return ("November");
	if (str[0] == '1' && str[1] == '2')
		return ("December");
	return (NULL);
}

int			ft_putiso_p(char *str, t_info *info)
{
	int		start;
	int		end;
	int		bc;
	char	*yr;
	char	*month;

	if (!str)
		return (ft_putstr_p(str, info));
	start = 0;
	bc = str[0] == '-' && ++start ? 1 : 0;
	end = start;
	yr = get_yr(str, &start, &end);
	if (!yr)
		return (ft_putstr_p(NULL, info));
	month = get_month(str + ++end);
	start = end + 2;
	if (!month || (str[start] != '-' && str[start] != '.') ||
			!(str[start + 1] >= '0' && str[start + 1] <= '3' && str[start + 2]
			>= '0' && str[start + 2] <= '9') || str[start + 3] != '\0')
		return (ft_putstr_p(concat_date(yr, month, NULL, bc), info));
	if (!(month = concat_date(yr, month, get_day(yr, str, ++start, end), bc)))
		return (ft_putstr_p(NULL, info));
	free(yr);
	(start = ft_putstr_p(month, info)) ? free(month) : 0;
	return (start);
}
