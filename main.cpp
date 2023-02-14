#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <unistd.h>



#include "vector/vector.hpp"
#include "utils/iterator_traits.hpp"
#include "utils/reverse_iterator.hpp"
#include "utils/is_integral.hpp"
#include "utils/enable_if.hpp"
#include "utils/make_pair.hpp"
#include "utils/pair.hpp"
#include "red-black_tree/RBTree.hpp"
#include "red-black_tree/RBTree_visualizer.hpp"


// int main ()
// {
// 	ft::vector<int> myvector;
// 	for (int i = 1; i <= 10; i+=2)
// 		myvector.push_back(i);
// 	ft::vector<int>::iterator beg = myvector.begin();
// 	ft::vector<int>::iterator end = myvector.end();
// 	ft::vector<int>::iterator foo;
// 	ft::vector<int>::iterator bar(beg);

// 	ft::vector<int>::reverse_iterator revbeg(beg);
// 	ft::vector<int>::reverse_iterator revend(end);

// 	std::vector<int> std_myvector;
// 	for (int i=1; i<=5; i++)
// 		myvector.push_back(i);
// 	std::vector<int>::iterator std_beg = std_myvector.begin();
// 	std::vector<int>::iterator std_end = std_myvector.end();
// 	std::vector<int>::iterator std_foo;
// 	std::vector<int>::iterator std_bar(std_beg);

// 	std::vector<int>::reverse_iterator std_revbeg(std_beg);
// 	std::vector<int>::reverse_iterator std_revend(std_end);


// 	return 0;
// }


// int main ()
// {
//   ft::vector<int> myints;
//   std::cout << "0. size: " << myints.size() << '\n';

//   for (int i=0; i<10; i++) myints.push_back(i);
//   std::cout << "1. size: " << myints.size() << '\n';

//   myints.insert (myints.end(),10,100);
//   std::cout << "2. size: " << myints.size() << '\n';

//   myints.pop_back();
//   std::cout << "3. size: " << myints.size() << '\n';

//   return 0;
// }


// int main ()
// {
//   ft::vector<int> first;
//   ft::vector<int> second;
//   ft::vector<int> third;

//   first.assign (7,100);             // 7 ints with a value of 100

//   ft::vector<int>::iterator it;
//   it=first.begin()+1;

//   second.assign (it,first.end()-1); // the 5 central values of first

//   int myints[] = {1776,7,4};
//   third.assign (myints,myints+3);   // assigning from array.

//   std::cout << "Size of first: " << int (first.size()) << '\n';
//   std::cout << "Size of second: " << int (second.size()) << '\n';
//   std::cout << "Size of third: " << int (third.size()) << '\n';
//   return 0;
// }


#include <fstream>
#include <iostream>
int	rng() {
	int rng = 0;
	size_t size = sizeof(rng); 
	std::ifstream urandom("/dev/urandom", std::ios::in| std::ios::binary);
	urandom.read(reinterpret_cast<char *>(&rng), size);
	return (rng % 100);
}

int main() {
	Tree<int> mytree(0);
	
	// for (size_t i = 0; i < 10; i++) {
		mytree.insert(0);
	// }
	std::cout << mytree << std::endl;
	
	mytree.remove_node(0);

	// mytree.insert(1);
	// mytree.insert(2);
	// mytree.insert(4);
	// mytree.insert(3);


	std::cout << mytree << std::endl;
}
