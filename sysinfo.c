#include<stdio.h>
#include<stdlib.h>
#include<sys/utsname.h>  

int main()
{
struct utsname u;
uname(&u);
printf("Operating System: %s\n",u.sysname);
printf("Version: %s\n",u.release);
printf("Modification: %s\n",u.version);
printf("Information about the platform: %s \n",u.machine);
return 0;
}
