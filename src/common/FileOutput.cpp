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

#include <sstream>

#include <boost/algorithm/string/replace.hpp>
#include <Poco/String.h>
#include <Poco/NumberFormatter.h>

#include "FileOutput.h"

namespace smartcube
{
	FileOutput::FileOutput(int fd, char fieldSeparator, char groupSeparator, bool quote) :
		_ofstream(fd), _fieldSeparator(fieldSeparator), _groupSeparator(groupSeparator), _quote(quote),
		_regex("([\\\\ \\\"])")
	{
		// TODO Auto-generated constructor stub

	}

	FileOutput::FileOutput(
			const std::string& path, char fieldSeparator, char groupSeparator, bool quote) :
		_ofstream(path), _fieldSeparator(fieldSeparator), _groupSeparator(groupSeparator), _quote(quote),
		_regex("([\\\\ \\\"])")
	{
	}

	FileOutput::~FileOutput()
	{
		// TODO Auto-generated destructor stub
	}

	void FileOutput::push(RecordPtr record)
	{
		std::ostringstream oss;

		Record::Iterator iter = record->begin();
		for (; iter != record->end(); ++iter)
		{
			if (iter != record->begin())
			{
				oss << _fieldSeparator;
			}

			if (iter->isArray())
			{
				typedef std::vector<Poco::DynamicAny> VecType;
				const VecType& anys = iter->extract<VecType>();
				std::vector<Poco::DynamicAny>::const_iterator iter = anys.begin();
				for (; iter != anys.end(); ++iter)
				{
					if (iter != anys.begin())
					{
						oss << _groupSeparator;
					}

					if (_quote)
					{
						const std::string& origin = static_cast<const std::string&>(*iter);
						/*
						std::string modified = boost::replace_all_copy(
								static_cast<const std::string&> (*iter), "\"", "\\\"");
								*/
						std::string modified = boost::regex_replace(origin, _regex, "\\\\$1", boost::match_default | boost::format_all);
						if (modified.length() != origin.length())
						{
							oss << '"' << modified << '"';
						}
						else
						{
							oss << origin;
						}
					}
					else
					{
						oss << static_cast<const std::string&> (*iter);
					}
				}

				continue;
			}

			if (_quote)
			{
				const std::string& origin = static_cast<const std::string&>(*iter);
				/*
				 *
				std::string modified = boost::replace_all_copy(
						static_cast<const std::string&> (*iter), "\"", "\\\"");
						*/
				std::string modified = boost::regex_replace(origin, _regex, "\\\\$1", boost::match_default | boost::format_all);
				if (modified.length() != origin.length())
				{
					oss << '"' << modified << '"';
				}
				else
				{
					oss << origin;
				}
			}
			else
			{
				oss << static_cast<const std::string&> (*iter);
			}
		}

		_ofstream << oss.str() << std::endl;
	}
}
