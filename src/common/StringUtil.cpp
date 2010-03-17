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

#include "StringUtil.h"

void StringUtil::split(const std::string& s, char delimiter, std::vector<
		std::string>& parts)
{
	parts.reserve(64);

	std::string::iterator start = s.begin();
	std::string::iterator end = s.end();
	std::string::iterator iter = s.begin();
	std::size_t i = 0;

	for (; iter != end; iter++)
	{
		if (*iter == delimiter)
		{
			parts.push_back(std::string(start, iter));
			//parts[i++].assign(start, iter);

			start = iter + 1;
		}
	}

	if (start != end)
	{
		parts.push_back(std::string(start, iter));
		//parts[i].assign(start, iter);
	}
}

/*
 std::string& StringUtil::escapeString(std::string& to, const std::string& from)
 {
 to.resize(from.size() + 20);

 to.clear();

 std::string::const_iterator iter = from.begin();
 for (; iter != from.end(); ++iter)
 {
 if ('\\' != *iter)
 {
 to.append(*iter);
 continue;
 }

 if (iter == from.end())
 {
 to.append('\\');
 continue;
 }

 switch (*iter)
 {
 case 'e':
 break;
 case 'a':
 break;
 case 'b':
 break;
 case 'f':
 break;
 case 'n':
 break;
 case 'r':
 break;
 case 't':
 break;
 case 'v':
 break;
 case '\'':
 break;
 case '\\':
 break;
 }
 }

 return to;
 }
 */
