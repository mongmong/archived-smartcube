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

#ifndef BITXOR_H_
#define BITXOR_H_

#include <sys/types.h>

#include "RoutineImpl.h"

namespace smartcube
{
	class BitXorOp
	{
		public:
			inline void operator ()(const Poco::DynamicAny& op1,
					const Poco::DynamicAny& op2,
					Poco::DynamicAny& out)
			{
				uint64_t o1 = static_cast<uint64_t> (op1);
				uint64_t o2 = static_cast<uint64_t> (op2);
				out = (o1 | o2) & ~(o1 & o2);
			}
	};

	typedef SimpleRoutineWrapper<Project2To1RoutineImpl<BitXorOp> , BitXorOp>
			BitXor;
}

#endif /* BITXOR_H_ */
