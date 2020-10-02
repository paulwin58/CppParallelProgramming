#include <thread>
#include "SWSRQueue.h"

SWSRQueue<int> *queue;

const int size=100000000;
void consume(){
    for(int i = 0; i < size; ++i){
    	while(!queue->pop(i)){
            sched_yield();
	    }
    }
}

void produce(){
    for(int i = 0; i < size; ++i){
        while(!queue->push(i)){
            sched_yield();
        }
    }
}


int main(){

    queue = new SWSRQueue<int>(100);
    std::thread t1(consume);
    std::thread t2(produce);

    t1.join();
    t2.join();
    return 0;

}
