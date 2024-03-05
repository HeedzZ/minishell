/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:10:58 by marvin            #+#    #+#             */
/*   Updated: 2024/02/06 18:10:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	echo(int argc, char *argv[])
{
	if (argc == 1)
		ft_printf("%s\n", argv[0]);
}

int main(int argc, char *argv[])
{
	echo(argv - 1, argv + 1);
	return 0;
}
