/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_isprint.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lykostan <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/01/19 16:34:45 by lykostan		  #+#	#+#			 */
/*   Updated: 2023/01/19 16:34:47 by lykostan		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c < 127)
		return (1);
	return (0);
}