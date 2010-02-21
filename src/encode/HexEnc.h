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

#ifndef HEXENC_H_
#define HEXENC_H_

#include <sstream>

#include <Poco/DynamicAny.h>
#include <Poco/HexBinaryEncoder.h>

#include "RoutineImpl.h"

namespace smartcube
{
	class HexEncOp
	{
		public:
			inline void operator()(const Poco::DynamicAny& op,
					Poco::DynamicAny& out)
			{
				std::ostringstream oss;
				Poco::HexBinaryEncoder enc(oss);
				enc << static_cast<const std::string&> (op);

				out = oss.str();
			}
	};

	typedef SimpleRoutineWrapper<Project1To1RoutineImpl<HexEncOp> , HexEncOp>
			HexEnc;
}

#endif /* HEXENC_H_ */
