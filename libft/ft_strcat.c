/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:48:41 by grohr             #+#    #+#             */
/*   Updated: 2025/06/26 14:49:10 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Concatène src à la fin de dst
char	*ft_strcat(char *dst, const char *src)
{
    char	*ptr;
	
	ptr = dst;
    while (*ptr)
    	ptr++;
    while (*src)
    	*ptr++ = *src++;
    *ptr = '\0';
    return (dst);
}
