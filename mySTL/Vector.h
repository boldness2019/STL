#ifndef _VECTOR_H_
#define _VECTOR_H_

#include"Allocator.h"
#include"Iterator.h"
namespace STL {
	template <class T, class Alloc = allocator<T> >
	class vector {


	public:

		typedef T value_type;
		typedef value_type*             pointer;
		typedef value_type*             iterator;
		typedef value_type&             reference;
		typedef const value_type*       const_iterator;
		typedef const value_type&       const_reference;
		typedef size_t					size_type;
		typedef ptrdiff_t	            difference_type;
	private:
		iterator start_;   //��ʾĿǰʹ�ÿռ��ͷ��

		iterator finish_;     //��ʾĿǰʹ�ÿռ��β��
		iterator end_of_storage; //��ʾ��ǰ���ÿռ��β��

		typedef Alloc data_Allocator;

	public:
		//���캯�������ƺ�������������
		vector() :
			begin_(0), end_(0), end_of_storage(0) {}
		vector(size_type n, const value_type& value);
		explicit vector(const size_type n);

		//�Ƚϲ���
		bool operator ==(const vector& v);
		bool operator !=(const vector& v);


		~vector();
		//��������λ�����

		iterator begin() { return (start_); }
		const_iterator end()const { return (finish_); }
		iterator end() { return (finish_); }
		const_iterator begin() const { return (start_); }
		const_iterator cbegin() { return (start_); }
		const_iterator cend() { return (start_); }
		//test new road

		//��С������
		size_type size() { return  end() - begin(); }
		size_type capacity() { return end_of_storage - begin(); }
		bool empty() { return begin() == end(); }
		//Ԫ�ط���
		const_reference operator[](const difference_type i)const { return *(cbegin() + i); }
		reference front() { return *begin(); }//��һ��Ԫ��
		reference back() { return *(end() - 1); }//���һ��Ԫ��
		reference operator[](size_type i) { return *(begin() + i); }
		pointer data() { return start_; }

		//�������ݵ��޸Ĳ�������
		void clear();


		void swap(vector& v);
		void pop_back();
		void copy(iterator start, iterator new_start);
		void insert(iterator position, const size_type& n, const value_type& val);
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		void push_back(const value_type & value);//ĩβ���
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

		//�ռ���������صĲ�������
	private:
		void deallocate();
		void reallocate(size_t n = 0);
		void fill_initialize(size_t n, const value_type& value);
		void allocate_and_fill_n(size_type n, const T& x);
		
	};

}
//ʵ��
#include"Vector_detail.h"
#endif