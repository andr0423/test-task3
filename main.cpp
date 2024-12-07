#include <netinet/in.h>
#include <iostream>
#include <thread>
#include <chrono>

#include "common/client_udp.h"
#include "common/server_udp.h"

int THR_DEFAULT = 16;

using namespace std;

int main( int argc, char* argv[] ){

//  int gth = (argc == 2) ? atoi(argv[1]) : -1;
//  int THR = (0 < gth && gth < 255) ? gth : THR_DEFAULT;
    int THR = (argc == 2) ? ((atoi(argv[1]))? atoi(argv[1]) : THR_DEFAULT) : THR_DEFAULT;

    const int PORT_SRV = 34567;

    cout << "==== ==== test-task3 is running = ==== ==== ====" << endl;
    cout << "==== ==== threads: " << THR << endl;

    ServerUdp * srv = new ServerUdp( PORT_SRV, INADDR_LOOPBACK, 0, "main.log" );
    thread th_server( &ServerUdp::start, srv);
    th_server.detach();

    ClientUdp * clnt[THR];
    thread * thrds[THR];

    for ( int i ; i < THR ; i++ ) {
        cout << "==== i=" << i << endl;
        clnt[i] = new ClientUdp( PORT_SRV, INADDR_LOOPBACK, (unsigned char) i );
        thrds[i] = new thread ( &ClientUdp::start, clnt[i] );
    }

    for ( auto th : thrds ){
        th->join();
    }

    cout << "==== ==== threads: " << THR << endl;
    cout << "==== ==== all threads are over == ==== ==== ====" << endl;
    sleep(3);
    srv->stop();

    delete srv;

    for ( int i; i < THR ; i++){
        delete clnt[i];
        delete thrds[i];
    }

    cout << "==== ==== test-task3 is completed ==== ==== ====" << endl;

    return 0;
}
