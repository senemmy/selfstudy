#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>



void *func1(void *arg)
{
    while(1)
    {
        sleep(1);
        printf("func1 is running...\n");
    }

    return NULL;
}

void *func2(void *arg)
{
    while(1)
    {
        sleep(1);
        printf("func2 is running...\n");
    }

    return NULL;
}


// int main()
// {
//     pthread_t my_thread1;
//     pthread_t my_thread2;

//     pthread_create(&my_thread1, NULL, func1, NULL);
//     pthread_create(&my_thread2, NULL, func2, NULL);
//     func1(NULL);
//     func2(NULL);

//     pthread_join(my_thread1, NULL);
//     pthread_join(my_thread2, NULL);
//     return 0;
// }


void* foo1(void *arg){

    for(int i = 0; i<10; i++) {
        sleep(1);
        printf("foo1 is calling... i = %d\n", i);
    }
}

void foo2(){

    for(int i = 0; i<3; i++) {
        sleep(1);
        printf("foo2 is calling... i = %d\n", i);
    }
}

int main()
{
    pthread_t my_thread1;
    pthread_t my_thread2;
    
    //creating a new thread which is my_thread1
    pthread_create(&my_thread1, NULL, foo1, NULL);

    foo2(); // this func is running on main thread
    //when main thread terminate we can not see the my_thread1's all functionalities. 
    
    //For this reason we need to use pthread_join func to wait func1's functionalities.
    pthread_join(my_thread1, NULL);
}
