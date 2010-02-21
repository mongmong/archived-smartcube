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

#ifndef FILTER_H_
#define FILTER_H_

#include <sys/types.h>

#include "Routine.h"

namespace smartcube
{
	class Filter : public Routine
	{
		public:
			enum FilterType {FilterAnd, FilterOr};

			Filter(FilterType filterType, const std::vector<std::size_t>& columns);
			virtual ~Filter();

		public:
			virtual void handle(Input& input, Output& output);

		private:
			FilterType					_filterType;
			std::vector<std::size_t>	_columns;
	};
}

#endif /* FILTER_H_ */
