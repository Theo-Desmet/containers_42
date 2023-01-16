#pragma once

#include <memory>
#include <stdexcept>
#include <sstream>

#include "reverse_iterator.hpp"
#include "iteratorVector.hpp"
#include "iteratorConstVector.hpp"

namespace ft{
	template<class T, class Allocator = std::allocator<T> >
	class vector {

		/*	
		**	private members
		*/

		private:
			Allocator	_alloc;
			T			*_ptr_t;
			std::size_t	_allocaded_mem;
			std::size_t	_used_mem;

		public:

			/*	
			**	member types
			*/

			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename std::ptrdiff_t 					difference_type;
			typedef typename std::size_t 						size_type;

			typedef ft::iteratorVector<value_type>			iterator;
			typedef ft::iteratorConstVector<value_type> 	const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;


			/*	
			**	constructor/destructor
			*/

			explicit vector (const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _ptr_t(NULL), _allocaded_mem(0), _used_mem(0) {};

			explicit vector (size_type n, const value_type& val = value_type()
			, const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _ptr_t(NULL), _allocaded_mem(0), _used_mem(0) {
				this->reserve(n);
				for (std::size_t i = 0; i < n; i++)
					_alloc.construct(_ptr_t + i, val);
				_allocaded_mem = n;
				_used_mem = n;



				//change for insert whit opti extend



			};

			template <class InputIterator>
			vector (InputIterator first, InputIterator last, 
				const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _ptr_t(NULL), _allocaded_mem(0), _used_mem(0) {
				difference_type diff = last - first;
				_alloc.allocate(diff);
				_allocaded_mem = (diff);
				for (std::size_t i = 0; i < diff; i++)
					_alloc.construct(_ptr_t + i , first + i);
				_used_mem = (diff);
			};

			vector (const vector& x) : _alloc(allocator_type())
			, _ptr_t(0), _allocaded_mem(0), _used_mem(0) {
				*this = x;
			};

			virtual ~vector() {
				for (std::size_t i = 0; i < _used_mem; i++) {
					_alloc.destroy(_ptr_t + i);
				}
				if (_allocaded_mem != 0) 
					_alloc.deallocate(_ptr_t, _allocaded_mem);
			};

			/*
			**	iterator fonctions
			*/

			iterator begin() {
				return (iterator(_ptr_t));
			};

			const_iterator begin() const {
				return (const_iterator(this->_ptr_t));
			};

			iterator end() {
				return (iterator(this->_ptr_t + this->_used_mem));
			};

			const_iterator end() const {
				return (const_iterator(this->_ptr_t + this->_used_mem));
			};

			reverse_iterator rbegin() {
				return (reverse_iterator(this->_ptr_t + this->_used_mem));
			};

			const_reverse_iterator rbegin() const {
				return (reverse_const_iterator(this->_ptr_t + this->_used_mem));
			};

			reverse_iterator rend() {
				return (reverse_iterator(this->_ptr_t));
			};

			const reverse_iterator rend() const {
				return (reverse_const_iterator(this->_ptr_t));
			};

			/*	
			**	capacity fonction:
			*/

			size_type size() const {
				return (this->_used_mem);
			};

			size_type max_size() const {
				return (this->_alloc.max_size());
			};

			void resize (size_type n, value_type val = value_type()) {
				if (n < this->_used_mem) {
					for (std::size_t i = this->_used_mem; i > n; i--)
						this->_alloc.destroy(_ptr_t + i);
					this->_used_mem = n;
				} else if (n > this->_used_mem) {
					while (n > this->_allocaded_mem)
						this->_extend_mem_();
					for (std::size_t i = this->_used_mem; i < n; i++)
						this->_alloc.construct(_ptr_t + i, val);
					this->_used_mem = n;
				}
			};


			size_type capacity() const {
				return (this->_allocaded_mem);
			};

			bool empty() const {
				return (!_used_mem);
			};

			void reserve (size_type n) {
				if (n <= this->_allocaded_mem)
					return;
				value_type* new_ptr = _alloc.allocate(n);
				for (std::size_t i = 0; i < _used_mem; i++) {
					_alloc.construct(new_ptr + i, *(this->_ptr_t + i));
					_alloc.destroy(_ptr_t + i);
				}
				_ptr_t = new_ptr;
				_allocaded_mem = n;
				_used_mem = n;
			};

			/*
			**	element access fonctions
			*/

			reference operator[] (size_type n) {
				return (this->_ptr_t[n]);
			};

			const_reference operator[] (size_type n) const {
				return (this->_ptr_t[n]);
			};

		    reference at (size_type n) {
				if (n >= this->_used_mem)
					throw std::out_of_range(this->_out_of_range(this->_used_mem));
				return (this->_ptr_t[n]);
			};

			const_reference at (size_type n) const {
				return (this->_ptr_t[n]);
			};


			reference front() {
				return (*(this->_ptr_t));
			};

			const_reference front() const {
				return (*(this->_ptr_t));
			};

			reference back() {
				return (*(this->_ptr_t + this->_used_mem - 1));
			};

			const_reference back() const {
				return (*(this->_ptr_t + this->_used_mem - 1));
			};


			/*	
			**	modifiers fonction:
			*/

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last) {
				this->clear();
				for ( ; first < last; first++)
					this->_alloc.construct(this->_ptr_t + first, *first);
				this->_used_mem = last - first;
			};

			void assign (size_type n, const value_type& val) {
				this->clear();
				for (std::size_t i = 0; i < n; i++)
					this->_alloc.construct(this->_ptr_t + i, val);
				this->_used_mem = n;
			};

			void push_back (const value_type& val){
				if (_used_mem == _allocaded_mem)
					_extend_mem_();
				_alloc.construct(_ptr_t + _used_mem, val);
				_used_mem++;
			}

			void pop_back (){
				_alloc.destroy(_ptr_t + _used_mem);
				_used_mem--;
			}

			void clear() {
				for (std::size_t i = 0; i < this->_used_mem; i++)
					this->_alloc.destroy(this->_ptr_t + i);
				this->_used_mem = 0;
			};

		/*	
		**	private members fonction
		*/

		//double the mem size
		void	_extend_mem_() {
			if (!_allocaded_mem) {
				_ptr_t = _alloc.allocate(1);
				_allocaded_mem++;
			} else {
				T	*new_ptr_t = _alloc.allocate(
					_allocaded_mem * 2, _ptr_t);
				if (new_ptr_t != _ptr_t) {
					for (std::size_t i = 0; i < _used_mem; i++) {
						_alloc.construct(new_ptr_t + i, *(_ptr_t + i));
						_alloc.destroy(_ptr_t + i);
					}
					_alloc.deallocate(_ptr_t, _allocaded_mem);
					_ptr_t = new_ptr_t;
				}
				_allocaded_mem *= 2;
			}
		}

		std::string	_out_of_range(size_type pos) {
			std::stringstream ss;

			ss << "vector::_M_range_check: __n (which is "
			<< pos << ") >= this->size() (which is " << this->_used_mem << ")";
			return (ss.str());
		};
	};
}