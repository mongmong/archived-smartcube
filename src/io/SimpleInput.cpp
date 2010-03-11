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

#include <string>

#include <boost/tokenizer.hpp>

#include "FileInput.h"

namespace smartcube
{
	SimpleInput::SimpleInput(int fd,
			const std::string& fieldSeparators,
			const std::string& groupSeparators,
			bool unquote) :
		_ifstream(fd), _fieldEscapedSeparator("\\", fieldSeparators, "\""),
				_fieldCharSeparator(
						fieldSeparators.c_str(), "", boost::keep_empty_tokens),
				_groupSeparator(
						groupSeparators.c_str(), "", boost::keep_empty_tokens),
				_unquote(unquote)
	{
		// TODO Auto-generated constructor stub
	}

	SimpleInput::SimpleInput(const std::string& path,
			const std::string& fieldSeparators,
			const std::string& groupSeparators,
			bool unquote) :
		_ifstream(path), _fieldEscapedSeparator("\\", fieldSeparators, "\""),
				_fieldCharSeparator(
						fieldSeparators.c_str(), "", boost::keep_empty_tokens),
				_groupSeparator(
						groupSeparators.c_str(), "", boost::keep_empty_tokens),
				_unquote(unquote)
	{
	}

	SimpleInput::~SimpleInput()
	{
		// TODO Auto-generated destructor stub
	}

	RecordPtr SimpleInput::pop()
	{
		std::string line;

		RecordPtr rec(new Record());

		while (rec->empty() && std::getline(_ifstream, line))
		{
			if (_unquote)
			{
				boost::tokenizer<boost::escaped_list_separator<char> > tokens(
						line, _fieldEscapedSeparator);
				rec->insert(rec->end(), tokens.begin(), tokens.end());
			}
			else
			{
				boost::tokenizer<boost::char_separator<char> > tokens(
						line, _fieldCharSeparator);
				rec->insert(rec->end(), tokens.begin(), tokens.end());
			}
		}

		return rec;
	}
}
