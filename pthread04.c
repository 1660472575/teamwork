#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

// 信号回调函数
// 发送信号以及处理信号


void sighandler01(int val)
{
	printf("this is sighandler01\n");
}
void sighandler02(int val)
{
	printf("this is sighandler02\n");
}
/*
 int sigaction(int signum, const struct sigaction *act,
                     struct sigaction *oldact);
***/
// 新线程
void* pfunc01(void* arg)
{
	struct sigaction act;
	act.sa_handler = sighandler01;
	sigaddset(&act.sa_mask,SIGQUIT);
	//act.sa_mask = 
	sigaction(SIGQUIT,&act,NULL);  // 安装信号
	
	// pthread_sigmask(SIG_BLOCK,&act.sa_mask,NULL);   //  信号掩码
	sleep(2);
	return (void*)0;
}
void* pfunc02(void* arg)
{
	struct sigaction act1;
	act1.sa_handler = sighandler02;
	sigaddset(&act1.sa_mask,SIGQUIT);
	sigaction(SIGQUIT, &act1,NULL);
	
	pthread_sigmask(SIG_BLOCK,&act1.sa_mask,NULL);
	sleep(2);
	
	return (void*)0;
}

int main()
{
	pthread_t tid1,tid2;
	int err;
	err = pthread_create(&tid1,NULL,pfunc01,NULL);
	if(err < 0){
		printf("create new pthread one failed\n");
	}
	err = 0;
	err = pthread_create(&tid2,NULL,pfunc02,NULL);
	if(err < 0){
		printf("create new pthread two failed\n");
	}
	sleep(1);
	pthread_kill(tid1,SIGQUIT);
	pthread_kill(tid2,SIGQUIT);
	
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	return 0;
}


