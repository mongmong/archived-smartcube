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

#include "Exp.h"

#include "ExpApp.h"

namespace smartcube
{
	ExpApp::ExpApp()
	{
		// TODO Auto-generated constructor stub

	}

	ExpApp::~ExpApp()
	{
		// TODO Auto-generated destructor stub
	}

	void ExpApp::defineOptions(Poco::Util::OptionSet& options)
	{
		ConsoleApp::defineOptions(options);

		options.addOption(Poco::Util::Option(
				"base", "b", "specify base.").required(
				false).repeatable(false) .argument("base", true).binding(
				"smartcube.math.exp.base"));
	}

	const std::string ExpApp::getUsage() const
	{
		return "[OPTIONS] [-b <base>] <column> [<column> ..]";
	}

	const std::string ExpApp::getHeader() const
	{
		return "Calculate exponential value of columns.";
	}

	int ExpApp::main2(const std::vector<std::string>& args)
	{
		std::vector<std::size_t> columns;
		double base = config().getDouble("smartcube.math.exp.base",  2.71828182845904523536028747135266250);

		std::vector<std::string>::const_iterator iter = args.begin();
		for (; iter != args.end(); ++iter)
		{
			columns.push_back(Poco::DynamicAny(*iter).convert<std::size_t>());
		}

		Exp exp(base, columns);
		exp.handle(*getInput(), *getOutput());

		return Poco::Util::Application::EXIT_OK;
	}
}

POCO_APP_MAIN(smartcube::ExpApp);
