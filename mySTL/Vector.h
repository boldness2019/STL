#ifndef _VECTOR_H_
#define _VECTOR_H_

#include"Allocator.h"
#include"Iterator.h"
namespace STL {
	template <class T, class Alloc = allocator<T> >
	class vector {


	public:
		typedef vector<T> myVec_;

		typedef T value_type;
		typedef value_type*             pointer;
		typedef value_type*             iterator;
		typedef value_type&             reference;
		typedef const value_type*       const_iterator;
		typedef const value_type&       const_reference;
		typedef size_t					size_type;
		typedef ptrdiff_t	            difference_type;
	private:
		iterator begin_;   //��ʾĿǰʹ�ÿռ��ͷ��
		iterator end_;     //��ʾĿǰʹ�ÿռ��β��
		iterator end_of_storage; //��ʾ��ǰ���ÿռ��β��

		typedef Alloc data_Allocator;

	public:
		//���캯�������ƺ�������������
		vector() :
			begin_(0), end_(0), end_of_storage(0) {}
		vector(size_type n, const value_type& value);
		explicit vector(const size_type n);

		//�Ƚϲ���
		vector& operator =(const vector& v);
		vector& operator =(vector&& v);

		void deallocate();
		~vector();
		//��������λ�����
		
		iterator begin() { return begin_; }
		const_iterator end()const { return end_; }
		iterator end() { return end_; }
		const_iterator begin() const { return begin_; }
		const_iterator cbegin() { return begin_; }
		const_iterator cend() { return end_; }
		//test github

		//��С������
		size_type size() { return  end() - begin(); }
		size_type capacity() { return end_of_storage - begin(); }
		bool empty() { return begin() == end(); }
		void push_back(const value_type & value);
		void pop_back() { if (!empty()) --end_; }

		//Ԫ�ط���
		const_reference operator[](const difference_type i)const { return *(cbegin() + i); }
		reference front() { return *begin(); }
		reference back() { return *(end() - 1); }
		reference operator[](size_type i) { return *(begin() + i); }
		pointer data() { return start_; }

		//

		//�������ݵ��޸�
		void clear();
		
		void reallocate(size_t n = 0);
		void swap(vector& v);
		void pop_back();
		void copy(iterator start, iterator new_start);
		void insert(iterator position, const size_type& n, const value_type& val);
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		void push_back(const value_type & value);
		void fill_initialize(size_t n, const value_type& value);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

		//�ռ���������صĲ�������
	private:

		void fill_initialize(size_t n, const value_type& value);

		
	};
	
	template <typename T>
	void vector<T>::reallocate(size_t n = 0) {
		size_t old_size = n;
		size_t newCapacity = 2 * old_size + 1;

		iterator new_begin;
		iterator new_end;

		new_begin = new value_type[newCapacity];

		copy(begin(), new_begin);

		free();

		begin_ = new_begin;
		end_ = begin_ + old_size;
		end_of_storage = begin_ + newCapacity;
	}

}
#endif