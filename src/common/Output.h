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

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include <boost/noncopyable.hpp>

#include <Poco/SharedPtr.h>

#include "Record.h"

namespace smartcube
{
	class Output : public boost::noncopyable
	{
		public:
			Output();
			virtual ~Output();

		public:
			virtual void push(RecordPtr record) = 0;

			virtual void free(RecordPtr rec);
	};

	typedef Poco::SharedPtr<Output> OutputPtr;
}

#endif /* OUTPUT_H_ */
