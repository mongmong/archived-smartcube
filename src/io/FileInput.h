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

#ifndef CONSOLEINPUT_H_
#define CONSOLEINPUT_H_

#include <fstream>
#include <iostream>
#include <string>

#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/tokenizer.hpp>

#include "Input.h"

namespace smartcube
{
	/**
	 * SimpleInput
	 *
	 * Read simple delimited records from specified file.<br/>
	 * A simple delimited record contains fields which are separated by one of specified characters.
	 */
	class SimpleInput: public Input
	{
		public:
			SimpleInput(int fd, const std::string& fieldSeparators = "\t", const std::string& groupSeparators = ",", bool unquote = false);
			SimpleInput(const std::string& path, const std::string& fieldSeparators = "\t", const std::string& groupSeparators = ",", bool unquote = false);
			virtual ~SimpleInput();

		public:
			virtual RecordPtr pop();

		private:
			boost::iostreams::stream<boost::iostreams::file_descriptor_source>
					_ifstream;
			boost::escaped_list_separator<char> _fieldEscapedSeparator;
			boost::char_separator<char> _fieldCharSeparator;
			boost::char_separator<char> _groupSeparator;
			bool	_unquote;
	};
}

#endif /* CONSOLEINPUT_H_ */
