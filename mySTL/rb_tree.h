#ifndef _RB_TREE_H_
#define _RB_TREE_H_
#include"Iterator.h"
#include<new>
namespace STL {
	namespace detail {

		typedef bool __rb_tree_color_type;
		const __rb_tree_color_type __rb_tree_red = false;   //��ɫ  0
		const __rb_tree_color_type __rb_tree_black = true;  //��ɫ  1

		//������Ľڵ����
		struct __rb_tree_node_base {
			typedef __rb_tree_color_type color_type;
			typedef __rb_tree_node_base* base_ptr;

			color_type   color;
			base_ptr     parent;
			base_ptr     left;
			base_ptr     right;
			static base_ptr minmun(base_ptr x) {//Ѱ����Сֵ
				while (nullptr != x->left)x = x->left;
				return x;
			}
			static base_ptr maxmum(base_ptr x) {//Ѱ�����ֵ
				while (nullptr != x->right)x = x->right;
				return x;
			}
		};

		//������Ľڵ�
		template<class Value>
		struct  __rb_tree_node :public __rb_tree_node_base {
			typedef __rb_tree_node<Value>* link_type;
			Value value_field;   //�ڵ�ֵ
		};


		//��������������
			//����������
		struct __rb_tree_base_iterator
		{
			typedef __rb_tree_node_base*                base_ptr;
			typedef STL::bidirectional_iterator_tag     iterator_category;
			typedef ptrdiff_t                           defference;

			base_ptr  node;
			void increment() {
				if (nullptr != node->right) {                //��������ӽڵ�
					node = node->right;                      //��������
					while (nullptr != node->left) {          //Ȼ��һֱ���󵽵�
						node = node->left;
					}
				}
				else {                                        //û�����ӽڵ�
					base_ptr y = node->parent;               //�ҳ����ڵ�
					while (node == y->right) {               //����
						node = y;
						y = y->parent;
					}
					if (node->right != y) {
						node = y;
					}
				}
			}
			void decrement() {
				if (node->color == __rb_tree_red &&
					node->parent->parent == node)
					node = node->right;
				else if (node->left != 0) {
					base_ptr y = node->left;
					while (y->right != 0)
						y = y->right;
					node = y;
				}
				else {
					base_ptr y = node->parent;
					while (node == y->left) {
						node = y;
						y = y->parent;
					}
					node = y;
				}
			}
		};

		//������ĵ�����
		template<class Value, class  Ref, class Ptr>
		struct __rb_tree_iterator :public __rb_tree_base_iterator {
			//����typedef
			typedef Value      value_type;
			typedef Ref        reference;
			typedef Ptr        pointer;
			typedef __rb_tree_iterator<Value, Value&, Value*>             iterator;
			typedef __rb_tree_iterator<Value, const Value&, const Value*> const_iterator;
			typedef __rb_tree_iterator<Value, Ref, Ptr>                   self;
			typedef __rb_tree_node<Value>* link_type;

			__rb_tree_iterator() {}
			__rb_tree_iterator(link_type x) { node = x; }
			__rb_tree_iterator(const iterator& it) { node = it.node; }

			//��������
			pointer operator->() const { return &(operator*()); }
			reference operator*() const { return link_type(node)->value_field; }
			self& operator++();
			self operator++(int);
			self& operator--();
			self operator--(int);
			
		};

	}//end of detail 
}
//ʵ��ϸ��
#include"rb_tree_detail.h"

#endif // !_RB_TREE_H_

