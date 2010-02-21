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

#ifndef MEMORYOUTPUT_H_
#define MEMORYOUTPUT_H_

#include "SharedQueue.h"
#include "Record.h"
#include "Output.h"

namespace smartcube
{
	class MemoryOutput : public Output
	{
		public:
			MemoryOutput(SharedQueuePtr queue);
			virtual ~MemoryOutput();

		public:
			void push(RecordPtr record);

			SharedQueuePtr getQueue();

		public:
			SharedQueuePtr	_queue;
	};
}

#endif /* MEMORYOUTPUT_H_ */
