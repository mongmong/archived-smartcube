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

#include "Grade.h"
#include "FileInput.h"
#include "FileOutput.h"

#include "GradeApp.h"

namespace smartcube
{
	GradeApp::GradeApp()
	{
		// TODO Auto-generated constructor stub

	}

	GradeApp::~GradeApp()
	{
		// TODO Auto-generated destructor stub
	}

	void GradeApp::defineOptions(Poco::Util::OptionSet& options)
	{
		ConsoleApp::defineOptions(options);

		options.addOption(Poco::Util::Option(
				"decimal", "d", "specify decimal number.").required(
				false).repeatable(false) .argument("decimal", true).binding(
				"smartcube.math.grade.decimal"));

		options.addOption(Poco::Util::Option(
				"precision", "p", "specify precision.").required(
				false).repeatable(false) .argument("precision", true).binding(
				"smartcube.math.grade.precision"));
	}

	const std::string GradeApp::getUsage() const
	{
		return "[OPTIONS] -d <decimal> <column> [<column> ..]";
	}

	const std::string GradeApp::getHeader() const
	{
		return "Grading ...";
	}

	int GradeApp::main2(const std::vector<std::string>& args)
	{
		std::vector<std::size_t> columns;
		std::size_t decimal = config().getInt("smartcube.math.grade.decimal", 1);
		double precision = config().getDouble("smartcube.math.grade.precision", 1.0);

		std::vector<std::string>::const_iterator iter = args.begin();
		for (; iter != args.end(); ++iter)
		{
			columns.push_back(Poco::DynamicAny(*iter).convert<std::size_t>());
		}

		Grade g(columns, decimal, precision);
		g.handle(*getInput(), *getOutput());

		return Poco::Util::Application::EXIT_OK;
	}
}

POCO_APP_MAIN(smartcube::GradeApp);
