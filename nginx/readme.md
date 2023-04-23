
## nginx make问题解决
- 安装nginx 编译时候报objs/Makefile:460: recipe for target 'objs/src/core/ngx_murmurhash.o' failed

  - 1.cd objs
  - 2.vi Makefile
  - 3.去掉-Werror参数之后保存退出 
  - 4.cd ../    #回到上级目录 
  - 5.make   #再次执行makefile文件
