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

#include "Error.h"

#include "Record.h"

namespace smartcube
{
	Record::Record()
	{
		// TODO Auto-generated constructor stub

	}

	Record::~Record()
	{
		// TODO Auto-generated destructor stub
	}

	Record::Iterator Record::begin()
	{
		return _fields.begin();
	}

	Record::Iterator Record::end()
	{
		return _fields.end();
	}

	Record::ReverseIterator Record::rbegin()
	{
		return _fields.rbegin();
	}

	Record::ReverseIterator Record::rend()
	{
		return _fields.rend();
	}

	std::size_t Record::count() const
	{
		return _fields.size();
	}

	bool Record::eof() const
	{
		return _fields.size() == 0;
	}

	void Record::clear()
	{
		_fields.clear();
	}

	void Record::resize(std::size_t newSize)
	{
		_fields.resize(newSize);
	}

	void Record::insert(
			Record::Iterator position, std::size_t n, const Poco::DynamicAny& x)
	{
		_fields.insert(position, n, x);
	}

	Record::Iterator Record::insert(
			Record::Iterator position, const Poco::DynamicAny& x)
	{
		return _fields.insert(position, x);
	}

	Poco::DynamicAny& Record::operator [](std::size_t index)
	{
		if (index > 1000)
		{
			if (1000 - (int) index < -static_cast<int>(_fields.size()))
			{
				SMARTCUBE_EXCEPTION("Index %z out of range.", index);
			}
			return _fields.end()[1000 - (int) index];
		}
		else
		{
			if (index >= _fields.size())
			{
				SMARTCUBE_EXCEPTION("Index %z out of range.", index);
			}
			return _fields[index];
		}
	}

	/*
	 * Private methods
	 */
	Record::Record(const Record&)
	{
	}

	Record& Record::operator =(const Record&)
	{
		return *this;
	}
}
