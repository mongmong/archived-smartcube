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
#include <Poco/StringTokenizer.h>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

#include "Ungroup.h"
#include "FileInput.h"
#include "FileOutput.h"

#include "UngroupApp.h"

namespace smartcube
{
	UngroupApp::UngroupApp()
	{
		// TODO Auto-generated constructor stub

	}

	UngroupApp::~UngroupApp()
	{
		// TODO Auto-generated destructor stub
	}

	void UngroupApp::defineOptions(Poco::Util::OptionSet& options)
	{
		ConsoleApp::defineOptions(options);

		options.addOption(Poco::Util::Option(
				"gsep", "t", "specify group separators. [default: ',']") .required(
				false).repeatable(false).argument("sep", true) .binding(
				"smartcube.group.ungroup.separators"));
	}

	const std::string UngroupApp::getUsage() const
	{
		return "[OPTIONS] [-t separator] [--] <column> [<column> ...]";
	}

	const std::string UngroupApp::getHeader() const
	{
		return ConsoleApp::getHeader();
	}

	int UngroupApp::main2(const std::vector<std::string>& args)
	{
		std::vector<std::size_t> columns;
		std::string separators = config().getString("smartcube.group.ungroup.separators", ",");

		std::vector<std::string>::const_iterator iter = args.begin();
		for (; iter != args.end(); ++iter)
		{
			columns.push_back(Poco::DynamicAny(*iter).convert<std::size_t>());
		}

		Ungroup g(columns, separators);
		g.handle(*getInput(), *getOutput());

		return Poco::Util::Application::EXIT_OK;
	}
}

POCO_APP_MAIN(smartcube::UngroupApp);
