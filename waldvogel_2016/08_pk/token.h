/** \file token.h
 * token declarations
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * */

#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#define NUMBER '0' /** signal that a number was found */
void init(int argcnt, char **argvec);
int gettoken(int *value); /* return value is operator, NUMBER, or EOF */

#endif
