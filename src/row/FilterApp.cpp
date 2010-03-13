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

#include "Filter.h"

#include "FilterApp.h"

namespace smartcube
{
	FilterApp::FilterApp()
	{
		// TODO Auto-generated constructor stub

	}

	FilterApp::~FilterApp()
	{
		// TODO Auto-generated destructor stub
	}

	void FilterApp::defineOptions(Poco::Util::OptionSet& options)
	{
		ConsoleApp::defineOptions(options);

		options.addOption(Poco::Util::Option(
				"and", "a", "filter by and operation.").required(
				false).repeatable(false).group("filter").binding(
				"smartcube.row.filter.and"));

		options.addOption(Poco::Util::Option(
				"or", "o", "filter by or operation.").required(
				false).repeatable(false).group("filter").binding(
				"smartcube.row.filter.or"));
	}

	const std::string FilterApp::getUsage() const
	{
		return "[OPTIONS] [--and|--or] [--] <column> [<column> ... ]";
	}

	const std::string FilterApp::getHeader() const
	{
		return "Filter rows according boolean test result upon specified columns.";
	}

	int FilterApp::main2(const std::vector<std::string>& args)
	{
		std::vector<std::size_t> columns;
		Filter::FilterType filterType = Filter::FilterAnd;

		if (config().hasOption("smartcube.row.filter.and"))
		{
			filterType = Filter::FilterAnd;
		}
		else if (config().hasOption("smartcube.row.filter.or"))
		{
			filterType = Filter::FilterOr;
		}

		std::vector<std::string>::const_iterator iter = args.begin();
		for (; iter != args.end(); ++iter)
		{
			columns.push_back(Poco::DynamicAny(*iter).convert<std::size_t>());
		}

		Filter select(filterType, columns);
		select.handle(*getInput(), *getOutput());

		return Poco::Util::Application::EXIT_OK;
	}
}

POCO_APP_MAIN(smartcube::FilterApp);
