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

#include "Group.h"

namespace smartcube
{
	Group::Group(
			const std::vector<std::size_t>& columns, std::size_t group,
			char separator, bool showAll) :
		_columns(columns), _group(group), _separator(separator), _showAll(
				showAll)
	{
		// TODO Auto-generated constructor stub
	}

	Group::~Group()
	{
		// TODO Auto-generated destructor stub
	}

	void Group::handle(Input& input, Output& output)
	{
		typedef std::vector<std::string> GroupType;
		GroupType groups;
		groups.resize(_columns.size());
		GroupType::iterator groupit = groups.begin();
		for (; groupit != groups.end(); ++groupit)
		{
			groupit->clear();
		}

		std::size_t groupsize = 0;

		RecordPtr previous = input.pop();
		if (previous->eof())
		{
			return;
		}
		groupsize = 0;

		std::size_t index = 0;

		RecordPtr current = input.pop();
		if (!current->eof())
		{
			for (; !current->eof(); previous = current, current = input.pop())
			{
				groupsize++;

				std::vector<std::size_t>::iterator coit = _columns.begin();
				for (; coit != _columns.end(); ++coit)
				{
					std::size_t i = coit - _columns.begin();
					if (groupsize > 1)
					{
						groups[i] += _separator;
					}
					groups[i]
							+= static_cast<const std::string&> ((*previous)[*coit]);
				}

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
					previous->insert(
							previous->end(), groups.begin(), groups.end());
					output.push(previous);
				}

				if (!same)
				{
					groupit = groups.begin();
					for (; groupit != groups.end(); ++groupit)
					{
						groupit->clear();
					}

					groupsize = 0;
				}
			}
		}

		std::vector<std::size_t>::iterator iter = _columns.begin();
		for (; iter != _columns.end(); ++iter)
		{
			std::size_t i = iter - _columns.begin();
			if (groupsize > 1)
			{
				groups[i] += _separator;
			}
			groups[i] += static_cast<const std::string&> ((*previous)[*iter]);
		}
		previous->insert(previous->end(), groups.begin(), groups.end());
		output.push(previous);
	}
}
