/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharold <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:26:14 by hharold           #+#    #+#             */
/*   Updated: 2022/02/19 18:33:37 by hharold          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_stat(t_din *din_table, int pid, char *str)
{
	pthread_mutex_lock(&din_table->write);
	printf("%lld %d %s", time_in_ms() - din_table->st, pid + 1, str);
	if (str[0] != 'd')
		pthread_mutex_unlock(&din_table->write);
}

void	eat_action(t_philo *philo)
{
	pthread_mutex_lock(&philo->din_table->forks[philo->lf]);
	print_stat(philo->din_table, philo->pid, "taken left fork\n");
	pthread_mutex_lock(&philo->din_table->forks[philo->rf]);
	print_stat(philo->din_table, philo->pid, "taken right fork\n");
	pthread_mutex_lock(&philo->eating);
	print_stat(philo->din_table, philo->pid, "is eating\n");
	philo->lta = time_in_ms();
	philo->is_eating = 1;
	usleep(philo->din_table->tte * 1000 - 16000);
	while (time_in_ms() - philo->lta < philo->din_table->tte)
		continue ;
	philo->nta++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->eating);
	pthread_mutex_unlock(&philo->din_table->forks[philo->lf]);
	pthread_mutex_unlock(&philo->din_table->forks[philo->rf]);
	return ;
}

void	sleep_action(t_philo *philo)
{
	long long	time;

	print_stat(philo->din_table, philo->pid, "is sleeping\n");
	time = time_in_ms();
	usleep(philo->din_table->tts * 1000 - 16000);
	while (time_in_ms() - time < philo->din_table->tts)
		continue ;
	return ;
}

void	think_action(t_philo *philo)
{
	print_stat(philo->din_table, philo->pid, "is thinking\n");
	return ;
}

void	*start_actions(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->din_table->death)
	{
		eat_action(philo);
		sleep_action(philo);
		think_action(philo);
		usleep(100);
	}
	return (NULL);
}
