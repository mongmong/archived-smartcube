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

#ifndef REFORMAT_H_
#define REFORMAT_H_

#include <iostream>

#include <boost/regex.hpp>

#include <Poco/Any.h>
#include <Poco/Format.h>

#include "RoutineImpl.h"

namespace smartcube
{
	class ReFormat: public Project1To1RoutineImpl<ReFormat>
	{
		public:
			enum ReFormatOption
			{
				Search, Match
			};
			ReFormat(const std::vector<std::size_t>& columns,
					const std::string& pattern,
					const std::string& fmt,
					ReFormatOption option) :
				Project1To1RoutineImpl<ReFormat> (columns), _regex(pattern),
						_fmt(fmt), _option(option)
			{
			}

		public:
			inline bool operator ()(const Cell& op,
					Cell& out)
			{
				boost::smatch parts;

				if (_option == Search)
				{
					boost::regex_search(
							static_cast<const std::string&> (op), parts, _regex);
				}
				else
				{
					boost::regex_match(
							static_cast<const std::string&> (op), parts, _regex);
				}

				out = boost::regex_format(parts, _fmt, boost::match_default
						| boost::format_all);

				return true;
			}

		private:
			boost::regex _regex;
			std::string _fmt;
			ReFormatOption _option;
	};

}

#endif /* REFORMAT_H_ */
