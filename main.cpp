#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <unistd.h>



#include "vector.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "is_integral.hpp"
#include "enable_if.hpp"
#include "make_pair.hpp"
#include "pair.hpp"


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


int main ()
{
  ft::vector<int> myvector (3,100);
  ft::vector<int>::iterator it;

  it = myvector.begin();
  it = myvector.insert ( it , 200 );

  myvector.insert (it,2,300);

  // "it" no longer valid, get a new one:
  it = myvector.begin();

  ft::vector<int> anothervector (2,400);
  myvector.insert (it+2,anothervector.begin(),anothervector.end());

  int myarray [] = { 501,502,503 };
  myvector.insert (myvector.begin(), myarray, myarray+3);

  std::cout << "myvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}