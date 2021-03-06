#define MAXLEN 1001
#define MAXFIELDS 1000
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct inputstruct {
    char *name;               /* File name */
    FILE *f;                  /* File descriptor */
    int line;                 /* Line number */
    char text1[MAXLEN];       /* The line */
    char text2[MAXLEN];       /* Working -- contains fields */
    int NF;                   /* Number of fields */
    char *fields[MAXFIELDS];  /* Pointers to fields */
    int file;                 /* 1 for file, 0 for popen */
} *IS;

extern IS new_inputstruct(char*);
extern IS pipe_inputstruct(char*);
extern int get_line(IS); /* returns NF, or -1 on EOF.  Does not
                                  close the file */
extern void jettison_inputstruct(IS);  /* frees the IS and fcloses 
                                                the file */
