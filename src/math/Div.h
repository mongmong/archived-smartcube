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

#ifndef DIV_H_
#define DIV_H_

#include <sys/types.h>

#include "RoutineImpl.h"

namespace smartcube
{
	/*
	class Div : public Routine
	{
		public:
			Div(const std::vector<std::size_t>& columns);
			virtual ~Div();

		public:
			virtual void handle(Input& input, Output& output);

		private:
			std::vector<std::size_t>	_columns;
	};
	*/

	class DivOp
	{
		public:
			bool operator ()(const Cell& op1, const Cell& op2, Cell& out)
			{
				out = static_cast<double>(op1) / static_cast<double>(op2);
				return true;
			}
	};

	typedef Project2To1RoutineImpl<DivOp> Div;
}

#endif /* DIV_H_ */
