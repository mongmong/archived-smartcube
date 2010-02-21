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

#ifndef SIGN_H_
#define SIGN_H_

#include <sys/types.h>

#include "RoutineImpl.h"

namespace smartcube
{
	class SignOp
	{
		public:
			bool operator ()(const Poco::DynamicAny& op, Poco::DynamicAny& out)
			{
				double result = static_cast<double>(op);
				if (result > 0.0)
				{
					out = 1;
				}
				else if (result < 0.0)
				{
					out = -1;
				}
				else
				{
					out = 0;
				}

				return true;
			}
	};

	typedef Project2To1RoutineImpl<SignOp> Sign;
}

#endif /* SIGN_H_ */
