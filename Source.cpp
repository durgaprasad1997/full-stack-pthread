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
#include"Server.h"

#define n 1000
#define threads 2



void * menu(void *)
{
	int choice=1;

	
		printf("\n1. Insert Row");
		printf("\n2. Get Row Data");
		
		printf("\n5. Exit");
		printf("\n\nEnter your choice: ");
		int id=1, value=1;
		scanf("%d", &choice);
		//Sleep(100000);
		switch (choice){

		case 1: 
			printf("enter value\n");
			scanf("%d", &value);
			value = 1;
			MainBuf(value,1);
			break;
		case 2:
			printf("enter id\n");
			scanf("%d", &id);
			MainBuf(id,0);
			break;
		
			break;
		case 5: exit(1);
		default: printf("\nInvalid Option");
		
		}
	return NULL;
}

int main(){

	//pthread_t *gthread = (pthread_t *)malloc((threads)*sizeof(pthread_t));

		int i = 0;
		/*for (i = 0; i < threads; i++)
		{
			//printf("\n\n\nThread  %d\n\n", i + 1);
			//pthread_create(&gthread[i], 0, menu, NULL);
			
			
		}
		for (i = 0; i < threads; i++)
		{
			//pthread_join(gthread[i], 0);
		}*/

		while (1)
		{
			menu(NULL);
		}
	

	system("pause");
	return 0;

}