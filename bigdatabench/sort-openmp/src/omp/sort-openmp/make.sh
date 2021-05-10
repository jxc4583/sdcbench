#!/bin/bash

#gcc -MM *.c*

>make.2.txt
#make s_th 2>>make.2.txt
make all 2>>make.2.txt
#make m_th 2>>make.2.txt
echo ""
wc -l make.2.txt

