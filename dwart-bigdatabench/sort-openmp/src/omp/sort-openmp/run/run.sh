#!/bin/bash

./multi_thread ../dataset/test.data.01/test.data.01.txt ./output/m.f 3
mkdir ./output/m.d
./multi_thread ../dataset/test.data.01/ ./output/m.d 3

./single_thread ../dataset/test.data.01/test.data.01.txt ./output/s.f
mkdir ./output/s.d
./single_thread ../dataset/test.data.01/ ./output/s.d

