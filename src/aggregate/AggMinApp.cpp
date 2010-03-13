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

#include "AggMin.h"

#include "AggMinApp.h"

namespace smartcube
{
	AggMinApp::AggMinApp()
	{
		// TODO Auto-generated constructor stub

	}

	AggMinApp::~AggMinApp()
	{
		// TODO Auto-generated destructor stub
	}

	void AggMinApp::defineOptions(Poco::Util::OptionSet& options)
	{
		ConsoleApp::defineOptions(options);

		options.addOption(Poco::Util::Option(
				"groupby", "g", "specify group column.").required(
				false).repeatable(false) .argument("group", true).binding(
				"smartcube.agg.min.groupby"));

		options.addOption(Poco::Util::Option(
				"showall", "a", "show all rows.").required(
				false).repeatable(false).binding(
				"smartcube.agg.min.showall"));
	}

	const std::string AggMinApp::getUsage() const
	{
		return "[OPTIONS] [-g groupby] [-a] [--] <column> [<column> ...]";
	}

	const std::string AggMinApp::getHeader() const
	{
		return "Calculate minmum of rows";
	}

	int AggMinApp::main2(const std::vector<std::string>& args)
	{
		std::vector<std::size_t> columns;
		int group = config().getInt("smartcube.agg.min.groupby", 1);
		bool showall = config().hasOption("smartcube.agg.min.showall");

		std::vector<std::string>::const_iterator iter = args.begin();
		for (; iter != args.end(); ++iter)
		{
			columns.push_back(Poco::DynamicAny(*iter).convert<std::size_t>());
		}

		AggMin max(group, showall, columns);
		max.handle(*getInput(), *getOutput());

		return Poco::Util::Application::EXIT_OK;
	}
}

POCO_APP_MAIN(smartcube::AggMinApp);
