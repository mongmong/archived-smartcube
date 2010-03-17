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

#ifndef RECORDWRAPPER_H_
#define RECORDWRAPPER_H_

#include <boost/python.hpp>

#include <Poco/SharedPtr.h>

#include "Record.h"

namespace smartcube
{
	namespace python = boost::python;

	class RecordHelper
	{
		public:
			static python::list vectorToPythonList(const std::vector<Cell>& vector);
			static python::list recordToPythonList(RecordPtr rec);

			static Poco::SharedPtr<DynamicAny> pythonObjectToAny(python::object obj);
			static RecordPtr pythonListToRecord(python::object list);
	};
}

#endif /* RECORDWRAPPER_H_ */
