#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

void reader(FILE *kanal)
{
char buf[1024];
while(!feof(kanal) && fgets(buf,sizeof(buf),kanal)!=NULL)
  fputs(buf,stdout);
}

void writer(FILE *kanal,char *m)
{
fprintf(kanal,"%s\n",m);
fflush(kanal);
}

int main(int argc,char *argv[])
{
if (argc!=2)
  {
  printf("No string for writing\n");
  exit(1);
  }
int f[2];
pid_t pid;
pipe(f);
pid=fork();
if (pid!=0)
  {
  printf("\n\n\n\n!!!Parent channel with id %d is working...\n", pid);
  close(f[0]);
  FILE *kanal=fdopen(f[1],"w");
  printf("Writing string into the channel: %s",argv[1]);
  writer(kanal,argv[1]);
  close(f[1]);
  wait(&pid);
  printf("\nParent process completed its work\n");
  }
else
  {
  sleep(1);
  printf("\n!!!Subsidiary channel with is working...\n");
  close(f[1]);
  FILE *kanal=fdopen(f[0],"r");
  printf("Read the string from the channel: ");
  reader(kanal);
  close(f[0]);
  printf("Subsidiary process completed its work");
  }
return 0;
}
