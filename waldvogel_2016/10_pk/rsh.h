/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 */

#ifndef RSH_MAIN_H
#define RSH_MAIN_H

#define DELIM " \t\n"
#define TOKENBUFFER 32
#define LINEBUFFER 128

char *readCommand(void);
int parseCommand(char *line, char ***tokenStorage);
int executeExternCommand(int count, char **tokens);
int executeCommand(int count, char **tokens);
void prompt(void);
void init(void);
int main(void);

#endif //RSH_MAIN_H
