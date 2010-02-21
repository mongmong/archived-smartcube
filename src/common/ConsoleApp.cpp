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

#include <fcntl.h>
#include <sys/ioctl.h>

#include <iostream>
#include <string>

#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/AbstractConfiguration.h>

#include "Error.h"
#include "FileInput.h"
#include "FileOutput.h"

#include "ConsoleApp.h"

namespace smartcube
{
	ConsoleApp::ConsoleApp() :
		_helpRequest(false), _versionRequest(false), _input(), _output()
	{
		// TODO Auto-generated constructor stub

	}

	ConsoleApp::~ConsoleApp()
	{
		// TODO Auto-generated destructor stub
	}

	void ConsoleApp::initialize(Application& self)
	{
		loadConfiguration();
		Application::initialize(self);
		// logger().information("Starting up.");
	}

	void ConsoleApp::uninitialize()
	{
		// logger().information("Shutting down.");
		Application::uninitialize();
	}

	void ConsoleApp::reinitialize(Application& self)
	{
		Application::reinitialize(self);
	}

	void ConsoleApp::defineOptions(Poco::Util::OptionSet& options)
	{
		Application::defineOptions(options);

		/*
		 * General options
		 */
		options.addOption(
				Poco::Util::Option("help", "h", "display help information.").required(
						false).repeatable(false) .callback(
						Poco::Util::OptionCallback<ConsoleApp>(
								this, &ConsoleApp::handleHelp)));
		options.addOption(
				Poco::Util::Option("verbose", "v", "turn on verbose mode.").required(
						false).repeatable(false) .callback(
						Poco::Util::OptionCallback<ConsoleApp>(
								this, &ConsoleApp::handleVerbose)));
		options.addOption(
				Poco::Util::Option("Version", "V", "show version information.").required(
						false).repeatable(false).callback(
						Poco::Util::OptionCallback<ConsoleApp>(
								this, &ConsoleApp::handleVersion)));

		options.addOption(
				Poco::Util::Option("print", "", "print properties.").required(false).repeatable(false).
				callback(Poco::Util::OptionCallback<ConsoleApp>(this, &ConsoleApp::handlePrint)));

		options.addOption(Poco::Util::Option(
				"define", "D", "define a configuration property").required(
				false) .repeatable(true) .argument("key=value") .callback(
				Poco::Util::OptionCallback<ConsoleApp>(
						this, &ConsoleApp::handleDefine)));

		options.addOption(Poco::Util::Option(
				"input", "", "specify input source. [default: -]").required(
				false).repeatable(false) .argument("file").binding(
				"smartcube.common.input"));

		options.addOption(Poco::Util::Option(
				"output", "", "specify output source. [default: -]").required(
				false).repeatable(false).argument("file").binding(
				"smartcube.common.output"));

		options.addOption(
				Poco::Util::Option(
						"ifsep", "",
						"specify input field separators. [default: \\t]") .required(
						false).repeatable(false).argument("sep") .binding(
						"smartcube.common.input-field-separators"));

		options.addOption(
				Poco::Util::Option(
						"ofsep", "",
						"specify output field separator. [default: \\t]") .required(
						false).repeatable(false).argument("sep") .binding(
						"smartcube.common.output-field-separator"));

		options.addOption(
				Poco::Util::Option(
						"igsep", "",
						"specify input group separators. [default: ',']") .required(
						false).repeatable(false).argument("sep") .binding(
						"smartcube.common.input-field-separators"));

		options.addOption(
				Poco::Util::Option(
						"ogsep", "",
						"specify output group separator. [default: ',']") .required(
						false).repeatable(false).argument("sep") .binding(
						"smartcube.common.output-field-separator"));

		options.addOption(
				Poco::Util::Option("dont-escape-output", "", "quote output fields.") .required(
						false).repeatable(false).binding("smartcube.common.dont-escape-output"));

		options.addOption(
				Poco::Util::Option("dont-unescape-input", "", "unquote input fields.") .required(
						false).repeatable(false).binding("smartcube.common.dont-unescape-input"));
	}

	void ConsoleApp::handleHelp(
			const std::string& name, const std::string& value)
	{
		_helpRequest = true;
		displayHelp();
		stopOptionsProcessing();
	}

	void ConsoleApp::handleVerbose(
			const std::string& name, const std::string& value)
	{
		// TODO:
		_verbose = true;
	}

	void ConsoleApp::handlePrint(
			const std::string& name, const std::string& value)
	{
		_print = true;
	}

	void ConsoleApp::handleVersion(
			const std::string& name, const std::string& value)
	{
		_versionRequest = true;
		displayVersion();
		stopOptionsProcessing();
	}

	void ConsoleApp::handleDefine(
			const std::string& name, const std::string& value)
	{
		defineProperty(value);
	}

	void ConsoleApp::displayHelp()
	{
		struct winsize w;
		ioctl(0, TIOCGWINSZ, &w);

		Poco::Util::HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage(getUsage());
		helpFormatter.setHeader(getHeader());
		helpFormatter.setFooter(getFooter());
		helpFormatter.setAutoIndent();
		helpFormatter.setWidth(w.ws_col);
		helpFormatter.format(std::cout);
	}

	void ConsoleApp::displayVersion()
	{
		// TODO:
	}

	void ConsoleApp::defineProperty(const std::string& def)
	{
		std::string name;
		std::string value;
		std::string::size_type pos = def.find('=');
		if (pos != std::string::npos)
		{
			name.assign(def, 0, pos);
			value.assign(def, pos + 1, def.length() - pos);
		}
		else
		{
			name = def;
		}
		config().setString(name, value);
	}

	void ConsoleApp::printProperties(const std::string& base)
	{
		Poco::Util::AbstractConfiguration::Keys keys;
		config().keys(base, keys);
		if (keys.empty())
		{
			if (config().hasProperty(base))
			{
				std::string msg;
				msg.append(base);
				msg.append(" = ");
				msg.append(config().getString(base));
				logger().information(msg);
			}
		}
		else
		{
			for (Poco::Util::AbstractConfiguration::Keys::const_iterator it =
					keys.begin(); it != keys.end(); ++it)
			{
				std::string fullKey = base;
				if (!fullKey.empty())
					fullKey += '.';
				fullKey.append(*it);
				printProperties(fullKey);
			}
		}
	}

	const std::string ConsoleApp::getUsage() const
	{
		return "[OPTIONS] [ARGUMENTS]";
	}

	const std::string ConsoleApp::getHeader() const
	{
		return "SmartCube Data Manipulate Toolkit.";
	}

	const std::string ConsoleApp::getFooter() const
	{
		return "SmartCube Data Manipulate Toolkit.\nAuthor: Chris Chou <m2chrischou@gmail.com>\n";
	}

	InputPtr ConsoleApp::getInput()
	{
		return _input;
	}

	OutputPtr ConsoleApp::getOutput()
	{
		return _output;
	}

	int ConsoleApp::main(const std::vector<std::string>& args)
	{
		try
		{
			if (_helpRequest || _versionRequest)
			{
				return ConsoleApp::EXIT_OK;
			}

			if (_print)
			{
				printProperties("");
				return ConsoleApp::EXIT_OK;
			}

			std::string inputfile = config().getString("smartcube.common.input", "-");
			std::string outputfile =
					config().getString("smartcube.common.output", "-");
			std::string inputFieldSpt = config().getString(
					"smartcube.common.input-field-separators", "\t");
			std::string outputFieldSpt = config().getString(
					"smartcube.common.output-field-separator", "\t");
			std::string inputGroupSpt = config().getString(
					"smartcube.common.input-group-separators", "\t");
			std::string outputGroupSpt = config().getString(
					"smartcube.common.output-group-separator", "\t");
			bool escape = true;
			bool unescape = true;
			if (config().hasOption("smartcube.common.dont-escape-output"))
			{
				escape = false;
			}
			if (config().hasOption("smartcube.common.dont-unescape-input"))
			{
				unescape = false;
			}

			if (inputfile != "-")
			{
				// _input = new FileInput(inputfile, inputFieldSpt, unescape);
				_input = new FileInput(inputfile, inputFieldSpt, false);
			}
			else
			{
				// _input = new FileInput(STDIN_FILENO, inputFieldSpt, unescape);
				_input = new FileInput(STDIN_FILENO, inputFieldSpt, false);
			}

			if (outputfile != "-")
			{
				// _output = new FileOutput(outputfile, outputFieldSpt[0], outputGroupSpt[0], escape);
				_output = new FileOutput(outputfile, outputFieldSpt[0], outputGroupSpt[0], false);
			}
			else
			{
				/*
				_output = new FileOutput(
						STDOUT_FILENO, outputFieldSpt[0], outputGroupSpt[0], escape);
				*/
				_output = new FileOutput(
						STDOUT_FILENO, outputFieldSpt[0], outputGroupSpt[0], false);
			}

			return main2(args);

		} catch (smartcube::SmartCubeError& exc)
		{
			this->logger().log(exc);
		} catch (Poco::Exception& exc)
		{
			std::cout << "Poco::Exception" << std::endl;
			this->logger().log(exc);
		} catch (std::exception& exc)
		{
			std::cout << "std::exception" << std::endl;
			this->logger().error(exc.what());
		}

		return ConsoleApp::EXIT_SOFTWARE;
	}
}
