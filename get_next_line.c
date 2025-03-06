/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terramint <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:28:43 by terramint         #+#    #+#             */
/*   Updated: 2025/03/07 00:57:12 by terramint        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	is_meatball_on(char *plate)
{
	int	i;
	char	meatball;

	meatball = '\n';
	i = 0;
	if (plate == NULL)
		return (0);
	while (*(plate) + i =! '\0')
	{
		if (*(plate) + i == meatball)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_str_add(char *str1, char *str2, int char_read)
{
	int	i;
	char	*temp;
	int	len_s1;

	len_s1 = 0;
	i = -1;
	if (str1 == NULL)
		return (str2);
	while (str1[++i] != '\0')
		len_s1++;
	temp = (char *)malloc(sizeof(char) * (len_s1 + char_read + 1));
	if (temp == NULL)
		return (NULL);
	temp[len_s1 + char_read] = '\0';
	i = -1;
	while (++i < char_read + len_s1)
	{
		if (i < len_s1)
			temp[i] = str1[i];
		else
			temp[i] = str2[i];
	}
	free(str1);
	free(str2);
	return (temp);
}


char	*fork_to_plate(int pan, char **plate, bool *eof)
{
	char 	*fork;
	int	is_there_spaghetti;

	fork = (char *)malloc(sizeof(char) * BUFFERSIZE + 1);
	fork[BUFFERSIZE] = '\0';
	is_there_spaghetti = read(pan, fork, BUFFERSIZE);
	
	if (is_there_spaghetti ==  -1 || is_there_spaghetti == 0)
	{
		if (is_there_spaghetti == -1)
		{
			free(fork);
			free(*plate);
			*plate = NULL;
			return (NULL);
		}
		else
		{
			*eof = true;
			free(fork);
			return (*plate);
		}
	}
	else
	{
		*plate = ft_str_add(*plate, fork, is_there_spaghetti);
	}
	return (*plate);
}
	
char	*eat_meatball_from(char **plate)
{
	int	i;
	int	s1_len;
	char	*temp;
	char	*re_string;


	temp = *plate;
	int	j;
	j = 0;
	while (*plate[j] != '\0')
		j++;
	i = is_meatball_on(*plate);
	re_string = (char *)malloc(sizeof(char) * (i + 1));
	re_string[i] = '\0';
	int	k = -1;
	while (++k < i)
		re_string[k] = *plate[k];
	if (i < j)
	{
		temp = (char *)malloc(sizeof(char) * (j - i + 1));
		temp[j - i] = '\0';
		while (i < j)
		{
			temp[j - i] = *plate[j - i];
			i++;
		}
		free(*plate);
		*plate = temp;
	}
	free(plate);
	return (re_string);
}
	
char	*get_next_line(int fd)
{
	static char	*plate = NULL;
	char		*fork;
	int		pan_of_spaget;
	bool		eof;
	
	eof = false;
	pan_of_spaget = fd;

	while(is_meatball_on(plate) > -1)
	{
		fork_to_plate(pan_of_spaget, &plate, &eof);
		if (eof == true)
			return(plate);
		if (plate == NULL)
			return (NULL);
	}
	return (eat_meatball_from(&plate));
}

