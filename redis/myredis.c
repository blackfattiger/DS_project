//Author:learningLinux
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <hiredis.h>


int main(int argc, char* argv[]){
	
	//1.连接redis服务器
	redisContext* c = redisConnect("127.0.0.1", 6379);
	if(c->err != 0){
		return -1;
	}
	//2.执行redis命令
	void* ptr = redisCommand(c, "hmset user userName zhangsan pwd 123456 age %d sex %s", 18, "man");
	redisReply* ply = (redisReply*)ptr;
	if(ply->type == 5){
		//状态输出
		printf("状态: %s\n", ply->str);
	}
	freeReplyObject(ply);

	//3.从数据库中读数据
	ptr = redisCommand(c, "hgetall user");
	ply = (redisReply*)ptr;
	if(ply->type == 2){
		//遍历
		for(int i = 0; i < ply->elements; i += 2){
			printf("key: %s, value: %s\n", ply->element[i]->str, ply->element[i+1]->str);
		}
	}
	freeReplyObject(ply);
	redisFree(c);

	return 0;
}
