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

#include "Error.h"
#include "MemoryInput.h"
#include "MemoryOutput.h"
#include "Pipeline.h"

namespace smartcube
{
	Pipeline::Pipeline(InputPtr input, OutputPtr output) :
			_input(input),
			_output(output)
	{
		// TODO Auto-generated constructor stub

	}

	Pipeline::~Pipeline()
	{
		// TODO Auto-generated destructor stub
	}

	TaskPtr Pipeline::getHead()
	{
		return _headTask;
	}

	TaskPtr Pipeline::getTail()
	{
		return _tailTask;
	}

	Pipeline& Pipeline::append(RoutinePtr ptr)
	{
		SMARTCUBE_ASSERT(!_tailTask || NULL == _tailTask->output);

		TaskPtr current = new Task();
		current->routine = ptr;
		current->previous = _tailTask;
		current->output = _output;

		if (NULL == _tailTask)
		{
			_tailTask->next = current;

			SharedQueuePtr queue = new SharedQueue();
			InputPtr input = new MemoryInput(queue);
			OutputPtr output = new MemoryInput(queue);

			_tailTask->output = output;
			current->input = input;
		}

		if (NULL == _headTask)
		{
			_headTask = current;
			_headTask->input = _input;
		}

		_tailTask = current;

		return *this;
	}

	Pipeline& Pipeline::operator +(RoutinePtr ptr)
	{
		return append(ptr);
	}
}
