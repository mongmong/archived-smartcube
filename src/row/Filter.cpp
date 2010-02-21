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

#include "Filter.h"

namespace smartcube
{
	Filter::Filter(FilterType filterType, const std::vector<
			std::size_t>& columns) :
		_filterType(filterType), _columns(columns)
	{
		// TODO Auto-generated constructor stub
	}

	Filter::~Filter()
	{
		// TODO Auto-generated destructor stub
	}

	void Filter::handle(Input& input, Output& output)
	{
		RecordPtr rec = input.pop();


		if (_filterType == FilterAnd)
		{
			for (; !rec->eof(); rec = input.pop())
			{
				bool test = true;
				std::vector<std::size_t>::iterator iter = _columns.begin();
				for (; iter != _columns.end(); ++iter)
				{
					test = test && (bool) (*rec)[*iter];
					if (!test)
					{
						break;
					}
				}
				if (!test)
				{
					output.push(rec);
				}
			}
		}
		else // _filterType == OpOr
		{
			bool initial = _columns.begin() == _columns.end();
			for (; !rec->eof(); rec = input.pop())
			{
				bool test = initial;
				std::vector<std::size_t>::iterator iter = _columns.begin();
				for (; iter != _columns.end(); ++iter)
				{
					test = test || (bool) (*rec)[*iter];
					if (test)
					{
						break;
					}
				}
				if (!test)
				{
					output.push(rec);
				}
			}
		}
	}
}
