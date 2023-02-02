#pragma once

#include <iostream>
#include <memory>


#define RED 1
#define BLACK 0

template <typename T>
struct Node {
	T&		data;
	Node*	parent;
	Node*	left;
	Node*	right;
	bool	color;

	Node()	{};
	~Node()	{};
};


template <typename T, class Allocator = std::allocator<T> >
class Tree {
	
	public :
		typedef T											value_type;

		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename std::ptrdiff_t 					difference_type;
		typedef typename std::size_t 						size_type;
		typedef typename Allocator::template rebind<Node<value_type> >::other
				node_allocator;

		/*
		**	constructor/destructor
		*/

		Tree() {
			init_node();
		};

		Tree(value_type data) {
			init_node();
			this->_root_node->data = data;
		};

		// Tree(Tree& const lhs) {
		// 	this->_null_node = lhs._null_node;
		// };
		//add iterator

		~Tree() {
			this->_alloc.deallocate(this->_null_node, 1);
			this->_alloc.deallocate(this->_root_node, 1);
		}

		// Tree& operator=(Tree& const lhs) {
			
		// }
		//add iterator

		/*
		**	private menber fonctions
		*/

		void insert(value_type const new_elem) {
			new_node = new_node(new_elem);
			while (new_node )
		}

	private :
		node_allocator				_alloc;
		Node<value_type>*			_root_node;
		Node<value_type>*			_null_node;

		void	init_node() {
			this->_root_node = this->_alloc.allocate(1);
			this->_null_node = this->_alloc.allocate(1);
			this->_root_node->parent = this->_null_node;
			this->_root_node->left = this->_null_node;
			this->_root_node->right = this->_null_node;
			this->_root_node->color = BLACK;
		}

		Node<value_type>& new_node(value_type data) const{
			Node<T>	*new_node;
			new_node = this->_alloc.allocate(1);
			new_node->parent = nullptr;
			new_node->left = nullptr;
			new_node->right = nullptr;
			new_node->data = data;
			new_node->color = RED;

			return (*this);
		}
};