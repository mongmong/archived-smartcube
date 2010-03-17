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

#ifndef RECORD_H_
#define RECORD_H_

#include <stdint.h>
#include <memory>
#include <vector>

#include <boost/variant.hpp>

#include <Poco/SharedPtr.h>

#include "Cell.h"
#include "Error.h"

namespace smartcube
{

	/*
	class Cell : public boost::variant<int64_t, double, bool, std::string>
	{
		void a()
		{
			this->o
			this->which();
		}
	};
	*/


	class Record: public std::vector<Cell>
	{
		public:

			Record() {};
			virtual ~Record() {};

			inline bool eof() const
			{
				return size() == 0;
			}

			inline bool compare(const Record& right, size_t group) const
			{
				size_t index = 0;
				for (; index < group; ++index)
				{
					if ((*this)[index] == right[index])
					{
					}
					else
					{
						return false;
					}
				}

				return true;
			}

		public:
			inline Cell& operator [](std::size_t index)
			{
				/*
				if (index > 1000)
				{
					if (1000 - (int) index < -static_cast<int> (size()))
					{
						SMARTCUBE_EXCEPTION("Index %z out of range.", index);
					}
					return end()[1000 - (int) index];
				}
				else*/
				{
					if (index >= size())
					{
						SMARTCUBE_EXCEPTION("Index %z out of range.", index);
					}
					return *(begin() + index);
				}
			}

			inline const Cell& operator[] (std::size_t index) const
			{
				/*
				if (index > 1000)
				{
					if (1000 - (int) index < -static_cast<int> (size()))
					{
						SMARTCUBE_EXCEPTION("Index %z out of range.", index);
					}
					return end()[1000 - (int) index];
				}
				else*/
				{
					if (index >= size())
					{
						SMARTCUBE_EXCEPTION("Index %z out of range.", index);
					}
					return *(begin() + index);
				}
			}

			Record& operator = (const python::object& rhs)
			{
				this->clear();

				ssize_t max = python::len(rhs);
				this->reserve(max);

				ssize_t i = 0;
				for (; i < max; ++i)
				{
					(*this).push_back(static_cast<const python::object&>(rhs[i]));
				}

				return *this;
			}

		private:
			Record(const Record&)
			{
			}

			Record& operator=(const Record&)
			{
				return *this;
			}

	};




	typedef Poco::SharedPtr<Record> RecordPtr;

}
#endif /* RECORD_H_ */
