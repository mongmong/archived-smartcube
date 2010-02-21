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

#include "Norm.h"

namespace smartcube
{
	Norm::Norm(NormOption option, const std::vector<std::size_t>& columns) :
		_option(option), _columns(columns)
	{
		// TODO Auto-generated constructor stub
	}

	Norm::~Norm()
	{
		// TODO Auto-generated destructor stub
	}

	void Norm::handle(Input& input, Output& output)
	{
		typedef std::queue<RecordPtr> BufType;
		BufType buf;
		typedef std::vector<double> AggType;
		AggType aggs;
		typedef std::vector<double> ResultType;
		ResultType results;

		aggs.resize(_columns.size());
		AggType::iterator aggit = aggs.begin();
		for (; aggit != aggs.end(); ++aggit)
		{
			*aggit = 0.0;
		}

		results.resize(_columns.size());

		RecordPtr current = input.pop();
		for (; !current->eof(); current = input.pop())
		{
			std::vector<std::size_t>::iterator coit = _columns.begin();
			for (; coit != _columns.end(); ++coit)
			{
				std::size_t i = coit - _columns.begin();
				switch (_option)
				{
					case Max:
						if (aggs[i] < static_cast<double>((*current)[*coit]))
						{
							aggs[i] = static_cast<double>((*current)[*coit]);
						}
						break;
					case Average:
					case Sum:
						aggs[i] += static_cast<double>((*current)[*coit]);
						break;
				}
			}

			buf.push(current);
		}

		int factor = 1;
		if (_option == Average)
		{
			factor = buf.size();
		}

		while (buf.size() > 0)
		{
			current = buf.front();
			buf.pop();

			std::vector<std::size_t>::iterator coit = _columns.begin();
			for (; coit != _columns.end(); ++coit)
			{
				std::size_t i = coit - _columns.begin();
				results[i] = static_cast<double>((*current)[*coit]) * factor / aggs[i];
			}

			current->insert(current->end(), results.begin(), results.end());

			output.push(current);
		}
	}
}
