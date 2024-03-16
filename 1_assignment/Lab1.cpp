#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
class Lab1 {
	struct Elements {
		std::string date;
		size_t win;
		size_t number;
		size_t cost;
	};

	friend bool operator== (const Elements& c1, const Elements& c2) {
		if (c1.date == c2.date) {
			if (c1.win == c2.win) {
				if (c1.number == c2.number) {
					return true;
				}
			}
		}
		return false;
	}
	friend bool operator >(const Elements& c1, const Elements& c2) {
		if (std::strcmp(c1.date.c_str(), c2.date.c_str()) < 0) {
			return false;
		}
		if (std::strcmp(c1.date.c_str(), c2.date.c_str()) > 0) {
			return true;
		}
		if (std::strcmp(c1.date.c_str(), c2.date.c_str()) == 0) {
			if (c1.win < c2.win) {
				return true;
			}
			if (c1.win > c2.win) {
				return false;
			}
			if (c1.win == c2.win) {
				if (c1.number > c2.number) {
					return true;
				}
				if (c1.number < c2.number) {
					return false;
				}
			}
		}
		return false;
	}
	friend bool operator <(const Elements& c1, const Elements& c2) {
		if (c1 == c2) {
			return false;
		}
		return !(c1 > c2);
	}
	friend bool operator >=(const Elements& c1, const Elements& c2) {
		if (c1 == c2) {
			return true;
		}
		return c1 > c2;

	}
	friend bool operator <=(const Elements& c1, const Elements& c2) {
		if (c1==c2) {
			return true;
		}
		return c1 < c2;
	}

	std::vector<Lab1::Elements> data;

public:
	std::string filename;
	Lab1() = default;
	Lab1(std::string namefile);
	uint64_t bubbleSort();
	uint64_t selectionSort();
	void heapify(size_t n, size_t i);
	uint64_t heapSort();
	void output();
	~Lab1() = default;
};
Lab1::Lab1(std::string namefile)
{
	std::ifstream inf;
	filename = namefile;
	inf.open(namefile);
	if (!inf.is_open())
	{
		std::cerr << "The file could not be opened for reading!\n";
	} 
	std::string s;
	while (std::getline(inf, s)) {
		Lab1::Elements obj;
		size_t i = 0;
		bool flag = 1;
		std::string num;
		while (flag) {
			if (s[i] == ' ') {
				flag = 0;
				i++;
				break;
			}
			else {
				num += s[i];
				i++;
			}
		}
		obj.number = std::stoi(num.c_str());
		std::string cost;
		flag = 1;
		while (flag) {
			if (s[i] == ' ') {
				flag = 0;
				i++;
				break;
			}
			else {
				cost += s[i];
				i++;
			}
		}
		obj.cost = std::stoi(cost.c_str());
		std::string date;
		flag = 1;
		while (flag) {
			if (s[i] == ' ') {
				flag = 0;
				i++;
				break;
			}
			else {
				date += s[i];
				i++;
			}
		}
		obj.date = date;
		flag = 1;
		std::string sum;
		while (flag) {
			if (i==s.size()) {
				flag = 0;
				break;
			}
			else {
				sum += s[i];
				i++;
			}
		}

		obj.win = std::stoi(sum.c_str());
		data.push_back(obj);
	}
	inf.close();
}
uint64_t Lab1::bubbleSort()
{
	auto begin = std::chrono::steady_clock::now();

	this->filename = "BubbleSort'ed_" + this->filename;

	size_t len = data.size();
	while (len--)
	{
		bool swapped = false;

		for (size_t i = 0; i < len; i++)
		{
			if (data[i] > data[i + 1])
			{
				std::swap(data[i], data[i + 1]);
				swapped = true;
			}
		}

		if (swapped == false)
			break;
	}

	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	return elapsed_ms.count();
}
uint64_t Lab1::selectionSort() {

	auto begin = std::chrono::steady_clock::now();

	this->filename = "SelectionSort'ed_" + this->filename;

	size_t i, j, min_idx;
	for (i = 0; i < data.size() - 1; i++)
	{
		min_idx = i;
		for (j = i + 1; j < data.size(); j++)
		{
			if (data[j] < data[min_idx])
				min_idx = j;
		}
		if (min_idx != i)
			std::swap(data[min_idx], data[i]);
	}

	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	return elapsed_ms.count();
}
void Lab1::heapify(size_t n,size_t i) {

	size_t largest = i;
	size_t l = 2 * i + 1;
	size_t r = 2 * i + 2;

	if (l < n && data[l] > data[largest])
		largest = l;

	if (r < n && data[r] > data[largest])
		largest = r;
	if (largest != i)
	{
		std::swap(data[i], data[largest]);
		heapify( n, largest);
	}
}
uint64_t Lab1::heapSort() {

	auto begin = std::chrono::steady_clock::now();

	this->filename = "HeapSort'ed_" + this->filename;
	
	for (int i = data.size() / 2 - 1; i >= 0; i--) {
		heapify(data.size(), i);
	}
	for (int i = data.size() - 1; i >= 0; i--)
	{
		std::swap(data[0], data[i]);
		heapify(i, 0);
	}

	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	return elapsed_ms.count();
}
void Lab1::output()
{
	std::ofstream out;
	out.open(filename);
	if (out.is_open())
	{
		for (auto& it : data) {
			out << it.number << " " << it.cost << " " << it.date << " " << it.win << "\n";
		}
	}
}
int main() {
	std::string m[7]={"100.txt","1000.txt","5000.txt","10000.txt","20000.txt","40000.txt","100000.txt"};
	for (int i=0;i<7;i++) {
		if (i < 7) {
			std::string p = m[i % 7];
			Lab1 v(p);
			uint64_t time = v.heapSort();
			v.output();
			std::cout << "The time heapSort " << p << ": " << time << " ms\n";
		}
		if (i >= 7 && i < 14) {
			std::string p = m[i % 7];
			Lab1 v(p);
			uint64_t time = v.bubbleSort();
			v.output();
			std::cout << "The time bubbleSort " << p << ": " << time << " ms\n";
		}
		if (i >= 14) {
			std::string p = m[i % 7];
			Lab1 v(p);
			uint64_t time = v.selectionSort();
			v.output();
			std::cout << "The time selSort " << p << ": " << time << " ms\n";
		}
	}
}
