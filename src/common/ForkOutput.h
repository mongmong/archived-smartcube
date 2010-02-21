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

#ifndef FORKOUTPUT_H_
#define FORKOUTPUT_H_

#include <vector>

#include "Output.h"

namespace smartcube
{
	class ForkOutput : public Output
	{
		public:
			ForkOutput(std::vector<OutputPtr>& outputs);
			virtual ~ForkOutput();

		public:
			std::vector<OutputPtr>& getOutputs();
			virtual void push(RecordPtr record);

		private:
			std::vector<OutputPtr>	_outputs;
	};
}

#endif /* FORKOUTPUT_H_ */
