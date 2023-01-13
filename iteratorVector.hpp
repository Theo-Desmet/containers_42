#pragma once

#include <iterator>

namespace ft {
	template <class T>
	class iteratorVector {

		public:

			/*
			**	member types
			*/

			typedef T								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef std::random_access_iterator_tag	iterator_category;


			/*
			**	constructor
			*/

			iteratorVector() : _ptr(0) {};

			iteratorVector(pointer ptr) : _ptr(ptr) {};

			iteratorVector(iteratorVector const &copy) : _ptr(copy._ptr) {};

			iteratorVector operator=(iteratorVector const &copy) {
				if (this != &copy)
					this->_ptr = copy._ptr;
				return (*this);
			};

			~iteratorVector() {};

			/*
			**	member fonctions overload
			*/

			/*  BOOLEAN  */

			bool operator==(iteratorVector const &lhs) const {
				return (this->_ptr == lhs._ptr);
			}
			bool operator!=(iteratorVector const &lhs) const {
				return (this->_ptr != lhs._ptr);
			}
			bool operator<(iteratorVector const &lhs) const {
				return (this->_ptr < lhs._ptr);
			}
			bool operator<=(iteratorVector const &lhs) const {
				return (this->_ptr <= lhs._ptr);
			}
			bool operator>(iteratorVector const &lhs) const {
				return (this->_ptr > lhs._ptr);
			}
			bool operator>=(iteratorVector const &lhs) const {
				return (this->_ptr >= lhs._ptr);
			}

			/*  reference   */

			reference operator*() {
				return (*this->_ptr);
			}

			pointer operator->() {
				return (this->_ptr);
			}

			reference operator[](difference_type n) {
				return (*(this->_ptr + n));
			}

			/*  arithmetic   */

			iteratorVector operator+(difference_type lhs) const {
				return (iteratorVector(this->_ptr + lhs));
			}

			difference_type operator+(iteratorVector lhs) {
				return (difference_type(this->_ptr + lhs._ptr));
			}

			iteratorVector operator-(difference_type lhs) const {
				return (iteratorVector(this->_ptr - lhs));
			}

			difference_type operator-(iteratorVector lhs) {
				return (difference_type(this->_ptr - lhs._ptr));
			}

			void operator+=(int n) {
				this->_ptr += n;
			}

			void operator-=(int n) {
				this->_ptr -= n;
			}

			/*   incrementation   */

			iteratorVector& operator++() {
				++this->_ptr;
				return (*this);
			};

			iteratorVector  operator++(int){
				iteratorVector tmp(*this);
				++this->_ptr;
				return (tmp);
			};

			iteratorVector& operator--() {
				--this->_ptr;
				return (*this);
			};

			iteratorVector  operator--(int){
				iteratorVector tmp(*this);
				--this->_ptr;
				return (tmp);
			};





		private:
			value_type*	_ptr;
	};
}
