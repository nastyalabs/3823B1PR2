#ifndef __LIST_H__
#define __LIST_H__

#pragma once
#include <iostream>
#include <string>
using namespace std;
template <typename T>
struct TNode {
	T value;
	string exps;
	TNode* next;
};
template <typename T>
class TList
{
	TNode<T>* head;
	size_t size;
public:
	TList() : head(nullptr), size(0) {}

	TList(const TList& a): head(nullptr), size(0) {
		if (a.head) {
			size_t i = 0;
			TNode<T>* tmp = a.head;
			while (tmp) {
				insert(i++, tmp->exps, tmp->value);
				tmp = tmp->next;
			}
		}
	}

	~TList() {
		while (head) {
			TNode<T>* tmp = head;
			head = head->next;
			delete tmp;
		}
	}

	bool isEmpty() const {
		return size == 0;
	}

	size_t getSize() const {
		return size;
	}

	T getHead() {  // head value
		if (!head) {
			throw ("List is empty.");
		}
		return head->value;
	}

	void insert(size_t index, string exp, T val) {
		if (index > size) {
			throw ("Index is out of range.");
		}
		
		TNode<T>* add_node = new TNode<T>{val, exp, nullptr};

		if (index == 0) {
			add_node->next = head;
			head = add_node;
		} else {
			TNode<T>* tmp1 = head;
			for (Iterator i = begin(); i != (begin() + (index - 1)); i++) {
				tmp1 = tmp1->next;
			}
			add_node->next = tmp1->next;
			tmp1->next = add_node;
		}
		size++;
	}

	void Delete(size_t index) {
		if (index >= size) {
			throw ("Index is out of range.");
		}

		if (index == 0) {
			TNode<T>* tmp = head;
			head = head->next;
			delete tmp;
		} else {
			TNode<T>* tmp = head;
			for (Iterator i = begin(); i != (begin() + (index - 1)); i++) {
				tmp = tmp->next;
			}
			TNode<T>* delete_node = tmp->next;
			tmp->next = delete_node->next;
			delete delete_node;
		}
		size--;
	}

	T search(size_t index) const {
		if (index >= size) {
			throw ("Index is out of range.");
		}

		TNode<T>* current_node = head;
		for (Iterator i = begin(); i != (begin() + index); i++) {
				current_node = current_node->next;
			}
		
		return current_node->value;
	}

	T medium() const {
		if (!head) {
			throw ("List is empty.");
		}

		TNode<T>* base = head;
		TNode<T>* modif = head;
		while (modif != nullptr && modif->next != nullptr) {
			base = base->next;
			modif = modif->next->next;
		}
		return base->value;
	}

	class Iterator
	{
		TNode<T>* current;
	public:
		Iterator() : current(nullptr) {}

		Iterator(int val, string exp) : current(new TNode<T>{val, exp, nullptr}) {}

		Iterator(TNode<T>* _node) : current(_node) {}
		
		Iterator operator++(int) {
			Iterator tmp = *this;
			current = current->next;
			return tmp;
		}

		Iterator operator+(int val) {
			for (int i = 0; i < val; i++) {
				current = current->next;
			}
			return current;
		}

		T& operator*() {
			if (!current) {
				throw ("No existing pointer");
			}
			return current->value;
		}

		TNode<T>* get_node() const {
			return current;
		}

		bool operator==(const Iterator& a) const {
			return current == a.current;
		}
		
		bool operator!=(const Iterator& a) const {
			return current != a.current;
		}
	};

	Iterator begin() const {
		return Iterator(head);
	}

	Iterator end() const {
		return Iterator(nullptr);
	}

	bool operator==(const TList& a) const {
		if (size != a.size) {
			return false;
		}

		Iterator tmp = begin();
		Iterator a_tmp = a.begin();

		while (tmp != end()) {
			if (*tmp != *a_tmp) {
				return false;
			}
			tmp++;
			a_tmp++;
		}

		return true;
	}
	
	bool operator!=(const TList& a) const {
		if (size != a.size) {
			return true;
		}

		Iterator tmp = begin();
		Iterator a_tmp = a.begin();

		while (tmp != end()) {
			if (*tmp != *a_tmp) {
				return true;
			}
			tmp++;
			a_tmp++;
		}

		return false;
	}

	TList& operator=(const TList& l)
	{
		if (this == &l) {
		return *this;
		}

		TNode<T>* curr = head;
		TNode<T>* l_curr = l.head;
		TNode<T>* prev = nullptr;

		while (curr && l_curr) {
			curr->value = l_curr->value;
			curr->exps = l_curr->value;
			prev = curr;
			curr = curr->next;
			l_curr = l_curr->next;
		}

		while (l_curr) {  // this has less nodes;
			TNode<T>* add_node = new TNode<T>{l_curr->value, l_curr->exps, nullptr};
			if (prev) {
				prev->next = add_node;
			} else {
				head = add_node;
			}
			prev = add_node;
			l_curr = l_curr->next;
		}

		while (curr) {  // this has more nodes;
			TNode<T>* tmp = curr;
			curr = curr->next;
			delete tmp;
		}
		
		size = l.size;

		return *this;
	}

};
#endif
