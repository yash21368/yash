#include<pthread.h>
#include<stdio.h>
#include<sched.h>
#include<unistd.h>
#include<time.h>



void get_time(struct timespec in, struct timespec out, struct timespec *t)
{
t->tv_nsec=out.tv_nsec - in.tv_nsec;
t->tv_sec=out.tv_sec - in.tv_sec;

if(t->tv_sec > 0 && t->tv_nsec < 0)
{
t->tv_nsec +=1000000000;
t->tv_sec--;
}

else if(t->tv_sec < 0 && t->tv_nsec > 0)
{
t->tv_nsec-=1000000000;
t->tv_sec++;
}
}

void *countA()
{
struct timespec inA , outA , tA;
clock_gettime(CLOCK_REALTIME, &inA);
for(long long i=0;i<4294967296;i++);
clock_gettime(CLOCK_REALTIME, &outA);
get_time(inA,outA,&tA);
printf("SCHED_OTHER: %d.%.9ld\n",(int)tA.tv_sec,tA.tv_nsec);
}

void *countB()
{
struct timespec inB , outB , tB;
clock_gettime(CLOCK_REALTIME, &inB);
for(long long i=0;i<4294967296;i++);
clock_gettime(CLOCK_REALTIME, &outB);
get_time(inB,outB,&tB);
printf("SCHED_RR: %d.%.9ld\n",(int)tB.tv_sec,tB.tv_nsec);
}

void *countC()
{
struct timespec inC , outC , tC;
clock_gettime(CLOCK_REALTIME, &inC);
for(long long i=0;i<4294967296;i++);
clock_gettime(CLOCK_REALTIME, &outC);
get_time(inC,outC,&tC);
printf("SCHED_FIFO: %d.%.9ld\n",(int)tC.tv_sec,tC.tv_nsec);
}



int main()
{
pthread_t pidA;
pthread_t pidB;
pthread_t pidC;
struct sched_param A;
struct sched_param B;
struct sched_param C;
pthread_attr_t pA , pB , pC;
A.sched_priority=0;
B.sched_priority=1;
C.sched_priority=1;

int sched_policyA=SCHED_OTHER;
int sched_policyB=SCHED_RR;
int sched_policyC=SCHED_FIFO;
pthread_attr_init(&pA);
pthread_attr_setinheritsched(&pA,PTHREAD_EXPLICIT_SCHED);
pthread_attr_setschedpolicy(&pA,SCHED_OTHER);
pthread_attr_setschedparam(&pA,&A);

pthread_attr_init(&pB);
pthread_attr_setinheritsched(&pB,PTHREAD_EXPLICIT_SCHED);
pthread_attr_setschedpolicy(&pA,SCHED_RR);
pthread_attr_setschedparam(&pB,&B);

pthread_attr_init(&pC);
pthread_attr_setinheritsched(&pC,PTHREAD_EXPLICIT_SCHED);
pthread_attr_setschedpolicy(&pC,SCHED_FIFO);
pthread_attr_setschedparam(&pC,&C);


pthread_create(&pidA,&pA,&countA,NULL);
pthread_create(&pidB,&pB,&countB,NULL);
pthread_create(&pidC,&pC,&countC,NULL);


pthread_join(pidA,NULL);
pthread_join(pidB,NULL);
pthread_join(pidC,NULL);
}

