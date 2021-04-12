1. 官网下载源码：http://tailbench.csail.mit.edu/
2. 解压到当前路径
```
tar zxvf  tailbench-v0.9.tgz -C ./
```
3. 修改./tailbench-v0.9/configs.sh脚本中DATA_ROOT，JDK_ROOT，SCRATCH_DIR中的路径

```
DATA_ROOT = tailbench-v0.9的绝对路径
JDK_PATH = 本机的JDK安装路径
SCRATCH_DIR = tailbench-v0.9/scratch
（在tailbench-v0.9下新建scratch目录，用于存放应用采集到的数据）
```


4. 安装aptitude
```
apt install aptitude
```
5. 利用aptitude安装libopencv-dev
```
aptitude install libopencv-dev
```
6. 编译
```
make
```
7. 执行build.sh 
```
切换到tailbench-v0.9的安装路径，无需进入img-dnn目录下
./build.sh img-dnn
```

8. python2安装依赖的库

```
 python2 -m pip install numpy==1.16.1
 python2 -m pip install scipy==1.2.2
```
9. 运行程序

```
./run.sh
```
10. 对解析进行解析

parselats.py脚本在utilities目录下，可以把它复制到img-dnn目录下
```
python2 parselats.py lats.bin

```

11. 根据需求设置对应参数，参数含义如下

```
TBENCH_WARMUPREQS：预热阶段发送的请求数，在此期间不进行数据的采集
TBENCH_MAXREQS：总共需要发送多少条请求，不包含预热阶段的请求数量
TBENCH_MINSLEEPNS：客户端在遇到空闲时间（即未提交任何请求时）在内核中休眠的最短时间长度（以ns为单位） 
TBENCH_QPS：每秒发送多少条请求。（运行时间理论上为（MAXREQS + WARMUPREQS) / QPS）
TBENCH_RANDSEED：产生间隔时间的随机数生成器的种子 
TBENCH_CLIENT_THREADS：客户端发送请求的线程数
TBENCH_SERVER：服务端IP地址，默认为localhost
TBENCH_SERVER_PORT：服务端端口号，默认为8080
```



