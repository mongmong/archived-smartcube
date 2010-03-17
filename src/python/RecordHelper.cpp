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

#include <boost/foreach.hpp>

#include <Python.h>

#include "Error.h"
#include "RecordHelper.h"

namespace smartcube
{
	python::list RecordHelper::vectorToPythonList(const std::vector<Cell>& vector)
	{
		python::list list;

		std::vector<Cell>::const_iterator iter = vector.begin();
		for (; iter != vector.end(); iter++)
		//		BOOST_FOREACH(Poco::DynamicAny& any, vector)
		{
			const Cell& any = *iter;
			if (any.type() == typeid(bool))
			{
				list.append(static_cast<bool> (any));
			}
			else if (any.isInteger())
			{
				if (any.isSigned())
				{
					list.append(static_cast<int64_t> (any));
				}
				else
				{
					list.append(static_cast<uint64_t> (any));
				}
			}
			else if (any.isNumeric())
			{
				list.append(static_cast<double> (any));
			}
			else if (any.isString())
			{
				list.append(any.extract<std::string> ());
			}
			else if (any.isEmpty())
			{
				list.append(python::object());
			}
			else if (any.isArray())
			{
				list.append(vectorToPythonList(any.extract < std::vector<
						Poco::DynamicAny> > ()));
			}
			else
			{
				list.append(static_cast<const std::string&>(any));
			}
		}

		return list;
	}

	python::list RecordHelper::recordToPythonList(RecordPtr rec)
	{
		if (rec.isNull())
		{
			return python::list();
		}
		return vectorToPythonList(*rec);
	}

	Poco::SharedPtr<Poco::DynamicAny> RecordHelper::pythonObjectToAny(python::object obj)
	{
		if (PyBool_Check(obj.ptr()))
		{
			return new Poco::DynamicAny(python::extract<bool>(obj)());
		}
		else if (PyInt_Check(obj.ptr()))
		{
			return new Poco::DynamicAny(python::extract<long>(obj)());
		}
		else if (PyLong_Check(obj.ptr()))
		{
			return new Poco::DynamicAny(python::extract<long>(obj)());
		}
		else if (PyFloat_Check(obj.ptr()))
		{
			return new Poco::DynamicAny(python::extract<double>(obj)());
		}
		else if (PyString_Check(obj.ptr()))
		{
			return new Poco::DynamicAny(python::extract<std::string>(obj)());
		}
		else if (PyUnicode_Check(obj.ptr()))
		{
			return new Poco::DynamicAny(python::extract<std::string>(python::str(obj))());
		}
		else if (PyList_Check(obj.ptr()) || PyTuple_Check(obj.ptr()))
		{
			ssize_t max = python::len(obj);
			ssize_t i = 0;
			std::vector<Poco::DynamicAny> result;
			for (; i < max; ++i)
			{
				python::object item = obj[i];
				result.push_back(*pythonObjectToAny(item));
			}
			return new Poco::DynamicAny(result);
		}
		else
		{
			throw SmartCubeError("Unsupported Python object type.");
		}
		return NULL;
	}

	RecordPtr RecordHelper::pythonListToRecord(python::object obj)
	{
		ssize_t listSize = python::len(obj);

		ssize_t i = 0;

		RecordPtr ptr = new Record();
		ptr->reserve(listSize);

		for (; i < listSize; ++i)
		{
			ptr->insert(ptr->end(), *pythonObjectToAny(obj[i]));
		}

		return ptr;
	}

}
