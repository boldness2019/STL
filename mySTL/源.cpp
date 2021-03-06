#include<iostream>
#include"Allocator.h"
#include"Vector.h"
#include"TestVector.h"
#include"TestList.h"
#include<stack>
#include<vector>
#include<deque>
#include<map>
#include<string>
#include"List.h"
#include"TestDeque.h"
#include"TestQueue.h"
#include"rb_tree.h"
#include<functional>
int main() {

	STL::testList::testAll();
	STL::testVector::testAll();
	STL::testDeque::testAll();
	STL::testQueue::testAll();
	STL::rb_tree<int,int,std::identity<int>,std::less<int>> rbTree;
	rbTree.insert_unique(29);

	rbTree.insert_unique(11);
	rbTree.insert_unique(18);
	rbTree.insert_unique(12);
	rbTree.insert_unique(6);
	rbTree.insert_unique(5);
	std::cout << rbTree.size() << std::endl;
	//std::cout <<*STL::rb_tree<int, int, std::identity<int>, std::less<int>>::iterator(rbTree.leftmost()) << std::endl;
	//std::cout << *STL::rb_tree<int, int, std::identity<int>, std::less<int>>::iterator(rbTree.rightmost()) << std::endl;
	std::cout << *STL::rb_tree<int, int, std::identity<int>, std::less<int>>::iterator(rbTree.root()) << std::endl;
	for (auto it = rbTree.begin(); it != rbTree.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}