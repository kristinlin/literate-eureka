#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>

//for opening and writing and closing a file
void check_error(int e) {
  if (e < 0) {
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
}

//appropriately intercepting a signal
static void sighandler( int signo ) {
  //if it's SIGINT, open a file called msg and write to it, exit successfully
  if (signo == SIGINT) {
    int fd;
    fd = open("msg", O_CREAT | O_APPEND | O_RDWR, 0664);
    check_error(fd);
    check_error(write(fd,
		      "program ended due to SIGINT\n",
		      sizeof("program ended due to SIGINT\n")-1));
    check_error(close(fd));
    exit(EXIT_SUCCESS);
  }
  //if it's SIGUSR1, just printf the parent id, obtained by getppid
  if (signo == SIGUSR1) {
    printf("This is the parent program: %d\n", getppid());
  }
}


int main() {
  //forever loop
  while(1) {
    //check if signal is SIGINT or SIGUSR1, set sighandler 
    signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);
    //print pid of this program
    printf("Hey, my id is: %d\n", getpid());
    sleep(1);
  }
}
