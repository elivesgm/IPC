// threadpool_testmain.c
#include <stdio.h>
#include <unistd.h>
#include "threadpool.h"

void*
work(void* arg)
{
	char* p = (char*) arg;
	printf("threadpool callback function: %s\n", p);
	sleep(1);
	return NULL;
}


int
main(int argc, char** argv)
{
	int thread_num = 5;
	int queue_max_num = 10;
	struct threadpool* pool = threadpool_init(thread_num, queue_max_num);

	threadpool_add_job(pool, work, "1");
        threadpool_add_job(pool, work, "2");
        threadpool_add_job(pool, work, "3");
        threadpool_add_job(pool, work, "4");
        threadpool_add_job(pool, work, "5");
        threadpool_add_job(pool, work, "6");
        threadpool_add_job(pool, work, "7");
        threadpool_add_job(pool, work, "8");
        threadpool_add_job(pool, work, "9");
        threadpool_add_job(pool, work, "10");
        threadpool_add_job(pool, work, "11");

	sleep(5);
	threadpool_destroy(pool);
	return 0;
}
