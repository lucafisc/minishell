/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:12:53 by lde-ross          #+#    #+#             */
/*   Updated: 2023/04/24 17:14:37 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_lexer
{
	char			*data;
	int				info;
	int				pipe;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}				t_lexer;
#endif
