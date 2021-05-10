# bigdataSort
> 单二进制可执行文件
## 安装
源码地址：https://github.com/XingwXiong/SDC_Bench

这里可用同级目录下的sort。

- 编译
```
cd ./sort-openmp/src/omp/sort-openmp
make clean # 清楚编译文件
make all
```
- 运行
```
cd ./sort-openmp/src/omp/sort-openmp/run
./single_thread ../dataset/test.data.01/ ./output/t.01.m.txt
```
- 加大数据量，增长运行时间
```
cd ./sort-openmp/src/omp/sort-openmp/dataset/test.data.01
for i in {1..70}  ; do   cat ha.txt >> h1.txt;   done
```
