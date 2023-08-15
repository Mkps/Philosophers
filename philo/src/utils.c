/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:32:53 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/15 12:35:33 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_digit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if ((arg[i] < '0' || arg[i] > '9') && (arg[i] != '+' || arg[i] != '-'))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

long	ft_atol(const char *str)
{
	long	atol;
	long	sign;
	int		i;

	atol = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		atol = (atol * 10) + str[i] - 48;
		if (atol * sign > (INT_MAX) || atol * sign < INT_MIN)
			return (-2);
		i++;
	}
	if (sign == -1)
		return (-1);
	return (atol);
}

int	is_valid_value(char *arg)
{
	long	value;

	value = ft_atol(arg);
	if (value == -1)
	{
		printf("Error: arguments can only be positive.\n");
		return (2);
	}
	else if (value == -2)
	{
		printf("Error: arguments are limited to INT_MAX.\n");
		return (1);
	}
	return (0);
}

int	check_input(char *arg)
{
	if (arg[0] == 0)
	{
		printf("Error: empty argument provided.\n");
		return (3);
	}
	if (is_digit(arg) != 0)
	{
		printf("Error: arguments may only be digits.\n");
		return (1);
	}
	if (is_valid_value(arg) != 0)
		return (1);
	return (0);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}
