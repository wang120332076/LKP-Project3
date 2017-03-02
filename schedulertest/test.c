#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>
#include <assert.h>
#include <pthread.h>

#define SCHED_LOTT 6
#define N 39
#define NUMTHREADS 10

static int fib(int n)
{
        if (n == 0) return 0;
        if (n == 1) return 1;
        return fib(n-1) + fib(n-2);
}

void *worker(void *args)
{
        printf("Fib of %d is %d\n", N, fib(N));
        return NULL;
}
int main(void)
{
        int ret;
        ret = sched_getscheduler(getpid());
        assert(ret == SCHED_OTHER);
        const struct sched_param param = { .sched_priority = 0 };
        //ret = sched_setscheduler(getpid(), SCHED_LOTT, &param);
        assert (ret == 0);
        pthread_t threads[NUMTHREADS];
        for(int i = 0; i < NUMTHREADS; i++) {
                pthread_create(&threads[i], NULL, worker, NULL);
                pthread_setschedparam(threads[i], SCHED_LOTT, &param);
        }
        for(int i = 0; i < NUMTHREADS; i++) {
                pthread_join(threads[i], NULL);
        }
        return 0;
}

