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

#include <boost/algorithm/string/replace.hpp>
#include <Poco/String.h>
#include <Poco/NumberFormatter.h>

#include "SimpleOutput.h"

namespace smartcube
{
	SimpleOutput::SimpleOutput(int fd, char fieldSeparator) :
		_ofstream(fd), _fieldSeparator(fieldSeparator)
	{
		// TODO Auto-generated constructor stub

		_tmp.reserve(1024);
	}

	SimpleOutput::SimpleOutput(const std::string& path, char fieldSeparator) :
		_ofstream(path), _fieldSeparator(fieldSeparator)
	{
	}

	SimpleOutput::~SimpleOutput()
	{
		// TODO Auto-generated destructor stub
	}

	void SimpleOutput::push(RecordPtr record)
	{
		if (!_ofstream.good())
		{
			return;
		}

		_tmp.clear();
		//std::ostringstream oss;

		Record::iterator iter = record->begin();
		for (; iter != record->end(); ++iter)
		{
			if (iter != record->begin())
			{
				_tmp.append(1, _fieldSeparator);
				// oss << _fieldSeparator;
			}

			//std::cout << static_cast<const std::string&>(*iter);
			_tmp.append(static_cast<const std::string&> (*iter));
			// oss << static_cast<const std::string&> (*iter);
			//oss << iter.base();
		}

		_tmp.append(1, '\n');

		try
		{
			_ofstream.write(_tmp.c_str(), _tmp.size());
		} catch (std::exception&)
		{
		}

		// _ofstream << oss.str() << std::endl;

		this->free(record);
	}
}
