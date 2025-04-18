/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:03:06 by lihrig            #+#    #+#             */
/*   Updated: 2025/04/18 12:49:33 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void print_instructions()
{
	printf("The Programm takes the arguments in the following Order\n");
	printf("programm [Number of Philosophers] [time to die] [time to eat] [time to sleep] [meals he has to eat]\n");
}

int main (int argc, char* argv[])
{
	if(argc < 5 || argc > 6)
	{

	}
	print_instructions;
	
}
