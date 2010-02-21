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

#include "Expand.h"

namespace smartcube
{
	Expand::Expand(const std::vector<std::string>& columns) :
		_columns(columns)
	{
		// TODO Auto-generated constructor stub
	}

	Expand::~Expand()
	{
		// TODO Auto-generated destructor stub
	}

	void Expand::handle(Input& input, Output& output)
	{
		RecordPtr rec = input.pop();

		for (; !rec->eof(); output.push(rec), rec = input.pop())
		{
			rec->insert(rec->end(), _columns.begin(), _columns.end());
		}
	}
}
