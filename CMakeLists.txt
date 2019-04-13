cmake_minimum_required(VERSION 3.12)
project(Project2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-pthread")

add_executable(Project2 main.cpp Server.cpp Server.h MySerialServer.cpp MySerialServer.h ClientHandler.cpp ClientHandler.h MyTestClientHandler.cpp MyTestClientHandler.h Solver.cpp Solver.h CacheManager.cpp CacheManager.h FileCacheManager.cpp FileCacheManager.h StringReverser.cpp StringReverser.h OtherFunctions.cpp OtherFunctions.h Files.cpp Files.h State.cpp State.h ISearcher.cpp ISearcher.h Searchable.cpp Searchable.h ISearchable.cpp ISearchable.h Searcher.cpp Searcher.h SolverBestSearch.cpp SolverBestSearch.h SolverSearchCost.cpp SolverSearchCost.h Point.cpp Point.h Matrix.cpp Matrix.h BestFirstSearch.cpp BestFirstSearch.h DFS.cpp DFS.h Graph.cpp Graph.h MyClientHandler.cpp MyClientHandler.h BFS.cpp BFS.h Edge.cpp Edge.h MyParallelServer.cpp MyParallelServer.h MatrixFileCacheManager.cpp MatrixFileCacheManager.h AStarSearch.cpp AStarSearch.h Headers.h FileGenerator.cpp FileGenerator.h)