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

#include "SubstrApp.h"

#include "Substr.h"
#include "FileInput.h"
#include "FileOutput.h"

#include "SubstrApp.h"

namespace smartcube
{
	SubstrApp::SubstrApp()
	{
		// TODO Auto-generated constructor stub

	}

	SubstrApp::~SubstrApp()
	{
		// TODO Auto-generated destructor stub
	}

	void SubstrApp::defineOptions(Poco::Util::OptionSet& options)
	{
		ConsoleApp::defineOptions(options);

		options.addOption(Poco::Util::Option(
				"left", "l", "extract substring at left side.").required(
				false).repeatable(false).group("substr").binding(
				"smartcube.str.substr.left"));

		options.addOption(Poco::Util::Option(
				"right", "r", "extract substring at right side.").required(
				false).repeatable(false).group("substr").binding(
				"smartcube.str.substr.right"));

		options.addOption(Poco::Util::Option(
				"mid", "m", "extract substring at middle. [default]").required(
				false).repeatable(false).group("substr").binding(
				"smartcube.str.substr.mid"));

		options.addOption(Poco::Util::Option(
				"start", "s", "specify start position.").required(
				false).repeatable(false).argument("start", true).binding(
				"smartcube.str.substr.start"));

		options.addOption(Poco::Util::Option(
				"size", "n", "specify length of substring.").required(
				false).repeatable(false).argument("size", true).binding(
				"smartcube.str.substr.size"));
	}

	const std::string SubstrApp::getUsage() const
	{
		return "[OPTIONS] [-l|-r|-m] [--] <column> [<column> ...]";
	}

	const std::string SubstrApp::getHeader() const
	{
		return "Extract substring of columns, resulting in new columns.";
	}

	int SubstrApp::main2(const std::vector<std::string>& args)
	{
		std::vector<std::size_t> columns;
		Substr::SubstrOption option = Substr::Mid;

		if (config().hasOption("smartcube.str.substr.left"))
		{
			option = Substr::Left;
		}
		else if (config().hasOption("smartcube.str.substr.right"))
		{
			option = Substr::Right;
		}
		else if (config().hasOption("smartcube.str.substr.mid"))
		{
			option = Substr::Mid;
		}

		std::size_t start = config().getInt("smartcube.str.substr.start", 0);
		std::size_t n = config().getInt("smartcube.str.substr.size", INT_MAX);

		std::vector<std::string>::const_iterator iter = args.begin();
		for (; iter != args.end(); ++iter)
		{
			columns.push_back(Poco::DynamicAny(*iter).convert<std::size_t>());
		}

		Substr sub(columns, start, n, option);
		sub.handle(*getInput(), *getOutput());

		return Poco::Util::Application::EXIT_OK;
	}
}

POCO_APP_MAIN(smartcube::SubstrApp);
