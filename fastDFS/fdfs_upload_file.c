/**
* Copyright (C) 2008 Happy Fish / YuQing
*
* FastDFS may be copied only under the terms of the GNU General
* Public License V3, which may be found in the FastDFS source kit.
* Please visit the FastDFS Home Page http://www.csource.org/ for more detail.
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "fdfs_client.h"


int upload_file1(const char* confFile, const char* myFile, char* fileID)
{
	char group_name[FDFS_GROUP_NAME_MAX_LEN + 1];
	ConnectionInfo *pTrackerServer;
	int result;
	int store_path_index;
	ConnectionInfo storageServer;
	

	if ((result=fdfs_client_init(confFile)) != 0)
	{
		return result;
	}

	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL)
	{
		fdfs_client_destroy();
		return errno != 0 ? errno : ECONNREFUSED;
	}

	*group_name = '\0';

	if ((result=tracker_query_storage_store(pTrackerServer, \
	                &storageServer, group_name, &store_path_index)) != 0)
	{
		fdfs_client_destroy();
		fprintf(stderr, "tracker_query_storage fail, " \
			"error no: %d, error info: %s\n", \
			result, STRERROR(result));
		return result;
	}

	result = storage_upload_by_filename1(pTrackerServer, \
			&storageServer, store_path_index, \
			myFile, NULL, \
			NULL, 0, group_name, fileID);
	if (result == 0)
	{
		printf("%s\n", fileID);
	}
	else
	{
		fprintf(stderr, "upload file fail, " \
			"error no: %d, error info: %s\n", \
			result, STRERROR(result));
	}

	tracker_disconnect_server_ex(pTrackerServer, true);
	fdfs_client_destroy();

	return result;
}

//使用多进程的方式实现
int upload_file2(const char* confFile, const char* uploadFile, char* fileID, int size){//size为传出参数fileID的大小
	//1.创建匿名管道
	int fd[2];
	int ret = pipe(fd);
	if(ret == -1){
		perror("pipe error");
		exit(0);
	}
	//2.创建子进程
	pid_t pid = fork();
	//判断是否为子进程，如果是子进程
	if(pid == 0){
		//3.将标准输出重定向->到管道的写端
		int ret = dup2(fd[1], STDOUT_FILENO);
		//4.关闭读端
		close(fd[0]);
		//5.执行execlp命令
		execlp("fdfs_upload_file", "xxx", confFile, uploadFile, NULL);//第二个参数是占位参数，一般写成和第一个参数相同
	}else{
		//父进程，读管道
		//关闭写端
		close(fd[1]);
		//char buf[1024]; 用fileID这个传出参数替换掉了
		//read(fd[0], buf, sizeof(buf))；
		read(fd[0], fileID, size);
		//回收pcb->子进程的
		wait(NULL);
	}

	
}
