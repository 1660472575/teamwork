#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>

// 线程清除
/**********************
pthread_cleanup_push()
pthread_cleanup_pop()

*/
void cleanup01(void* arg)
{
	printf("this is clean up func01\n");
}
void cleanup02(void* arg)
{
	printf("this is clean up func02\n");
}

// 线程定义
void* pfunc1(void* arg)
{
	printf("new thread is %s\n",arg);
	pthread_cleanup_push(cleanup01,NULL);
	pthread_cleanup_push(cleanup01,NULL);
	
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(1);
	return 0;
}
void* pfunc2(void* arg)
{
	printf("this is new thread2\n");
	pthread_cleanup_push(cleanup02,NULL);
	pthread_cleanup_push(cleanup02,NULL);
	
	pthread_cleanup_pop(1);
	pthread_cleanup_pop(0);
	pthread_exit(0);
}
int main()
{
	pthread_t tid1,tid2;
	int err;
	err = pthread_create(&tid1,NULL,pfunc1,"thread1");
	if(err !=0){
		printf("create new thread1 failed\n");
		return -1;
	}
	err = pthread_create(&tid2,NULL,pfunc2,"thread2");
	if(err != 0){
		printf("create new thread2 failed\n");
		return -1;
	}
	sleep(2);
	
	
	return 0;
}




