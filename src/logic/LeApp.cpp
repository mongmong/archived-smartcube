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

#include "LeApp.h"

#include "Le.h"

#include "LeApp.h"

namespace smartcube
{
	LeApp::LeApp()
	{
		// TODO Auto-generated constructor stub

	}

	LeApp::~LeApp()
	{
		// TODO Auto-generated destructor stub
	}

	void LeApp::defineOptions(Poco::Util::OptionSet& options)
	{
		ConsoleApp::defineOptions(options);

		options.addOption(Poco::Util::Option(
				"numeric", "n", "compare numerics.").required(
				false).repeatable(false).group("le").binding(
				"smartcube.log.le.numeric"));

		options.addOption(Poco::Util::Option(
				"case-sensitive", "c", "compare strings, case sensitive.").required(
				false).repeatable(false).group("le").binding(
				"smartcube.log.le.string-case-sensitive"));

		options.addOption(Poco::Util::Option(
				"case-insensitive", "i", "compare strings, case insensitive.").required(
				false).repeatable(false).group("le").binding(
				"smartcube.log.le.string-case-insensitive"));
	}

	const std::string LeApp::getUsage() const
	{
		return "[OPTIONS] [-n|-c|-i] [--] <column1> <column2> [<column1> <column2> ...]";
	}

	const std::string LeApp::getHeader() const
	{
		return "Compare column pairs, <column1> <= <column2>, resulting in new boolean columns.";
	}

	int LeApp::main2(const std::vector<std::string>& args)
	{
		std::vector<std::size_t> columns;
		Le::LeOption leOption = Le::Numeric;

		if (config().hasOption("smartcube.log.le.numeric"))
		{
			leOption = Le::Numeric;
		}
		else if (config().hasOption("smartcube.log.le.string-case-sensitive"))
		{
			leOption = Le::StringCaseSensitive;
		}
		else if (config().hasOption("smartcube.log.le.string-case-insensitive"))
		{
			leOption = Le::StringCaseInsensitive;
		}

		std::vector<std::string>::const_iterator iter = args.begin();
		for (; iter != args.end(); ++iter)
		{
			columns.push_back(Poco::DynamicAny(*iter).convert<std::size_t>());
		}

		Le le(columns, leOption);
		le.handle(*getInput(), *getOutput());

		return Poco::Util::Application::EXIT_OK;
	}
}

POCO_APP_MAIN(smartcube::LeApp);
