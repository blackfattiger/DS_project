//Author:learningLinux
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "fdfs_upload_file.h"

int main(int argc, char* argv[]){
	char fileID[1024] = {0};
	//upload_file1("etc/fdfs/client.conf", "test.c", fileID);
	//printf("fileID: %s\n", fileID);
	printf("===============================\n");

	upload_file2("/etc/fdfs/client.conf", "test.c", fileID, sizeof(fileID));
	printf("fileID: %s\n", fileID);

	return 0; 
}
