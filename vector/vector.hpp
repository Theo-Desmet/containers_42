#pragma once

#include <memory>
#include <stdexcept>
#include <sstream>

#include "iteratorVector.hpp"
#include "../utils/reverse_iterator.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/is_integral.hpp"

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
			typedef ft::iteratorVector<value_type const> 	const_iterator;
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
				this->_ptr_t = this->_alloc.allocate(n);
				for (std::size_t i = 0; i < n; i++)
					_alloc.construct(_ptr_t + i, val);
				_allocaded_mem = n;
				_used_mem = n;
			};

			template <class InputIt>
			vector (InputIt first, InputIt last, 
					const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIt>::value,
					bool>::type = true)
					: _alloc(alloc), _ptr_t(NULL), _allocaded_mem(0),
					_used_mem(0) {
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

			 vector& operator= (const vector& x) {
				if (this == &x)
					return (*this);
				this->reserve(x._allocaded_mem);

				iterator it = this->begin();
				for (size_t i = 0; i < x._allocaded_mem; i++, it++)
					*it = x[i];
				this->_used_mem = x._used_mem;
				return (*this);
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
					throw std::out_of_range(this->_out_of_range(
							this->_used_mem));
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

			template <class InputIt>
			void assign (InputIt first, InputIt last,
					typename ft::enable_if<!ft::is_integral<InputIt>::value,
					bool>::type = true) {
				size_t	dist = last - first;
				this->clear();
				if (dist > this->_allocaded_mem) {
					this->_alloc.deallocate(this->_ptr_t, this->_allocaded_mem);
					this->_ptr_t = this->_alloc.allocate(dist);
					this->_allocaded_mem = dist;
				}
				for (std::size_t i = 0; i < dist; i++, ++first)
					this->_alloc.construct(this->_ptr_t + i, *first);
				this->_used_mem = dist;
			};

			void assign (size_type n, const value_type& val) {
				this->clear();
				if (n > this->_allocaded_mem) {
					this->_alloc.deallocate(this->_ptr_t, this->_allocaded_mem);
					this->_ptr_t = this->_alloc.allocate(n);
					this->_allocaded_mem = n;
				}
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

			void pop_back() {
				_alloc.destroy(_ptr_t + _used_mem);
				_used_mem--;
			}

			iterator insert (iterator pos, const value_type& val) {
				size_t dist = &(*pos) - this->_ptr_t;
				if (this->_allocaded_mem == this->_used_mem)
					_extend_mem_();
				for (size_t i = this->_used_mem; i > dist; i--) {
					this->_alloc.destroy(this->_ptr_t + i);
					this->_alloc.construct(this->_ptr_t + i,
						*(this->_ptr_t + i - 1));
				}				
				this->_alloc.destroy(this->_ptr_t + dist);
				this->_alloc.construct(this->_ptr_t + dist, val);
				this->_used_mem++;

				return (begin() + dist);
			};

			void insert (iterator pos, size_type n, const value_type& val) {
				size_t dist = &(*pos) - this->_ptr_t;
				while (this->_used_mem + n > this->_allocaded_mem)
					_extend_mem_();
				for (size_t i = this->_used_mem; i > dist; i--) {
					this->_alloc.destroy(this->_ptr_t + i + n - 1);
					this->_alloc.construct(this->_ptr_t + i + n - 1,
						*(this->_ptr_t + i - 1));
				}
				for (size_t i = 0; i < n; i++)	{
					this->_alloc.destroy(this->_ptr_t + i + dist);
					this->_alloc.construct(this->_ptr_t + i + dist, val);
				}
				this->_used_mem += n;
			};

			template <class InputIt>
		    void insert (iterator pos, InputIt first, InputIt last,
					typename ft::enable_if<!ft::is_integral<InputIt>::value,
					bool>::type = true) {
				size_t dist = &(*pos) - this->_ptr_t;
				size_t count = last - first;
				while (this->_used_mem + dist > this->_allocaded_mem)
					_extend_mem_();
				for (size_t i = this->_used_mem; i > dist; i--) {
					this->_alloc.destroy(this->_ptr_t + i + count - 1);
					this->_alloc.construct(this->_ptr_t + i + count - 1,
						*(this->_ptr_t + i - 1));
				}
				for (size_t i = 0; i < count; i++, first++)	{
					this->_alloc.destroy(this->_ptr_t + i + count);
					this->_alloc.construct(this->_ptr_t + i + dist, *first);
				}
				this->_used_mem += count;
			};

			iterator erase (iterator pos) {
				for (pointer i = &(*pos); i < this->_ptr_t + this->_used_mem;
						i++) {
					this->_alloc.destroy(i);
					this->_alloc.construct(i, *(i + 1));
				}
				this->_used_mem--;
				
				return (pos);
			};

			iterator erase (iterator first, iterator last) {
				size_t	dist = last - first;
				pointer	pos = &(*first);

				for (pointer i = &(*first);
						i < (this->_ptr_t + this->_used_mem - dist) ; i++) {
					this->_alloc.destroy(i);
					this->_alloc.construct(i, *(i + dist));
				}
				for (pointer i = &(*first) + this->_used_mem - dist;
						i < (this->_ptr_t + this->_used_mem ); i++)
					this->_alloc.destroy(i);
				this->_used_mem -= dist;

				return (pos);
			};

			void swap (vector& x) {
				pointer	temp_ptr = x._ptr_t;
				x._ptr_t = this->_ptr_t;
				this->_ptr_t = temp_ptr;

				allocator_type	temp_alloc = x._alloc;
				x._alloc = this->_alloc;
				this->_alloc = temp_alloc;

				size_t	temp = x._allocaded_mem;
				x._allocaded_mem = this->_allocaded_mem;
				this->_allocaded_mem = temp;

				temp = x._used_mem;
				x._used_mem = this->_used_mem;
				this->_used_mem = temp;
			};

			void clear() {
			for (size_type i = 0; i < this->_used_mem; i++)
				this->_alloc.destroy(this->_ptr_t + i);
			this->_used_mem = 0;
			};


			/*	
			**	allocator fonction
			*/

			allocator_type get_allocator() const {
				return (this->_alloc);
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

/*	
**	non-menber fonction overloads
*/

template <class T, class Alloc>
bool operator==(const ft::vector<T,Alloc>& lhs
		, const ft::vector<T,Alloc>& rhs) {
	if (lhs.size() != rhs.size())
		return (false);
	for (size_t i = 0; i < lhs.size(); i++) {
		if (lhs[i] != rhs[i])
			return (false);
	}
	return (true);
};

template <class T, class Alloc>
bool operator!= (const ft::vector<T,Alloc>& lhs,
		const ft::vector<T,Alloc>& rhs) {
	if (lhs.size() != rhs.size())
		return (true);
	for (size_t i = 0; i < lhs.size(); i++) {
		if (lhs[i] != rhs[i])
			return (true);
	}
	return (false);
};

template <class T, class Alloc>
bool operator<(const ft::vector<T,Alloc>& lhs
		, const ft::vector<T,Alloc>& rhs) {
	if (lhs.size() > rhs.size())
		return (true);
	for (size_t i = 0; i < lhs.size(); i++) {
		if (lhs[i] > rhs[i])
			return (true);
	}
	return (false);
};

template <class T, class Alloc>
bool operator<=(const ft::vector<T,Alloc>& lhs
		, const ft::vector<T,Alloc>& rhs) {
	if (lhs.size() >= rhs.size())
		return (true);
	for (size_t i = 0; i < lhs.size(); i++) {
		if (lhs[i] >= rhs[i])
			return (true);
	}
	return (false);
};

template <class T, class Alloc>
bool operator>(const ft::vector<T,Alloc>& lhs
		, const ft::vector<T,Alloc>& rhs) {
	if (lhs.size() > rhs.size())
		return (false);
	for (size_t i = 0; i < lhs.size(); i++) {
		if (lhs[i] > rhs[i])
			return (false);
	}
	return (true);
};

template <class T, class Alloc>
bool operator>=(const ft::vector<T,Alloc>& lhs
		, const ft::vector<T,Alloc>& rhs) {
	if (lhs.size() >= rhs.size())
		return (false);
	for (size_t i = 0; i < lhs.size(); i++) {
		if (lhs[i] >= rhs[i])
			return (false);
	}
	return (true);
};

template <class T, class Alloc>
void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y) {
	x.swap(y);
};