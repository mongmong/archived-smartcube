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

#ifndef CELL_H_
#define CELL_H_

#include <iostream>

#include <boost/variant.hpp>
#include <boost/python.hpp>

#include <Poco/NumberParser.h>
#include <Poco/NumberFormatter.h>
#include <Poco/SharedPtr.h>
#include <Poco/String.h>

#include "Error.h"

#if defined(_MSC_VER)
#define I64_FMT "I64"
#elif defined(__APPLE__)
#define I64_FMT "q"
#else
#define I64_FMT "ll"
#endif

namespace smartcube
{
	namespace python = boost::python;

	typedef boost::variant<int64_t, uint64_t, double, bool, std::string>
			_MediumType;
	inline _MediumType convert(const python::object& obj)
	{
		if (PyBool_Check(obj.ptr()))
		{
			return python::extract<bool>(obj)();
		}
		else if (PyInt_Check(obj.ptr()))
		{
			return python::extract<int64_t>(obj)();
		}
		else if (PyLong_Check(obj.ptr()))
		{
			return python::extract<int64_t>(obj)();
		}
		else if (PyFloat_Check(obj.ptr()))
		{
			return python::extract<double>(obj)();
		}
		else if (PyString_Check(obj.ptr()))
		{
			return python::extract<std::string>(obj)();
		}
		else if (PyUnicode_Check(obj.ptr()))
		{
			return python::extract<std::string>(python::str(obj))();
		}
		else
		{
			return python::extract<std::string>(python::str(obj))();
		}
	}

	template<typename T>
	class CellVisitor: public boost::static_visitor<T>
	{
		public:
			virtual T operator()(int64_t) const = 0;
			virtual T operator()(uint64_t) const = 0;
			virtual T operator()(double) const = 0;
			virtual T operator()(bool) const = 0;
			virtual T operator()(const std::string&) const = 0;
			virtual T operator()(const python::object& obj) const = 0;
	};

	template<>
	class CellVisitor<int64_t> : public boost::static_visitor<int64_t>
	{
		public:
			int64_t operator()(int64_t v) const
			{
				return v;
			}
			int64_t operator()(uint64_t v) const
			{
				if (v
						> static_cast<uint64_t> (std::numeric_limits<int64_t>::max()))
				{
					SMARTCUBE_EXCEPTION("Unsigned 64bit value %"I64_FMT"u too large to convert to 64bit integer.", v);
				}
				return static_cast<int64_t> (v);
			}
			int64_t operator()(double v) const
			{
				int64_t fmax = std::numeric_limits<int64_t>::max();
				int64_t fmin = std::numeric_limits<int64_t>::min();

				if (v > fmax)
				{
					SMARTCUBE_EXCEPTION("Double value %f too large to convert to 64bit integer.", v);
				}
				if (v < fmin)
				{
					SMARTCUBE_EXCEPTION("Double value %f too small to convert to 64bit integer.", v);
				}
				return static_cast<int64_t> (v);
			}
			int64_t operator()(bool v) const
			{
				return v;
			}
			int64_t operator()(const std::string& v) const
			{
				return Poco::NumberParser::parse64(v);
			}
			int64_t operator()(const python::object& v) const
			{
				const static CellVisitor<int64_t> visitor;
				_MediumType c = convert(v);
				return boost::apply_visitor(visitor, c);
				//return python::extract<int64_t> (python::long_(v))();
			}
	};

	template<>
	class CellVisitor<uint64_t> : public boost::static_visitor<uint64_t>
	{
		public:
			uint64_t operator()(int64_t v) const
			{
				if (v < 0)
				{
					SMARTCUBE_EXCEPTION("64bit integer %"I64_FMT"d is too small to convert to unsigned 64bit integer.", v);
				}
				return static_cast<int64_t> (v);
			}
			uint64_t operator()(uint64_t v) const
			{
				return v;
			}
			uint64_t operator()(double v) const
			{
				if (v > std::numeric_limits<uint64_t>::max())
				{
					SMARTCUBE_EXCEPTION("Double value %f too large to convert to unsigned 64bit integer.", v);
				}
				if (v < std::numeric_limits<uint64_t>::min())
				{
					SMARTCUBE_EXCEPTION("Double value %f too small to convert to unsigned 64bit integer.", v);
				}
				return static_cast<uint64_t> (v);
			}
			uint64_t operator()(bool v) const
			{
				return v;
			}
			uint64_t operator()(const std::string& v) const
			{
				return Poco::NumberParser::parseUnsigned64(v);
			}
			uint64_t operator()(const python::object& v) const
			{
				const static CellVisitor<uint64_t> visitor;
				_MediumType c = convert(v);
				return boost::apply_visitor(visitor, c);
				//return (*this)(python::extract<int64_t> (python::long_(v))());
			}
	};

	template<>
	class CellVisitor<double> : public boost::static_visitor<double>
	{
		public:
			double operator()(int64_t v) const
			{
				return static_cast<double> (v);
			}
			double operator()(uint64_t v) const
			{
				return static_cast<double> (v);
			}
			double operator()(double v) const
			{
				return v;
			}
			double operator()(bool v) const
			{
				return static_cast<double> (v);
			}
			double operator()(const std::string& v) const
			{
				return Poco::NumberParser::parseFloat(v);
			}
			double operator()(const python::object& v) const
			{
				const static CellVisitor<double> visitor;
				_MediumType c = convert(v);
				return boost::apply_visitor(visitor, c);

				//return python::extract<double> (v)();
			}
	};

	template<>
	class CellVisitor<bool> : public boost::static_visitor<bool>
	{
		public:
			bool operator()(int64_t v) const
			{
				return v != 0;
			}
			bool operator()(uint64_t v) const
			{
				return v != 0;
			}
			bool operator()(double v) const
			{
				return v;
			}
			bool operator()(bool v) const
			{
				return !(v <= std::numeric_limits<double>::min() && v >= -1
						* std::numeric_limits<double>::min());
			}
			bool operator()(const std::string& v) const
			{
				static const std::string VAL_FALSE("False");
				static const std::string VAL_INTFALSE("0");

				if (v == VAL_INTFALSE || (Poco::icompare(v, VAL_FALSE) == 0))
				{
					return false;
				}

				return true;
			}
			bool operator()(const python::object& v) const
			{
				const static CellVisitor<bool> visitor;
				_MediumType c = convert(v);
				return boost::apply_visitor(visitor, c);

				//return PyObject_IsTrue(v.ptr());
			}
	};

	template<>
	class CellVisitor<std::string> : public boost::static_visitor<std::string>
	{
		public:
			const std::string operator()(int64_t v) const
			{
				return Poco::NumberFormatter::format(v);
			}
			const std::string operator()(uint64_t v) const
			{
				return Poco::NumberFormatter::format(v);
			}
			const std::string operator()(double v) const
			{
				return Poco::NumberFormatter::format(v);
			}
			const std::string operator()(bool v) const
			{
				return v ? "True" : "False";
			}
			const std::string& operator()(const std::string& v) const
			{
				return v;
			}
			const std::string operator()(const python::object& v) const
			{
				const static CellVisitor<std::string> visitor;
				_MediumType c = convert(v);
				return boost::apply_visitor(visitor, c);

				//return python::extract<std::string> (python::str(v))();
			}
	};

	template<>
	class CellVisitor<python::object> : public boost::static_visitor<
			python::object>
	{
		public:
			const python::object operator()(int64_t v) const
			{
				return python::object(v);
			}
			const python::object operator()(uint64_t v) const
			{
				return python::object(v);
			}
			const python::object operator()(double v) const
			{
				return python::object(v);
			}
			const python::object operator()(bool v) const
			{
				return python::object(v);
			}
			const python::object operator()(const std::string& v) const
			{
				return python::object(v);
			}
			const python::object& operator()(const python::object& v) const
			{
				return v;
			}
	};

	inline int64_t unifyValue(int8_t v)
	{
		return static_cast<int64_t> (v);
	}

	inline int64_t unifyValue(int16_t v)
	{
		return static_cast<int64_t> (v);
	}

	inline int64_t unifyValue(int32_t v)
	{
		return static_cast<int64_t> (v);
	}

	inline int64_t unifyValue(int64_t v)
	{
		return static_cast<int64_t> (v);
	}

	inline uint64_t unifyValue(uint8_t v)
	{
		return static_cast<uint64_t> (v);
	}

	inline uint64_t unifyValue(uint16_t v)
	{
		return static_cast<uint64_t> (v);
	}

	inline uint64_t unifyValue(uint32_t v)
	{
		return static_cast<uint64_t> (v);
	}

	inline uint64_t unifyValue(uint64_t v)
	{
		return static_cast<uint64_t> (v);
	}

	inline double unifyValue(float v)
	{
		return v;
	}

	inline double unifyValue(double v)
	{
		return v;
	}

	inline bool unifyValue(bool v)
	{
		return v;
	}

	inline const std::string& unifyValue(const std::string& v)
	{
		return v;
	}

	inline const python::object& unifyValue(const python::object& v)
	{
		return v;
	}

	class Cell
	{
		public:
			typedef boost::variant<int64_t, uint64_t, double, bool,
					std::string, python::object> _baseType;

			Cell()
			{
			}

			template<typename T>
			Cell(const T& rhs) :
				_base(rhs)
			{
			}

			_baseType base() const
			{
				return _base;
			}

			template<typename T>
			Cell& operator =(const T& rhs)
			{
				_base = unifyValue(rhs);
				return *this;
			}

			Cell& operator =(const Cell& rhs)
			{
				_base = rhs._base;
				return *this;
			}

			bool operator ==(const Cell& rhs) const
			{
				return _base == rhs._base;
			}

			bool operator !=(const Cell& rhs) const
			{
				return !(*this == rhs);
			}

			template<typename T>
			operator T() const
			{
				const static CellVisitor<T> visitor;
				return boost::apply_visitor(visitor, _base);
			}

			const std::type_info& type() const
			{
				return _base.type();
			}

			bool isInteger() const
			{
				const static bool types[] =
				{ true, true, false, false, false, false };
				return types[_base.which()];
			}

			bool isSignedInteger() const
			{
				const static bool types[] =
				{ true, false, false, false, false, false };
				return types[_base.which()];
			}

			bool isUnsignedInteger() const
			{
				const static bool types[] =
				{ false, true, false, false, false, false };
				return types[_base.which()];
			}

			bool isFloat() const
			{
				const static bool types[] =
				{ false, false, true, false, false, false };
				return types[_base.which()];
			}

			bool isNumber() const
			{
				const static bool types[] =
				{ true, true, true, false, false, false };
				return types[_base.which()];
			}

			bool isBool() const
			{
				const static bool types[] =
				{ false, false, false, true, false, false };
				return types[_base.which()];
			}

			bool isString() const
			{
				static bool types[] =
				{ false, false, false, false, true, false };
				return types[_base.which()];
			}

			bool isPyObject() const
			{
				const static bool types[] =
				{ false, false, false, false, false, true };
				return types[_base.which()];
			}

		private:
			_baseType _base;
	};

	typedef Poco::SharedPtr<Cell> CellPtr;
}

#endif /* CELL_H_ */
