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

#ifndef SUBSTR_H_
#define SUBSTR_H_

#include "RoutineImpl.h"

namespace smartcube
{
	class Substr: public Project1To1RoutineImpl<Substr>
	{
		public:
			enum SubstrOption
			{
				Left, Right, Mid
			};

			Substr(const std::vector<std::size_t>& columns,
					std::size_t start,
					std::size_t n,
					SubstrOption option) :
				Project1To1RoutineImpl<Substr> (columns), _start(start), _n(n),
						_option(option)
			{
			}

		public:
			inline void operator()(const Cell& op,
					Cell& out)
			{
				switch (_option)
				{
					case Left:
					{
						const std::string& str =
								static_cast<const std::string&> (op);
						out = str.substr(0, _n);
						break;
					}
					case Right:
					{
						const std::string& str =
								static_cast<const std::string&> (op);
						std::size_t index = 0;
						if (_n < str.size())
						{
							index = str.size() - _n;
						}
						out = str.substr(index, str.size());
						break;
					}
					case Mid:
					default:
					{
						const std::string& str =
								static_cast<const std::string&> (op);
						out = str.substr(_start, _n);

						break;
					}
				}
			}

		private:
			std::size_t _start;
			std::size_t _n;
			SubstrOption _option;
	};
}

#endif /* SUBSTR_H_ */
