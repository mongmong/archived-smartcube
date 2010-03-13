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

#ifndef RECORDPOOL_H_
#define RECORDPOOL_H_

#include <queue>

#include <Poco/Mutex.h>

#include "Record.h"

namespace smartcube
{
	class RecordPool
	{
		public:
			virtual ~RecordPool();

			static inline RecordPool& getInstance()
			{
				return _pool;
			}

		public:

			inline RecordPtr allocate()
			{
				Poco::FastMutex::ScopedLock lock(_mutex);

				if (_queue.empty())
				{
					return new Record();
				}

				RecordPtr rec = _queue.front();
				_queue.pop();

				rec->clear();

				return rec;
			}
			inline void free(RecordPtr rec)
			{
				Poco::FastMutex::ScopedLock lock(_mutex);

				if (_queue.size() < 10000)
				{
					_queue.push(rec);
				}
			}

		private:
			RecordPool();

			static RecordPool _pool;

			std::queue<RecordPtr> 	_queue;
			Poco::FastMutex			_mutex;
	};
}

#endif /* RECORDPOOL_H_ */
