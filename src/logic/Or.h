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

#ifndef OR_H_
#define OR_H_

#include <sys/types.h>

#include "RoutineImpl.h"

namespace smartcube
{
	class OrOp
	{
		public:
			inline void operator ()(const Cell& op1, const Cell& op2, Cell& out)
			{
				out = static_cast<bool> (op1) || static_cast<bool> (op2);
			}
	};

	typedef SimpleRoutineWrapper<Project2To1RoutineImpl<OrOp> , OrOp> Or;
}

#endif /* OR_H_ */
