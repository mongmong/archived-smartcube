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

#ifndef RECORD_H_
#define RECORD_H_

#include <memory>
#include <vector>

#include <Poco/SharedPtr.h>
#include <Poco/DynamicAny.h>

namespace smartcube
{
	class Record
	{
		public:
			typedef std::vector<Poco::DynamicAny>::iterator Iterator;
			typedef std::vector<Poco::DynamicAny>::reverse_iterator
					ReverseIterator;

			Record();
			virtual ~Record();

		public:

			Iterator begin();
			Iterator end();

			ReverseIterator rbegin();
			ReverseIterator rend();

			std::size_t count() const;
			bool eof() const;

			void clear();

			void resize(std::size_t newSize);

			template<typename InputIterator>
			void insert(
					Iterator position, InputIterator first, InputIterator last)
			{
				_fields.insert(position, first, last);
			}
			void insert(Iterator position, std::size_t n, const Poco::DynamicAny& x);
			Iterator insert(Iterator position, const Poco::DynamicAny& x);

		public:
			Poco::DynamicAny& operator [](std::size_t index);

		private:
			std::vector<Poco::DynamicAny> _fields;

			Record(const Record&);
			Record& operator= (const Record&);
	};

	typedef Poco::SharedPtr<Record> RecordPtr;

}
#endif /* RECORD_H_ */
