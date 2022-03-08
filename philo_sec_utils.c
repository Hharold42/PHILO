/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharold <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:04:42 by hharold           #+#    #+#             */
/*   Updated: 2022/02/19 17:26:07 by hharold          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**init_philos(t_din *din_table)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = (t_philo **)malloc(sizeof(t_philo *) * din_table->nop + 1);
	if (!philos)
		return (NULL);
	while (i < din_table->nop)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (NULL);
		if (pthread_mutex_init(&philos[i]->eating, 0) != 0)
			return (NULL);
		philos[i]->din_table = din_table;
		philos[i]->pid = i;
		philos[i]->is_eating = 0;
		philos[i]->nta = 0;
		philos[i]->lf = i;
		philos[i]->rf = (i + 1) % philos[i]->din_table->nop;
		i++;
	}
	return (philos);
}

pthread_mutex_t	*init_forks(t_din *din_table)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	if (din_table->nop == -2 || din_table->ttd == -2 || din_table->tte == -2
		|| din_table->tts == -2 || din_table->ntpme == -2)
	{
		write (2, "Error: Invalid Args\n", 21);
		return (NULL);
	}
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * din_table->nop);
	if (!forks)
		return (NULL);
	while (i < din_table->nop)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (NULL);
		i++;
	}
	return (forks);
}
