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

#include <boost/tokenizer.hpp>

#include "ReSplit.h"

namespace smartcube
{
	ReSplit::ReSplit(
			const std::vector<std::size_t>& columns,
			const std::string& pattern, ReSplitOption option) :
		_columns(columns), _regex(pattern), _option(option)
	{
		// TODO Auto-generated constructor stub

	}

	ReSplit::~ReSplit()
	{
		// TODO Auto-generated destructor stub
	}

	void ReSplit::handle(Input& input, Output& output)
	{
		RecordPtr rec = input.pop();
		for (; !rec->eof(); output.push(rec), rec = input.pop())
		{
			std::vector<std::size_t>::iterator iter = _columns.begin();
			for (; iter != _columns.end(); ++iter)
			{
				const std::string& col =
						static_cast<const std::string&> ((*rec)[*iter]);

				boost::smatch parts;
				if (_option == Search)
				{
					boost::regex_search(col, parts, _regex);
				}
				else
				{
					boost::regex_match(col, parts, _regex);
				}

				boost::smatch::iterator iter = parts.begin();
				for (; iter != parts.end(); ++iter)
				{
					if (!iter->matched)
					{
						continue;
					}
					rec->insert(rec->end(), std::string(
							iter->first, iter->second));
				}
			}
		}
	}
}
