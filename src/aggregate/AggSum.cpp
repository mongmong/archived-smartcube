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

#include "AggSum.h"

namespace smartcube
{
	AggSum::AggSum(std::size_t group, bool showAll, const std::vector<
			std::size_t>& columns) :
		_groupBy(group), _showAll(showAll), _columns(columns)
	{
		// TODO Auto-generated constructor stub
	}

	AggSum::~AggSum()
	{
		// TODO Auto-generated destructor stub
	}

	void AggSum::handle(Input& input, Output& output)
	{
		typedef std::vector<double> SumType;
		SumType sums;
		sums.resize(_columns.size());

		RecordPtr previous = input.pop();
		if (previous->eof())
		{
			return;
		}

		std::vector<std::size_t>::iterator coit = _columns.begin();
		for (; coit != _columns.end(); ++coit)
		{
			std::size_t i = coit - _columns.begin();
			sums[i] = static_cast<double> ((*previous)[*coit]);
		}

		std::size_t index = 0;

		RecordPtr current = input.pop();
		for (; !current->eof(); previous = current, current = input.pop())
		{
			bool same = true;
			for (index = 0; index < _groupBy; ++index)
			{
				if ((*current)[index] != (*previous)[index])
				{
					same = false;
					break;
				}
			}

			if (_showAll || !same)
			{
				previous->insert(previous->end(), sums.begin(), sums.end());
				output.push(previous);
			}

			if (!same)
			{
				std::vector<std::size_t>::iterator coit = _columns.begin();
				for (; coit != _columns.end(); ++coit)
				{
					std::size_t i = coit - _columns.begin();
					sums[i] = static_cast<double> ((*current)[*coit]);
				}
			}
			else
			{
				std::vector<std::size_t>::iterator coit = _columns.begin();
				for (; coit != _columns.end(); ++coit)
				{
					std::size_t i = coit - _columns.begin();
					sums[i] += static_cast<double> ((*current)[*coit]);
				}
			}
		}

		previous->insert(previous->end(), sums.begin(), sums.end());
		output.push(previous);
	}
}
