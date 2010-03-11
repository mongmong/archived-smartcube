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

#ifndef ROUTINEWRAPPER_H_
#define ROUTINEWRAPPER_H_

#include <boost/python.hpp>

#include "Routine.h"

namespace smartcube
{
	namespace python = boost::python;

	/*
	 * Wrapper for Routine Python class.
	 */
	class RoutineWrapper: public Routine, public python::wrapper<Routine>
	{
		public:
			void handle(Input& input, Output& output);
	};
}

#endif /* ROUTINEWRAPPER_H_ */
