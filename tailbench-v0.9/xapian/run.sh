#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
source ${DIR}/../configs.sh

NSERVERS=1
QPS=500
WARMUPREQS=1000
REQUESTS=3000

TBENCH_QPS=${QPS} TBENCH_MAXREQS=${REQUESTS} TBENCH_WARMUPREQS=${WARMUPREQS} \
       TBENCH_MINSLEEPNS=100000 TBENCH_TERMS_FILE=${DATA_ROOT}/xapian-1.4.4/terms.in \
       chrt -r 99 ./xapian_integrated -n ${NSERVERS} -d /home/tank/jxc/tailbench/imgdnn/tailbench-v0.9/xapian-1.4.4/wiki -r 1000000000
#/home/tank/jxc/tailbench/imgdnn/tailbench-v0.9/xapian-1.4.4/wiki

# ${DATA_ROOT}/xapian-1.4.4/wiki
