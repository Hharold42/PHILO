/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharold <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 16:33:46 by hharold           #+#    #+#             */
/*   Updated: 2022/02/19 18:08:14 by hharold          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_philo
{
	pthread_mutex_t	eating;
	pthread_t		thd_philo;
	pthread_t		myhem;
	int				pid;
	int				nta;
	int				lf;
	int				rf;
	int				is_eating;
	long long		lta;
	struct s_din	*din_table;
}				t_philo;

typedef struct s_din
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	t_philo			**philos;
	long long		st;
	int				death;
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				ntpme;
}	t_din;

t_philo			**init_philos(t_din *din_table);
long long		time_in_ms(void);
int				ft_is_num(char *str);
int				ft_atoi(const char *str);
pthread_mutex_t	*init_forks(t_din *din_table);
void			*start_actions(void *data);
void			print_stat(t_din *din_table, int pid, char *str);

#endif