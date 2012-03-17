#include <lib/lock.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <lib/error.h>
#include <errno.h>

static struct flock lock_it, unlock_it;
static int lock_fd = -1;

void lock_init(char * pathname) {
  char lock_file[1024];

  strncpy(lock_file, pathname, sizeof(lock_file));
  lock_fd = mkstemp(lock_file);
  //unlink the lock file
  unlink(lock_file);
  lock_it.l_type = F_WRLCK;
  lock_it.l_whence = SEEK_SET;
  lock_it.l_start = 0;
  lock_it.l_len = 0;

  unlock_it.l_type = F_UNLCK;
  unlock_it.l_whence = SEEK_SET;
  unlock_it.l_start = 0;
  unlock_it.l_len = 0;

}

void lock_wait() {
  int rc;
  while ((rc = fcntl(lock_fd, F_SETLKW, &lock_it)) < 0) {
    if (errno == EINTR)
      continue;
    else
      err_quit("error lock wait");
  }

}

void lock_release() {
  if (fcntl(lock_fd, F_SETLKW, &unlock_it) < 0) {
    err_quit("error unlock wait");
  }
}