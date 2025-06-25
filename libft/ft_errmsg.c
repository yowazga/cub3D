/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errmsg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 01:05:01 by zmoumen           #+#    #+#             */
/*   Updated: 2023/07/31 01:06:11 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_errmsg(char *msg, int status)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(status);
}
