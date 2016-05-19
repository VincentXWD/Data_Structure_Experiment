#pragma once
#include <cstdio>
#include <cassert>

namespace kirai {
	template<class type> class List {
	private:
		typedef struct ListNode {
			type data;
			ListNode* pre;
			ListNode* next;
			ListNode() : data(data) { pre = NULL; next = NULL; }
			ListNode(const type& dd, ListNode*& pp, ListNode*& nn) :
				data(dd), pre(pp), next(nn) {}
		}ListNode;
		ListNode* head;
	public:
		List() : head(new ListNode()) { head->pre = head->next = head; };
		int size() const;
		bool empty() const;
		void push_back(const type&);
		type last() const;
		void pop_back();
		void modifyLast(const type&);
		void insert(const type& ele, int idx);
		type get(int idx) const;
		type& operator [](int idx);
		type remove(int idx);
		void modify(const type& ele, int idx);
		int find(const type&) const;
		void clear();
		~List() = default;
	};

	template<class type>
	int List<type>::size() const {
		int tot = 0;
		ListNode* p = head->next;
		while (p != head) {
			tot++;
			p = p->next;
		}
		return tot;
	}

	template<class type>
	bool List<type>::empty() const {
		return head == head->next ? 1 : 0;
	}

	template<class type>
	void List<type>::push_back(const type& element) {
		ListNode* p = new ListNode(element, head->pre, head);
		head->pre = head->pre->next = p;
	}

	template<class type>
	type List<type>::last() const {
		assert(!empty());
		return head->pre->data;
	}

	template<class type>
	void List<type>::pop_back() {
		assert(!empty());
		ListNode* p = head->pre->pre;
		delete head->pre;
		head->pre = p;
		p->next = head;
	}

	template<class type>
	void List<type>::modifyLast(const type& element) {
		assert(!empty());
		head->pre->data = element;
	}

	template<class type>
	void List<type>::insert(const type& element, int idx) {
		idx++;
		assert(idx > 0 && idx <= size() + 1);
		ListNode* p = head;
		while (idx--) p = p->next;
		ListNode* cur = new ListNode(element, p->pre, p);
		p->pre = p->pre->next = cur;
	}

	template<class type>
	type List<type>::get(int idx) const {
		idx++;
		assert(!empty() && idx > 0 && idx <= size());
		ListNode* p = head->next;
		while (--idx) p = p->next;
		return p->data;
	}
	template<class type>
	type& List<type>::operator [](int idx) {
		idx++;
		assert(!empty() && idx > 0 && idx <= size());
		ListNode* p = head->next;
		while (--idx) p = p->next;
		return p->data;
	}
	template<class type>
	type List<type>::remove(int idx) {
		idx++;
		assert(!empty() && idx > 0 && idx <= size());
		ListNode* p = head->next;
		while (--idx) p = p->next;
		p->pre->next = p->next;
		p->next->pre = p->pre;
		type d = p->data;
		delete p;
		return d;
	}

	template<class type>
	void List<type>::modify(const type& ele, int idx) {
		idx++;
		assert(!empty() && idx > 0 && idx <= size());
		ListNode* p = head->next;
		while (--idx) p = p->next;
		p->data = ele;
	}

	template<class type>
	int List<type>::find(const type& ele) const {
		ListNode* p = head->next;
		int idx = 0;
		while (p != head) {
			if (p->data == ele) return idx;
			p = p->next;
			idx++;
		}
		return -1;
	}
	template<class type>
	void List<type>::clear() {
		if (empty()) return;
		ListNode* p = head->next;
		ListNode* tmp = NULL;
		while (p != head) {
			tmp = p->next;
			delete p;
			p = tmp;
		}
		head->pre = head->next = head;
	}
}