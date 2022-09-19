#include <time.h>
#include <stdio.h>
#include<stdlib.h>

int main(){
time_t timeV;
time(&timeV);
printf("%s",ctime(&timeV));
}
