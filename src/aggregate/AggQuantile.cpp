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

#include <algorithm>
#include <iostream>
#include <cmath>

#include "AggQuantile.h"

namespace smartcube
{
	AggQuantile::AggQuantile(const std::vector<std::size_t>& columns, double quartile, std::size_t group, bool showAll) :
		_quartile(quartile), _groupBy(group), _showAll(showAll), _columns(columns)
	{
		// TODO Auto-generated constructor stub
	}

	AggQuantile::~AggQuantile()
	{
		// TODO Auto-generated destructor stub
	}

	void AggQuantile::handle(Input& input, Output& output)
	{
		typedef std::vector<double> BufType;
		typedef std::vector<BufType> AggMedianType;
		AggMedianType medians;
		medians.resize(_columns.size());
		BufType results;
		results.resize(_columns.size());

		RecordPtr previous = input.pop();
		if (previous->eof())
		{
			return;
		}

		std::vector<std::size_t>::iterator coit = _columns.begin();
		for (; coit != _columns.end(); ++coit)
		{
			std::size_t i = coit - _columns.begin();
			medians[i].push_back(static_cast<double> ((*previous)[*coit]));
		}

		RecordPtr current = input.pop();
		for (; !current->eof(); previous = current, current = input.pop())
		{
			int same = current->compare(*previous, _groupBy);

			if (_showAll || !same)
			{
				AggMedianType::iterator iter = medians.begin();
				for (; iter != medians.end(); ++iter)
				{
					std::size_t i = iter - medians.begin();

					std::sort(iter->begin(), iter->end());
					results[i] = (*iter)[static_cast<std::size_t>(iter->size() * std::abs(_quartile))];
				}
				previous->insert(previous->end(), results.begin(), results.end());
				output.push(previous);
			}

			if (!same)
			{
				AggMedianType::iterator iter = medians.begin();
				for (; iter != medians.end(); ++iter)
				{
					iter->clear();
				}
			}
			else
			{
			}

			std::vector<std::size_t>::iterator coit = _columns.begin();
			for (; coit != _columns.end(); ++coit)
			{
				std::size_t i = coit - _columns.begin();
				medians[i].push_back(static_cast<double> ((*current)[*coit]));
			}
		}

		AggMedianType::iterator iter = medians.begin();
		for (; iter != medians.end(); ++iter)
		{
			std::size_t i = iter - medians.begin();

			std::sort(iter->begin(), iter->end());
			results[i] = (*iter)[static_cast<std::size_t>(iter->size() * std::abs(_quartile))];
		}
		previous->insert(previous->end(), results.begin(), results.end());
		output.push(previous);
	}
}
