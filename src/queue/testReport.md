g++ -g main.cpp -std=c++11 -lpthread  

init time ./a.out
real    0m18.129s
user    0m34.508s
sys     0m1.732s

with _writeIndex.store(next_tail,std::memory_order_release); 
real    0m16.701s
user    0m31.808s
sys     0m1.576s


with auto cur_read = _readIndex.load(std::memory_order_acquire);
     auto cur_write = _writeIndex.load(std::memory_order_acquire);

real    0m15.913s
user    0m30.572s
sys     0m1.252s
