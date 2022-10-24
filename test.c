#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>

#define KERNEL_2D_MEMCPY 451

int main()
{
float a[3][4];
for(int i=0;i<3;i++)
{
for(int j=0;j<4;j++)
{
a[i][j]=i+j;
}
}
float b[3][4];
for(int i=0;i<3;i++)
{
for(int j=0;j<4;j++)
{
b[i][j]=1;
}
}

long sys_call_status;
sys_call_status = syscall(KERNEL_2D_MEMCPY,a,b);
for(int i=0;i<3;i++){
	for(int j=0;j<4;j++){
		printf("%lf ",b[i][j]);}
printf("\n");
}
return 0;
}
