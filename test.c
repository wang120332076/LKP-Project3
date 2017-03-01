#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>
#include <assert.h>

#define SCHED_LOTT 6

static int fib(int n)
{
        return fib(n-1) + fib(n-2);
}

#define N 20
int main(void)
{
        int ret;
        ret = sched_getscheduler(getpid());
        assert(ret == SCHED_OTHER);
        const struct sched_param param = { .sched_priority = 0 };
        ret = sched_setscheduler(getpid(), SCHED_LOTT, &param);
        assert (ret == 0);
        printf("Fib of %d is %d\n", N, fib(N));
}

