<<<<<<< HEAD
# K8s Mongodb搭建说明
1. 采用Stateful部署
2. 使用接口30004
3. 需使用sidecar决定搭建顺序（用于声明生命周期）
4. 需要node2节点（106） 具备挂载目录

```
for vol in vol1 vol2 vol3; do mkdir /mnt/sdcbench/mongodb/$vol; mount -t tmpfs $vol /mnt/sdcbench/mongodb/$vol; done
```

# Mongodb 搭建流程
1. 创建sdc-mongodb
```
kubectl apply -f sdc-mongodb-ns.yaml
```
2. 创建mongo-pv资源
```
kubectl apply -f mongodb-pv.yaml
```
3. 赋予SA授权
```
kubectl apply -f rbac.yaml
```
4. 启动mongodb集群
```
kubectl apply -f mongodb.yaml
```

# 测试
测试集群是否启动，以及节点状态
```
kubectl exec -it mongo-0 -n sdc-mongo -- mongo
```
在mongo环境下输入：
```
rs.status()
```

# 访问

需编写mongodb负载发生器

目前已知ycsb可压测

=======
# K8s Mongodb搭建说明
1. 采用Stateful部署
2. 使用接口30004
3. 需使用sidecar决定搭建顺序（用于声明生命周期）
4. 需要node2节点（106） 具备挂载目录

```
for vol in vol1 vol2 vol3; do mkdir /mnt/sdcbench/mongodb/$vol; mount -t tmpfs $vol /mnt/sdcbench/mongodb/$vol; done
```

# Mongodb 搭建流程
1. 创建sdc-mongodb
```
kubectl apply -f sdc-mongodb-ns.yaml
```
2. 创建mongo-pv资源
```
kubectl apply -f mongodb-pv.yaml
```
3. 赋予SA授权
```
kubectl apply -f rbac.yaml
```
4. 启动mongodb集群
```
kubectl apply -f mongodb.yaml
```

# 测试
测试集群是否启动，以及节点状态
```
kubectl exec -it mongo-0 -n sdc-mongo -- mongo
```
在mongo环境下输入：
```
rs.status()
```

# 访问

需编写mongodb负载发生器

目前已知ycsb可压测

>>>>>>> ssd model
mongodb.url=mongodb://192.168.1.105:30004