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

#ifndef BASE64ENCAPP_H_
#define BASE64ENCAPP_H_

#include "ConsoleApp.h"

namespace smartcube
{
	class Base64EncApp : public ConsoleApp
	{
		public:
			Base64EncApp();
			virtual ~Base64EncApp();

		protected:
			void defineOptions(Poco::Util::OptionSet& options);

			virtual const std::string getUsage() const;
			virtual const std::string getHeader() const;

		protected:
			int main2(const std::vector<std::string>& args);
	};
}

#endif /* BASE64ENCAPP_H_ */
