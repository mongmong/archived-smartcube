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

#include "AggQuantile.h"

#include "AggQuantileApp.h"

namespace smartcube
{
	AggMedianApp::AggMedianApp()
	{
		// TODO Auto-generated constructor stub

	}

	AggMedianApp::~AggMedianApp()
	{
		// TODO Auto-generated destructor stub
	}

	void AggMedianApp::defineOptions(Poco::Util::OptionSet& options)
	{
		ConsoleApp::defineOptions(options);

		options.addOption(Poco::Util::Option(
				"groupby", "g", "specify group column.").required(
				false).repeatable(false) .argument("group", true).binding(
				"smartcube.agg.median.groupby"));

		options.addOption(Poco::Util::Option(
				"showall", "a", "show all rows.").required(
				false).repeatable(false).binding(
				"smartcube.agg.median.showall"));

		options.addOption(Poco::Util::Option(
				"quantile", "q", "specify quantile.").required(
				false).repeatable(true).argument("quantile", true).binding(
				"smartcube.agg.median.quantile"));
	}

	const std::string AggMedianApp::getUsage() const
	{
		return "[OPTIONS] [-g groupby] [-a] [--] <column> [<column> ...]";
	}

	const std::string AggMedianApp::getHeader() const
	{
		return "Calculate median of rows.";
	}

	int AggMedianApp::main2(const std::vector<std::string>& args)
	{
		std::vector<std::size_t> columns;
		int group = config().getInt("smartcube.agg.median.groupby", 1);
		bool showall = config().hasOption("smartcube.agg.median.showall");
		double quartile = config().getDouble("smartcube.agg.median.quantile", 0.5);

		std::vector<std::string>::const_iterator iter = args.begin();
		for (; iter != args.end(); ++iter)
		{
			columns.push_back(Poco::DynamicAny(*iter).convert<std::size_t>());
		}

		AggQuantile avg(columns, quartile, group, showall);
		avg.handle(*getInput(), *getOutput());

		return Poco::Util::Application::EXIT_OK;
	}
}

POCO_APP_MAIN(smartcube::AggMedianApp);
