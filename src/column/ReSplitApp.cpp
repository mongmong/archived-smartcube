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

#include "ReSplit.h"
#include "FileInput.h"
#include "FileOutput.h"

#include "ReSplitApp.h"

namespace smartcube
{
	ReSplitApp::ReSplitApp()
	{
		// TODO Auto-generated constructor stub

	}

	ReSplitApp::~ReSplitApp()
	{
		// TODO Auto-generated destructor stub
	}

	void ReSplitApp::defineOptions(Poco::Util::OptionSet& options)
	{
		ConsoleApp::defineOptions(options);

		options.addOption(Poco::Util::Option(
				"pattern", "p", "specify RE pattern.") .required(
				false).repeatable(false).argument("pattern", true) .binding(
				"smartcube.col.resplit.pattern"));

		options.addOption(Poco::Util::Option(
				"match", "m", "use match mode. [default]") .required(
				false).repeatable(false).group("resplit") .binding(
				"smartcube.col.resplit.match"));

		options.addOption(Poco::Util::Option(
				"search", "s", "use search mode.") .required(
				false).repeatable(false).group("resplit") .binding(
				"smartcube.col.resplit.search"));
	}

	const std::string ReSplitApp::getUsage() const
	{
		return "[OPTIONS] [-p pattern] [--] <column> [<column> ... ]";
	}

	const std::string ReSplitApp::getHeader() const
	{
		return "Split columns with specified RE pattern, resulting in new columns.";
	}

	int ReSplitApp::main2(const std::vector<std::string>& args)
	{
		std::vector<std::size_t> columns;
		std::string pattern = config().getString("smartcube.col.resplit.pattern", "");
		ReSplit::ReSplitOption option = ReSplit::Match;
		if (config().hasOption("smartcube.col.resplit.search"))
		{
			option = ReSplit::Search;
		}
		else if (config().hasOption("smartcube.col.resplit.match"))
		{
			option = ReSplit::Match;
		}

		std::vector<std::string>::const_iterator iter = args.begin();
		for (; iter != args.end(); ++iter)
		{
			columns.push_back(Poco::DynamicAny(*iter).convert<std::size_t>());
		}

		ReSplit split(columns, pattern, option);
		split.handle(*getInput(), *getOutput());

		return Poco::Util::Application::EXIT_OK;
	}
}

POCO_APP_MAIN(smartcube::ReSplitApp);
