#include <stdio.h>
#include <unistd.h>

int main() {
	// This is program 1  with inifinite loop
	printf("Program 1 is now running/n");
	
	while (1) {
        	sleep(1);
    	}
	return 0;
}
