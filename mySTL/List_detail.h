#include "List.h"
#ifndef _LIST_DETAIL_H_
#define _LIST_DETAIL_H_
namespace STL {

	namespace Detail {//         Detail namespace
		template<class T>
		list_iterator<T>& list_iterator<T>::operator ++() {
			p = p->next;
			return *this;
		}

		template<class T>
		inline list_iterator<T> list_iterator<T>::operator ++(int) {
			auto res = *this;
			++*this;
			return res;
		}

		template<class T>
		inline list_iterator<T>& list_iterator<T>::operator--() {
			p = p->prev;
			return *this;
		}

		template<class T>
		inline list_iterator<T> list_iterator<T>::operator--(int) {
			auto res = *this;
			--*this;
			return res;
		}
		template<class T>
		bool operator==(const list_iterator<T>& lhs, const list_iterator<T>& rhs) {
			return lhs.p == rhs.p;
		}
		template<class T>
		bool operator!=(const list_iterator<T>& lhs, const list_iterator<T>& rhs) {
			return !(lhs == rhs);
		}
	}//end of Detail

	//                                    ���캯��

	template<class T> 
	list<T>::list()
	{
		head.p = newNode();
		tail.p = head.p;
	}
	//__list���ͽ��л���
	template<class T>
	list<T>::list(size_type n, const value_type & val)
	{
		__list(n, val, std::is_integral<value_type>());
	}
	template<class T>
	template <class InputIterator>
	list<T>::list(InputIterator first, InputIterator last) {
		__list(first, last, std::is_integral<InputIterator>());
	}
	template<class T>
	inline list<T>::list(const list & lis)
	{
		//__list(lis.begin(), lis.end(), std::is_integral<lis.begin()>());
		//����ֱ��ʹ��

		head.p = newNode();
		tail.p = head.p;
		for (auto node = l.head.p; node != l.tail.p; node = node->next)
			push_back(node->data);
	}

	template<class T>
	inline list<T>& list<T>::operator=(const list & rhs)
	{
		if (this != &rhs) {
			list(rhs).swap(*this);
		}
		return *this;
	}
	template<class T>
	inline list<T>::~list()
	{
		for (; head != tail;) {
			auto temp = head++;
			nodeAllocator::destroy(temp.p);
			nodeAllocator::deallocate(temp.p);
		}
		nodeAllocator::deallocate(tail.p);
	}

	//******************************** �ռ����������******************************************   
	template<class T>
	void list<T>::__insert(iterator position, size_type n, const T& val, std::true_type) {
		for (auto i = n; i != 0; --i) {
			position = insert(position, val);
		}
	}
	template<class T>
	template<class InputIterator>
	void list<T>::__insert(iterator position, InputIterator first, InputIterator last, std::false_type) {
		for (--last; first != last; --last) {//����
			position = insert(position, *last);
		}
		insert(position, *last);
	}
	template<class T>
	template<class InputIterator>
	inline void list<T>::__list(InputIterator first, InputIterator last, std::false_type)
	{
		head.p = newNode();
		tail.p = newNode();
		for (; first != last; ++first) {
			push_back(*first);
		}
	}

	template<class T>
	inline void list<T>::__list(size_type n, const value_type & val, std::true_type)
	{
		head.p = newNode();
		tail.p = newNode();
		while (n--) {
			push_back(val);
		}
	}


	template<class T>
	inline typename list<T>::nodePtr list<T>::newNode(const T& value = T())
	{
		nodePtr node = nodeAllocator::allocate();
		nodeAllocator::construct(node, Detail::__list_node<T>(value, nullptr, nullptr));
		return node;
	}
	template<class T>
	inline void list<T>::deleteNode(nodePtr p)
	{
		p->prev = p->next = nullptr;
		nodeAllocator::destroy(p);
		nodeAllocator::deallocate(p);
	}
	//**************************** Ԫ�ز������**********************************************     
	template<class T>
	void list<T>::swap(list& x) {
		STL::swap(head.p, x.head.p);
		STL::swap(tail.p, x.tail.p);
	}
	template<class T>
	void list<T>::remove(const value_type& val) {
		for (auto it = begin(); it != end();) {
			if (*it == val)
				it = erase(it);
			else
				++it;
		}
	}
	template<class T>
	template<class Func>
	void list<T>::remove_if(Func ifFunc){
		for (auto it = begin(); it != end();) {
			if (ifFunc(*it))
				it = erase(it);
			else
				++it;
		}
	}

	template<class T>
	typename list<T>::iterator list<T>::insert(iterator position, const value_type& value) {
		//���������ж�Ϊ�˷�ֹ����λ��Ϊͷβʱ�����쳣
		if (position == begin()) {
			push_front(value);
			return begin();
		}
		else if (position == end()) {
			auto ret = position;
			push_back(value);
			return ret;
		}
		auto node = newNode(value);
		auto prev = position.p->prev;
		node->next = position.p;
		node->prev = prev;
		prev->next = node;
		position.p->prev = node;
		return iterator(node);  //����ת��
	}

	template<class T>
	typename list<T>::iterator list<T>::erase(iterator position) {
		//��ֹ����λ��Ϊͷβʱ�����쳣
		if (position == head) {
			pop_front();
			return head;
		}
		auto prev = position.p->prev;
		prev->next = position.p->next;
		position.p->next->prev = prev;
		deleteNode(position.p);
		return iterator(prev->next);//ָ��ɾ���ڵ����һ���ڵ�
	}
	template<class T>
	typename list<T>::iterator list<T>::erase(iterator first, iterator last) {
		typename list<T>::iterator res;
		for (; first != last;) {
			auto temp = first++;
			res = erase(temp);
		}
		return res;
	}
	template<class T>
	inline void list<T>::splice(iterator position, list & other){
		if (other.empty())return;
		this->insert(position, other.begin(), other.end());
		other.head.p = other.tail.p;  //��rhs�б���Ϊ��
	}
	template<class T>
	inline void list<T>::splice(iterator position, list & other, iterator otherPos){
		auto next = otherPos;
		++next;
		this->splice(position, other, otherPos, next);
	}
	template<class T>
	inline void list<T>::splice(iterator position, list & other, iterator first, iterator last){
		if (first == last) return;
		//����other����
		if (other.head.p == first.p) {
			other.head.p = last.p;
			other.head.p->prev = nullptr;
		}
		else {
			first.p->prev->next = last.p;
			last.p->prev = first.p->prev;
		}
		//����this����
		insert(position, first, last);

	}
	template<class T>
	void list<T>::unique()//�Ƴ���ֵ��ͬ��������Ԫ��,ֱ��ֻʣ�µ���
	{
		
		iterator first = begin();
		iterator last = end();
		if (first == last) {//������
			return;
		}
		iterator next = first;
		while (++next != last) {
			if (*first == *next) {//����ͬ�ڵ㣬�Ƴ�һ��
				erase(next);
			}
			else {
				first = next;    //����
			}
			next = first;
		}
	}
	template<class T>
	void list<T>::clear() {
		erase(begin(), end());
	}
	template<class T>
	void list<T>::push_front(const value_type& val) {
		auto node = newNode(val);
		head.p->prev = node;
		node->next = head.p;
		head.p = node;
	}
	template<class T>
	void list<T>::pop_front() {
		auto oldNode = head.p;
		head.p = oldNode->next;
		head.p->prev = nullptr;
		deleteNode(oldNode);
	}
	template<class T>
	void list<T>::push_back(const value_type& val) {
		auto node = newNode();
		tail.p->data = val;
		(tail.p)->next = node;
		node->prev = tail.p;
		tail.p = node;
	}
	template<class T>
	void list<T>::pop_back() {
		auto newTail = tail.p->prev;
		newTail->next = nullptr;
		deleteNode(tail.p);
		tail.p = newTail;
	}

	template<class T>
	void list<T>::insert(iterator position, size_type n, const value_type& val) {
		__insert(position, n, val, typename std::is_integral<InputIterator>::type());
	}
	template<class T>
	template <class InputIterator>
	void list<T>::insert(iterator position, InputIterator first, InputIterator last) {
		__insert(position, first, last, typename std::is_integral<InputIterator>::type());
	}

	//***********************************�������***************************************                              

	template<class T>
	typename list<T>::size_type list<T>::size()const {
		size_type length = 0;
		for (auto h = head; h != tail; ++h)
			++length;
		return length;
	}
	//***********************************Ԫ�ط���***************************************
	                            
	template<class T>
	typename list<T>::iterator list<T>::begin() {
		return head;
	}
	template<class T>
	typename list<T>::iterator list<T>::end() {
		return tail;
	}

	//*********************************�ȽϺ���*****************************************                            
	template <class T>
	bool operator== (const list<T>& lhs, const list<T>& rhs) {
		auto nodeL = lhs.head.p, nodeR = rhs.head.p;
		for (; nodeL != lhs.tail.p && nodeR != rhs.tail.p; nodeL = nodeL->next, nodeR = nodeR->next) {
			if (nodeL->data != nodeR->data)
				break;
		}
		if (nodeL == lhs.tail.p && nodeR == rhs.tail.p)
			return true;
		return false;
	}
	template <class T>
	bool operator!= (const list<T>& lhs, const list<T>& rhs) {
		return !(lhs == rhs);
	}
	
}
#endif // !_LIST_DETAIL_H_

