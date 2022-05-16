/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <hverda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 11:20:52 by hverda            #+#    #+#             */
/*   Updated: 2021/07/29 11:47:56 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_nbr(long int nbr)
{
	int			j;
	long int	n;

	j = 1;
	n = nbr;
	while (n >= 10)
	{
		j++;
		n = n / 10;
	}
	return (j);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	int			j;

	i = 0;
	j = ft_nbr(n);
	str = malloc(sizeof(*str) * (j + 1));
	if (str == 0)
		return (0);
	while (i < j - 1)
		i++;
	str[i + 1] = '\0';
	while (i >= 0)
	{
		str[i] = n % 10 + '0';
		i--;
		n = n / 10;
	}
	free(str);
	return (str);
}

void	ft_write_address(int address_for_char)
{
	if (address_for_char != 0)
		write(1, &address_for_char, 1);
	else
		write(1, "\n", 1);
}

void	my_handler(int signum)
{
	static int	address_for_char;
	static int	bit;
	static int	i;

	if (bit == 0)
		bit = 128;
	if (signum == SIGUSR1)
	{
		address_for_char = address_for_char + bit;
		bit = bit / 2;
		i++;
	}
	if (signum == SIGUSR2)
	{
		bit = bit / 2;
		i++;
	}
	if (i == 8)
	{
		ft_write_address(address_for_char);
		bit = 128;
		address_for_char = 0;
		i = 0;
	}
}

int	main(void)
{
	char	*p;
	int		i;

	i = 0;
	p = ft_itoa((int)getpid());
	while (p[i] != '\0')
		i++;
	write (1, p, i);
	write (1, "\n", 1);
	signal(SIGUSR1, my_handler);
	signal(SIGUSR2, my_handler);
	while (1)
		pause();
	return (0);
}
