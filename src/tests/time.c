#include <stdio.h>
#include <time.h>
#include <unistd.h>



void sleeptime(int n)
{
    int dt,i;
    dt = n;
    i = 0;
    while(1){
        if(dt == 0){
            dt = n;
            printf("completed %d cycles\n",++i);
        }
        else{
            dt--;
            usleep(16666);
        }
    }
}

void gettime(int n) 
{
    
    int dt = n;
    int i = 0;
    double freq = (1/60) * CLOCKS_PER_SEC;
    clock_t poll,start,diff;
    while(1){
        if(dt <= 0){ //timer isn't running
            dt = n;
            printf("%d timer intervals elapsed\n",++i);
            start = clock();
        }
        else{ //timer is running
            poll = clock();
            diff = poll - start;
            if ((double)diff > freq){
                start = clock();
                dt--;
            }
        }
    }

}


//NOTE: it seems clock is only precise to 10k ticks

int main()
{    
    int n = 60;
    gettime(n);
    //sleeptime(n);
    //while (n>0){
    //    printf("\r%d",n);
    //    n--;
    //}
    return 0;
}
