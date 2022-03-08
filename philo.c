/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharold <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:31:59 by hharold           #+#    #+#             */
/*   Updated: 2022/02/28 17:18:01 by hharold          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(int argsize, char **args)
{
	int	i;

	i = 1;
	if (argsize - 1 < 4 || argsize - 1 > 6)
		return (-1);
	while (i < argsize)
	{
		if (args[i][0] == '-' || ft_is_num(args[i]) != 1)
			return (-1);
		i++;
	}
	return (1);
}

t_din	*fill_table(int argsize, char **args)
{
	t_din	*din_table;
	int		counter;

	counter = 1;
	din_table = (t_din *)malloc(sizeof(t_din) * 1);
	if (!din_table)
		return (NULL);
	din_table->nop = ft_atoi(args[counter++]);
	din_table->ttd = ft_atoi(args[counter++]);
	din_table->tte = ft_atoi(args[counter++]);
	din_table->tts = ft_atoi(args[counter++]);
	din_table->ntpme = -1;
	din_table->death = 1;
	if (argsize -1 == 5)
		din_table->ntpme = ft_atoi(args[counter]);
	din_table->forks = init_forks(din_table);
	if (!din_table->forks)
		return (NULL);
	din_table->philos = init_philos(din_table);
	if (!din_table->philos || din_table->nop == 0)
		return (NULL);
	if (pthread_mutex_init(&din_table->write, 0) != 0)
		return (NULL);
	return (din_table);
}

void	*mr_mayhem(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->din_table->death)
	{
		if (!philo->is_eating
			&& time_in_ms() - philo->lta >= philo->din_table->ttd)
		{
			pthread_mutex_lock(&philo->eating);
			print_stat(philo->din_table, philo->pid, "died\n");
			philo->din_table->death = 0;
			pthread_mutex_unlock(&philo->eating);
		}
		if (philo->din_table->philos[philo->din_table->nop - 1]->nta
			== philo->din_table->ntpme)
			philo->din_table->death = 0;
		usleep(100);
	}
	return (NULL);
}

int	start_threads(t_din *din_table)
{
	int	i;

	i = 0;
	din_table->st = time_in_ms();
	while (i < din_table->nop)
	{
		din_table->philos[i]->lta = time_in_ms();
		if (pthread_create(&din_table->philos[i]->thd_philo, NULL,
				&start_actions, (void *)din_table->philos[i]) != 0)
			return (-1);
		i++;
		usleep(100);
	}
	i = 0;
	while (i < din_table->nop)
	{
		if (pthread_create(&din_table->philos[i]->myhem, NULL, &mr_mayhem,
				(void *)din_table->philos[i]) != 0)
			return (-1);
		usleep(100);
		i++;
	}
	while (din_table->death)
		continue ;
	return (1);
}

int	main(int argc, char **argv)
{
	t_din	*din_table;
	int		p_counter;
	int		i;

	i = 1;
	p_counter = 0;
	din_table = NULL;
	if (check_arg(argc, argv) != 1)
	{
		write(2, "Error: Invalid Argument\n", 25);
		return (-1);
	}
	din_table = fill_table(argc, argv);
	if (din_table == NULL)
		return (-1);
	if (start_threads(din_table) != 1)
		return (-1);
	return (1);
}
