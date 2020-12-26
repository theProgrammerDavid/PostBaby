#include "threadPool.hpp"

ThreadPool pool(std::thread::hardware_concurrency());