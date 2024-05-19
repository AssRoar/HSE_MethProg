#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <map>

class Lab2 {
    struct Elements {
        std::string date;
        size_t win;
        size_t number;
        size_t cost;
        
    };
    friend bool operator== (const Elements& c1, const Elements& c2) {
        if (c1.date == c2.date) {
            if (c1.win == c2.win) {
                if (c1.number == c1.number) {
                    return true;
                }
            }
        }
        return false;
    }
    friend bool operator >(const Elements& c1, const Elements& c2) {
        if (std::strcmp(c1.date.c_str(), c2.date.c_str()) == -1) {
            return false;
        }
        if (std::strcmp(c1.date.c_str(), c2.date.c_str()) == 1) {
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
                if (c1.number == c2.number) {
                    return false;
                }
            }
        }
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
        if (c1 == c2) {
            return true;
        }
        return c1 < c2;
    }

    std::vector<Lab2::Elements> data;

public:
    std::multimap<std::string, Lab2::Elements> dataMap;
    std::unordered_map<std::string, std::vector<Elements> > dateHashTable;
    std::string filename;
    Lab2() = default;
    Lab2(std::string namefile);
    void heapify(size_t n, size_t i) {

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
            heapify(n, largest);
        }
    }
    void heapSort() {

        for (int i = data.size() / 2 - 1; i >= 0; i--) {
            heapify(data.size(), i);
        }
        for (int i = data.size() - 1; i >= 0; i--)
        {
            std::swap(data[0], data[i]);
            heapify(i, 0);
        }
    }
    std::vector<int> LinearSearch(std::string key) {
        std::vector<int> res;
        for (size_t i = 0; i != data.size(); ++i) {
            if (data[i].date == key) {
                res.push_back(i);
            }
        }
        return res;
    }

    int getLowerBound(std::string key) {
        int mid = 0, left = 0, right = data.size();
        while (1)
        {
            mid = (left + right) / 2;

            if (mid < 0 || mid >= data.size())
                return -1;

            if (key <= data[mid].date)
                right = mid - 1;
            else if (key > data[mid].date && mid + 1 < data.size() && key == data[mid + 1].date)
                return mid+1;
            else if (key > data[mid].date)
                left = mid + 1;

            if (left > right)
                return -1;
        }
    }

    int getUpperBound(std::string key) {
        int mid = 0, left = 0, right = data.size();
        while (1)
        {
            mid = (left + right) / 2;

            if (mid < 0 || mid >= data.size())
                return -1;

            if (key < data[mid].date && mid - 1 >= 0 && key == data[mid - 1].date)
                return mid-1;
            else if (key < data[mid].date)
                right = mid - 1;
            else if (key >= data[mid].date)
                left = mid + 1;

            if (left > right)
                return -1;
        }
    }

    std::vector<int> binarySearch(std::string key) {
        int left = getLowerBound(key);
        int right = getUpperBound(key);
        std::vector<int> res;

        if (left == -1 || right == -1)
            return res;

        for (size_t i = left; i <= right; ++i) {
            res.push_back(i);
        }

        return res;
    }

    std::vector<Lab2::Elements> hashSearch(std::string date) {
    if (dateHashTable.find(date) != dateHashTable.end()) {
        return dateHashTable[date];
    } else {
        return std::vector<Elements>();  // Return empty vector if not found
    }
}
    ~Lab2() = default;
};

Lab2::Lab2(std::string namefile)
{
    std::ifstream inf(namefile);
    filename = namefile;

    if (!inf.is_open())
    {
        std::cerr << "The file (" << namefile << ")could not be opened for reading!\n";
    }
    std::string s;
    while (std::getline(inf, s)) {
        Lab2::Elements obj;
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
            if (i == s.size()) {
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
        dataMap.insert(make_pair(date,obj));
        dateHashTable[obj.date].push_back(obj);
    }
    inf.close();
}

int main() {
    std::string m[6] = { "100000.txt","200000.txt","300000.txt","400000.txt","500000.txt","600000.txt" };
    std::string m1[6] = { "HeapSort'ed_100000.txt","HeapSort'ed_200000.txt","HeapSort'ed_300000.txt","HeapSort'ed_400000.txt","HeapSort'ed_500000.txt","HeapSort'ed_600000.txt" };
    for (int i = 0; i < 6; ++i) {
        Lab2 v(m[i%6]);
        std::cout << "________________\n";
        auto begin = std::chrono::steady_clock::now();
        v.LinearSearch("1999/04/14");
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << "The time of linear search " << m[i % 7] << ": " << elapsed_ms.count() << " mc\n";



        Lab2 v1(m1[i%6]);
        begin = std::chrono::steady_clock::now();
        v1.binarySearch("1999/04/14");
        end = std::chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << "The time of binary search in sorted arrange " << m[i % 7] << ": " << elapsed_ms.count() << " mc\n";



        begin = std::chrono::steady_clock::now();
        v.heapSort();
        v.binarySearch("1999/04/14");
        end = std::chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << "The time of binary search in unsorted arrange " << m[i % 7] << ": " << elapsed_ms.count() << " mc\n";



        Lab2 v2(m[i % 6]);
        begin = std::chrono::steady_clock::now();
        v2.dataMap.equal_range("1999/04/14");
        end = std::chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << "The time of multimap " << m[i % 7] << ": " << elapsed_ms.count() << " mc\n";

        begin = std::chrono::steady_clock::now();
        v2.hashSearch("1999/04/14");
        end = std::chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << "The time of hash-table search " << m[i % 7] << ": " << elapsed_ms.count() << " mc\n";
    }
}
