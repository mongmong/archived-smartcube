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

#include "Split.h"

namespace smartcube
{
	Split::Split(
			const std::vector<std::size_t>& columns,
			const std::string& separators) :
		_columns(columns), _charSeparator(
				separators.c_str(), "", boost::keep_empty_tokens)
	{
		// TODO Auto-generated constructor stub

	}

	Split::~Split()
	{
		// TODO Auto-generated destructor stub
	}

	void Split::handle(Input& input, Output& output)
	{
		RecordPtr rec = input.pop();
		for (; !rec->eof(); output.push(rec), rec = input.pop())
		{
			std::vector<std::size_t>::iterator iter = _columns.begin();
			for (; iter != _columns.end(); ++iter)
			{
				boost::tokenizer<boost::char_separator<char> > tokens(
						static_cast<const std::string&> ((*rec)[*iter]),
						_charSeparator);
				rec->insert(rec->end(), tokens.begin(), tokens.end());
			}
		}
	}
}
