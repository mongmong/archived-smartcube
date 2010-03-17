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

#include "ForkOutput.h"
#include "Module.h"

#include "OutputWrapper.h"

namespace smartcube
{
	OutputWrapper::OutputWrapper() :
		_output(&_dummyOutput)
	{
	}

	OutputWrapper::OutputWrapper(Output& output) :
		_output(&output)
	{
	}

	OutputWrapper::~OutputWrapper()
	{
	}

	void OutputWrapper::wrap(Output& output)
	{
		_output = &output;
	}

	python::object OutputWrapper::getOutputs()
	{
		python::list obj;

		ForkOutput* foutput = dynamic_cast<ForkOutput*> (_output);

		if (NULL != foutput)
		{
			std::vector<OutputPtr>& outputs = foutput->getOutputs();
			std::vector<OutputPtr>::iterator iter = outputs.begin();

			for (; iter != outputs.end(); ++iter)
			{
				python::object o = Module::OutputWrapper();
				OutputWrapper& owrapper = python::extract<OutputWrapper&>(o);
				owrapper.wrap(**iter);

				obj.append(o);
			}
		}

		return obj;
	}
}
