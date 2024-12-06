#ifndef __STACK_H__
#define __STACK_H__
#pragma once
#include <iostream>
using namespace std;
template <class T>
class Stack
{
private:
	T* begin;
	int end;
	int size;
public:
	Stack(){
		end = -1;
		size = 1;
		begin = new T[size];
	}
	Stack(int _n){
		if(_n > 0){
			size = _n;
			end = -1;
			begin = new T[size];
		}
		else throw "negative size";
	}
	Stack(const Stack& _A){
		size = _A.size;

		begin = new T[size];
		for(int i = 0; i < size;i++){
			begin[i] = _A.begin[i];
		}
		end = _A.end;
	}
	~Stack(){
		delete[] begin;
	}
	void Push(T a){
		if(end != size - 1){
			end++;
			begin[end] = a;
		}
		else{
			T* arr = new T[size];
			std::copy(begin, begin + size, arr);
			delete[] begin;

			size  *= 2;
			begin = new T[size];
			std::copy(arr,arr + size / 2, begin);

			end++;
			begin[end] = a;
		}
	}
	T top(){
		if(!empty()){
			return begin[end];
		}
		else throw -1;
	}
	T pop(){
		T ans = begin[end];
		end--;
		return ans;
	}
	bool empty(){
		return end == -1;
	}
	int Size(){
		return end + 1;
	}
	bool operator==(Stack<T>& a){
		if(size == a.size && end == a.end){
			for(int i = 0; i < size;i++){
				if(begin[i] != a.begin[i]){
					return false;
				}
			}
		}
		else return false;
		return true;
	}
	friend ostream& operator<<(ostream& out, const Stack& a) {
		for (int i = 0; i <= a.end; i++)
			out << a.begin[i] << ' ';
		return out;
	}
};
#endif