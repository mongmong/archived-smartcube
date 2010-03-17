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

#ifndef STRINGUTIL_H_
#define STRINGUTIL_H_

#include <string>

namespace smartcube
{
	class StringUtil
	{
		public:
			template<typename ArrayType>
			static void StringUtil::split(const std::string& s,
					char delimiter,
					ArrayType& parts)
			{
				parts.reserve(64);

				std::string::const_iterator start = s.begin();
				std::string::const_iterator end = s.end();
				std::string::const_iterator iter = s.begin();

				for (; iter != end; iter++)
				{
					if (*iter == delimiter)
					{
						parts.push_back(std::string(start, iter));

						start = iter + 1;
					}
				}

				if (start != end)
				{
					parts.push_back(std::string(start, iter));
				}
				else
				{
					parts.push_back(std::string(""));
				}
			}

			template<typename ArrayType>
			static void StringUtil::split(const std::string& s,
					const std::string& delimiters,
					ArrayType& parts)
			{
				if (delimiters.size() == 1)
				{
					return split<ArrayType> (s, delimiters[0], parts);
				}

				parts.reserve(64);

				std::string::const_iterator start = s.begin();
				std::string::const_iterator end = s.end();
				std::string::const_iterator iter = s.begin();

				for (; iter != end; iter++)
				{
					if (delimiters.find(*iter) != std::string::npos)
					{
						parts.push_back(std::string(start, iter));

						start = iter + 1;
					}
				}

				if (start != end)
				{
					parts.push_back(std::string(start, iter));
				}
				else
				{
					parts.push_back(std::string(""));
				}
			}

	};
}

#endif /* STRINGUTIL_H_ */
