#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

/******************************
主线程给新线程传递结构体参数

*/

typedef struct Student{
	int age;
	char name[20];
	char id[4];
}student;

// 新线程打印传递进来的结构体参数
void* pFunc(void* p)
{
	student* stu = (student*)p;
	printf("pthread func student name is %s,age is %d,id is %s\n",stu->name,stu->age,stu->id);
	return (void*)0;
}
// 如果主线程直接退出，创建的新线程可能执行不到
// 程序进程如果释放了，那么进程中的进程肯定无法执行
int main(int argc,char* argv[])
{
	int retVal;
	pthread_t tid;
	int err;
	student stu;
	stu.age = 20;
	strcpy(stu.name, "LiHuaHua");
	strcpy(stu.id, "007");
	
	err = pthread_create(&tid,NULL,pFunc,(student*)(&stu));
	if(err !=0){
		printf("func pthread_create is create failed\n");
		return 0;
	}
	
	int i = 0;
	printf("main thread has %d argc\n",argc);
	for(i=0;i<argc;i++){
		printf("main thread argv is %s\n",argv[i]);
	}
	pthread_exit(&retVal);   // 主线程等待创建的子线程结束
	printf("pthread exit code is %d\n",retVal);
	return 0;
}



// 传递结构体到线程中
int main01(int argc,char* argv[])
{
	pthread_t tid;
	int err;
	student stu;
	stu.age = 20;
	strcpy(stu.name, "LiHuaHua");
	strcpy(stu.id, "007");
	
	err = pthread_create(&tid,NULL,pFunc,(student*)(&stu));
	if(err !=0){
		printf("func pthread_create is create failed\n");
		return 0;
	}
	
	int i = 0;
	printf("main thread has %d argc\n",argc);
	for(i=0;i<argc;i++){
		printf("main thread argv is %s\n",argv[i]);
	}
	
	sleep(2);
	return 0;
}

