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

#include "JoinInput.h"
#include "Module.h"

#include "InputWrapper.h"

namespace smartcube
{
	InputWrapper::InputWrapper() :
		_input(&_dummyInput)
	{
	}

	InputWrapper::InputWrapper(Input& input) :
		_input(&input)
	{
	}

	InputWrapper::~InputWrapper()
	{
	}

	void InputWrapper::wrap(Input& input)
	{
		_input = &input;
	}

	python::object InputWrapper::getInputs()
	{
		python::list obj;

		JoinInput* jinput = dynamic_cast<JoinInput*> (_input);

		if (NULL != jinput)
		{
			std::vector<InputPtr>& inputs = jinput->getInputs();
			std::vector<InputPtr>::iterator iter = inputs.begin();

			for (; iter != inputs.end(); ++iter)
			{
				python::object i = Module::InputWrapper();
				InputWrapper& iwrapper = python::extract<InputWrapper&>(i);
				iwrapper.wrap(**iter);

				obj.append(i);
			}
		}

		return obj;
	}
}
