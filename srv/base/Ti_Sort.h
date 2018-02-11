/**
 * Created by suli on 18/2/4.
 */

#ifndef ALGO_BASE_SORT_H
#define ALGO_BASE_SORT_H

#include <iostream>
#include <vector>

namespace TiAlloy {
enum {
	QUICK_SORT,
	MERGE_SORT,
	HEADP_SORT
};
template<typename T>
class sort_base {
	typedef std::vector <T> Data;
 public:
	sort_base() {}
	~sort_base() {}
 public:
	void quick_sort(std::vector <T> &v, int b, int e) {
		if (b >= e) {
			return;
		}
		int low = b;
		int hight = e;
		T key = v[low];
		while (low < hight) {
			while (low < hight && v[hight] >= key) {
				hight--;
			}
			v[low] = v[hight];
			while (low < hight && v[low] <= key) {
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

	void heap_sort(Data &v) {
		//TODO
	}
 private:
	void merge(Data &v, int low, int mid, int hight) {
		Data tmp;
		int l = low;
		int h = mid + 1;
		//数据
		while (l <= mid && h <= hight) {
			if (v[l] < v[h]) {
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

template<typename T>
bool sort(std::vector <T> &v, int type = QUICK_SORT) {
	sort_base<T> sort;
	switch (type) {
		case MERGE_SORT:
			sort.merge_sort(v, 0, v.size());
			break;
		case HEADP_SORT:
			break;
		default:
			sort.quick_sort(v, 0, v.size());
			break;
	}
}
}

#endif //ALGO_BASE_SORT_H
