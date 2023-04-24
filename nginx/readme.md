
## nginx make问题解决
- 安装nginx 编译时候报objs/Makefile:460: recipe for target 'objs/src/core/ngx_murmurhash.o' failed

  - 1.cd objs
  - 2.vi Makefile
  - 3.去掉-Werror参数之后保存退出 
  - 4.cd ../    #回到上级目录 
  - 5.make   #再次执行makefile文件

- nginx配置文件中添加处理指令
  - location 指令{
  
      root 相对路径;
      
      index 默认要显示的静态网页;
    
    } 
    
   - 指令是指去掉协议、去掉域名/IP地址、去掉端口、去掉尾部的文件名剩下的就是要处理的指令。
