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

#include "AggCount.h"

namespace smartcube
{
	AggCount::AggCount(std::size_t group, bool showAll) :
		_group(group), _showAll(showAll)
	{
		// TODO Auto-generated constructor stub
	}

	AggCount::~AggCount()
	{
		// TODO Auto-generated destructor stub
	}

	void AggCount::handle(Input& input, Output& output)
	{

		RecordPtr previous = input.pop();
		if (previous->eof())
		{
			return;
		}

		int64_t count = 1;
		std::size_t index = 0;

		RecordPtr current = input.pop();
		for (; !current->eof(); previous = current, current = input.pop())
		{
			int same = true;
			for (index = 0; index < _group; ++index)
			{
				if ((*current)[index] != (*previous)[index])
				{
					same = false;
					break;
				}
			}

			if (_showAll || !same)
			{
				//previous->push_back(count);
				previous->resize(previous->size() + 1);
				*previous->rbegin() = count;
				output.push(previous);
			}

			if (!same)
			{
				count = 1;
			}
			else
			{
				count++;
			}
		}

		previous->resize(previous->size() + 1);
		*previous->rbegin() = count;
		output.push(previous);

	}
}
