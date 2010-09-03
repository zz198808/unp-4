/*
 * 图27.7 pr_cpu_time 函数：输出总cpu时间
 * */

#include <stdio.h>
#include <sys/resource.h>
#include <stdlib.h>

#ifndef HAVE_GETRUSAGE_PROTO
int getrusage(int ,struct rusage *);
#endif

void
pr_cpu_time(void)
{
    double user;
    double sys;
    struct rusage myusage;
    struct rusage childusage;

    if(getrusage(RUSAGE_SELF,&myusage) < 0)
    {
        perror("getrusage");
        exit(1);
    }

    if(getrusage(RUSAGE_CHILDREN,&childusage) < 0)
    {
        perror("getrusage");
        exit(1);
    }

    user = (double)myusage.ru_utime.tv_sec +
           myusage.ru_utime.tv_usec/1000000.0;
    user += (double)childusage.ru_utime.tv_sec +
            childusage.ru_utime.tv_usec/1000000.0;

    sys = (double)myusage.ru_stime.tv_sec +
          myusage.ru_stime.tv_usec/1000000.0;
    sys += (double)childusage.ru_stime.tv_sec +
           childusage.ru_stime.tv_usec/1000000.0;

    printf("\nuser time=%g,sys time=%g\n",user,sys);
}
