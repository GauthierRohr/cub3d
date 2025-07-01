/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:11:49 by grohr             #+#    #+#             */
/*   Updated: 2025/06/26 14:11:49 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Compare deux chaînes de caractères
int	ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
    	s1++;
    	s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
