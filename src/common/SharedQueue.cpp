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

#include <Poco/Thread.h>

#include "Error.h"

#include "SharedQueue.h"

namespace smartcube
{
	SharedQueue::SharedQueue(std::size_t maxSize, long waitMilliseconds) :
		_maxSize(maxSize), _waitMilliseconds(waitMilliseconds), _popSign(false), _pushSign(false)
	{
		// TODO Auto-generated constructor stub

	}

	SharedQueue::~SharedQueue()
	{
		// TODO Auto-generated destructor stub
	}

	RecordPtr SharedQueue::pop()
	{
		RecordPtr ret;

		do
		{
			_popSign = true;
			if (!_pushSign)
			{
				if (!_queue.empty())
				{
					ret = _queue.front();

					SMARTCUBE_ASSERT(!ret.isNull());

					_queue.pop();
				}
			}
			_popSign = false;

			Poco::Thread::sleep(_waitMilliseconds);
		} while (ret.isNull());

		return ret;
	}

	void SharedQueue::push(RecordPtr value)
	{
		bool pushed = false;

		do
		{
			_pushSign = true;
			if (!_popSign)
			{
				if (_queue.size() < _maxSize)
				{
					_queue.push(value);
				}
			}
			_pushSign = false;

			Poco::Thread::sleep(_waitMilliseconds);
		} while (!pushed);
	}

	std::size_t SharedQueue::size() const
	{
		return _queue.size();
	}
}
