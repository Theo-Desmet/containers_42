#pragma once

#include <memory>

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
			typedef ft::iteratorConstVector<value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>			revserse_iterator;
			typedef ft::reverse_iterator<const_iterator>	revserse_cosnt_iterator;


			/*	
			**	constructor/destructor
			*/

			explicit vector (const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _ptr_t(NULL), _allocaded_mem(0), _used_mem(0) {};

			explicit vector (size_type n, const value_type& val = value_type()
			, const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _ptr_t(&val), _allocaded_mem(0), _used_mem(0) {
				_alloc.allocate(n);
				_allocaded_mem = n;
				for (std::size_t i = 0; i < n; i++)
					_alloc.construct(_ptr_t + i, n);
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
				return (this->_ptr_t);
			};

			const_iterator begin() const {
				return (this->_ptr_t);
			};

			iterator end() {
				return (this->_ptr_t + this->_used_mem);
			};

			const_iterator end() const {
				return (this->_ptr_t + this->_used_mem);
			};

			/*
			**	operator overload
			*/

			reference operator[] (size_type n) {
				return (this->_ptr_t[n]);
			};

			const_reference operator[] (size_type n) const {
				return (this->_ptr_t[n]);
			};

			/*	
			**	modifiers fonction:
			*/

			void push_back (const value_type& val){
				if (_used_mem == _allocaded_mem)
					_extend_mem_();
				_alloc.construct(_ptr_t + _used_mem, val);
				_used_mem++;
			}


		/*	
		**	private menbers fonction
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
	};
}