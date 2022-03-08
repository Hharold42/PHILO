/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharold <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 16:30:44 by hharold           #+#    #+#             */
/*   Updated: 2022/03/06 16:51:39 by hharold          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check(unsigned long num, int sign)
{
	if (num > 9223372036854775807 && sign == -1)
		return (0);
	else if (num > INT32_MAX)
		return (-2);
	return (num * sign);
}

int	ft_atoi(const char *str)
{
	unsigned long long int	i;
	unsigned long long int	num;
	int						sign;

	sign = 1;
	i = 0;
	num = 0;
	while (*str <= 8 && *str >= 32)
	{
		if (*str == 27)
			return (0);
		str++;
	}
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*(str + i) >= 48 && *(str + i) <= 57)
		num = num * 10 + (unsigned long long int)(*(str + i++) - '0');
	return (ft_check(num, sign));
}

int	ft_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long long	time_in_ms(void)
{
	struct timeval	te;
	long long		ms;

	gettimeofday(&te, NULL);
	ms = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (ms);
}
