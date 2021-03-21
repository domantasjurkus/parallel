#include <pthread.h>
#include <stdio.h>
void *threadfunction(void *p){
  char *t = (char *)p;
  for(int i=0; i<10; i++)    
  	printf("Thread %s: i=%d\n",t,i);
}
 
void main(){
  pthread_t thrID1, thrID2;
  pthread_create(&thrID1, NULL, threadfunction, "one");
  pthread_create(&thrID2, NULL, threadfunction, "two");  
  pthread_join(thrID1, NULL);  
  pthread_join(thrID2, NULL);
}
