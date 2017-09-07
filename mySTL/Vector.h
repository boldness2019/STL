#ifndef _VECTOR_H_
#define _VECTOR_H_

#include"Allocator.h"
#include"Iterator.h"
#include"Algorithm.h"
#include"UninitializedFunc.h"
#include<algorithm>
namespace STL {
	template <class T, class Alloc = allocator<T> >
	class vector {


	public:

		typedef T                       value_type;
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
		iterator end_of_storage_; //��ʾ��ǰ���ÿռ��β��

		typedef Alloc data_Allocator;

	public:
		//���캯������ֵ���캯������������
		vector() :
			start_(0), finish_(0), end_of_storage_(0) {}
		vector(size_type n, const value_type& value);
		explicit vector(const size_type n);
		template<class InputIterator>
		vector(InputIterator first, InputIterator last);
		vector(const vector& v);
		vector(vector&& v);
		vector& operator = (const vector& v);
		vector& operator = (vector&& v);
		~vector();
		//�Ƚϲ���
		bool operator ==(const vector& v)const;
		bool operator !=(const vector& v)const;

		
		//��������λ�����
		iterator begin() { return (start_); }
		const_iterator begin() const { return (start_); }
		const_iterator end()const { return (finish_); }
		iterator end() { return (finish_); }
		const_iterator cbegin() { return (start_); }
		const_iterator cend() { return (start_); }

		//��С������
		size_type size()const { return  end() - begin(); }
		size_type capacity() const{ return end_of_storage_ - begin(); }
		bool empty()const { return begin() == end(); }
		void resize(size_t n,value_type value=value_type());
		void reserve(size_t n);
		void shrink_to_fit();//ɾ��δʹ�õ�����
		//Ԫ�ط���
		reference operator[](const difference_type i) { return *(begin() + i); }
		const_reference operator[](const difference_type i)const { return *(cbegin() + i); }
		reference front() { return *begin(); }//��һ��Ԫ��
		reference back() { return *(end() - 1); }//���һ��Ԫ��
		reference operator[](size_type i) { return *(begin() + i); }
		pointer data() { return start_; }
		reference at(size_type pos);
		const_reference at(size_type pos)const;

		//�������ݵ��޸Ĳ�������
		void clear();
//		void copy(iterator start, iterator new_start);
//		void swap(vector& v);

		void pop_back();
		void insert(iterator position, const size_type& n, const value_type& val);
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		iterator insert(iterator position, const value_type& value);
		void push_back(const value_type & value);//ĩβ���
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

		//�ռ���������صĲ�������
		data_Allocator get_allocator() { return data_Allocator; }
	private:
		template<class InputIterator>
		void __insert(iterator position, InputIterator first, InputIterator last, std::false_type);
		void __insert(iterator position,size_type n, const value_type& value, std::true_type);

		void deallocate();
		void fill_initialize(size_t n, const value_type& value);
		void allocateAndFillN(size_type n, const T& x);
		template<class InputIterator>
		void allocateAndCopy(InputIterator first, InputIterator last);
		template<class InputIterator>
		void reallocateAndCopy(iterator position, InputIterator first, InputIterator last);
		void reallocateAndFillN(iterator position, const size_type& n, const value_type& value);

		size_type getNewCapacitySize(size_type n)const;

		template<class InputIterator>
		void __vector(InputIterator first, InputIterator last, std::false_type);
		template<class Integer>
		void __vector(Integer n, const value_type& value, std::true_type);
		
		//         =��=
	public:   
		template<class T, class Alloc>
		friend bool operator == (const vector<T, Alloc>& v1, const vector<T, Alloc>& v2);
		template<class T, class Alloc>
		friend bool operator != (const vector<T, Alloc>& v1, const vector<T, Alloc>& v2);


	};

}
//ʵ��
#include"Vector_detail.h"
#endif