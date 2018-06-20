
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




int* mainArray;
int index = 0;

void* add(void *a)
{
	int value = int(a);
	if (index == 0)
	{
		index++;
		mainArray = (int *)malloc(1000 * sizeof(int));
	}

	mainArray[index] = value;
	
	printf("\n\n\nur entry is succefffuly added\n");
	printf("ur details are id:%d value %d\n",index,mainArray[index] );
		index++;

		return NULL;
}

void*  get(void *a)
{
	int i;
	int id = int(a);
	for (i = 1; i < index; i++)
	{
		if (i == id)
		{
			printf("\n\nur details are id:%d value %d\n\n", i, mainArray[i]);
		}
	}

	return NULL;
}