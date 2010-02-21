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

#include "StripApp.h"

#include "Strip.h"
#include "FileInput.h"
#include "FileOutput.h"

#include "StripApp.h"

namespace smartcube
{
	StripApp::StripApp()
	{
		// TODO Auto-generated constructor stub

	}

	StripApp::~StripApp()
	{
		// TODO Auto-generated destructor stub
	}

	void StripApp::defineOptions(Poco::Util::OptionSet& options)
	{
		ConsoleApp::defineOptions(options);

		options.addOption(Poco::Util::Option(
				"left", "l", "strip left side.").required(
				false).repeatable(false).group("strip").binding(
				"smartcube.str.strip.left"));

		options.addOption(Poco::Util::Option(
				"right", "r", "strip right side.").required(
				false).repeatable(false).group("strip").binding(
				"smartcube.str.strip.right"));

		options.addOption(Poco::Util::Option(
				"both", "b", "strip both sides. [default]").required(
				false).repeatable(false).group("strip").binding(
				"smartcube.str.strip.both"));
	}

	const std::string StripApp::getUsage() const
	{
		return "[OPTIONS] [-l|-r|-b] [--] <column> [<column> ...]";
	}

	const std::string StripApp::getHeader() const
	{
		return "Strip columns, resulting in new columns.";
	}

	int StripApp::main2(const std::vector<std::string>& args)
	{
		std::vector<std::size_t> columns;
		Strip::StripOption option = Strip::Both;

		if (config().hasOption("smartcube.str.strip.left"))
		{
			option = Strip::Left;
		}
		else if (config().hasOption("smartcube.str.strip.right"))
		{
			option = Strip::Right;
		}
		else if (config().hasOption("smartcube.str.strip.both"))
		{
			option = Strip::Both;
		}

		std::vector<std::string>::const_iterator iter = args.begin();
		for (; iter != args.end(); ++iter)
		{
			columns.push_back(Poco::DynamicAny(*iter).convert<std::size_t>());
		}

		Strip strip(columns, option);
		strip.handle(*getInput(), *getOutput());

		return Poco::Util::Application::EXIT_OK;
	}
}

POCO_APP_MAIN(smartcube::StripApp);
