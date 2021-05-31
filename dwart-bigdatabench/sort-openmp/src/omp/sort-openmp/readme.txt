to make:
cd src/omp/sort
make all

to help:
cd src/omp/sort/run
./multi_thread
./single_thread

to run: NOTE: thread_cnt is the last arg for multi_thread!
cd src/omp/sort/run
./multi_thread ../dataset/test.data.01/ ./output/t.01.s.txt 3
./single_thread ../dataset/test.data.01/ ./output/t.01.m.txt


