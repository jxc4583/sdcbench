#!/bin/bash

#DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
#source ${DIR}/../configs.sh
QPS=500
export TBENCH_CLIENT_THREADS=1 # threads of client
export TBENCH_SERVER=172.17.0.1
export TBENCH_SERVER_PORT=8087
export TBENCH_QPS=${QPS} 
export TBENCH_MINSLEEPNS=100000 
export TBENCH_RANDSEED=5000
export TBENCH_TERMS_FILE=/home/tank/tailbench/database/terms.in 
./xapian_networked_client &

echo $! > client.pid

wait $(cat client.pid)

# Clean up
./kill_networked.sh
rm client.pid
