#include <memory>

namespace ft{
	template<class T, class Allocator = std::allocator<T> >
	class vector {
		public:

			/*	
			**	member types
			*/

			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename Allocator_type::reference			reference;
			typedef typename Allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename std::ptrdiff_t 					difference_type;
			typedef typename std::size_t 						size_type;

			/*	
			**	constructor/destructor
			*/

			explicit vector (const allocator_type& alloc = allocator_type())
			: _ref_alloc(alloc), _ptr_t(NULL), _allocaded_mem(0)
			, _used_mem(0) {};

			explicit vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
			: _ref_alloc(alloc), _ptr_t(&val), _allocaded_mem(n)
			, _used_mem(n) {
				//new n
			};

			template <class InputIterator>
			vector (InputIterator first, InputIterator last, 
				const allocator_type& alloc = allocator_type())
			: _ref_alloc(alloc), _ptr_t(NULL) {
				//push_back
			};

			vector (const vector& x) {
				//copy
			};

			virtual ~destructor() {
				//delete all
			};


		/*	
		**	private members
		*/

		Allocator	&_ref_alloc;
		T			*_ptr_t;
		std::size_t	_allocaded_mem;
		std::size_t	_used_mem;

		//double the mem size
		void	_extend_mem_() {
			if (!_allocaded_mem) {
				_ptr_t = _ref_alloc.allocate(1);
				_allocaded_mem++;
			} else {
				T	*new_ptr_t = _ref_alloc.allocate(
					_allocaded_mem * 2, _ptr_t);
				_allocaded_mem *= 2;
				if (new_ptr_t != _ptr_t) {
					for (std::size_t i = 0, i < _used_mem, i++) {
						_ref_alloc.construct(new_ptr_t + i, *(_ptr_t + i))
						_ref_alloc.destroy(_ptr_t + i);
					}
					_ref_alloc.deallocate(_ptr_t);
					_ptr_t = new_ptr_t;
				}
			}
		}

	};
}