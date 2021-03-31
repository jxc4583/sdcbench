<<<<<<< HEAD
# Solr服务搭建说明
1. 说明搭建过程所使用的基础镜像，都来自docker hub
2. 采用Stateful服务部署solr
3. 不需要进行人工配置，在yaml文件中已实现对于zookeeper和Solr的二次配置
4. 需要注意，由于采取的是pv本地挂载，则续保证node（106节点）上存在挂载目录/mnt/sdcbench/solr

```
for vol in vol1 vol2 vol3; do mkdir /mnt/sdcbench/zk/$vol; mount -t tmpfs $vol /mnt/sdcbench/zk/$vol; done
for vol in vol1 vol2 vol3; do mkdir /mnt/sdcbench/solr/$vol; mount -t tmpfs $vol /mnt/sdcbench/solr/$vol; done
```

# k8s zookeeper集群搭建流程
1. 创建sdc-solr的命名空间
```
kubectl apply -f sdc-solr-ns.yaml
```
2. 创建基础存储服务
```
kubectl apply -f sc.yaml
```
3. 创建pv资源
```
kubectl apply -f zk-pv.yaml
```
4. 启动zookeeper
```
kubectl apply -f zk.yaml
```

# zookeeper + solr串联
1. 创建solr-pv资源
```
kubectl apply -f solr-pv.yaml
```
2. 启动solr
```
kubectl apply -f solr.yaml
```

# 遇到的问题
k8s的基础不懂，一切白搭。（建议先看动基础概念。。。）

所使用的zookeeper镜像为3.4.10，因此使用headless进行zookeeper集群访问，会出现单节点访问。

解决方案：
https://lucene.472066.n3.nabble.com/How-to-resolve-a-single-domain-name-to-multiple-zookeeper-IP-in-Solr-td4450236.html

或者指定访问形式：https://www.jianshu.com/p/257d1be4badd

（博客中最重要的话：除此之外，StatefulSet在Headless Service的基础上又为StatefulSet控制的每个Pod副本创建了一个DNS域名）


# 数据注入
```
# 进入pod
kubectl exec -it sdc-solr-0 -n sdc-solr bash 
# 创建collection
bin/solr create_collection -c cloudsuite_web_search -shards 3 -replicationFactor 3 -d /opt/solr/example/example-DIH/solr/solr/conf -p 8983
# 为collection加载数据
bin/post -c cloudsuite_web_search /opt/solr/example/exampledocs/*
```

# 访问流程

- solr中已开启nodePort（30002），使用masterIP：30002即可访问。
- http://192.168.1.105:30002/solr/#/~cores
=======
# Solr服务搭建说明
1. 说明搭建过程所使用的基础镜像，都来自docker hub
2. 采用Stateful服务部署solr
3. 不需要进行人工配置，在yaml文件中已实现对于zookeeper和Solr的二次配置
4. 需要注意，由于采取的是pv本地挂载，则续保证node（106节点）上存在挂载目录/mnt/sdcbench/solr

```
for vol in vol1 vol2 vol3; do mkdir /mnt/sdcbench/zk/$vol; mount -t tmpfs $vol /mnt/sdcbench/zk/$vol; done
for vol in vol1 vol2 vol3; do mkdir /mnt/sdcbench/solr/$vol; mount -t tmpfs $vol /mnt/sdcbench/solr/$vol; done
```

# k8s zookeeper集群搭建流程
1. 创建sdc-solr的命名空间
```
kubectl apply -f sdc-solr-ns.yaml
```
2. 创建基础存储服务
```
kubectl apply -f sc.yaml
```
3. 创建pv资源
```
kubectl apply -f zk-pv.yaml
```
4. 启动zookeeper
```
kubectl apply -f zk.yaml
```

# zookeeper + solr串联
1. 创建solr-pv资源
```
kubectl apply -f solr-pv.yaml
```
2. 启动solr
```
kubectl apply -f solr.yaml
```

# 遇到的问题
k8s的基础不懂，一切白搭。（建议先看动基础概念。。。）

所使用的zookeeper镜像为3.4.10，因此使用headless进行zookeeper集群访问，会出现单节点访问。

解决方案：
https://lucene.472066.n3.nabble.com/How-to-resolve-a-single-domain-name-to-multiple-zookeeper-IP-in-Solr-td4450236.html

或者指定访问形式：https://www.jianshu.com/p/257d1be4badd

（博客中最重要的话：除此之外，StatefulSet在Headless Service的基础上又为StatefulSet控制的每个Pod副本创建了一个DNS域名）


# 数据注入
```
# 进入pod
kubectl exec -it sdc-solr-0 -n sdc-solr bash 
# 创建collection
bin/solr create_collection -c cloudsuite_web_search -shards 3 -replicationFactor 3 -d /opt/solr/example/example-DIH/solr/solr/conf -p 8983
# 为collection加载数据
bin/post -c cloudsuite_web_search /opt/solr/example/exampledocs/*
```

# 访问流程

- solr中已开启nodePort（30002），使用masterIP：30002即可访问。
- http://192.168.1.105:30002/solr/#/~cores
>>>>>>> ssd model
- 访问链接：`http://192.168.1.105:30002/solr/cloudsuite_web_search/select?q=*:*`