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

#include "Log.h"
#include "FileInput.h"
#include "FileOutput.h"

#include "LogApp.h"

namespace smartcube
{
	LogApp::LogApp()
	{
		// TODO Auto-generated constructor stub

	}

	LogApp::~LogApp()
	{
		// TODO Auto-generated destructor stub
	}

	void LogApp::defineOptions(Poco::Util::OptionSet& options)
	{
		ConsoleApp::defineOptions(options);

		options.addOption(Poco::Util::Option(
				"base", "b", "specify base.").required(
				false).repeatable(false) .argument("base", true).binding(
				"smartcube.math.log.base"));
	}

	const std::string LogApp::getUsage() const
	{
		return "[OPTIONS] [-b <base>] <column> [<column> ..]";
	}

	const std::string LogApp::getHeader() const
	{
		return "Calculate log value of columns.";
	}

	int LogApp::main2(const std::vector<std::string>& args)
	{
		std::vector<std::size_t> columns;
		double base = config().getDouble("smartcube.math.log.base",  2.71828182845904523536028747135266250);

		std::vector<std::string>::const_iterator iter = args.begin();
		for (; iter != args.end(); ++iter)
		{
			columns.push_back(Poco::DynamicAny(*iter).convert<std::size_t>());
		}

		Log log(base, columns);
		log.handle(*getInput(), *getOutput());

		return Poco::Util::Application::EXIT_OK;
	}
}

POCO_APP_MAIN(smartcube::LogApp);
