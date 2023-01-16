#pragma once

#include <iterator>

#include "iteratorVector.hpp"

namespace ft {
	template <class T>
	class iteratorConstVector {

		public:

			/*
			**	member types
			*/

			typedef T										value_type;
			typedef std::ptrdiff_t							difference_type;
			typedef T const*								pointer;
			typedef T const&								reference;
			typedef std::random_access_iterator_tag			iterator_category;


			/*
			**	constructor
			*/

			iteratorConstVector() : _ptr(0) {};

			iteratorConstVector(pointer ptr) : _ptr(ptr) {};

			iteratorConstVector(iteratorConstVector const &copy)
			: _ptr(copy._ptr) {};

			iteratorConstVector(iteratorVector<value_type> const &src) {
				this->_ptr = src.operator->();
			};


			~iteratorConstVector() {};

			/*
			**	member fonctions overload
			*/

			/*  BOOLEAN  */

			bool operator==(iteratorConstVector const &lhs) const {
				return (this->_ptr == lhs._ptr);
			}
			bool operator!=(iteratorConstVector const &lhs) const {
				return (this->_ptr != lhs._ptr);
			}
			bool operator<(iteratorConstVector const &lhs) const {
				return (this->_ptr < lhs._ptr);
			}
			bool operator<=(iteratorConstVector const &lhs) const {
				return (this->_ptr <= lhs._ptr);
			}
			bool operator>(iteratorConstVector const &lhs) const {
				return (this->_ptr > lhs._ptr);
			}
			bool operator>=(iteratorConstVector const &lhs) const {
				return (this->_ptr >= lhs._ptr);
			}

			/*  reference   */

			reference operator*() const {
				return (*this->_ptr);
			}

			pointer operator->() const {
				return (this->_ptr);
			}

			reference operator[](difference_type n) const {
				return (*(this->_ptr + n));
			}

			/*  arithmetic   */

			iteratorConstVector operator+(difference_type lhs) const {
				return (iteratorConstVector(this->_ptr + lhs));
			}

			difference_type operator+(iteratorConstVector lhs) {
				return (difference_type(this->_ptr + lhs._ptr));
			}

			iteratorConstVector operator-(difference_type lhs) const {
				return (iteratorConstVector(this->_ptr - lhs));
			}

			difference_type operator-(iteratorConstVector lhs) {
				return (difference_type(this->_ptr - lhs._ptr));
			}

			void operator+=(int n) {
				this->_ptr += n;
			}

			void operator-=(int n) {
				this->_ptr -= n;
			}

			/*   incrementation   */

			iteratorConstVector& operator++() {
				++this->_ptr;
				return (*this);
			};

			iteratorConstVector  operator++(int){
				iteratorConstVector tmp(*this);
				++this->_ptr;
				return (tmp);
			};

			iteratorConstVector& operator--() {
				--this->_ptr;
				return (*this);
			};

			iteratorConstVector  operator--(int){
				iteratorConstVector tmp(*this);
				--this->_ptr;
				return (tmp);
			};





		private:
			value_type const*	_ptr;
	};
}
