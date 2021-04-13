#include <cstring>
#include <iostream>
#include <sstream>

#include <assert.h>
#include <unistd.h>

#include "server.h"
#include "tbench_server.h"

using namespace std;

unsigned long Server::numReqsToProcess = 0;
volatile atomic_ulong Server::numReqsProcessed(0);
pthread_barrier_t Server::barrier;

Server::Server(int id, string dbPath) 
    : db(dbPath)
    , enquire(db)
    , stemmer("english")
    , id(id)
{
    //Xapian::Database db6(Xapian::Remote::open("192.168.1.128",8009));
    //   db1.add_database(db6);
    enquire=Xapian::Enquire(db);
    parser.set_database(db);

    parser.set_default_op(Xapian::Query::OP_OR);
    parser.set_stemmer(stemmer);
    parser.set_stemming_strategy(Xapian::QueryParser::STEM_SOME);
}

Server::~Server() {
}

void Server::_run() {
    pthread_barrier_wait(&barrier);

    tBenchServerThreadStart();

    while (numReqsProcessed < numReqsToProcess) {
       processRequest();
       ++numReqsProcessed;
    }
}

void Server::processRequest() {
    const unsigned MAX_TERM_LEN = 5000;
    char term[MAX_TERM_LEN];
    void* termPtr;

    size_t len = tBenchRecvReq(&termPtr);
    memcpy(reinterpret_cast<void*>(term), termPtr, len);
    term[len] = '\0';

    unsigned int flags = Xapian::QueryParser::FLAG_DEFAULT;
    Xapian::Query query = parser.parse_query(term, flags);
    enquire.set_query(query);
    mset = enquire.get_mset(0, MSET_SIZE);

    const unsigned MAX_RES_LEN = 1 << 20; 
    char res[MAX_RES_LEN];

    unsigned resLen = 0;
    unsigned doccount = 0;
    const unsigned MAX_DOC_COUNT = 1; // up to 25 results per page
    for (auto it = mset.begin(); it != mset.end(); ++it) {
        std::string desc = it.get_document().get_description();
       // resLen += desc.size();
        resLen += 1;//防止溢出
        assert(resLen <= MAX_RES_LEN);
        memcpy(reinterpret_cast<void*>(&res[resLen]), desc.c_str(), 1);

        if (++doccount == MAX_DOC_COUNT) break;
    }

    tBenchSendResp(reinterpret_cast<void*>(res), resLen);
}

void* Server::run(void* v) {
    Server* server = static_cast<Server*> (v);
    server->_run();
    return NULL;
}

void Server::init(unsigned long _numReqsToProcess, unsigned numServers) {
    numReqsToProcess = _numReqsToProcess;
    pthread_barrier_init(&barrier, NULL, numServers);
}

void Server::fini() {
    pthread_barrier_destroy(&barrier);
}
