# sdcbench
文件位置：109节点 /home/tank/1_yiming/SDC/sn
需要的文件包括namespaces.yml，yaml-db和yaml-func目录，其余不需要

部署步骤：
1. 创建命名空间
kubectl apply -f ./namespaces.yml
2. 部署数据库和函数
kubectl apply -f yaml-db/
kubectl apply -f yaml-func/
3. 初始化数据库
curl -d 1 http://HOST-IP:30400
注：HOST-IP为主节点的IP，即向主节点的30400端口发送数据为1的POST请求

如何运行： 
1.调用协调器
curl -d X http://HOST-IP:30300
注：HOST-IP为主节点的IP，X为正整数，即向主节点的30300端口发送数据为正整数的POST请求，X最好不重复
2. 清理已有结果
curl -d 2 http://HOST-IP:30400
注：HOST-IP为主节点的IP，即向主节点的30400端口发送数据为2的POST请求
