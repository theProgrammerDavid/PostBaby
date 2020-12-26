#include "ThreadPool.h"

ThreadPool pool(std::thread::hardware_concurrency());