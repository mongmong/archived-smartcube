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
	FileInput::FileInput(
			int fd, const std::string& fieldSeparators, bool unquote) :
		_ifstream(fd), _escapedSeparator("\\", fieldSeparators, "\""),
				_charSeparator(fieldSeparators.c_str(), "", boost::keep_empty_tokens),
				_unquote(unquote)
	{
		// TODO Auto-generated constructor stub
	}

	FileInput::FileInput(
			const std::string& path, const std::string& fieldSeparators, bool unquote) :
		_ifstream(path), _escapedSeparator("\\",fieldSeparators, "\""),
				_charSeparator(fieldSeparators.c_str(), "", boost::keep_empty_tokens),
				_unquote(unquote)
	{
	}

	FileInput::~FileInput()
	{
		// TODO Auto-generated destructor stub
	}

	RecordPtr FileInput::pop()
	{
		std::string line;

		RecordPtr rec(new Record());

		if (std::getline(_ifstream, line))
		{
			if (_unquote)
			{
				boost::tokenizer<boost::escaped_list_separator<char> > tokens(
						line, _escapedSeparator);
				rec->insert(rec->end(), tokens.begin(), tokens.end());
			}
			else
			{
				boost::tokenizer<boost::char_separator<char> > tokens(
						line, _charSeparator);
				rec->insert(rec->end(), tokens.begin(), tokens.end());
			}
		}

		return rec;
	}
}
