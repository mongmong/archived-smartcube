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

#include "Norm.h"

#include "NormApp.h"

namespace smartcube
{
	NormApp::NormApp()
	{
		// TODO Auto-generated constructor stub

	}

	NormApp::~NormApp()
	{
		// TODO Auto-generated destructor stub
	}

	void NormApp::defineOptions(Poco::Util::OptionSet& options)
	{
		ConsoleApp::defineOptions(options);

		options.addOption(Poco::Util::Option(
				"max", "m", "normalize by maximum value.").required(
				false).repeatable(false).group("norm").binding(
				"smartcube.norm.max"));

		options.addOption(Poco::Util::Option(
				"average", "g", "normalize by average value.").required(
				false).repeatable(false).group("norm").binding(
				"smartcube.norm.average"));

		options.addOption(Poco::Util::Option(
				"sum", "s", "normalize by sum value.").required(
				false).repeatable(false).group("norm").binding(
				"smartcube.norm.sum"));
	}

	const std::string NormApp::getUsage() const
	{
		return "[OPTIONS] [-m|-g|-s] [--] <column> [<column> ...]";
	}

	const std::string NormApp::getHeader() const
	{
		return "Normalize specified columns.";
	}

	int NormApp::main2(const std::vector<std::string>& args)
	{
		std::vector<std::size_t> columns;
		Norm::NormOption normOption = Norm::Max;

		if (config().hasOption("smartcube.norm.max"))
		{
			normOption = Norm::Max;
		}
		else if (config().hasOption("smartcube.norm.average"))
		{
			normOption = Norm::Average;
		}
		else if (config().hasOption("smartcube.norm.sum"))
		{
			normOption = Norm::Sum;
		}

		std::vector<std::string>::const_iterator iter = args.begin();
		for (; iter != args.end(); ++iter)
		{
			columns.push_back(Poco::DynamicAny(*iter).convert<std::size_t>());
		}

		Norm norm(normOption, columns);
		norm.handle(*getInput(), *getOutput());

		return Poco::Util::Application::EXIT_OK;
	}
}

POCO_APP_MAIN(smartcube::NormApp);
