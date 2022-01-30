#ifndef ERROR_H
#define ERROR_H

void raiseInvalidInputError(char *message);
void raiseOutOfBoundsError(char *message);
void raiseNullPointerError(char *message, char *file, const char *func, int line);

#endif
