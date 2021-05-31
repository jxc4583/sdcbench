
functionbench项目简介：该项目包含ALU，MatMul, Disk IO三个serverless应用。
---
#### 依赖环境
- Kubernetes


#### **部署步骤：**
##### 1. 创建命名空间

```
kubectl apply -f ./namespaces.yml
```

##### 2. 部署函数

```
kubectl apply -f yaml-func/
```


#### 如何运行： 
##### 1.ALU

```
curl -d '{"loopTime": 100000000}' http://HOST-IP:30351
注：HOST-IP为主节点的IP，即向主节点的30351端口发送POST请求，loopTime对应的数据越大，执行时间越长
```


##### 2.Disk IO

```
curl -d '{"file_size": 300, "byte_size": 1024}' http://HOST-IP:30352
注：HOST-IP为主节点的IP，即向主节点的30351端口发送POST请求，file_size对应读写数据大小(MB)，byte_size对应缓存大小，file_size越大，执行时间越长，注意该值不要设置过大以免出现磁盘空间不足问题
```


##### 3.MatMul

```
curl -d '{"n": 10000}' http://HOST-IP:30353
注：HOST-IP为主节点的IP，即向主节点的30353端口发送POST请求，n对应的数据越大，执行时间越长
```