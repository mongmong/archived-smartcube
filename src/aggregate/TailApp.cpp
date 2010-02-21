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

#include "Tail.h"
#include "FileInput.h"
#include "FileOutput.h"

#include "TailApp.h"

namespace smartcube
{
	TailApp::TailApp()
	{
		// TODO Auto-generated constructor stub

	}

	TailApp::~TailApp()
	{
		// TODO Auto-generated destructor stub
	}

	void TailApp::defineOptions(Poco::Util::OptionSet& options)
	{
		ConsoleApp::defineOptions(options);

		options.addOption(Poco::Util::Option(
				"groupby", "g", "specify group column.").required(
				false).repeatable(false) .argument("group", true).binding(
				"smartcube.agg.tail.groupby"));

		options.addOption(Poco::Util::Option(
				"lines", "n", "specify the number of lines.").required(
				false).repeatable(false).argument("num").binding(
				"smartcube.agg.tail.lines"));
	}

	const std::string TailApp::getUsage() const
	{
		return "[OPTIONS] [-g groupby] [-n num] [--]";
	}

	const std::string TailApp::getHeader() const
	{
		return ConsoleApp::getHeader();
	}

	int TailApp::main2(const std::vector<std::string>& args)
	{
		std::vector<std::size_t> columns;
		int group = config().getInt("smartcube.agg.tail.groupby", 1);
		int showNum = config().getInt("smartcube.agg.tail.lines", 1);

		Tail tail(group, showNum);
		tail.handle(*getInput(), *getOutput());

		return Poco::Util::Application::EXIT_OK;
	}
}

POCO_APP_MAIN(smartcube::TailApp);
