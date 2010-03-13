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

#include "Backfill.h"

namespace smartcube
{
	Backfill::Backfill(const std::vector<std::size_t>& columns) :
		_columns(columns)
	{
	}

	Backfill::~Backfill()
	{
	}

	void Backfill::handle(Input& input, Output& output)
	{
		RecordPtr rec = input.pop();

		std::size_t size = _columns.size() / 3;
		for (; !rec->eof(); output.push(rec), rec = input.pop())
		{
			std::size_t s = rec->size();
			rec->resize(s + size);

			std::size_t i = 0;
			for (; i < size; ++i)
			{
				std::size_t x = _columns[3 * i + 0];
				std::size_t y = _columns[3 * i + 1];
				std::size_t z = _columns[3 * i + 2];
				std::size_t index = s + i;

				Poco::DynamicAny& any = (*rec)[x];
				if (!static_cast<bool> (any))
				{
					y = z;
				}

				(*rec)[index] = (*rec)[y];
			}

		}
	}
}
