/* Compile and run: g++ -std=c++11 -W -Wall -O3 -o main main.cpp && ./main
 */

#include <iostream>
#include <cstdint>

#include "mtree.hpp"

int main()
{
	mtree<uint32_t> *p1 = new mtree<uint32_t>(1);
	mtree<uint32_t> *p2 = new mtree<uint32_t>(p1, 2);
	mtree<uint32_t> *p3 = new mtree<uint32_t>(p1, 3);
	mtree<uint32_t> *p4 = new mtree<uint32_t>(p1, 4);
	mtree<uint32_t> *p5 = new mtree<uint32_t>(p2, 5);
	mtree<uint32_t> *p6 = new mtree<uint32_t>(p2, 6);
	mtree<uint32_t> *p7 = new mtree<uint32_t>(p2, 7);
	mtree<uint32_t> *p8 = new mtree<uint32_t>(p7, 8);
	mtree<uint32_t> *p9 = new mtree<uint32_t>(p7, 9);
	mtree<uint32_t> *p10 = new mtree<uint32_t>(p7, 10);
	mtree<uint32_t> *p11 = new mtree<uint32_t>(p2, 11);
	mtree<uint32_t> *p12 = new mtree<uint32_t>(12);
	mtree<uint32_t> *p13 = new mtree<uint32_t>(13);

	mtree<uint32_t> *tmp = p2->get_parent();
	mtree<uint32_t> *tmp_child = p2->get_child(2);
	std::cout << "p2 parent (p1): " << std::endl;
	std::cout << "has children?: "; 
	if (tmp->has_children()) {
		std::cout << "yes";
	} else {
		std::cout << "no";
	}
	std::cout << std::endl;
	std::cout << "children count: " << tmp->get_children_count() << std::endl;
	std::cout << "descendants count: " << tmp->get_descendants_count() << std::endl;
	std::cout << std::endl;
	std::cout << "p2 child (p7): " << std::endl;
	std::cout << "children count: " << tmp_child->get_children_count() << std::endl;
	std::cout << "descendants count: " << tmp_child->get_descendants_count() << std::endl;
	std::cout << std::endl;

	tmp_child->push_back(p12);
	std::cout << "pushing back p12: " << std::endl;
	std::cout << "children count: " << tmp_child->get_children_count() << std::endl;
	std::cout << "descendants count: " << tmp_child->get_descendants_count() << std::endl;
	std::cout << std::endl;

	tmp_child->insert(2, p13);
	std::cout << "inserting p13 at position 2: " << std::endl;
	std::cout << "children count: " << tmp_child->get_children_count() << std::endl;
	std::cout << "descendants count: " << tmp_child->get_descendants_count() << std::endl;
	std::cout << "p13 index: " << p13->get_index() << std::endl;
	std::cout << "is p13 sibling of p7?: ";
	if (p13->is_sibling(tmp_child)) {
		std::cout << "yes";
	} else {
		std::cout << "no";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	p13->disconnect();
	std::cout << "disconnecting p13 from p7: " << std::endl;
	std::cout << "is p13 sibling of p7?: ";
	if (p13->is_sibling(tmp_child)) {
		std::cout << "yes";
	} else {
		std::cout << "no";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	return 0;
}
