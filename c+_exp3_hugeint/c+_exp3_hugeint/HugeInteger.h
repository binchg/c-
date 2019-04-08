#pragma once
#include<iostream>
#include<string>
#include<math.h>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;

class Hugeinteger {
public:
	static const int n_max_size = 40;
	int n_dig_arr[n_max_size];
	int n_dig_size;
	int flag;
public:
	// 默认构造函数
	Hugeinteger() {
		memset(n_dig_arr, 0, sizeof n_dig_arr);
		n_dig_arr[0] = 0;
		n_dig_size = 1;
		flag = 0;
	}
	//string构造函数
	Hugeinteger(string str_n) {
		if (str_n[0] - '-' == 0) {
			flag = -1;
			str_n = str_n.substr(1);
		}
		else {
			flag = 0;
		}
		memset(n_dig_arr, 0, sizeof n_dig_arr);
		int l_str = str_n.length();
		for (int i = 0; i < l_str; i++) {
			
			n_dig_arr[i] = str_n[l_str - i - 1] - '0';
		}
		get_length();
	}
	//复制构造函数
	Hugeinteger(const Hugeinteger &H) {
		memcpy(n_dig_arr, H.n_dig_arr, sizeof H.n_dig_arr);
		n_dig_size = H.n_dig_size;
		flag = H.flag;

	}
	Hugeinteger(long long n) {
		if (n < 0) {
			flag = -1;
			n *= -1;
		}
		else flag = 0;
		memset(n_dig_arr, 0, sizeof n_dig_arr);
		for (n_dig_size = 0; n > 0; n_dig_size++) {
			n_dig_arr[n_dig_size] = n % 10;
			n /= 10;
		}
		get_length();
	}

	int get_length()
	{
		int leng = n_max_size;
		while (n_dig_arr[leng-1] == 0&&leng>=1) {
			leng--;
		}
		if (leng == 0) { leng = 1; flag = 0; }
		n_dig_size = leng;
		return leng;
	}
	bool operator <(const Hugeinteger& h)
	{
		//负 真
		if (flag < h.flag)
		{
			return true;
		}
		//正 假
		else if (flag > h.flag) {
			return false;
		}
		//当做正数比较
		bool f = false;
		//短真
		if (n_dig_size < h.n_dig_size) {
			f = true;
		}
		else if (n_dig_size > h.n_dig_size) {
			f = false;
		}
		else {
			for (int i = n_dig_size; i > 0; i--) {
				if (n_dig_arr[i - 1] == h.n_dig_arr[i - 1]) continue;
				else if (n_dig_arr[i - 1] > h.n_dig_arr[i - 1]) {
					f = false;
					break;
				}
				else {
					f = true;
					break;
				}
			}
		}
		//正负号影响，负号取反结果
		if (flag) {
			f = f*-1;
		}
		return f;
	}
	bool operator == (const Hugeinteger& h) {
		bool f=false;
		if (flag != h.flag)return f;
		if(n_dig_size!=h.n_dig_size)return f;
		for (int i = 0; i < n_dig_size; i++) {
			if (n_dig_arr[i] != h.n_dig_arr[i])return f;
		}
		return true;
	}
	bool operator <=(const Hugeinteger& h)
	{
		return ((*this == h)||(*this < h));
	}
	friend ostream &operator<<(ostream &output, const Hugeinteger &H)
	{
		if (H.flag)output << "-";
		for (int i = H.n_dig_size; i > 0; i--) {
			output << H.n_dig_arr[i - 1];
		}
		return output;
	}

	friend istream &operator >> (istream  &input, Hugeinteger &H)
	{
		string str_n;
		input >> str_n;
		if (str_n[0] - '-' == 0) {
			H.flag = -1;
			str_n = str_n.substr(1);
		}
		else
		{
			H.flag = 0;
		}
		memset(H.n_dig_arr, 0, sizeof H.n_dig_arr);
		int l_str = str_n.length();
		for (int i = 0; i < l_str; i++)
			H.n_dig_arr[i] = str_n[l_str - i - 1] - '0';
		H.get_length();
		return input;
	}
	void operator=(const Hugeinteger &H) {
		memcpy(n_dig_arr, H.n_dig_arr, sizeof H.n_dig_arr);
		n_dig_size = H.n_dig_size;
		flag = H.flag;
	}
	//正数+正数
	Hugeinteger add(const Hugeinteger& A, const Hugeinteger& H) {
		Hugeinteger h;
		for (int i = 0; i < A.n_max_size; i++) {
			int a = A.n_dig_arr[i];
			int b = H.n_dig_arr[i];
			int c = h.n_dig_arr[i];

			h.n_dig_arr[i] = a + b + c;
			int j = i;
			while (h.n_dig_arr[j] > 9)
			{
				h.n_dig_arr[j] -= 10;
				h.n_dig_arr[j + 1] += 1;
				j++;
			}
		}
		h.get_length();
		return h;
	}
	Hugeinteger operator+(string str_H)
	{
		Hugeinteger h = Hugeinteger(*this)+ Hugeinteger(str_H);
		return h;
	}
	Hugeinteger operator+(const Hugeinteger& H)
	{
		//同号
		if (flag == H.flag) {
			Hugeinteger h = add(*this, H);
			h.flag = flag;
			return h;
		}
		//后-
		else if(H.flag==-1&&flag==0) {
			Hugeinteger a(*this);
			Hugeinteger b(H);
			b.flag = 0;
			Hugeinteger h = a - b;
			return h;
		}
		//前-
		else {
			Hugeinteger a(*this);
			Hugeinteger b(H);
			a.flag = 0;
			Hugeinteger h = b - a;
			return h;
		}

	}
	//正大数-正小数
	Hugeinteger sub(Hugeinteger A, Hugeinteger H) {
		Hugeinteger c;
		Hugeinteger a(A);
		Hugeinteger b(H);
		for (int i = 0; i < a.n_dig_size || i < b.n_dig_size; i++) {
			if (a.n_dig_arr[i] < b.n_dig_arr[i]) {//如果不够减法，则向高位借位 
				if (a.n_dig_arr[i + 1] > 0) {
					a.n_dig_arr[i + 1]--;
					a.n_dig_arr[i] += 10;
				}
			}
			c.n_dig_arr[i] = a.n_dig_arr[i] - b.n_dig_arr[i];
		}
		c.get_length();
		return c;
	}
	Hugeinteger operator-() {
		Hugeinteger h(*this);
		if (h.flag)h.flag = 0;
		else h.flag = -1;
		h.get_length();
		return h;
	}
	Hugeinteger operator-(const Hugeinteger& H)
	{
		Hugeinteger c;
		//- - -
		if (flag == -1&& H.flag == -1) {
			Hugeinteger a(*this);
			Hugeinteger b(H);
			a.flag = 0;
			b.flag = 0;
			c = a - b;
			//取反
			return -c;
		}
		//- - +
		else if(flag == -1) {
			Hugeinteger a(*this);
			Hugeinteger b(H);
			a.flag = 0;
			c = a + b;
			c.flag = -1;
			c.get_length();
			return c;
		}
		//+ - -
		else if (H.flag == -1) {
			Hugeinteger a(*this);
			Hugeinteger b(H);
			b.flag = 0;
			c = a + b;
			c.get_length();
			return c;
		}
		//+ - +
		if (Hugeinteger(*this) < H) {
			c = sub(H, *this);
			c.flag = -1;
		}
		else {
			c = sub(*this, H);
			c.flag = 0;
		}
		c.get_length();
		return c;
	}
	Hugeinteger POW(int n, int l) {
		Hugeinteger ptemp(n);
		Hugeinteger p("1");
		for (int i = 0; i < l; i++) {
			p = p*ptemp;
		}
		return p;
	}
	Hugeinteger operator*(const Hugeinteger& H)     //高精度乘法 
	{
		int sign = 1;
 
		if (flag == -1)sign *= -1;
		if (H.flag == -1)sign *= -1;

		Hugeinteger total;//记录当前值
		int L1 = n_dig_size;
		int L2 = H.n_dig_size;
		for (int i = 0; i < L2; i++) {
			for (int j = 0; j < L1; j++) {
				int temp;
				Hugeinteger t;
				temp = n_dig_arr[j] * H.n_dig_arr[i];
				int x = 0;
				while (temp) {
					if (i + j + x > 39)break;
					t.n_dig_arr[i+j+x] = temp % 10;
					temp /= 10;
					x++;
				}
				t.get_length();
				t.flag = 0;
				total = total + t;
			}
		}
		if (sign == -1)total.flag = -1;
		total.get_length();
		return total;
	}
	Hugeinteger operator/(const Hugeinteger& H) {
		if (Hugeinteger() == H)
			return Hugeinteger();
		int L1 = n_dig_size;
		int L2 = H.n_dig_size;
		if (L1 < L2)return Hugeinteger();

		int sign = 1;
		if (flag == -1)sign *= -1;
		if (H.flag == -1)sign *= -1;

		int d_len = L1 - L2;
		Hugeinteger a(*this);
		a.flag = 0;

		Hugeinteger b(H);
		b.flag = 0;

		Hugeinteger c;

		Hugeinteger btemp(H);
		btemp.flag = 0;

		for (int i = d_len; i >= 0; i--) {
			int temp = 0;
			btemp = b*POW(10, i);
			for (; btemp <= a; ) {
				a = a - btemp;
				temp++;
			}
			c = c + POW(10, i)*temp;
		}
		if (sign == -1)c.flag = -1;
		c.get_length();
		return c;

	}
	Hugeinteger operator%(const Hugeinteger& H) {
		if (Hugeinteger() == H)
			return Hugeinteger();
		Hugeinteger a(*this); 
		Hugeinteger b(H);
		Hugeinteger c;
		Hugeinteger temp = a/b;
		c = a - b*temp;
		return c;
	}

	~Hugeinteger()
	{
		memset(n_dig_arr, 0, sizeof n_dig_arr);
		n_dig_size = 0;
	}
};