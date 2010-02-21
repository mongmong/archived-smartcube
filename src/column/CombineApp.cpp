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

#include "Combine.h"
#include "FileInput.h"
#include "FileOutput.h"

#include "CombineApp.h"

namespace smartcube
{
	CombineApp::CombineApp()
	{
		// TODO Auto-generated constructor stub

	}

	CombineApp::~CombineApp()
	{
		// TODO Auto-generated destructor stub
	}

	void CombineApp::defineOptions(Poco::Util::OptionSet& options)
	{
		ConsoleApp::defineOptions(options);

		options.addOption(Poco::Util::Option(
				"gsep", "t", "specify separator. [default: ',']") .required(
				false).repeatable(false).argument("separator", true) .binding(
				"smartcube.col.combine.separator"));
	}

	const std::string CombineApp::getUsage() const
	{
		return "[OPTIONS] [-t separator] [--] <column> [<column> ... ]";
	}

	const std::string CombineApp::getHeader() const
	{
		return "Combine columns with specified separators, resulting in new columns.";
	}

	int CombineApp::main2(const std::vector<std::string>& args)
	{
		std::vector<std::size_t> columns;
		std::string separator = config().getString("smartcube.col.combine.separator", ",");

		std::vector<std::string>::const_iterator iter = args.begin();
		for (; iter != args.end(); ++iter)
		{
			columns.push_back(Poco::DynamicAny(*iter).convert<std::size_t>());
		}

		Combine combine(columns, separator[0]);
		combine.handle(*getInput(), *getOutput());

		return Poco::Util::Application::EXIT_OK;
	}
}

POCO_APP_MAIN(smartcube::CombineApp);
