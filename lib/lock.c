#include <lib/lock.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <lib/error.h>
#include <errno.h>

#define LOCK_FILE "/tmp/lock.%d"
#define MAX_LOCK 5

static struct flock lock_it[MAX_LOCK], unlock_it[MAX_LOCK];
static int lock_fd[MAX_LOCK];

void lock_init(int lock_num) {
  char lock_file[1024];

  sprintf(lock_file, LOCK_FILE, lock_num);
  lock_fd[lock_num] = mkstemp(lock_file);
  //unlink the lock file
  unlink(lock_file);
  lock_it[lock_num].l_type = F_WRLCK;
  lock_it[lock_num].l_whence = SEEK_SET;
  lock_it[lock_num].l_start = 0;
  lock_it[lock_num].l_len = 0;

  unlock_it[lock_num].l_type = F_UNLCK;
  unlock_it[lock_num].l_whence = SEEK_SET;
  unlock_it[lock_num].l_start = 0;
  unlock_it[lock_num].l_len = 0;

}

void lock_wait(int lock_num) {
  int rc;
  while ((rc = fcntl(lock_fd[lock_num], F_SETLKW, &lock_it[lock_num])) < 0) {
    if (errno == EINTR)
      continue;
    else
      err_quit("error lock wait");
  }

}

void lock_release(int lock_num) {
  if (fcntl(lock_fd[lock_num], F_SETLKW, &unlock_it[lock_num]) < 0) {
    err_quit("error unlock wait");
  }
}
