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

#include "Select.h"

namespace smartcube
{
	Select::Select(const std::vector<std::size_t>& columns) :
		_columns(columns)
	{
		// TODO Auto-generated constructor stub
	}

	Select::~Select()
	{
		// TODO Auto-generated destructor stub
	}

	void Select::handle(Input& input, Output& output)
	{
		RecordPtr rec = input.pop();

		for (; !rec->eof(); rec = input.pop())
		{
			RecordPtr ptr = new Record();
			ptr->resize(_columns.size());

			std::vector<std::size_t>::iterator iter = _columns.begin();
			for (; iter != _columns.end(); ++iter)
			{
				std::size_t index = iter - _columns.begin();
				(*ptr)[index] = (*rec)[*iter];
			}
			output.push(ptr);
		}
	}
}
