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

#ifndef GROUP_H_
#define GROUP_H_

#include <sys/types.h>

#include "Routine.h"

namespace smartcube
{
	class Group : public Routine
	{
		public:
			Group(const std::vector<std::size_t>& columns, std::size_t groupBy = 1, char separator = ',', bool showAll = false);
			virtual ~Group();

		public:
			virtual void handle(Input& input, Output& output);

		private:
			std::vector<std::size_t>	_columns;
			std::size_t					_group;
			char						_separator;
			bool						_showAll;
	};
}

#endif /* GROUP_H_ */
