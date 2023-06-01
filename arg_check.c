/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:46:28 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/01 10:59:58 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_digit(int argc, char **argv)
{
	int	i;
	int	j;

	j = argc;
	while (j > 1)
	{
		i = 0;
		while (argv[j - 1][i] != '\0')
		{
			if (argv[j - 1][i] < '0' || argv[j - 1][i] > '9')
			{
				printf("Argument %d cotains other", j - 1);
				printf("than int or negative numbers\n");
				return (0);
			}
			i++;
		}
		j--;
	}
	return (1);
}

int	ft_check_int(int argc, char **argv)
{
	int		i;
	char	*s;
	int		j;

	j = argc;
	s = "2147483647";
	while (j > 1)
	{
		if (ft_strlen(argv[j - 1]) > 10)
		{
			printf("Argument %d does not fit into an int\n", j - 1);
			return (0);
		}
		i = 0;
		while (argv[j - 1][i] != '\0' && ft_strlen(argv[j - 1]) == 10)
		{
			if(argv[j - 1][i] > s[i])
			{
				printf("Argument %d does not fit into an int\n", j - 1);
				return (0);
			}
			i++;
		}
		j--;
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
