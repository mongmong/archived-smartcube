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

#ifndef REREPLACE_H_
#define REREPLACE_H_

#include <iostream>

#include <boost/regex.hpp>

#include "RoutineImpl.h"

namespace smartcube
{
	class ReReplace: public Project1To1RoutineImpl<ReReplace>
	{
		public:
			ReReplace(const std::vector<std::size_t>& columns,
					const std::string& pattern,
					const std::string& fmt) :
				Project1To1RoutineImpl<ReReplace> (columns), _regex(pattern),
						_fmt(fmt)
			{
			}

		public:
			inline bool operator ()(const Poco::DynamicAny& op, Poco::DynamicAny& out)
			{
				out = boost::regex_replace(
						static_cast<const std::string&> (op), _regex, _fmt,
						boost::match_default | boost::format_all);
				return true;
			}

		private:
			boost::regex _regex;
			std::string _fmt;
	};
}

#endif /* REREPLACE_H_ */
