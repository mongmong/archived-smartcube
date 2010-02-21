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

#include "Div.h"

#include <math.h>

#include "Div.h"

namespace smartcube
{
	/*
	Div::Div(const std::vector<std::size_t>& columns) :
		_columns(columns)
	{
		// TODO Auto-generated constructor stub
	}

	Div::~Div()
	{
		// TODO Auto-generated destructor stub
	}

	void Div::handle(Input& input, Output& output)
	{
		RecordPtr rec = input.pop();

		std::size_t size = _columns.size() / 2;
		for (; !rec->eof(); output.push(rec), rec = input.pop())
		{
			if (size > 0)
			{
				std::size_t s = rec->count();
				rec->resize(s + size);

				std::size_t i = 0;
				for (; i < size; ++i)
				{
					std::size_t x = _columns[2 * i + 0];
					std::size_t y = _columns[2 * i + 1];
					std::size_t index = s + i;

					(*rec)[index] = static_cast<double> ((*rec)[x])
							/ static_cast<double> ((*rec)[y]);
				}
			}
		}
	}
	*/
}
