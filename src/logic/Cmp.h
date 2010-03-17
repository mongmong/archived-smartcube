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

#ifndef CMP_H_
#define CMP_H_

#include <sys/types.h>

#include <Poco/String.h>

#include "RoutineImpl.h"

namespace smartcube
{
	class Cmp: public Project2To1RoutineImpl<Cmp>
	{
		public:
			enum CmpOption
			{
				Numeric, StringCaseSensitive, StringCaseInsensitive
			};

			Cmp(const std::vector<std::size_t>& columns, CmpOption option =
					Numeric) :
				Project2To1RoutineImpl<Cmp> (columns), _option(option)
			{
			}

		public:
			inline void operator()(const Cell& op1,
					const Cell& op2,
					Cell& out)
			{
				switch (_option)
				{
					case StringCaseSensitive:
						out = static_cast<const std::string&> (op1).compare(
								static_cast<const std::string&> (op2));
						break;
					case StringCaseInsensitive:
						out = Poco::icompare(
								static_cast<const std::string&> (op1),
								static_cast<const std::string&> (op2));
						break;
					case Numeric:
					default:
						double result = static_cast<double> (op1)
								- static_cast<double> (op2);
						if (result > 0.0)
						{
							out = 1;
						}
						else if (result < 0.0)
						{
							out = -1;
						}
						else
						{
							out = 0;
						}
						break;
				}
			}

		private:
			CmpOption _option;
	};
}

#endif /* CMP_H_ */
