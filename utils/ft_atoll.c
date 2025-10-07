/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoshahi < enoshahi@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:45:12 by enoshahi          #+#    #+#             */
/*   Updated: 2025/10/07 19:12:10 by enoshahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoll(const char *str)
{
	long long	res;
	int			sign;
	int			last_digit;
	long long	llmax_wo_last_digit;

	res = 0;
	sign = 1;
	last_digit = __LONG_LONG_MAX__ % 10;
	llmax_wo_last_digit = __LONG_LONG_MAX__ / 10;
	while (*str != '\0')
	{
		if ((*str == '-' || *str == '+') && (*(str++) == '-'))
			sign = -1;
		while (*str >= '0' && *str <= '9')
		{
			if ((res > llmax_wo_last_digit) || (res == llmax_wo_last_digit
					&& ((*str - '0') > last_digit + (sign == -1)
						|| *(str + 1) != '\0')))
				return (-1 * (sign == 1));
			res = res * 10 + (*(str++) - '0');
		}
		return (res * sign);
	}
	return (0);
}
