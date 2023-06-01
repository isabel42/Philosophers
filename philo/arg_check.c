/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:46:28 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/01 11:54:31 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_digit(int argc, char **argv)
{
	int	i;
	int	j;

	j = 1;
	while (j < argc)
	{
		i = 0;
		while (argv[j][i] != '\0')
		{
			if (argv[j][i] < '0' || argv[j][i] > '9')
			{
				printf("Argument %d cotains other ", j);
				printf("than digit or negative numbers\n");
				return (0);
			}
			i++;
		}
		j++;
	}
	return (1);
}

int	ft_check_int(int argc, char **argv)
{
	int		i;
	char	*s;
	int		j;

	j = 1;
	s = "2147483647";
	while (j < argc)
	{
		i = 0;
		while (argv[j][i] != '\0' && ft_strlen(argv[j]) >= 10)
		{
			if (argv[j][i] > s[i] || ft_strlen(argv[j]) > 10)
			{
				printf("Argument %d does not fit into an int\n", j);
				return (0);
			}
			i++;
		}
		j++;
	}
	return (1);
}

int	ft_check_arg(int argc, char **argv)
{
	if (argc > 6 || argc < 5)
	{
		printf("Incorrect number of arguments!!\n");
		return (0);
	}
	if (ft_check_digit(argc, argv) == 0)
		return (0);
	if (ft_check_int(argc, argv) == 0)
		return (0);
	return (1);
}
