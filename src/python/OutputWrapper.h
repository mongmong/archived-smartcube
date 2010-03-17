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

#ifndef OUTPUTWRAPPER_H_
#define OUTPUTWRAPPER_H_

#include <iostream>

#include <boost/python.hpp>

#include "Output.h"
#include "DummyOutput.h"

namespace smartcube
{
	namespace python = boost::python;

	class OutputWrapper: public Output
	{
		public:
			OutputWrapper();
			OutputWrapper(Output& output);
			virtual ~OutputWrapper();

		public:
			void wrap(Output& output);

			inline void push(RecordPtr ptr)
			{
				_output->push(ptr);
			}
			inline void push2(python::object obj)
			{
				// std::cout << "OutputWrapper::push2() called." << std::endl;
				RecordPtr rec = new Record();
				*rec = obj;
				//std::cout << "OutputWrapper::push2() after *rec = obj." << std::endl;
				// _output->push(RecordHelper::pythonListToRecord(obj));
				_output->push(rec);
			}

			python::object getOutputs();

		private:
			DummyOutput _dummyOutput;
			Output* _output;
	};
}

#endif /* OUTPUTWRAPPER_H_ */
