#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <stdexcept>

class HashTable
{
public:
	HashTable(int size = primes_[0], double loadFactor = 0.75)		
		: elementNum_(0)
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

			if (primeIdx_ == PRIME_SIZE)
			{
				primeIdx_ = PRIME_SIZE - 1;
			}
		}

		table_.resize(primes_[primeIdx_]);
	}

	~HashTable() = default;

public:
	// 增加元素 不含重复元素
	void insert(int key)
	{
		// 计算扩容后的理论负载因子
		double factor = (elementNum_ + 1) * 1.0 / table_.size();

		/*
		std::cout << "未扩容负载因子: " << factor << std::endl;
		*/

		if (factor > loadFactor_)
		{
			expand();

			/*
			double factor = (elementNum_ + 1) * 1.0 / table_.size();
			std::cout << "扩容后负载因子: " << factor << std::endl;
			*/
		}

		int idx = hash(key);

		auto it = std::find(table_[idx].begin(), table_[idx].end(), key);

		if (it == table_[idx].end())
		{
			table_[idx].emplace_front(key);
			elementNum_++;
		}
	}

	// 删除元素
	void erase(int key)
	{
		int idx = hash(key);

		auto it = std::find(table_[idx].begin(), table_[idx].end(), key);

		if (it != table_[idx].end())
		{
			table_[idx].erase(it);
			elementNum_--;
		}
	}

	// 查找元素
	bool find(int key) const
	{
		int idx = hash(key);

		auto it = std::find(table_[idx].begin(), table_[idx].end(), key);
		
		return it != table_[idx].end();
	}
private:

	// 哈希函数
	int hash(int key) const
	{
		int idx = key % (int)table_.size();

		if (idx < 0)
		{
			idx += table_.size();
		}

		return idx;
	}

	// 扩容函数
	void expand()
	{
		primeIdx_++;
		if (primeIdx_ == PRIME_SIZE)
		{
			throw std::overflow_error("HashTable can not expand anymore!");
		}

		std::vector<std::list<int>> swapTable;
		table_.swap(swapTable);

		table_.resize(primes_[primeIdx_]);

		for (const auto& list : swapTable)
		{
			for (int key : list)
			{
				int idx = hash(key);

				table_[idx].emplace_front(key);
			}
		}
	}
private:
	std::vector<std::list<int>> table_;		// 链表数组
	int elementNum_;						// 元素数量
	double loadFactor_;						// 负载因子

	static const int PRIME_SIZE = 10;		// 素数表的大小
	static int primes_[PRIME_SIZE];			// 素数表
	int primeIdx_;							// 当前素数表索引
};

int HashTable::primes_[PRIME_SIZE] = { 3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773 };		// 类外定义素数表

int main()
{
	HashTable htable;
	htable.insert(15);
	htable.insert(23);
	htable.insert(45);
	htable.insert(178);
	htable.insert(-5);
	htable.insert(-75);
	htable.insert(-19);
	htable.insert(-58);
	htable.insert(23);

	std::cout << htable.find(45) << "\n";
	htable.erase(45);
	std::cout << htable.find(45) << "\n";

	std::cin.get();
}