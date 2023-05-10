1.在nginx目录下 ./configure --add-module=/home/passoni/DS_project/nginx/fastdfs-nginx-module/src --with-openssl=../openssl-1.0.1t --with-pcre=../pcre-8.40 --with-zlib=../zlib-1.2.11

2.make 如果报错根据报错信息一个个解决即可；

3.make install；

---其他错误：根据/usr/local/nginx/logs中error.log最新的报错信息来进行排除，最主要的问题就是配置文件的问题，**一定要注意路径是否输入正确！**

