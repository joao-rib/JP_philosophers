/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/15 10:32:36 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>
# include <signal.h>
# include <time.h>
# include <pthread.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
//# include "../libft/libft.h"

typedef struct s_table	t_table;

typedef enum e_socas
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
}	t_socas;

typedef enum e_thraction
{
	INITIATE,
	DESTROY,
	LOCK,
	UNLOCK,
	CREATE,
	JOIN,
	DETACH,
}	t_thraction;

typedef struct s_fork
{
	long int		index;
	pthread_mutex_t	fork_mutex;
	struct s_fork	*left;
	struct s_fork	*right;
}			t_fork;

typedef struct s_philo
{
	long int		index;
	long int		meals;
	long int		satt_time;
	bool			satt;
	pthread_t		ph_thread;
	pthread_mutex_t	ph_mutex;
	struct s_fork	*l_hand;
	struct s_fork	*r_hand;
	struct s_philo	*left;
	struct s_philo	*right;
	struct s_table	*tab;
}			t_philo;

typedef struct s_table
{
	struct s_philo	*phil_list;
	struct s_fork	*fork_list;
	long int		num_philo;
	long int		time_die;
	long int		time_eat;
	long int		time_sleep;
	long int		num_meals;
	long int		starting_time;
	long int		running_threads;
	bool			ready_to_start;
	bool			ready_to_end;
	pthread_t		tab_thread;
	pthread_mutex_t	tab_mutex;
	pthread_mutex_t	print_mutex;
}			t_table;

//Utils - Listing
t_philo	*phil_last(t_philo *lst);
void	phil_addback(t_philo **p_lst, t_philo *new);
t_philo	*find_phil(t_philo *lst, long index);
t_fork	*fork_last(t_fork *lst);
void	fork_addback(t_fork **p_lst, t_fork *new);
//Utils - Validating
bool	validate_args(char **av, int ac);
bool	validate_numbers(t_table *tab);
//Utils - Clearing
void	clear_table(t_table *tab);

//Utils (mtx) - Setting
void	set_mtx_bool(pthread_mutex_t *mutex, bool *dest, bool value);
void	set_mtx_long(pthread_mutex_t *mutex, long *dest, long value);
void	add_mtx_long(pthread_mutex_t *mutex, long *dest, long value);
void	subtr_mtx_long(pthread_mutex_t *mutex, long *dest, long value);
//Utils (mtx) - Getting
bool	get_mtx_bool(pthread_mutex_t *mutex, bool *dest);
long	get_mtx_long(pthread_mutex_t *mutex, long *dest);
long	get_time(void);
//Utils (mtx) - Checking
bool	check_mtx_equalto(pthread_mutex_t *mutex, long *val1, long *val2);
//Utils (mtx) - Threading
void	thread_mtx(pthread_mutex_t *mutex, t_thraction action);
void	thread(pthread_t *thread, void *(*handle_action)(void *),
			void *arg, t_thraction action);

//Utils (other)
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
bool	ft_isdigit(int c);
bool	ft_isdelim(int c);
long	ft_atol(const char *str);
int		ft_error_msg(char *str);

//Meal - Eating
void	start_eating(t_table *tab);
void	eat_alone(t_table *tab);
//Meal - Handling
void	*handle_table(void *arg);
void	*handle_spaghetti(void *arg);
void	*handle_onephil(void *arg);
//Meal - Phil Actions
void	report_status(t_philo *phil, t_socas status);
void	phil_eat(t_philo *phil);
void	phil_sleep(t_philo *phil);
void	phil_think(t_philo *phil);
bool	phil_die(t_philo *phil);

#endif

/*

#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h> // for sleep()

// Mutex type definition for simplicity
typedef pthread_mutex_t t_mtx;

// Shared long
long shared_long = 1;

// Mutex to protect shared_long
t_mtx long_mutex;

// Function to increment a long variable safely
void add_long(t_mtx *mutex, long *dest, long value)
{
    pthread_mutex_lock(mutex);
    *dest += value;
    pthread_mutex_unlock(mutex);
}

// Thread function to perform a task and then increment
void* thread_task(void* arg)
{
    int id = *(int*)arg;

    // Simulate some work
    printf("Thread %d: working...\n", id);
    sleep(1); // Simulate a delay

    // Safely increment the variable
    printf("Thread %d: incrementing shared_long=%ld\n", id, shared_long);
    add_long(&long_mutex, &shared_long, 1);
    //shared_long++;

    return NULL;
}

int main()
{
    // Initialize the mutex
    pthread_mutex_init(&long_mutex, NULL);

    // Create multiple threads
    pthread_t threads[3];
    int thread_ids[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, thread_task, &thread_ids[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    // Check the value of shared_long
    printf("Main thread: final value of shared_long = %ld\n", shared_long);

    // Destroy the mutex
    pthread_mutex_destroy(&long_mutex);

    return 0;
}
*/
