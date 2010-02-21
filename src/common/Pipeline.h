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
	class Pipeline
	{
		public:
			class Runner: public Poco::Runnable
			{
			};

			struct Task;
			typedef Poco::SharedPtr<Task> TaskPtr;
			struct Task : public Poco::Runnable
			{
					RoutinePtr 	routine;
					InputPtr 	input;
					OutputPtr 	output;
					TaskPtr		previous;
					TaskPtr		next;


			};

			Pipeline(InputPtr input, OutputPtr output);
			virtual ~Pipeline();

		public:
			TaskPtr getHead();
			TaskPtr getTail();

			InputPtr getInput();
			OutputPtr getOutput();

			Pipeline& append(RoutinePtr ptr);
			Pipeline& append(const Pipeline& pipeline);

			Pipeline& operator + (RoutinePtr ptr);
			Pipeline& operator + (const Pipeline& pipeline);

		private:
			TaskPtr _headTask;
			TaskPtr	_tailTask;

			InputPtr	_input;
			OutputPtr	_output;
	};
}

#endif /* PIPELINE_H_ */
