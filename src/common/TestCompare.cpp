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

#include <iostream>
#include <vector>

#include <Poco/Stopwatch.h>
#include <Poco/Any.h>
#include <Poco/NumberFormatter.h>

#include <boost/variant.hpp>
#include <boost/any.hpp>

#include "Cell.h"
#include "Record.h"
#include "StringUtil.h"

using namespace smartcube;

class FastRecord : public std::vector<boost::variant<bool, int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t, double, std::string> >
{
};

class FastRecord2 : public std::vector<Poco::Any>
{
};

class FastRecord3 : public std::vector<boost::any>
{
};

/*
void test(const std::string& line, int max)
{
	Record rec;
	Poco::Stopwatch sw;
	int i;

	sw.start();
	for (i = 0; i < max; i++)
	{
		StringUtil::split<Record>(line, "\t", rec);
	}
	sw.stop();

	std::cout << "test:  " << sw.elapsed() << std::endl;
}
*/

void test1(const std::string& line, int max)
{
	FastRecord rec;
	Poco::Stopwatch sw;
	int i;

	sw.start();
	for (i = 0; i < max; i++)
	{
		StringUtil::split<FastRecord>(line, "\t", rec);
	}
	sw.stop();

	std::cout << "test1: " << sw.elapsed() << std::endl;
}

void test2(const std::string& line, int max)
{
	FastRecord2 rec;
	Poco::Stopwatch sw;
	int i;

	sw.start();
	for (i = 0; i < max; i++)
	{
		StringUtil::split<FastRecord2>(line, "\t", rec);
	}
	sw.stop();

	std::cout << "test2: " << sw.elapsed() << std::endl;
}

void test3(const std::string& line, int max)
{
	FastRecord3 rec;
	Poco::Stopwatch sw;
	int i;

	sw.start();
	for (i = 0; i < max; i++)
	{
		StringUtil::split<FastRecord3>(line, "\t", rec);
	}
	sw.stop();

	std::cout << "test3: " << sw.elapsed() << std::endl;
}

void tests(const std::string& line, int max)
{
	std::vector<std::string> rec;
	Poco::Stopwatch sw;
	int i;

	sw.start();
	for (i = 0; i < max; i++)
	{
		StringUtil::split<std::vector<std::string> >(line, "\t", rec);
	}
	sw.stop();

	std::cout << "tests: " << sw.elapsed() << std::endl;
}


void testnew(const std::string& line, int max)
{
	Record rec;
	Poco::Stopwatch sw;
	int i;

	sw.start();
	for (i = 0; i < max; i++)
	{
		StringUtil::split<std::vector<Cell> >(line, "\t", rec);
	}
	sw.stop();

	std::cout << "new : " << sw.elapsed() << std::endl;
}


int main()
{
	std::string line = "1342234342262337	www.baidu.com	search.yahoo.com	20	30	40	50	60	70	128	1024	65535";

	//test(line, 100000);
	//test1(line, 100000);
	//test2(line, 100000);
	//test3(line, 100000);
	//tests(line, 100000);
	//testnew(line, 100000);


	// typedef std::vector<boost::variant<bool, int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t, double, std::string> > testtype;
	typedef std::vector<boost::variant<std::string> > testtype;
	testtype a;
	a.resize(1024000);


	std::cout << sizeof(int64_t) << std::endl;

	//std::cin >> line;

	std::cout << Poco::NumberFormatter::format((double)0.7) << std::endl;
}
