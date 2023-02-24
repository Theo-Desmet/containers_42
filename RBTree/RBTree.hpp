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
		compare						_cmp;
		Node<value_type>*			_root_node;
		Node<value_type>*			_null_node;
		/*
		**	constructor/destructor
		*/

		Tree(const compare &comp = compare(),
            	const allocator_type &alloc = allocator_type())
            	: _alloc(alloc), _cmp(comp) {
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
			Node<value_type>* temp = this->_root_node;
			Node<value_type>* node = NULL;
			while (this->_root_node) {
				node = search_min(temp);
				if (node == this->_root_node)
					break ;
				temp = node->parent;
				__delete_node(node);
				this->_alloc.destroy(node);
				this->_alloc.deallocate(node, 1);
			}
			this->_alloc.deallocate(this->_null_node, 1);
			this->_alloc.deallocate(this->_root_node, 1);
			this->_alloc.destroy(this->_null_node);
			this->_alloc.destroy(this->_root_node);

		}

		// Tree& operator=(Tree& const lhs) {
			
		// }
		//add iterator

		/*
		**	public member fonctions
		*/

		void insert(value_type const new_elem, compare _cmp) {
			Node<value_type>*	act_node = this->_root_node;
			Node<value_type>*	parent;
			bool 	direction;

			if (!this->_root_node) {
				this->_root_node = __new_node(act_node, new_elem);
				this->_root_node->color = BLACK;
				return ;
			}
			while (act_node && act_node != this->_null_node) {
				if (_cmp(new_elem, act_node->data)) {
					parent = act_node;
					act_node = act_node->left;
					direction = LEFT;
				} else if (_cmp(act_node->data, new_elem)){
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

		void	remove_node(value_type const elem
				, compare _cmp) {
			Node<value_type>*	node = search(elem, _cmp);
			Node<value_type>*	temp;
			if (!node)
				return ;
			bool	color_del = node->color;

			if (node->left == this->_null_node) {
				temp = node->right;
				transplant(node, node->right);
			} else if (node->right == this->_null_node) {
				temp = node->left;
				transplant(node, node->left);
			} else {
				Node<value_type>* right_smallest = find_minimum(node->right);
				color_del = right_smallest->color;
				temp = right_smallest->right;
				if (right_smallest->parent == node) {
					temp->parent = right_smallest;
				} else {
					transplant(right_smallest, right_smallest->right);
					right_smallest->right = node->right;
					right_smallest->right->parent = right_smallest;
				}

				transplant(node, right_smallest);
				right_smallest->left = node->left;
				right_smallest->left->parent = right_smallest;
				right_smallest->color = node->color;
			}
			if (node->right == this->_root_node)
				this->_root_node = NULL;
			this->_alloc.deallocate(node, 1);
			if (color_del == BLACK) {
				remove_rebalance(temp);
			}
			this->_null_node->parent = this->_root_node;
		}

		void	remove_rebalance(Node<value_type>* node) {
			Node<value_type>*	sibling;
		    while (node != this->_root_node && node->color == BLACK) {
				if (node == node->parent->left) {
					sibling = node->parent->right;
					if (sibling->color == RED) {
						sibling->color = BLACK;
						node->parent->color = RED;
						rotate_left(node->parent);
						sibling = node->parent->right;
					}

					if (sibling->left->color == BLACK 
							&& sibling->right->color == BLACK) {
						sibling->color = RED;
						node = node->parent;
					} else {
						if (sibling->right->color == BLACK) {
							sibling->left->color = BLACK;
							sibling->color = RED;
							rotate_right(sibling);
							sibling = node->parent->right;
						}
					sibling->color = node->parent->color;
					node->parent->color = BLACK;
					sibling->right->color = BLACK;
					rotate_left(node->parent);
					node = this->_root_node;
					}
				} else {
					sibling = node->parent->left;
					if (sibling->color == RED) {
						sibling->color = BLACK;
						node->parent->color = RED;
						rotate_right(node->parent);
						sibling = node->parent->left;
					}

					if (sibling->right->color == BLACK 
							&& sibling->left->color == BLACK) {
						sibling->color = RED;
						node = node->parent;
					} else {
						if (sibling->left->color == BLACK) {
							sibling->right->color = BLACK;
							sibling->color = RED;
							rotate_left(sibling);
							sibling = node->parent->left;
						}

					sibling->color = node->parent->color;
					node->parent->color = BLACK;
					sibling->left->color = BLACK;
					rotate_right(node->parent);
					node = _root_node;
					}
				}
			}
			node->color = 0;
		}

		/*
		**	utils fonctions
		*/

		Node<value_type>*	search(value_type const new_elem
				, compare _cmp) {
			Node<value_type>* act_node = this->_root_node;

			while (1) {
				if (act_node == this->_null_node)
					return (NULL);
				if (_cmp(new_elem, act_node->data)) {
						act_node = act_node->left;
				} else if (_cmp(act_node->data, new_elem)) {
						act_node = act_node->right;
				} else {
					return (act_node);
				}
			}
		}

		void transplant(Node<value_type>* x, Node<value_type>* y) {
			if (x->parent == this->_null_node)
				this->_root_node = y;
			if (x == x->parent->left) {
				x->parent->left = y;
			} else {
				x->parent->right = y;
			}
			y->parent = x->parent;
  		}

		Node<value_type>*	search_min(Node<value_type>* node) {
			Node<value_type>* temp;
			
			while (1) {
				temp = node;
				while (node->left && node->left != this->_null_node)
					node = node->left;
				if (node->right && node->right != this->_null_node)
					node = node->right;
				if (node == temp)
					break ;
			}

			return (node);
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

		Node<value_type>*	get_node(value_type elem,
				compare _cmp) const {
			Node<value_type>*	act_node = this->_root_node;

			while (act_node->data != elem && act_node
					&& act_node != this->_null_node) {
				if (_cmp(elem, act_node->data)) {
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
			if (temp->right != this->_null_node)
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
			if (temp->left != this->_null_node)
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

		int    getBlackHeight(Node<value_type>* node)
		{
			if (node == this->_null_node)
				return (0);
			int     left = getBlackHeight(node->left);
			int     right = getBlackHeight(node->right);
			int     cur = node->color;
			if (left == -1 || right == -1 || left != right)
				return (-1);
			else
				return (left + cur);
		}

		bool redChildAreBlack(Node<value_type>* node)
		{
			bool left = true;
			bool right = true;
			if (node == this->_null_node)
				return (true);
			if (node->color == RED)
			{
				if (node->left != this->_null_node)
					left = node->left->color == BLACK;
				if (node->right != this->_null_node)
					right = node->right->color == BLACK;
			}
			return (this->_root_node->color == BLACK && right && left
					&& redChildAreBlack(node->left)
					&& redChildAreBlack(node->right));
		}

		bool isValidTree(void)
		{
			return (getBlackHeight(this->_root_node) >= 0
					&& redChildAreBlack(this->_root_node));
		}

	private :


		/*
		**	private member fonctions
		*/

		void	__init_node() {
			this->_root_node = this->_alloc.allocate(1);
			this->_null_node = this->_alloc.allocate(1);

			this->_root_node->parent = this->_null_node;
			this->_root_node->left = this->_null_node;
			this->_root_node->right = this->_null_node;
			this->_root_node->color = BLACK;

			this->_null_node->parent = this->_root_node;
			this->_null_node->left = NULL;
			this->_null_node->right = NULL;
			this->_null_node->color = BLACK;
		}

		void	__delete_node(Node<value_type>*  node) {
			if (node->parent->right == node)
				node->parent->right = this->_null_node;
			if (node->parent->left == node)
				node->parent->left = this->_null_node;
		}

		Node<value_type>* __new_node(Node<value_type>* parent,
				value_type data) {
			Node<value_type>	*new_node;
			new_node = this->_alloc.allocate(1);
			new_node->parent = parent;
			new_node->left = _null_node;
			new_node->right = _null_node;
			new_node->data = data;
			new_node->color = RED;		
			return (new_node);
		}


		
};