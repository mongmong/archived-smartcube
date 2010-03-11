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

#include "InputWrapper.h"
#include "OutputWrapper.h"
#include "Module.h"

#include "RoutineWrapper.h"

namespace smartcube
{
	void RoutineWrapper::handle(Input& input, Output& output)
	{
		python::object i = Module::InputWrapper();
		python::object o = Module::OutputWrapper();
		InputWrapper& iwrapper = python::extract<InputWrapper&>(i);
		OutputWrapper& owrapper = python::extract<OutputWrapper&>(o);
		iwrapper.wrap(input);
		owrapper.wrap(output);
		this->get_override("handle")(i, o);
	}
}

