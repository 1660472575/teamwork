#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

/****************************
信号的默认处理

*/

void* pFunc(void* p)
{
	printf("this is new thread\n");
	sleep(2);
	return (void*)0;
}
// 传递结构体到线程中
int main(int argc,char* argv[])
{
	pthread_t tid;
	int err;
	int s;
	
	err = pthread_create(&tid,NULL,pFunc,NULL);
	if(err !=0){
		printf("func pthread_create is create failed\n");
		return 0;
	}
	printf("main thread has %d argc\n",argc);
	//sleep(2);
	// 向线程发送信号
	//s = pthread_kill(tid,0);
	if(s == ESRCH){ // 新的线程在发送信号之前退出了
		printf("thread id not found\n");
	}
	
	pthread_kill(tid,SIGQUIT);   // 向线程发送SIGQUIT推出信号，整个进程都会退出
	
	printf("I am main thread\n"); // 整个进程退出，这句话不会打印
	
	return 0;
}
/*
topeet@ubuntu:~/mycode/pthread$ gcc -pthread pthread03.c 
topeet@ubuntu:~/mycode/pthread$ ./a.out 
main thread has 1 argc
I am main thread
***/
 