#include <iostream>

// 桶的状态
enum State
{
	STATE_UNUSE,		// 没使用的桶
	STATE_USING,		// 使用的桶
	STATE_DEL			// 使用过但处于删除状态的桶
};

// 桶结构
struct Bucket
{
	Bucket(int key = 0, State state = STATE_UNUSE)
		: key_(key)
		, state_(state)
	{}

	int key_;			// 桶里的值
	State state_;		// 桶的状态
};

// 线性探测哈希表
class HashTable
{
public:
	HashTable(int size = primes_[0], double loadFactor = 0.75)
		: useBucketNum_(0)
		, loadFactor_(loadFactor)
		, primeIdx_(0)
	{
		if (size != primes_[0])
		{
			for (; primeIdx_ < PRIME_SIZE; primeIdx_++)
			{
				if (primes_[primeIdx_] >= size)
				{
					break;
				}
			}

			// 边界保护
			if (primeIdx_ == PRIME_SIZE)
			{
				primeIdx_--;
			}
		}

		tableSize_ = primes_[primeIdx_];
		table_ = new Bucket[tableSize_];
	}

	~HashTable()
	{
		delete[] table_;
		table_ = nullptr;
	}

public:
	// 增加元素
	bool insert(int key)
	{
		double factor = useBucketNum_ * 1.0 / tableSize_;
		std::cout << "factor: " << factor << std::endl;
		if (factor > loadFactor_)
		{
			// 扩容
			expand();
		}

		int idx = key % tableSize_;
		
		int i = idx;
		do
		{
			if (table_[i].state_ != STATE_USING)
			{
				table_[i].key_ = key;
				table_[i].state_ = STATE_USING;
				useBucketNum_++;
				return true;
			}
			i = (i + 1) % tableSize_;
		} while (i != idx);

		return false;
	}

	// 删除元素
	bool erase(int key)
	{
		int idx = key % tableSize_;

		int i = idx;
		do
		{
			if (table_[i].state_ == STATE_USING && table_[i].key_ == key)
			{
				table_[i].state_ = STATE_DEL;
				useBucketNum_--;
			}
			i = (i + 1) % tableSize_;
		} while (table_[i].state_ != STATE_UNUSE && i != idx);

		return true;
	}

	// 查询元素
	bool find(int key)
	{
		int idx = key % tableSize_;

		int i = idx;
		do
		{
			if (table_[i].state_ == STATE_USING && table_[i].key_ == key)
			{
				return true;
			}
			i = (i + 1) % tableSize_;
		} while (table_[i].state_ != STATE_UNUSE && i != idx);

		return false;
	}
private:
	void expand()
	{
		++primeIdx_;
		if (primeIdx_ == PRIME_SIZE)
			throw "The HashTable is too large, can not expand anymore!";

		Bucket* newTable = new Bucket[primes_[primeIdx_]];
		for (int i = 0; i < tableSize_; i++)
		{
			if (table_[i].state_ == STATE_USING)
			{
				int idx = table_[i].key_ % primes_[primeIdx_];

				int k = idx;
				do
				{
					if (newTable[k].state_ != STATE_USING)
					{
						newTable[k].key_ = table_[i].key_;
						newTable[k].state_ = STATE_USING;
						break;
					}
					k = (k + 1) % primes_[primeIdx_];
				} while (k != idx);
			}
		}

		delete[] table_;
		table_ = newTable;
		tableSize_ = primes_[primeIdx_];
	}
private:
	Bucket* table_;			// 指向开辟的哈希表
	int tableSize_;			// 哈希表的大小
	int useBucketNum_;		// 已使用的桶数量
	double loadFactor_;		// 负载因子

	static const int PRIME_SIZE = 10;	// 素数表的大小
	static int primes_[PRIME_SIZE];		// 素数表
	int primeIdx_;						// 当前素数表索引
};

int HashTable::primes_[PRIME_SIZE] = { 3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773 };		// 类外定义素数表

int main()
{
	HashTable htable;
	htable.insert(15);
	htable.insert(23);
	htable.insert(45);
	htable.insert(178);
	htable.insert(10);
	htable.insert(23);

	std::cout << htable.find(45) << "\n";
	htable.erase(45);
	std::cout << htable.find(45) << "\n";

}