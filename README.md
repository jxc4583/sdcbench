# SDCBench
我们主要是针对软件定义云计算系统提出了一套基于混合负载的基准测试程序，并在此基础之上开发实现了一套度量与评测系统-SDCBench1.0,与现有工作相比，SDCBench最大的特点是支持多种类型的在线离线应用混合部署和应用的负载强度调节，目前该基准测试程序包含在线服务应用7种，离线作业6种，在线应用的响应时间分布覆盖微秒、毫秒到秒级，离线应用包含CPU密集型，IO密集型，和综合型作业，该评测系统可用于对应用的性能和系统资源利用率的度量，并提供可视化展示界面，支持项目组其他课题提出的对应方案的效果评测与分析。
---

## 项目结构
<details>
<summary>展开查看</summary>
<pre><code>
SDCBench
|
├─── socialnetwork-func
|       ├── yaml-func
|       ├── yaml-db
├─── mongodb
|       ├── yaml
├─── solr
|       ├── yaml
├─── dnninference
|       ├── dssm-minclass
|       ├── half
|       ├── mobilenet
|       ├── resnet
|       ├── ssd
|       ├── textcnn
|       ├── yamnet
├─── tailbench
|       ├── img-dnn
|       ├── masstree
|       ├── xapian
├─── tpc-w
├─── cloudsuite
|       ├── memcached
</code></pre>
</details>
