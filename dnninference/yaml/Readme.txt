每个应用对应的k8s nodePort为：
resnet-59 30100
bert 30101
dssm-minclass-2365 30102
half 30103
mobilenet 30104
ssd 30105
textcnn-69 30106
yamnet 30107

1. 准备模型文件
假如模型文件存储目录为 /usr/local/sdcbench/dnninference/models
则修改每个模型的yml文件中Path路径，在yml文件的最后一行
例如  path: /mnt/sdcbench/dnninference/models/resnet-50 改为  path: /usr/local/sdcbench/dnninference/models/resnet-50

2. 创建namespace
cd dnninference
kubectl apply -f sdc-dnninference-namespace.yml

3. 创建推理应用，以resnet-50为例，yml文件中默认定义了副本为3
kubectl apply -f resnet-50/sdc-dnninference-resnet-50-rs.yml

注：在每个模型的replicaSet定义的yml文件中，可以指定节点进行部署，具体修改 nodeName: tank-node2 --> nodeName: xxx ，xxx为你的环境下k8s节点。
