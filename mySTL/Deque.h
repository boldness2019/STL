#ifndef _DEQUE_H_
#define _DEQUE_H_
#include"Allocator.h"
#include"Iterator.h"
#include"Algorithm.h"
namespace STL {
	template<class T, class Alloc = allocator<T>>
	class deque;
	//deque_iterator detail
	namespace Detail {

		template<class T>
		class deque_iterator :public iterator<random_access_iterator_tag, T> {//�̳��԰�����׼������typedef��iterator
			//static size_t buffer_size;
			template<class T, class Alloc>
			friend class deque;
			typedef deque<T>* containerPtr;
			//
		private:
			containerPtr container_;
			size_t    mapIndex_;
			T*           cur_;      //�˵�������ָ�������ĵ�ǰλ��
			//T*         first_;    //��������ָ�Ļ�������ͷ��
			//T*         last_;     //��������ָ�Ļ�������β��

		public:

			//�������
			deque_iterator()
				:mapIndex_(-1), cur_(nullptr), container_(nullptr) {}
			deque_iterator(size_t index, T *ptr, containerPtr container)
				:mapIndex_(index), cur_(ptr), container_(container) {}
			deque_iterator(const deque_iterator& it)
				:mapIndex_(it.mapIndex_), cur_(it.cur_), container_(it.container_) {}
			
			deque_iterator& operator = (const deque_iterator& it);

			//��������
			deque_iterator& operator ++ ();
			deque_iterator operator ++ (int);
			deque_iterator& operator -- ();
			deque_iterator operator -- (int);
			reference operator *() { return *cur_; }
			const reference operator *()const { return *cur_; }
			pointer operator ->() { return &(operator*()); }
			const pointer operator ->()const { return &(operator*()); }

			bool operator ==(const deque_iterator& rhs)const;
			bool operator !=(const deque_iterator& rhs)const;

		private://�������
			T* getNowBuckTail();
			T* getNowBuckHead();
			size_t getBuckSize();

		};

	}//end of Detail

	template<class T, class Alloc = allocator<T>>
	class deque {
	public:
		typedef T                  value_type;
		typedef value_type*        pointer;
		typedef T&                 reference;
		typedef const reference    const_reference;
		typedef size_t             size_type;
		typedef ptrdiff_t          difference_type;
		typedef Alloc              allocator_type;
		typedef Detail::deque_iterator<T>   iterator;
	private:
		template<class T>
		friend class       ::STL::Detail::deque_iterator;
		typedef Alloc              dataAllocator;
		typedef pointer*      map_Pointer;
	private:
		iterator start_;   //ָ��map��ͷ��
		iterator finish_;  //ָ��map��β��
		map_Pointer map_;   //ָ��map��mapΪһ�������ռ䣩,���ڲ�Ԫ��Ϊָ�룬ָ��һ��������

		size_type map_size_; //map�ڲ�ָ��ĸ���
		enum class BuckSize { BUCK_SIZE = 16};
	public:
		//Ԫ�ط���
		iterator begin() { return start_; }
		iterator end() { return finish_; }
		iterator begin()const { return start_; }
		iterator end() const { return finish_; }
		reference operator[] (size_type n);
		reference front();
		reference back();
		const_reference operator[] (size_type n) const;
		const_reference front() const;
		const_reference back() const;

		//�ռ�
		size_type size() const { return end() - begin(); }
		bool empty() const { return begin() == end(); }

	public:
		deque();
		explicit deque(size_type n, const value_type& val = value_type());
		template <class InputIterator>
		deque(InputIterator first, InputIterator last);
		deque(const deque& x);
		~deque();
	private:
		//�ռ�������

		T * getANewBuck();
		T ** getNewMapAndGetNewBucks(const size_t size);
		T**  GetNewMap(const size_t& size);
		void __deque(size_t n, const value_type& value, std::true_type);
		template<class Iterator>
		void __deque(Iterator first, Iterator last, std::false_type);
		bool isFrontFull()const;
		void reallocateMap(size_t nodes_to_add,bool add_at_front);
		void init();
	public:

		//Ԫ�ز���
		void push_back(const value_type& val);
		void push_front(const value_type& val);
		void pop_back();
		void pop_front();
		void clear();

	private:

		//��ȡ����(�ڲ��������ʹ�ã�
		size_type getBuckSize()const { return (size_t)BuckSize::BUCK_SIZE; }
		size_t getNewMapSize(const size_t size);
		bool isBackFull()const;

	};

}
#include"Deque_detail.h"


#endif // !_DEQUE_H_
