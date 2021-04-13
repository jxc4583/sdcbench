#!/bin/bash

#DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
#source ${DIR}/../configs.sh

NSERVERS=1 # threads of server
WARMUPREQS=1000
REQUESTS=3000
export TBENCH_SERVER=172.17.0.1
export TBENCH_SERVER_PORT=8087
export TBENCH_NCLIENTS=1 # num of clients
DATA_ROOT=/home/tank/tailbench/database/wiki
export TBENCH_MAXREQS=${REQUESTS} 
export TBENCH_WARMUPREQS=${WARMUPREQS} 
  ./xapian_networked_server -n ${NSERVERS} -d ${DATA_ROOT} \
    -r 1000000000 &
echo $! > server.pid


