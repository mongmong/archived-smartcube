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
	Pipeline::Pipeline()
	{
		// TODO Auto-generated constructor stub

	}

	Pipeline::~Pipeline()
	{
		// TODO Auto-generated destructor stub
	}

	std::vector<TaskPtr>& Pipeline::getHead()
	{
		return _headTasks;
	}

	std::vector<TaskPtr>& Pipeline::getTail()
	{
		return _tailTasks;
	}

	Pipeline& Pipeline::operator +(RoutinePtr ptr)
	{
		TaskPtr current = new Task();
		current->routine = ptr;
		current->previous = _tailTask;
		// current->next
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

	Pipeline& Pipeline::operator +(const Pipeline& pipeline)
	{

	}

	Pipeline& Pipeline::operator *(RoutinePtr ptr)
	{
	}

	Pipeline& Pipeline::operator *(const Pipeline& pipeline)
	{
	}
}
