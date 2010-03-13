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

#include "And.h"

#include "AndApp.h"

namespace smartcube
{
	AndApp::AndApp()
	{
		// TODO Auto-generated constructor stub

	}

	AndApp::~AndApp()
	{
		// TODO Auto-generated destructor stub
	}

	void AndApp::defineOptions(Poco::Util::OptionSet& options)
	{
		ConsoleApp::defineOptions(options);

	}

	const std::string AndApp::getUsage() const
	{
		return "[OPTIONS] [--] <column1> <column2> [<column1> <column2> ...]";
	}

	const std::string AndApp::getHeader() const
	{
		return "Calculate logic AND of column pairs, <column1> and <column2>, resulting in new boolean columns.";
	}

	int AndApp::main2(const std::vector<std::string>& args)
	{
		std::vector<std::size_t> columns;

		std::vector<std::string>::const_iterator iter = args.begin();
		for (; iter != args.end(); ++iter)
		{
			columns.push_back(Poco::DynamicAny(*iter).convert<std::size_t>());
		}

		And a(columns);
		a.handle(*getInput(), *getOutput());

		return Poco::Util::Application::EXIT_OK;
	}
}

POCO_APP_MAIN(smartcube::AndApp);
