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

#ifndef GE_H_
#define GE_H_

#include <sys/types.h>

#include <Poco/String.h>

#include "RoutineImpl.h"

namespace smartcube
{
	class Ge: public Project2To1RoutineImpl<Ge>
	{
		public:
			enum GeOption
			{
				Numeric, StringCaseSensitive, StringCaseInsensitive
			};

			Ge(const std::vector<std::size_t>& columns, GeOption option) :
				Project2To1RoutineImpl<Ge> (columns), _option(option)
			{
			}

		public:
			inline void operator()(const Poco::DynamicAny& op1,
					const Poco::DynamicAny& op2,
					Poco::DynamicAny& out)
			{
				switch (_option)
				{
					case StringCaseSensitive:
						out = static_cast<const std::string&> (op1)
								>= static_cast<const std::string&> (op2);
						break;
					case StringCaseInsensitive:
						out = 0 <= Poco::icompare(
								static_cast<const std::string&> (op1),
								static_cast<const std::string&> (op2));
						break;
					case Numeric:
					default:
						out = static_cast<double> (op1)
								>= static_cast<double> (op2);
						break;
				}
			}

		private:
			GeOption _option;
	};
}

#endif /* GE_H_ */