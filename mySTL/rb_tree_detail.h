#include "rb_tree.h"
#ifndef _RB_TREE_DETAIL_H
#define _RB_TREE_DETAIL_H

namespace STL {
	namespace detail {

		template<class Value, class Ref, class Ptr>
		 self & __rb_tree_iterator<Value, Ref, Ptr>::operator++(){
			increment();
			return *this;
		}
		template<class Value, class Ref, class Ptr>
		 self __rb_tree_iterator<Value, Ref, Ptr>::operator++(int){
			self tmp = *this;
			increment();
			return tmp;
		}

		template<class Value, class Ref, class Ptr>
		 self & __rb_tree_iterator<Value, Ref, Ptr>::operator--(){
			decrement();
			return *this;
		}

		template<class Value, class Ref, class Ptr>
		 self __rb_tree_iterator<Value, Ref, Ptr>::operator--(int){
			self tmp = *this;
			decrement();
			return tmp;
		}
		
	}//end of detail

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	link_type rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::create_node(const value_type & x){
		link_type tmp = get_node();
		construct(&tmp->value_field, x);
		return tmp;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	link_type rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::clone_node(link_type x)
	{
		return link_type();
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	inline void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::destroy_node(link_type p){
		destroy(&p->value_field);
		put_node(p);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	 iterator rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::
		 __insert(base_ptr x, base_ptr y, const value_type & v){
		
	}
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	link_type rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::__copy(link_type x, link_type p) {
		// structural copy.  x and p must be non-null.
		link_type top = clone_node(x);
		top->parent = p;

		if (x->right)
			top->right = __copy(right(x), top);
		p = top;
		x = left(x);

		while (x != 0) {
			link_type y = clone_node(x);
			p->left = y;
			y->parent = p;
			if (x->right)
				y->right = __copy(right(x), y);
			p = y;
			x = left(x);
		}
		return top;
	}
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	 void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::__erase(link_type x) {
		 // ɾ���ڵ㣬�������µ�����
		 while (x != 0) {
			 __erase(right(x));
			 link_type y = left(x);
			 destroy_node(x);
			 x = y;
		 }
	 }
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	 void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::init(){
		 //��header�ĸ�ָ������ҽڵ㶼ָ������
		 header = get_node();
		 color(header) = __rb_tree_red;
		 root() = 0;
		 leftmost() = header;
		 rightmost() = header;
	}
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	 rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::rb_tree(const Compare & comp)
		 : node_count(0)
		 , key_compare(comp) {
		 init(); 
	 }
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	 rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::rb_tree(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x) 
		 : node_count(0)
		 , key_compare(x.key_compare)
	 {
		 header = get_node();
		 color(header) = __rb_tree_red;
		 if (x.root() == 0) {
			 root() = 0;
			 leftmost() = header;
			 rightmost() = header;
		 }
		 else {
			 root() = __copy(x.root(), header);
			 __STL_UNWIND(put_node(header));
			 leftmost() = minimum(root());
			 rightmost() = maximum(root());
		 }
		 node_count = x.node_count;
	 }
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	 rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::~rb_tree()
	{
	}
	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	 rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::
		 operator = (const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x)
	{
		// TODO: �ڴ˴����� return ���
	}
}






#endif // !_RB_TREE_DETAIL_H
