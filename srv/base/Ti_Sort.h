/**
 * Created by suli on 18/2/4.
 */

#ifndef ALGO_BASE_SORT_H
#define ALGO_BASE_SORT_H

#include <iostream>
#include <vector>

namespace TiAlloy {

class Equal {
 public:
	int operator()(int a, int b) {
		return a - b;
	}
};

enum {
	QUICK_SORT,
	MERGE_SORT,
	HEADP_SORT
};
template<typename T, typename Eq>
class Ti_Sort {
	typedef std::vector <T> Data;
 public:
	Ti_Sort() {}
	~Ti_Sort() {}
 public:
	void quick_sort(std::vector <T> &v, int b, int e) {
		if (b >= e) {
			return;
		}
		int low = b;
		int hight = e;
		T key = v[low];
		while (low < hight) {
			while (low < hight && equal(v[hight], key) > 0) {
				hight--;
			}
			v[low] = v[hight];
			while (low < hight && equal(v[low], key) < 0) {
				low++;
			}
			v[hight] = v[low];
		}
		v[low] = key;
		quick_sort(v, b, low - 1);//切分左边
		quick_sort(v, low + 1, e);//切分右边
	}

	void merge_sort(Data &v, int b, int e) {
		if (b < e) {
			int mid = (b + e) / 2;
			merge_sort(v, b, mid);
			merge_sort(v, mid + 1, e);
			merge(v, b, mid, e);
		}
	}
	void heap_sort(Data &v, int len) {
		for (int i = len / 2 - 1; i >= 0; i--) {
			adjust_head(v, i, len);
		}
		for (int i = len - 1; i >= 1; i--) {
			T temp = v[0];
			v[0] = v[i];
			v[i] = temp;
			adjust_head(v, 0, i);
		}
		return;
	}
 private:
	Eq equal;
	//堆的调整,首先对比节点和左节点的大小,进而对比右节点的大小,
	// 得到最大或者最小,然后swap节点和最大或最小节点,递归完成调整
	void adjust_head(Data &v, int idx, int len) {
		int left = idx * 2 + 1;
		int right = left + 1;
		int largest = idx;

		if (left < len && equal(v[left], v[idx]) > 0) {
			largest = left;
		}

		if (right < len && equal(v[largest], v[right]) < 0) {
			largest = right;
		}

		if (largest != idx) {
			T temp = v[largest];   //较大的节点值将交换到其所在节点的父节点
			v[largest] = v[idx];
			v[idx] = temp;
			adjust_head(v, largest, len); //递归遍历
		}
	}
	void merge(Data &v, int low, int mid, int hight) {
		Data tmp;
		int l = low;
		int h = mid + 1;
		//数据
		while (l <= mid && h <= hight) {
			if (equal(v[l], v[h]) < 0) {
				tmp.push_back(v[l]);
				l++;
			} else {
				tmp.push_back(v[h]);
				h++;
			}
		}
		while (l <= mid) {
			tmp.push_back(v[l]);
			l++;
		}
		while (h <= hight) {
			tmp.push_back(v[h]);
			h++;
		}
		int size = tmp.size();
		for (int i = 0; i < size; i++, low++) {
			v[low] = tmp[i];
		}
	}
};

template<typename T, typename Eq>
bool sort(std::vector <T> &v, int type = QUICK_SORT) {
	Ti_Sort <T, Eq> sort;
	switch (type) {
		case MERGE_SORT:
			sort.merge_sort(v, 0, v.size());
			break;
		case HEADP_SORT:
			sort.heap_sort(v, v.size());
			break;
		default:
			sort.quick_sort(v, 0, v.size());
			break;
	}
	return true;
}
}

#endif //ALGO_BASE_SORT_H
