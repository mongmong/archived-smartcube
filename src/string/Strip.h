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

#ifndef STRIP_H_
#define STRIP_H_

#include <boost/algorithm/string/trim.hpp>

#include "RoutineImpl.h"

namespace smartcube
{
	class Strip: public Project1To1RoutineImpl<Strip>
	{
		public:
			enum StripOption
			{
				Left, Right, Both
			};

			Strip(const std::vector<std::size_t>& columns, StripOption option =
					Both) :
				Project1To1RoutineImpl<Strip> (columns), _option(option)
			{
			}

		public:
			inline void operator ()(const Cell& op,
					Cell& out)
			{
				switch (_option)
				{
					case Left:
						out = boost::trim_left_copy(
								static_cast<const std::string&> (op));
						break;
					case Right:
						out = boost::trim_right_copy(
								static_cast<const std::string&> (op));
						break;
					case Both:
					default:
						out = boost::trim_copy(
								static_cast<const std::string&> (op));
						break;
				}
			}

		private:
			StripOption _option;
	};
}

#endif /* STRIP_H_ */
