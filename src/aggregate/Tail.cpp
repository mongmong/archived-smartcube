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

#include "Tail.h"

namespace smartcube
{
	Tail::Tail(std::size_t group, std::size_t showNum) :
		_groupBy(group), _showNum(showNum)
	{
		// TODO Auto-generated constructor stub
	}

	Tail::~Tail()
	{
		// TODO Auto-generated destructor stub
	}

	void Tail::handle(Input& input, Output& output)
	{
		typedef std::queue<RecordPtr> TailType;
		TailType tails;

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
				while (tails.size() && tails.size() >= _showNum)
				{
					tails.pop();
				}
				if (tails.size() - _showNum > 0)
				{
					tails.push(previous);
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
					while (tails.size() > 0)
					{
						output.push(tails.front());
						tails.pop();
					}
				}
			}
		}

		while (tails.size() >= _showNum)
		{
			tails.pop();
		}
		if (tails.size() - _showNum > 0)
		{
			tails.push(previous);
		}

		while (tails.size() && tails.size() > 0)
		{
			output.push(tails.front());
			tails.pop();
		}
	}
}
