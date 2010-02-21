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

#include <queue>

#include "Head.h"

namespace smartcube
{
	Head::Head(std::size_t group, std::size_t showNum) :
		_groupBy(group), _showNum(showNum)
	{
		// TODO Auto-generated constructor stub
	}

	Head::~Head()
	{
		// TODO Auto-generated destructor stub
	}

	void Head::handle(Input& input, Output& output)
	{
		typedef std::queue<RecordPtr> HeadType;
		HeadType heads;

		RecordPtr previous = input.pop();
		if (previous->eof())
		{
			return;
		}

		std::size_t index = 0;

		RecordPtr current = input.pop();
		if (!current->eof())
		{
			for (; !current->eof(); previous = current, current = input.pop())
			{
				if (heads.size() < _showNum)
				{
					heads.push(previous);
				}

				int same = true;
				for (index = 0; index < _groupBy; ++index)
				{
					if ((*current)[index] != (*previous)[index])
					{
						same = false;
						break;
					}
				}

				if (!same)
				{
					while (heads.size() > 0)
					{
						output.push(heads.front());
						heads.pop();
					}
				}
			}
		}

		if (heads.size() < _showNum)
		{
			heads.push(previous);
		}

		while (heads.size() > 0)
		{
			output.push(heads.front());
			heads.pop();
		}
	}
}
