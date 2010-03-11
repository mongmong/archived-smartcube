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

#include <iostream>

#include <boost/python.hpp>



#include "Input.h"
#include "InputWrapper.h"
#include "DummyInput.h"
#include "Output.h"
#include "OutputWrapper.h"
#include "DummyOutput.h"
#include "RoutineWrapper.h"
#include "Module.h"

#include "PythonWrapperApp.h"

namespace python = boost::python;

BOOST_PYTHON_MODULE(smartcube)
{
	smartcube::Module::registerModule();
}

namespace smartcube
{
	PythonWrapperApp::PythonWrapperApp()
	{
		// TODO Auto-generated constructor stub

	}

	PythonWrapperApp::~PythonWrapperApp()
	{
		// TODO Auto-generated destructor stub
	}

	void PythonWrapperApp::defineOptions(Poco::Util::OptionSet& options)
	{
		ConsoleApp::defineOptions(options);

		/*
		options.addOption(Poco::Util::Option(
				"", "g", "specify group columns.").required(
				false).repeatable(false) .argument("group", true).binding(
				"smartcube.agg.count.groupby"));

		options.addOption(Poco::Util::Option(
				"showall", "a", "show all rows.").required(
				false).repeatable(false).binding(
				"smartcube.agg.count.showall"));
		*/
	}

	const std::string PythonWrapperApp::getUsage() const
	{
		return "[OPTIONS] <module>";
	}

	const std::string PythonWrapperApp::getHeader() const
	{
		return "Execute specified module.";
	}

	void PythonWrapperApp::getProperties(const std::string& base, python::dict& d)
	{
		Poco::Util::AbstractConfiguration::Keys keys;
		config().keys(base, keys);
		if (keys.empty())
		{
			if (config().hasProperty(base))
			{
				d[base] = config().getString(base);
			}
		}
		else
		{
			for (Poco::Util::AbstractConfiguration::Keys::const_iterator it =
					keys.begin(); it != keys.end(); ++it)
			{
				std::string fullKey = base;
				if (!fullKey.empty())
					fullKey += '.';
				fullKey.append(*it);
				getProperties(fullKey, d);
			}
		}
	}


	int PythonWrapperApp::main2(const std::vector<std::string>& args)
	{
		if (args.size() == 0)
		{
			this->displayHelp();
			return Poco::Util::Application::EXIT_USAGE;
		}

		Py_Initialize();
		atexit(Py_Finalize);

		/*
		 * Initialize smartcube module
		 */
		initsmartcube();

		try
		{
			python::object module = python::import(args[0].c_str());
			python::object routineClass = python::getattr(module, "__routine__");

			python::dict d;
			this->getProperties("", d);

			python::object routine = routineClass(d);
			RoutineWrapper& wrapper =
					python::extract<RoutineWrapper&>(routine)();

			wrapper.handle(*createInput(), *createOutput());
		}
		catch(const python::error_already_set&)
		{
			PyErr_Print();
			return Poco::Util::Application::EXIT_SOFTWARE;
		}
		return Poco::Util::Application::EXIT_OK;
	}
}

POCO_APP_MAIN(smartcube::PythonWrapperApp);
