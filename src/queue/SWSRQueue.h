#include <atomic>
#include <iostream>

template<typename T>
class SWSRQueue{
public:
	SWSRQueue(uint32_t size):_readIndex(0),_writeIndex(0),_size(size){
		_record = new T[size];
	};
	bool push(const T& t){
		auto cur_read = _readIndex.load(std::memory_order_seq_cst);
		auto cur_write = _writeIndex.load(std::memory_order_seq_cst);

		//is full
		auto next_tail = (cur_write+1) % _size;
		if(next_tail == cur_read){
			return false;
		}

		_record[cur_write] = t;

		_writeIndex.store(next_tail,std::memory_order_seq_cst);

		return true;
	};

	bool pop(T&t){
		auto cur_read = _readIndex.load(std::memory_order_seq_cst);
		auto cur_write = _writeIndex.load(std::memory_order_seq_cst);

		//is empty
		if(cur_read == cur_write){
			return false;
		}

		t = _record[cur_read];
		_readIndex.store( (cur_read+1)%_size,std::memory_order_seq_cst);
		return true;

	};

private:
	std::atomic<unsigned int> _readIndex;
	std::atomic<unsigned int> _writeIndex;

	unsigned int _size;

	T* _record;
};

