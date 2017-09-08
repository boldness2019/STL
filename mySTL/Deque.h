#ifndef _DEQUE_H_
#define _DEQUE_H_
#include"Allocator.h"
#include"Iterator.h"
namespace STL {
	
	//deque_iterator detail
	namespace Detail {
		template<class T>
		class deque_iterator:public iterator<random_access_iterator_tag, T>{//�̳��԰�����׼������typedef��iterator
			//static size_t buffer_size;
			
			//
		private:
			size_type  mapIndex_; 
			T*         cur_;      //�˵�������ָ�������ĵ�ǰλ��
			T*         first_;    //��������ָ�Ļ�������ͷ��
			T*         last_;     //��������ָ�Ļ�������β��

		public:
			
			deque_iterator():mapIndex_(-1),cur_(nullptr),first_(nullptr),last_(nullptr){}
			deque_iterator()

		};
	}//end of Detail
	
	template<class T, class Alloc>
	class deque {
	public :
		typedef T                  value_type;
		typedef value_type*        pointer;
		typedef T&                 reference;
		typedef const reference    const_reference;
		typedef size_t             size_type;
		typedef ptrdiff_t          difference_type;
		typedef Alloc              allocator_type;
		
	private:
		template<T>
		friend class Detail::deque_iterator;

		typedef pointer* map_Pointer;
	private:
		iterator start_;   //ָ��map��ͷ��
		iterator finish_;  //ָ��map��β��
		map_Pointer map_;   //ָ��map��mapΪһ�������ռ䣩,���ڲ�Ԫ��Ϊָ�룬ָ��һ��������
		
		size_type map_size_ //map�ڲ�ָ��ĸ���
	public:
		iterator begin() { return start_; }
		iterator end() { return finish_; }
		iterator begin()const { return start_; }
		iterator end(const{ return finish_; }

	public:
		deque(size_t n, const value_type & value)
			:start_(nullptr), finish_(nullptr), map_(nullptr), map_size_(0);
		
	};
}



#endif // !_DEQUE_H_
