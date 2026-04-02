#include <iostream>
#include <string>
#include <vector>

// BF算法，时间复杂度O(n*m)，空间复杂度O(1)
int BF(const std::string& s, const std::string& t)
{
	if (t.empty()) return 0;
	if (s.empty() || size(s) < size(t)) return -1;

	int i = 0;
	int j = 0;
	int size_s = size(s);		// 主串长度
	int size_t = size(t);		// 子串长度

	while (i < size_s && j < size_t) {
		if (s[i] == t[j]) {
			i++;
			j++;
		}
		else {
			i = i - j + 1;
			j = 0;
		}
	}
	if (j == size_t)
		return i - j;

	return -1;
}

// next数组，时间复杂度O(m)，空间复杂度O(m)
std::vector<int> GetNext(const std::string& str)
{
	int len = size(str);
	if (len == 0) return {};

	std::vector<int> next(len);
	int j = 0;			// 子串索引
	int k = -1;			// 公共前后缀长度
	next[j] = k;

	while (j < len - 1) {
		if (k == -1 || str[j] == str[k]) {
			j++;
			k++;

			// 算法优化，进一步回退
			if (str[j] == str[k]) {
				next[j] = next[k];
			}
			else {
				next[j] = k;
			}
		}
		else {
			k = next[k];
		}
	}
	return next;
}

// KMP算法 总时间复杂度O(n + m) 总空间复杂度O(m)
int KMP(const std::string& s, const std::string& t)
{
	if (t.empty()) return 0;
	if (s.empty() || size(s) < size(t)) return -1;

	int i = 0;
	int j = 0;
	// 将无符号整数转为整数，防止while循环出错
	int size_s = size(s);		// 主串长度
	int size_t = size(t);		// 子串长度
	std::vector<int> next = GetNext(t);

	while (i < size_s && j < size_t) {
		if (j == -1 || s[i] == t[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
	}
	if (j == size_t)
		return i - j;

	return -1;
}

int main()
{
	std::string s = "ABCBADBBCADBCAA";
	std::string t = "BCA";

	int pos = KMP(s, t);
	std::cout << pos << std::endl;
}