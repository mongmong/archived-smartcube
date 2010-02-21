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

#ifndef ERROR_H_
#define ERROR_H_

#include <Poco/Exception.h>
#include <Poco/Format.h>
#include <Poco/Logger.h>
#include <Poco/String.h>

#ifndef SMARTCUBE_API
#define SMARTCUBE_API
#endif

namespace smartcube
{
	using namespace Poco;

	POCO_DECLARE_EXCEPTION(SMARTCUBE_API, SmartCubeError, Poco::Exception)

#define SMARTCUBE_EXCEPTION(fmt, args...) \
		do { \
			std::string errmsg; \
			std::string fmtstr = format("[SmartCube] %s:%d:[%s] %s", std::string(__FILE__), __LINE__, std::string(__FUNCTION__), std::string(fmt)); \
			errmsg = Poco::format(fmtstr, ##args); \
			throw smartcube::SmartCubeError(errmsg); \
		} while(0)

#define SMARTCUBE_ASSERT(expr) \
		do { \
			if (!(expr)) \
			{ \
				std::string errmsg = format("[SmartCube] %s:%d:[%s] Assertion failure - %s", std::string(__FILE__), __LINE__, std::string(__FUNCTION__), std::string(#expr)); \
				throw smartcube::SmartCubeError(errmsg); \
			} \
		} while(0)
}

#endif /* ERROR_H_ */
