/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 11:16:30 by hverda            #+#    #+#             */
/*   Updated: 2021/07/29 11:20:38 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_atoi(const char *str)
{
	int			m;
	long int	r;
	int			z;

	m = 1;
	z = 0;
	r = 0;
	while (*str != 0 && ((*str >= 9 && *str <= 13) || *str == 32))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			m = -m;
		str++;
		z++;
	}
	if (z > 1)
		return (0);
	while (*str != 0 && (*str >= '0' && *str <= '9'))
	{
		r = (r * 10) + (*str - 48);
		str++;
	}
	return (r * m);
}

void	my_handler(int pid, char *str)
{
	int	i;
	int	num;

	i = 0;
	while (1)
	{
		num = 128;
		while (num != 0)
		{
			usleep(100);
			if ((str[i] & num) > 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			num = num / 2;
		}
		if (!str[i])
			break ;
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;

	if (argc < 3)
		write(1, "few arguments", 13);
	else if (argc > 3)
		write(1, "too much arguments", 18);
	else if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		str = argv[2];
		my_handler(pid, str);
	}
	return (0);
}
