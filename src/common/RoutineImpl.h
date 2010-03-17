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

#ifndef ROUTINEIMPL_H_
#define ROUTINEIMPL_H_

#include "Routine.h"

namespace smartcube
{
	template<typename Type>
	class Project1To1RoutineImpl: public Routine
	{
		public:
			Project1To1RoutineImpl(const std::vector<std::size_t>& columns) :
				_columns(columns)
			{
			}
		public:
			void handle(Input& input, Output& output)
			{
				RecordPtr rec = input.pop();

				std::size_t size = _columns.size();
				for (; !rec->eof(); output.push(rec), rec = input.pop())
				{
					if (size > 0)
					{
						std::size_t s = rec->size();
						rec->resize(s + size);

						std::vector<std::size_t>::iterator iter =
								_columns.begin();
						for (; iter != _columns.end(); ++iter)
						{
							std::size_t index = s + iter - _columns.begin();
							Cell& op = (*rec)[*iter];
							Cell& out = (*rec)[index];

							dynamic_cast<Type&> (*this)(op, out);
						}
					}
				}
			}

		private:
			std::vector<std::size_t> _columns;
	};

	template<class Type>
	class Project2To1RoutineImpl: public Routine
	{
		public:
			Project2To1RoutineImpl(const std::vector<std::size_t>& columns) :
				_columns(columns)
			{
			}
		public:
			void handle(Input& input, Output& output)
			{
				RecordPtr rec = input.pop();

				std::size_t size = _columns.size() / 2;
				for (; !rec->eof(); output.push(rec), rec = input.pop())
				{
					if (size > 0)
					{
						std::size_t s = rec->size();
						rec->resize(s + size);

						std::size_t i = 0;
						for (; i < size; ++i)
						{
							std::size_t x = _columns[2 * i + 0];
							std::size_t y = _columns[2 * i + 1];
							std::size_t index = s + i;

							const Cell& op1 = (*rec)[x];
							const Cell& op2 = (*rec)[y];
							Cell& out = (*rec)[index];

							dynamic_cast<Type&> (*this)(op1, op2, out);
						}
					}
				}
			}

		private:
			std::vector<std::size_t> _columns;
	};

	template<class Type>
	class Project3To1RoutineImpl: public Routine
	{
		public:
			Project3To1RoutineImpl(const std::vector<std::size_t>& columns) :
				_columns(columns)
			{
			}
		public:
			void handle(Input& input, Output& output)
			{
				RecordPtr rec = input.pop();

				std::size_t size = _columns.size() / 3;
				for (; !rec->eof(); output.push(rec), rec = input.pop())
				{
					if (size > 0)
					{
						std::size_t s = rec->size();
						rec->resize(s + size);

						std::size_t i = 0;
						for (; i < size; ++i)
						{
							std::size_t x = _columns[3 * i + 0];
							std::size_t y = _columns[3 * i + 1];
							std::size_t z = _columns[3 * i + 3];
							std::size_t index = s + i;

							const Poco::DynamicAny& op1 = (*rec)[x];
							const Poco::DynamicAny& op2 = (*rec)[y];
							const Poco::DynamicAny& op3 = (*rec)[y];
							Poco::DynamicAny& out = (*rec)[index];

							dynamic_cast<Type&> (*this)(op1, op2, op3, out);
						}
					}
				}
			}

		private:
			std::vector<std::size_t> _columns;
	};

	template<typename Type, typename OpType>
	class SimpleRoutineWrapper: public Type, public OpType
	{
		public:
			SimpleRoutineWrapper(const std::vector<std::size_t>& columns) :
				Type(columns)
			{
			}
	};
}

#endif /* ROUTINEIMPL_H_ */
