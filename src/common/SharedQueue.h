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

#ifndef SHAREDQUEUE_H_
#define SHAREDQUEUE_H_

#include <sys/types.h>
#include <queue>

#include <boost/noncopyable.hpp>

#include "Record.h"

namespace smartcube
{
	class SharedQueue : public boost::noncopyable
	{
		public:
			SharedQueue(std::size_t maxSize = 100, long waitMilliseconds = 10);
			virtual ~SharedQueue();

		public:
			RecordPtr pop();
			void push(RecordPtr record);

			std::size_t size() const;

		public:
			std::size_t				_maxSize;
			long					_waitMilliseconds;

			std::queue<RecordPtr>	_queue;

			bool					_popSign;
			bool					_pushSign;
	};

	typedef Poco::SharedPtr<SharedQueue> SharedQueuePtr;
}

#endif /* SHAREDQUEUE_H_ */
