#ifndef LOCK_H
#define LOCK_H

void lock_init(int lock_num);
void lock_wait(int lock_num);
void lock_release(int lock_num);

#endif
