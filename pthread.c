#include <stdio.h>
#include <string.h>
#include <pthread.h> // pthread_create()
#include <unistd.h> // getpid()


/*****************************
打印进程id和主线程id、以及新的线程函数中的进程id和线程id
*/

// 打印id
void printID(char* name)
{
	printf("func name:%s pid is %d,tid is 0x%x\n",name,getpid(),pthread_self());	
}
// 线程回调函数
void* pthread_func(void *p)
{
	printf("pthread_func %s\n",(char*)p);
	printID(p);
	return (void*)0;
}

int main()
{
	pid_t pid;
	pthread_t tid;
	int err;
	
	err = pthread_create(&tid,NULL,pthread_func,"new thread");
	if(err != 0){
		printf("func pthread_create is failed\n");
		return 0;
	}
	printID("main thread ");
	sleep(2);
	return 0;
}