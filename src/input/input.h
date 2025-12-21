#ifndef INPUT_H
#define INPUT_H

typedef struct Input Input;

Input *input_read_input_file(char *filename, int *status);

#endif // !INPUT_H
