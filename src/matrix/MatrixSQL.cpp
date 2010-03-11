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

#include <Poco/Data/SQLite/Connector.h>
#include <Poco/Data/Session.h>
#include <Poco/Data/RecordSet.h>

#include "MatrixSQL.h"

namespace smartcube
{
	MatrixSQL::MatrixSQL(const std::string& sql) :
			_sql(sql)
	{
		// TODO Auto-generated constructor stub

	}

	MatrixSQL::~MatrixSQL()
	{
		// TODO Auto-generated destructor stub
	}

	void MatrixSQL::handle(Input& input, Output& output)
	{
		using namespace Poco::Data;

		RecordPtr head = input.pop();

		Poco::Data::SQLite::Connector::registerConnector();

		std::string db("/tmp/");
		db += this->getID().toString() + ".sqlite";
		Session session("SQLite", db);

		/*
		 * constructing table definition.
		 */
		std::string createSQL = "create table T (";


		session << "create table T(
	}
}
