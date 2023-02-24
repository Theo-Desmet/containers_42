#pragma once

#include <memory>
#include <functional>

#include "./iteratorMap.hpp"
#include "../RBTree/RBTree.hpp"
#include "../utils/pair.hpp"

namespace ft {
	template < class Key, class T,
			class Compare = std::less<Key>,
			class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map {
		public:
			typedef	Key											key_type;
			typedef	T											mapped_type;
			typedef	std::pair<const key_type, mapped_type>		value_type;
			typedef	Compare										key_compare;
			// typedef					Key	value_compare;
			typedef	Alloc										allocator_type;
			typedef	typename allocator_type::reference			reference;
			typedef	typename allocator_type::const_reference	const_reference;
			typedef	typename allocator_type::pointer			pointer;
			typedef	typename allocator_type::const_pointer		const_pointer;
			typedef	iteratorMap<value_type, Tree<value_type, key_compare> >	
					iterator;
			typedef	iteratorMap<value_type, Tree<value_type, key_compare> >	
					iterator;
			typedef	iteratorMap<value_type, Tree<value_type, key_compare> >	
					iterator;
			typedef	iteratorMap<value_type, Tree<value_type, key_compare> >	
					iterator;
			typedef typename std::ptrdiff_t					difference_type;
			typedef typename std::size_t						size_type;


			/*
			**	constructor
			*/


			explicit map (const key_compare& comp = key_compare(),
            		const allocator_type& alloc = allocator_type())
					: _tree(comp, alloc) {};
				
			// template <class InputIterator>
			// map (InputIterator first, InputIterator last,
    		// 		const key_compare& comp = key_compare(),
			// 		const allocator_type& alloc = allocator_type()) {

			// };

			// map (const map& x) {

			// };


			/*
			**	modifier fonction members
			*/

			// pair<iterator,bool> insert (const value_type& val) {

			// };


	private:
		Tree<value_type, key_compare> _tree;
	};
}