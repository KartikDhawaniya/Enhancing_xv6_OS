#include "types.h"
#include "stat.h"
#include "user.h"

char buf;

void
ead(int fd, int l)
{
  int n=0;

  while((n = read(fd, &buf, sizeof(char))) > 0 && l > 0) {
    if (write(1, &buf, n) != n) {
      printf(1, "cat: write error\n");
      exit();
    }
    if(buf == '\n')
      l--;
  }
  if(n < 0){
    printf(1, "cat: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{
  int fd, i;

  if(argc < 2) {
    printf(1, "usage: cat lines file ...\n");
  }

  int ln = atoi(argv[1]);

  if(argc <= 2){
    ead(0, ln);
    exit();
  }

  for(i = 2; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "cat: cannot open %s\n", argv[i]);
      exit();
    }
    ead(fd, ln);
    close(fd);
  }
  exit();
}
