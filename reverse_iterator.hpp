#pragma once

#include <iterator>

#include "iterator_traits.hpp"

namespace ft{
	template <class Iterator>
	class reverse_iterator{

		public:

			/*
			**	member types
			*/

			typedef Iterator iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;

			/*
			**	constructor
			*/

			reverse_iterator() : _base_iterator() {};

			explicit reverse_iterator (iterator_type it)
			: _base_iterator(it) {};

			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it)
			: _base_iterator(rev_it.base()) {};

			/*
			** member fonctions
			*/

			iterator_type base() const {
				return (this->_base_iterator);
			};

			/*
			** member fonctions overloads
			*/

			reference operator*() const {
				Iterator tmp = this->_base_iterator;
				return  (*--tmp);
			};

			reverse_iterator operator+ (difference_type n) const {
				return (this->_base_iterator - n);
			};

			reverse_iterator& operator+= (difference_type n) {
				return (*this->_base_iterator -= n);
			};


			reverse_iterator& operator++() {
				--this->_base_iterator;
				return (*this);
			};

			reverse_iterator  operator++(int){
				reverse_iterator tmp(*this);
				--this->_base_iterator;
				return (tmp);
			};

			reverse_iterator operator- (difference_type n) const {
				return (this->_base_iterator + n);
			};

			reverse_iterator& operator-= (difference_type n) {
				return (*this->_base_iterator += n);
			};


			reverse_iterator& operator--() {
				++this->_base_iterator;
				return (*this);
			};

			reverse_iterator  operator--(int){
				reverse_iterator tmp(*this);
				++this->_base_iterator;
				return (tmp);
			};

			pointer operator->() const {
				return &(operator*());
			}

			reference operator[] (difference_type n) const {
				Iterator tmp = this->_base_iterator;
				return (*tmp - n);
			};


		protected:

			iterator_type _base_iterator;
	};

	/*		
	**	non member fonctions overload
	*/

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs
	, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() == rhs.base());
	};

	template <class Iterator> 
	bool operator!=(const reverse_iterator<Iterator>& lhs
	, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() != rhs.base());
	};

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs
	, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() < rhs.base());
	};

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs
	, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() <= rhs.base());
	};
	
	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs
	, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() > rhs.base());
	};

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs
	, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() >= rhs.base());
	};

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (
	typename reverse_iterator<Iterator>::difference_type n
	, const reverse_iterator<Iterator>& rev_it) {
		return (reverse_iterator<Iterator>(rev_it.base() - n));
	};

	template <class Iterator>
	reverse_iterator<Iterator> operator- (
	typename reverse_iterator<Iterator>::difference_type n
	, const reverse_iterator<Iterator>& rev_it) {
		return (reverse_iterator<Iterator>(rev_it.base() + n));
	};

}