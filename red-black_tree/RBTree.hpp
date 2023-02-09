#pragma once

#include <iostream>
#include <functional>
#include <memory>


#define RED 1
#define BLACK 0
#define LEFT 1
#define RIGHT 0

template <class T>
struct Node {
	T		data;
	Node*	parent;
	Node*	left;
	Node*	right;
	bool	color;

	Node()	{};
	~Node()	{};
};


template <class T, class Compare = std::less<T>,
		class Allocator = std::allocator<T> >
class Tree {
	
	public :

		typedef T											value_type;

		typedef Allocator									allocator_type;
		typedef Compare										compare;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename std::ptrdiff_t 					difference_type;
		typedef typename std::size_t 						size_type;
		typedef typename Allocator::template rebind<Node<value_type> >::other
				node_allocator;

		node_allocator				_alloc;
		Node<value_type>*			_root_node;
		Node<value_type>*			_null_node;
		/*
		**	constructor/destructor
		*/

		Tree() {
			__init_node();
		};

		Tree(value_type data) {
			__init_node();
			this->_root_node->data = data;
		};

		// Tree(Tree& const lhs) {
		// 	this->_null_node = lhs._null_node;
		// };
		//add iterator

		~Tree() {
			this->_alloc.deallocate(this->_null_node, 1);
			this->_alloc.deallocate(this->_root_node, 1);
			//add loop free
		}

		// Tree& operator=(Tree& const lhs) {
			
		// }
		//add iterator

		/*
		**	public member fonctions
		*/

		void insert(value_type const new_elem, Compare cmp = std::less<T>()) {
			Node<value_type>*	act_node = this->_root_node;
			Node<value_type>*	parent;
			bool 	direction;

			while (act_node && act_node != this->_null_node) {
				if (cmp(new_elem, act_node->data)) {
					parent = act_node;
					act_node = act_node->left;
					direction = LEFT;
				} else if (cmp(act_node->data, new_elem)){
					parent = act_node;
					act_node = act_node->right;
					direction = RIGHT;
				} else {
					return ;
				}
			}

			act_node = parent;
			if (direction == LEFT) {
				act_node->left = __new_node(act_node, new_elem);
				insert_balance(act_node->left);
			}
			if (direction == RIGHT) {
				act_node->right = __new_node(act_node, new_elem);
				insert_balance(act_node->right);
			}
		}

		void insert_balance(Node<value_type>* node) {
			while (node->parent->color == RED) {
				if (!node->parent->parent || !node->parent) {
					break;
				}
				if (node->parent->parent->right 
						&& node->parent->parent->right == node->parent) {
					if (node->parent->parent->left
							&& node->parent->parent->left->color == RED) {
						node->parent->parent->left->color = BLACK;
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					} else {
						if (node == node->parent->left) {
							node = node->parent;
							rotate_right(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						rotate_left(node->parent->parent);
					}
				} else {
					if (node->parent->parent->right
							&& node->parent->parent->right->color == RED) {
						node->parent->parent->right->color = BLACK;
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					} else {
						if (node == node->parent->right) {
							node = node->parent;
							rotate_left(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						rotate_right(node->parent->parent);
					}					
				}
				if (node == this->_root_node)
					break;
			}
			this->_root_node->color = BLACK;
		}

		Node<value_type>*	search(value_type const new_elem
				, Compare cmp = std::less<T>()) {
			Node<value_type>* act_node = this->_root_node;

			while (act_node && act_node != this->_null_node) {
				if (cmp(new_elem, act_node->data)) {
					act_node = act_node->left;
				} else if (cmp(act_node->data, new_elem)){
					act_node = act_node->right;
				}
			}
			return (act_node)
		}

		Node<value_type>*	find_minimum(Node<value_type>* node) {
			while (node->left && node->left != this->_null_node)
				node = node->left;

			return (node);
		}

		Node<value_type>*	find_maximum(Node<value_type>* node) {
			while (node->right && node->right != this->_null_node)
				node = node->right;

			return (node);
		}

		void	delete_node(value_type const elem
				, Compare cmp = std::less<T>()) {
			Node<value_type>*	node = search(elem, cmp);
			if (!node)
				return ;
			Node<value_type>*	temp;
			bool	color = node->color;
		
			if (!node->left || node->left == this->_null_node
					|| !node->right || node->right == this->_null_node) {
				temp = node->parent;
				color = node->color;			
			} else {
 				Node inOrderSuccessor = find_minimum(node.right);

			}
		}

		/*
		**	utils fonctions
		*/

		Node<value_type>*	get_node(value_type elem,
				Compare cmp = std::less<T>()) const {
			Node<value_type>*	act_node = this->_root_node;

			while (act_node->data != elem && act_node
					&& act_node != this->_null_node) {
				if (cmp(elem, act_node->data)) {
					act_node = act_node->left;
				} else {
					act_node = act_node->right;
				}
			}
			return (act_node);
		}

		void	rotate_right(Node<value_type>* node) {
			Node<value_type>* temp = node->left;
			
			node->left = temp->right;
			if (temp->right)
				temp->right->parent = node;
			temp->parent = node->parent;
			if (node == this->_root_node)
				this->_root_node = temp;
			if (node->parent->right == node) {
				node->parent->right = temp;
			} else {
				node->parent->left = temp;
			}
			temp->right = node;
			node->parent = temp;
		}

		void	rotate_left(Node<value_type>* node) {
			Node<value_type>* temp = node->right;
			
			node->right = temp->left;
			if (temp->left)
				temp->left->parent = node;
			temp->parent = node->parent;
			if (node == this->_root_node)
				this->_root_node = temp;
			if (node->parent->left == node) {
				node->parent->left = temp;
			} else {
				node->parent->right = temp;
			}
			temp->left = node;
			node->parent = temp;
		}

	private :


		/*
		**	private menber fonctions
		*/

		void	__init_node() {
			this->_root_node = this->_alloc.allocate(1);
			this->_null_node = this->_alloc.allocate(1);
			this->_root_node->parent = this->_null_node;
			this->_root_node->left = this->_null_node;
			this->_root_node->right = this->_null_node;
			this->_root_node->color = BLACK;
			this->_null_node->parent = NULL;
			this->_null_node->left = NULL;
			this->_null_node->right = NULL;
			this->_null_node->color = BLACK;
		}

		Node<value_type>* __new_node(Node<value_type>* parent,
				value_type data) {
			Node<value_type>	*new_node;
			new_node = this->_alloc.allocate(1);
			new_node->parent = parent;
			new_node->left = NULL;
			new_node->right = NULL;
			new_node->data = data;
			new_node->color = RED;		
			return (new_node);
		}


		
};