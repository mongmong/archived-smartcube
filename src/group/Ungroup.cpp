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

#include <Poco/StringTokenizer.h>

#include "Record.h"

#include "Ungroup.h"

namespace smartcube
{
	Ungroup::Ungroup(const std::vector<std::size_t>& columns, const std::string& separators) :
		_columns(columns), _separators(separators)
	{
		// TODO Auto-generated constructor stub
	}

	Ungroup::~Ungroup()
	{
		// TODO Auto-generated destructor stub
	}

	void Ungroup::handle(Input& input, Output& output)
	{
		typedef std::vector<Poco::SharedPtr<Poco::StringTokenizer> >
				TokenizerType;
		TokenizerType tokenizers;
		typedef std::vector<Cell> ResultType;
		ResultType results;

		tokenizers.resize(_columns.size());

		results.resize(_columns.size());

		RecordPtr rec = input.pop();
		for (; !rec->eof(); rec = input.pop())
		{
			results.clear();
			TokenizerType::iterator iter = tokenizers.begin();
			for (; iter != tokenizers.end(); ++iter)
			{
				std::size_t i = iter - tokenizers.begin();
				*iter = new Poco::StringTokenizer(
						static_cast<const std::string&> ((*rec)[_columns[i]]),
						_separators);
			}

			std::size_t index = 0;
			for (; true; ++index)
			{
				RecordPtr ptr = new Record();
				ptr->insert(ptr->begin(), rec->begin(), rec->end());
				ptr->resize(rec->size() + _columns.size());

				bool hasparts = false;
				iter = tokenizers.begin();
				for (; iter != tokenizers.end(); ++iter)
				{
					std::size_t s = rec->size() + (iter - tokenizers.begin());
					if (index < (*iter)->count())
					{
						hasparts = true;
						(*ptr)[s] = (*(*iter))[index];
					}
					else
					{
						(*ptr)[s] = std::string("");
					}
				} // for tokenizer

				if (!hasparts)
				{
					break;
				}

				ptr->insert(ptr->end(), results.begin(), results.end());
				output.push(ptr);
			} // for parts
		} // for rec
	}
}
