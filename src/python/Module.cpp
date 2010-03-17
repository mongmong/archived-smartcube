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

#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>

#include "RoutineWrapper.h"
#include "InputWrapper.h"
#include "OutputWrapper.h"

#include "Module.h"

namespace smartcube
{
	python::object Module::InputWrapper;
	python::object Module::OutputWrapper;
	python::object Module::RoutineWrapper;

	void Module::registerModule()
	{
		static bool registered = false;

		if (registered)
		{
			return;
		}

		registered = true;

		RoutineWrapper =
				python::class_<smartcube::RoutineWrapper, boost::noncopyable>("Routine")
				.def("handle", python::pure_virtual(&smartcube::Routine::handle))
				;

		InputWrapper =
				python::class_<smartcube::InputWrapper, boost::noncopyable>("InputWrapper")
				.def("pop", &smartcube::InputWrapper::pop2)
				.def("get_inputs", &smartcube::InputWrapper::getInputs)
				;

		OutputWrapper =
				python::class_<smartcube::OutputWrapper, boost::noncopyable>("OutputWrapper")
				.def("push", &smartcube::OutputWrapper::push2)
				.def("get_outputs", &smartcube::OutputWrapper::getOutputs)
				;

		/*
		Config =
				python::class_<std::map<std::string, std::string> >("Config")
				.def(python::map_indexing_suite<std::map<std::string, std::string>, true>());
		*/
	}
}
