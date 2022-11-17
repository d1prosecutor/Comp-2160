#ifndef CONTAINER_H
#define CONTAINER_H

typedef struct CONTAINER Container;
typedef enum BOOL
{
    false,
    true
} Boolean;

Container *createContainer();
Boolean destroyContainer(Container **);

Boolean insertItem(Container *, char *);
Boolean deleteItem(Container *, char *);
Boolean clear(Container *);

char *firstItem(Container *);
char *nextItem(Container *);

Boolean contains(Container *, char *);
int size(Container *);

#endif