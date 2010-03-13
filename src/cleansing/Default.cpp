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

#include "Default.h"

namespace smartcube
{
	Default::Default(const std::vector<Poco::DynamicAny>& defaults) :
		_defaults(defaults)
	{
	}

	Default::~Default()
	{
	}

	void Default::handle(Input& input, Output& output)
	{
		RecordPtr rec = input.pop();

		for (; !rec->eof(); output.push(rec), rec = input.pop())
		{
			std::vector<Poco::DynamicAny>::iterator iter = _defaults.begin();
			for (; iter != _defaults.end(); ++iter)
			{
				std::size_t i = iter - _defaults.begin();
				if (rec->size() <= i)
				{
					rec->push_back(*iter);
				}
				else if ((*rec)[i].isEmpty())
				{
					(*rec)[i] = *iter;
				}
				else if ((*rec)[i].isString() && static_cast<const std::string&>((*rec)[i]).length() == 0)
				{
					(*rec)[i] = *iter;
				}
				else
				{
					// TODO: check array elements.
				}
			}
		}
	}
}
