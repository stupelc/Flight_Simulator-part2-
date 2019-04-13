#include <iostream>
#include <string>
#include "Headers.h"

using namespace std;

namespace boot {
    class Main {
    public:
        int main(int argc, char *argv[]) {
            return 0;
        }
    };
}

int main(int argc, char *argv[]) {
    boot::Main m;
    m.main(argc, argv);
    server_side::Server *server = new MyParallelServer();
    Solver<ISearchable<Point> *, string> *solver = new SolverBestSearch<Point>(new AStarSearch<Point>());
    FileCacheManager *cacheManager = new FileCacheManager("solutionsTest.txt");
    ClientHandler *clientHandler = new MyClientHandler<ISearchable<Point> *, string>(solver, cacheManager);
    server->open(stoi(argv[1]), clientHandler);

    delete server;
    delete solver;
    delete cacheManager;
    delete clientHandler;

    return 0;
}