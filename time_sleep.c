#include <stdio.h>
#include <unistd.h>

int main()
{

      // This line will be executed first
    printf("Program to sleep for 10 second in Linux.\n");

    sleep(10);
    // after 10 seconds this next line will be executed.
  
    printf("This line will be executed after 10 second.");

    return 0;
}
