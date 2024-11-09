/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/06 20:08:09 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/philo.h"

/*void	write_status(t_philo *philo, t_philo_status status)
{
	long	elapsed;

	elapsed = gettime(MILLISECONDS) - philo->table->start_simulation;
	safe_mutex_handle(&philo->table->print_mtx, LOCK);
	if (THINKING == status && !get_bool(&philo->table->table_mtx,
			&philo->table->end_simulation))
		printf("%ld %d is thinking\n", elapsed, philo->philo_id);
	else if (EATING == status && !get_bool(&philo->table->table_mtx,
			&philo->table->end_simulation))
		printf("%ld %d is eating\n", elapsed, philo->philo_id);
	else if (SLEEPING == status && !get_bool(&philo->table->table_mtx,
			&philo->table->end_simulation))
		printf("%ld %d is sleeping\n", elapsed, philo->philo_id);
	else if (DIED == status && !get_bool(&philo->table->table_mtx,
			&philo->table->end_simulation))
		printf("%ld %d died\n", elapsed, philo->philo_id);
	else if ((TAKING_FIRST_FORK == status || TAKING_SECOND_FORK == status)
		&& !get_bool(&philo->table->table_mtx,
			&philo->table->end_simulation))
		printf("%ld %d has taken a fork\n", elapsed, philo->philo_id);
	safe_mutex_handle(&philo->table->print_mtx, UNLOCK);
}*/

/*void	pick_forks(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(philo, TAKING_FIRST_FORK);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(philo, TAKING_SECOND_FORK);
}

void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(philo, TAKING_FIRST_FORK);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(philo, TAKING_SECOND_FORK);
	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(MILLISECONDS));
	philo->meals_counter++;
	write_status(philo, EATING);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mtx, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	think(t_philo *philo)
{
	write_status(philo, THINKING);
	precise_usleep(TIME_TO_THINK, philo->table);
}

void	sleep_philo(t_philo *philo)
{
	write_status(philo, SLEEPING);
	precise_usleep(philo->table->time_to_sleep, philo->table);
}*/

void	report_status(t_philo *phil, t_socas status)
{
	long	timestamp;

	timestamp = get_time() - phil->tab->starting_time;
	pthread_mutex_lock(phil->tab->tab_mutex); //Different mutex for printing? //Considerar um handle_error
	if (status == FORK)
		printf("%ld %d has taken a fork\n", timestamp, phil->index);
	else if (status == THINK)
		printf("%ld %d is thinking\n", timestamp, phil->index);
	else if (status == SLEEP)
		printf("%ld %d is sleeping\n", timestamp, phil->index);
	else if (status == EAT)
		printf("%ld %d is eating\n", timestamp, phil->index);
	else if (status = DEAD)
		printf("%ld %d died\n", timestamp, phil->index);
	pthread_mutex_unlock(phil->tab->tab_mutex); //Different mutex for printing? //Considerar um handle_error
}

/*void	phil_eat(t_philo *phil)
{

}

void	phil_sleep(t_philo *phil)
{
	
}

void	phil_think(t_philo *phil)
{
	report_status(phil, THINK);
}*/