#ifndef LOCK_H
#define LOCK_H

void lock_init(char * pathname);
void lock_wait();
void lock_release();

#endif
