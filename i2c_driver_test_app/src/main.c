#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#define BUF_LEN 80

int main()
{
    int file_desc;
    unsigned int slave_addr;
	unsigned char buff[BUF_LEN];
	unsigned short i;

	/* Initializig variables */	
	memset(buff, '\0', BUF_LEN);

	/* Open dummy file. */
    file_desc = open("/dev/i2c_dummy", O_RDWR);

    if(file_desc < 0)
    {
       	printf("Error, 'i2c_dummy' not opened\n");
       	return -1;
    }

	printf("Enter Slave Address: \n");
	scanf("%x", &slave_addr);
	printf("Slave Address You Entered: %X\n", slave_addr);

	buff[0] = 'A';
	buff[1] = (unsigned char)slave_addr;

	write(file_desc, buff, BUF_LEN);

	close(file_desc);
 
	while(1){

	   file_desc = open("/dev/i2c_dummy", O_RDWR);

    	if(file_desc < 0)
   		 {
       		printf("Error, 'i2c_dummy' not opened\n");
       		return -1;
   		 }

		system("clear");	
		read(file_desc, buff, BUF_LEN);
		for(i = 0; i < 6; i++)
			printf("DATA[%i] = %X\n", i, buff[i]);

		close(file_desc);

	}
    
   return 0;
}
