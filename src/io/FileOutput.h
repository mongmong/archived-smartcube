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

#ifndef CONSOLEOUTPUT_H_
#define CONSOLEOUTPUT_H_

#include <fstream>
#include <iostream>

#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/regex.hpp>

#include "Output.h"

namespace smartcube
{
	class FileOutput : public Output
	{
		public:
			FileOutput(int fd, char fieldSeparator = '\t', char groupSeparator = ',', bool quote = false);
			FileOutput(const std::string& path, char fieldSeparator = '\t', char groupSeparator = ',', bool quote = false);
			virtual ~FileOutput();

		public:
			virtual void push(RecordPtr record);

		private:
			boost::iostreams::stream<boost::iostreams::file_descriptor_sink>	_ofstream;
			char						_fieldSeparator;
			char						_groupSeparator;
			bool						_quote;

			boost::regex				_regex;
	};
}

#endif /* CONSOLEOUTPUT_H_ */
