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

#ifndef EXPAND_H_
#define EXPAND_H_

#include <string>

#include "Routine.h"

namespace smartcube
{
	class Expand : public Routine
	{
		public:
			Expand(const std::vector<std::string>& columns);
			virtual ~Expand();

		public:
			virtual void handle(Input& input, Output& output);

		private:
			std::vector<std::string>	_columns;
	};
}

#endif /* EXPAND_H_ */
