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

#include "ReFormat.h"
#include "FileInput.h"
#include "FileOutput.h"

#include "ReFormatApp.h"

namespace smartcube
{
	ReFormatApp::ReFormatApp()
	{
		// TODO Auto-generated constructor stub

	}

	ReFormatApp::~ReFormatApp()
	{
		// TODO Auto-generated destructor stub
	}

	void ReFormatApp::defineOptions(Poco::Util::OptionSet& options)
	{
		ConsoleApp::defineOptions(options);

		options.addOption(Poco::Util::Option(
				"pattern", "p", "specify RE pattern.") .required(
				false).repeatable(false).argument("pattern", true) .binding(
				"smartcube.str.xformat.pattern"));

		options.addOption(Poco::Util::Option(
				"format", "f", "specify RE format.") .required(
				false).repeatable(false).argument("format", true) .binding(
				"smartcube.str.xformat.format"));

		options.addOption(Poco::Util::Option(
				"match", "m", "use match mode. [default]") .required(
				false).repeatable(false).group("reformat") .binding(
				"smartcube.str.xformat.match"));

		options.addOption(Poco::Util::Option(
				"search", "s", "use search mode.") .required(
				false).repeatable(false).group("reformat") .binding(
				"smartcube.str.xformat.search"));
	}

	const std::string ReFormatApp::getUsage() const
	{
		return "[OPTIONS] [-p pattern] [-f format] [-m|-s] [--] <column> [<column> ... ]";
	}

	const std::string ReFormatApp::getHeader() const
	{
		return "Format columns with specified RE pattern, resulting in new columns.";
	}

	int ReFormatApp::main2(const std::vector<std::string>& args)
	{
		std::vector<std::size_t> columns;
		std::string pattern = config().getString("smartcube.str.xformat.pattern", "");
		std::string format = config().getString("smartcube.str.xformat.format", "");

		ReFormat::ReFormatOption option = ReFormat::Match;
		if (config().hasOption("smartcube.str.xformat.search"))
		{
			option = ReFormat::Search;
		}
		else if (config().hasOption("smartcube.str.xformat.match"))
		{
			option = ReFormat::Match;
		}

		std::vector<std::string>::const_iterator iter = args.begin();
		for (; iter != args.end(); ++iter)
		{
			columns.push_back(Poco::DynamicAny(*iter).convert<std::size_t>());
		}


		ReFormat split(columns, pattern, format, option);
		split.handle(*getInput(), *getOutput());

		return Poco::Util::Application::EXIT_OK;
	}
}

POCO_APP_MAIN(smartcube::ReFormatApp);
