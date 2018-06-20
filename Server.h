#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_NONSTDC_NO_DEPRECATE

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>
#include<string.h>
#include<pthread.h>
#include<Windows.h>
#include<time.h>
#include"DB.h"

pthread_t *gthread;
int *threadStatus;
int *buffer;
int *mode;
int size = -1;
int head = -1;

//0-read
//1-write
int status=0;

//0-free
//1-busy
int current = 0;

void init_server()
{
	++size;
	++head;
	 gthread= (pthread_t *)malloc(4*sizeof(pthread_t));
	 buffer = (int *)malloc(1000 * sizeof(int));
	 mode = (int *)malloc(1000 * sizeof(int));
	 threadStatus = (int *)malloc(4 * sizeof(int));

	 int i;
	 for (i = 0; i < 4; i++)
		 threadStatus[i] = 0;

}
int getFreeThreadInd()
{
	int i;
	for (i = 0; i < 4; i++)
	{
		if (threadStatus[i] == 0)
			return i;
	}
	return -1000;
}


void TaskManager(int x)
{
	int i;
	for (i = head; i < size; i++)
	{
		int f;
		if (current >= 0 && (f = getFreeThreadInd()) != -1000)
		{
			if (status == 1)
				continue;

			if (mode == 0)
			{
				threadStatus[f] = 1;
				printf("Thread  %d\n", threadStatus[f]);
				pthread_create(&gthread[f], 0, get, (void *)x);
				threadStatus[f] = 0;
				current--;
			}
			else
			{
				status = 1;
				threadStatus[f] = 1;
				printf("Thread  %d\n", threadStatus[f]);
				pthread_create(&gthread[f], 0, add, (void *)x);
				threadStatus[f] = 0;
				current--;
				status = 0;
			}



		}
		head = i;

	}
}

void MainBuf(int x, int stat)
{
	if (size == -1)
	{
		init_server();
		current = 0;
	}

	//db is free
	if (current == 0)
	{
		if (status == 0 && stat == 0)
		{
			current = 1;
			int f = getFreeThreadInd();
			threadStatus[f] = 1;
			printf("Thread  %d\n", threadStatus[f]);
			pthread_create(&gthread[f], 0, get, (void *)x);
			threadStatus[f] = 0;
			current = 0;


			//Sleep(10000);
			return;
		}
		else if (stat == 1)
		{
			status = 1;
			current = 1;

			int f = getFreeThreadInd();
			if (f == -1000)
			{
				printf("sorry server busy\n");
				printf("ur request in queue\nwait..............\n");
				current++;
				buffer[size] = x;
				mode[size] = stat;
				++size;

				//Sleep(10000);
				return;
			}
			threadStatus[f] = 1;
			printf("Thread  %d\n", threadStatus[f]);
			pthread_create(&gthread[f], 0, add, (void *)x);
			threadStatus[f] = 0;

			status = 0;
			current = 0;

			//Sleep(10000);
			return;
		}
	}
	//db is busy with read and present req is read

	else if (status == 0 && stat == 0)
	{
		current++;
		int f = getFreeThreadInd();
		if (f == -1000)
		{
			printf("sorry server busy\n");
			return;
		}
		threadStatus[f] = 1;
		printf("Thread  %d\n", threadStatus[f]);
		pthread_create(&gthread[f], 0, get, (void *)x);
		threadStatus[f] = 0;
		current--;

		//Sleep(10000);
		return;
	}
	//db is busy in writing
	else if (status == 1)
	{
		printf("ur request in queue\nwait..............\n");
		current++;
		buffer[size] = x;
		mode[size] = stat;
		++size;
	}




}


/*
void MainBuf(int x,int stat)
{
	if (size == -1)
	{
		init_server();
		current = 0;
	}

	//db is free
	if (current == 0)
	{
		if (status == 0 && stat == 0)
		{
			current = 1;
			int f = getFreeThreadInd();
			threadStatus[f] = 1;
			pthread_create(&gthread[f], 0, get, (void *)x);
			threadStatus[f] = 0;
			current=0;

			return;
		}
		else if (stat == 1)
		{
			status = 1;
			current = 1;

			int f = getFreeThreadInd();
			if (f == -1000)
			{
				printf("sorry server busy\n");
				printf("ur request in queue\nwait..............\n");
				current++;
				buffer[size] = x;
				mode[size] = stat;
				++size;

				return;
			}
			threadStatus[f] = 1;
			pthread_create(&gthread[f], 0, add, (void *)x);
			threadStatus[f] = 0;

			status = 0;
			current = 0;

			return;
		}
	}
	//db is busy with read and present req is read
	
	else if (status == 0 && stat == 0)
	{
		current++;
		int f = getFreeThreadInd();
		if (f == -1000)
		{
			printf("sorry server busy\n");
			return;
		}
		threadStatus[f] = 1;
		pthread_create(&gthread[f], 0, get, (void *)x);
		threadStatus[f] = 0;
		current--;

		return;
	}
	//db is busy in writing
	else if (status == 1)
	{
		printf("ur request in queue\nwait..............\n");
		current++;
		buffer[size] = x;
		mode[size] = stat;
		++size;
	}


	int i;
	for (i = head; i < size; i++)
	{
		int f;
		if (current >= 0 && (f = getFreeThreadInd()) != -1000)
		{
			if (status == 1)
				continue;

			if (mode == 0)
			{
				threadStatus[f] = 1;
				pthread_create(&gthread[f], 0, get, (void *)x);
				threadStatus[f] = 0;
				current--;
			}
			else
			{
				status = 1;
				threadStatus[f] = 1;
				pthread_create(&gthread[f], 0, add, (void *)x);
				threadStatus[f] = 0;
				current--;
				status = 0;
			}



		}
		head = i;
		
	}

	printf("vcxvdv");

}

*/