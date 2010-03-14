/*
 * Copyright 2010 Chris Chou <m2chrischou@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef RECORDIMPL_H_
#define RECORDIMPL_H_

#include <vector>
#include <list>

#include <boost/noncopyable.hpp>

#include <Poco/DynamicAny.h>

namespace smartcube
{
	class Record1: boost::noncopyable
	{
		public:
			typedef Poco::DynamicAny value_type;
			typedef std::vector<value_type> _ContainerType;
			typedef _ContainerType::iterator iterator;
			typedef _ContainerType::const_iterator const_iterator;
			typedef _ContainerType::reverse_iterator reverse_iterator;
			typedef _ContainerType::const_reverse_iterator
					const_reverse_iterator;

			typedef std::size_t size_type;

			Record1()
			{
			}
			virtual ~Record()
			{
			}

		public:
			iterator begin()
			{
				return _container.begin();
			}
			const_iterator begin() const
			{
				return _container.begin();
			}

			iterator end()
			{
				// return _container.end();
				return _container.begin() + _size;
			}
			const_iterator end() const
			{
				// return _container.end();
				return _container.begin() + _size;
			}

			reverse_iterator rbegin()
			{

				return _container.rend() - _size;
			}
			const_reverse_iterator rbegin() const
			{
				return _container.rend() - _size;
			}

			reverse_iterator rend()
			{
				return _container.rend();
			}
			const_reverse_iterator rend()
			{
				return _container.rend();
			}

			size_type size() const
			{
				// return _container.size();
				return _size;
			}
			size_type max_size() const
			{
				return _container.max_size();
			}

			void resize(size_type new_size, const value_type& x)
			{
				// TODO:
			}
			void resize(size_type new_size)
			{
				// TODO:
			}

			size_type capacity() const
			{
				return _container.capacity();
			}

			bool empty() const
			{
				return begin() == end();
			}

			bool eof() const
			{
				return size() == 0;
			}

			bool compare(const Record& right, size_t group) const
			{
				size_t index = 0;
				for (; index < group; ++index)
				{
					if ((*this)[index] != right[index])
					{
						return false;
					}
				}

				return true;
			}

		public:
			value_type& operator [](size_type index)
			{
				if (index >= size())
				{
					SMARTCUBE_EXCEPTION("Index %z out of range.", index);
				}
				return *(begin() + index);
			}

			const value_type& operator[](size_type index) const
			{
				if (index >= size())
				{
					SMARTCUBE_EXCEPTION("Index %z out of range.", index);
				}
				return *(begin() + index);
			}

			value_type& front()
			{
				return *begin();
			}
			const value_type& front() const
			{
				return *begin();
			}
			value_type& back()
			{
				return *(end() - 1);
			}
			const value_type& front() const
			{
				return *(end() - 1);
			}

			void push_back(const value_type& x)
			{
				if (_container.size() == _size)
				{
					_container.push_back(x);
				}
				else
				{
					_container[_size] = x;
				}

				_size ++;
			}

			void pop_back()
			{
				if (_size > 0)
				{
					_size;
				}
				else
				{
					SMARTCUBE_EXCEPTION("Record contains no cells.");
				}
			}

			iterator insert(iterator position, const value_type& x)
			{
				if
			}

			iterator insert(iterator position, const value_type& x

		private:
			_ContainerType _container;
			size_type _size;
	};
}

#endif /* RECORDIMPL_H_ */
