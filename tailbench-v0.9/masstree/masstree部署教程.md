1. 首先需要安装依赖
```
aptitude install libgoogle-perftools-dev
如果没有安装aptitude，可以选择安装aptitude：apt install aptitude，然后执行上面的命令
也可以执行通过apt install libgoogle-perftools-dev进行安装
对于依赖关系比较复杂的情况，推荐使用aptitude进行安装
```
2.修改tailbench-v0.9目录下的Makefile.config文件
```
将其中的JDK_PATH改为本机的JDK安装路径
```
3.安装autoconf
```
apt install autoconf
```
4. 编译
```
在masstree目录下执行 ./build.sh
```
5. 运行
```
在masstree目录下执行 ./run.sh
```
6. 解析结果
```
python2 ../utilities/parselats.py lats.bin
```

7. 根据需求设置对应参数，参数含义如下

```
TBENCH_WARMUPREQS：预热阶段发送的请求数，在此期间不进行数据的采集
TBENCH_MAXREQS：总共需要发送多少条请求，不包含预热阶段的请求数量
TBENCH_MINSLEEPNS：客户端在遇到空闲时间（即未提交任何请求时）在内核中休眠的最短时间长度（以ns为单位） 
TBENCH_QPS：每秒发送多少条请求。（运行时间理论上为（MAXREQS + WARMUPREQS) / QPS）
TBENCH_RANDSEED：产生间隔时间的随机数生成器的种子 
TBENCH_CLIENT_THREADS：客户端发送请求的线程数
TBENCH_SERVER：服务端IP地址，默认为localhost
TBENCH_SERVER_PORT：服务端端口号，默认为8080