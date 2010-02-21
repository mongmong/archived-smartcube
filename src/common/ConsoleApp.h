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

#ifndef CONSOLEAPP_H_
#define CONSOLEAPP_H_

#include <Poco/Util/Application.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/Option.h>

#include "Input.h"
#include "Output.h"

namespace smartcube
{
	class ConsoleApp: public Poco::Util::Application
	{
		public:
			ConsoleApp();
			virtual ~ConsoleApp();

		protected:
			void initialize(Application& self);
			void uninitialize();
			void reinitialize(Application& self);
			void defineOptions(Poco::Util::OptionSet& options);

			void handleHelp(const std::string& name, const std::string& value);
			void handleVerbose(
					const std::string& name, const std::string& value);
			void handleVersion(
					const std::string& name, const std::string& value);
			void
			handleDefine(const std::string& name, const std::string& value);
			void handlePrint(const std::string& name, const std::string& value);

			void displayHelp();
			void displayVersion();
			void defineProperty(const std::string& def);
			void printProperties(const std::string& base);

			InputPtr getInput();
			OutputPtr getOutput();

			int main(const std::vector<std::string>& args);

		public:
			virtual int main2(const std::vector<std::string>& args) = 0;

			virtual const std::string getUsage() const;
			virtual const std::string getHeader() const;
			virtual const std::string getFooter() const;

		private:
			bool _helpRequest;
			bool _versionRequest;
			bool _verbose;
			bool _print;

			InputPtr _input;
			OutputPtr _output;
	};
}

#endif /* CONSOLEAPP_H_ */
