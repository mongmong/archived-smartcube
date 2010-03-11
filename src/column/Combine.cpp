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

#include <sstream>

#include "Combine.h"

namespace smartcube
{
	Combine::Combine(const std::vector<std::size_t>& columns, char separator) :
		_columns(columns), _separator(separator)
	{
		// TODO Auto-generated constructor stub

	}

	Combine::~Combine()
	{
		// TODO Auto-generated destructor stub
	}

	void Combine::handle(Input& input, Output& output)
	{
		if (_columns.size() == 1)
		{
			RecordPtr rec = input.pop();
			for (; !rec->eof(); output.push(rec), rec = input.pop())
			{
				std::ostringstream oss;

				Record::iterator begin = rec->begin() + *_columns.begin();
				Record::iterator iter = begin;
				for (; iter != rec->end(); iter++)
				{
					if (iter == begin)
					{
						oss << static_cast<const std::string&> (*iter);
					}
					else
					{
						oss << _separator
								<< static_cast<const std::string&> (*iter);
					}
				}

				rec->insert(rec->end(), oss.str());
			}
		}
		else
		{
			RecordPtr rec = input.pop();
			for (; !rec->eof(); output.push(rec), rec = input.pop())
			{
				std::ostringstream oss;

				std::vector<std::size_t>::iterator iter = _columns.begin();
				for (; iter != _columns.end(); ++iter)
				{
					if (iter == _columns.begin())
					{
						oss << static_cast<const std::string&> ((*rec)[*iter]);
					}
					else
					{
						oss << _separator
								<< static_cast<const std::string&> ((*rec)[*iter]);
					}
				}

				rec->insert(rec->end(), oss.str());
			}
		}
	}
}
