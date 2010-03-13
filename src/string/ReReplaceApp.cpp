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

#include "ReReplace.h"

#include "ReReplaceApp.h"

namespace smartcube
{
	ReReplaceApp::ReReplaceApp()
	{
		// TODO Auto-generated constructor stub

	}

	ReReplaceApp::~ReReplaceApp()
	{
		// TODO Auto-generated destructor stub
	}

	void ReReplaceApp::defineOptions(Poco::Util::OptionSet& options)
	{
		ConsoleApp::defineOptions(options);

		options.addOption(Poco::Util::Option(
				"pattern", "p", "specify RE pattern.") .required(
				false).repeatable(false).argument("pattern", true) .binding(
				"smartcube.str.xreplace.pattern"));

		options.addOption(Poco::Util::Option(
				"format", "f", "specify RE format.") .required(
				false).repeatable(false).argument("format", true) .binding(
				"smartcube.str.xreplace.format"));
	}

	const std::string ReReplaceApp::getUsage() const
	{
		return "[OPTIONS] [-p pattern] [-f format] [--] <column> [<column> ... ]";
	}

	const std::string ReReplaceApp::getHeader() const
	{
		return "Replace columns with specified RE pattern, resulting in new columns.";
	}

	int ReReplaceApp::main2(const std::vector<std::string>& args)
	{
		std::vector<std::size_t> columns;
		std::string pattern = config().getString("smartcube.str.xreplace.pattern", "");
		std::string format = config().getString("smartcube.str.xreplace.format", "");

		std::vector<std::string>::const_iterator iter = args.begin();
		for (; iter != args.end(); ++iter)
		{
			columns.push_back(Poco::DynamicAny(*iter).convert<std::size_t>());
		}


		ReReplace split(columns, pattern, format);
		split.handle(*getInput(), *getOutput());

		return Poco::Util::Application::EXIT_OK;
	}
}

POCO_APP_MAIN(smartcube::ReReplaceApp);
