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

#include <Poco/DynamicAny.h>

#include "Default.h"

#include "DefaultApp.h"

namespace smartcube
{
	DefaultApp::DefaultApp()
	{
	}

	DefaultApp::~DefaultApp()
	{
	}

	void DefaultApp::defineOptions(Poco::Util::OptionSet& options)
	{
		ConsoleApp::defineOptions(options);
	}

	const std::string DefaultApp::getUsage() const
	{
		return "[OPTIONS] [--] <default> [<default> ...]";
	}

	const std::string DefaultApp::getHeader() const
	{
		return "Fill default values.";
	}

	int DefaultApp::main2(const std::vector<std::string>& args)
	{
		std::vector<Poco::DynamicAny> columns;

		std::vector<std::string>::const_iterator iter = args.begin();
		for (; iter != args.end(); ++iter)
		{
			columns.push_back(*iter);
		}

		Default Default(columns);
		Default.handle(*getInput(), *getOutput());

		return Poco::Util::Application::EXIT_OK;
	}
}

POCO_APP_MAIN(smartcube::DefaultApp);
