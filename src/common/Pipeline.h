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

#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <Poco/Runnable.h>
#include <Poco/SharedPtr.h>
#include <Poco/Thread.h>

#include "Input.h"
#include "Output.h"
#include "Record.h"
#include "Routine.h"
#include "SharedQueue.h"

namespace smartcube
{
	class Pipeline;

	Pipeline& operator + (RoutinePtr op1, RoutinePtr op2);
	Pipeline& operator * (RoutinePtr op1, RoutinePtr op2);

	class Pipeline
	{
		public:
			friend Pipeline& operator + (RoutinePtr op1, RoutinePtr op2);
			friend Pipeline& operator * (RoutinePtr op1, RoutinePtr op2);

			struct Task;
			typedef Poco::SharedPtr<Task> TaskPtr;
			struct Task : public Poco::Runnable
			{
					RoutinePtr 	routine;
					InputPtr 	input;
					OutputPtr 	output;
					std::vector<TaskPtr>		previous;
					std::vector<TaskPtr>		next;
			};

			Pipeline();
			virtual ~Pipeline();

		public:
			std::vector<TaskPtr>& getHead();
			std::vector<TaskPtr>& getTail();

			Pipeline& operator + (RoutinePtr ptr);
			Pipeline& operator + (const Pipeline& pipeline);

			Pipeline& operator * (RoutinePtr ptr);
			Pipeline& operator * (const Pipeline& pipeline);

		private:
			std::vector<TaskPtr>	_headTasks;
			std::vector<TaskPtr>	_tailTasks;
	};
}

#endif /* PIPELINE_H_ */
