/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:49:09 by jbaringo          #+#    #+#             */
/*   Updated: 2021/10/19 18:42:11 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

float	max_nb(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

float	normalize(float n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*special_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s3 = malloc((ft_strlen(s1) + ft_strlen(s2)) + 2);
	if (!s3)
		return (NULL);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	s3[i] = '\n';
	i++;
	j = -1;
	while (s2[++j])
	{
		s3[i] = s2[j];
		i++;
	}
	s3[i] = '\0';
	return (s3);
}

int	ft_atoi(char *str)
{
	long int	res;
	int			n;
	size_t		i;

	i = 0;
	n = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		n = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
		if ((res * n) > 2147483647)
			return (-1);
		else if ((res * n) < -2147483648)
			return (0);
	}
	return (res * n);
}
