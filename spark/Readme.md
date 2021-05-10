# SparkBench 
## Spark on yarn 
### node view
container name | spark node name
---|---
Spark-1 | master
Spark-2 | slave1
Spark-3 | slave2
### Quick Start
- 镜像拉取
```
docker pull sdcbench/spark:v1
```
- spark三节点容器启动（Spark-1 Spark-2 Spark-3）
```
# docker-compose.yml与readme在同级目录下
docker-compose up -d
```
- 配置spark三节点间的快速免密
```
# 记录 hosts
echo -e "172.27.0.5    master \n172.27.0.6    slave1 \n172.27.0.7    slave2" >> /etc/hosts

# 密钥共享
ssh-keygen -t rsa -P ''
ssh-copy-id -i ~/.ssh/id_rsa.pub -p 22 root@172.27.0.5
ssh-copy-id -i ~/.ssh/id_rsa.pub -p 22 root@172.27.0.6
ssh-copy-id -i ~/.ssh/id_rsa.pub -p 22 root@172.27.0.7
```
> 在公钥互持后，需要保证master通过ssh 连接到各个节点
- 启动journalnode
```
hadoop-daemons.sh start journalnode
```
- 启动dfs
```
start-dfs.sh
```
> 此处若无法启动namenode
``` 
rm -rf /root/hadoop/hadoop-2.7.7/tmp
hdfs namenode -format
# 再次启动dfs
start-dfs.sh
```
- 启动hadoop的history
```
mr-jobhistory-daemon.sh start historyserver
```
- 启动yarn
```
start-yarn.sh
```
- hdfs创建log目录
```
hdfs dfs -mkdir -p /tmp/logs/root/logs
```
- 启动spark日志
```
start-history-server.sh 
```
## sparkbench使用
> sparkbench 是已经编写好的spark项目代码， sparkbench 项目被放置在Spark-1

以下操作均在Spark-1容器上执行。

spark-bench源码已经存在统计目录下

- 解压源码
```
unzip spark-bench-legacy.zip
```
- 安装spark-bench依赖
```
apt install maven
git clone https://github.com/synhershko/wikixmlj.git
cd wikixmlj
mvn package install
```
- 编译sparkbench
```
cd spark-bench
./bin/build-all.sh
```
- 修改spark-bench中的环境配置
```
vim ./spark-bench-legacy/conf/env.sh
    master="master"
    MC_LIST="slave1 slave2"
    YARN_DEPLOY_MODE=client
    DATASET_DIR=/root/SparkBench/dataset 
    export SPARK_EXECUTOR_INSTANCES=2
    SPARK_VERSION=2.4.4
:wq
```
- 为sparkbench数据创建目录
```
hdfs dfs -mkdir -p /SparkBench
```
- Kmeans 运行
```
cd KMeans
./bin/gen_data_java.sh
./bin/run_java.sh
```