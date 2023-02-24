#pragma once

#include <iterator>

namespace ft {
	template<typename Key, typename T>
	class iteratorMap {
		public:
			typedef Key								key_type;
			typedef T								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef std::bidirectional_iterator_tag	iterator_category;

			key_type	first;
			value_type	second;

			/*
			**	constructor
			*/

			iteratorMap() {};

			// iteratorMap() :  {};

		private:
			pointer _begin;
			pointer _end;
	};

}