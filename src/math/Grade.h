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

#ifndef GRADE_H_
#define GRADE_H_

#include <cmath>

#include "RoutineImpl.h"

namespace smartcube
{
	class Grade: public Project1To1RoutineImpl<Grade>
	{
		public:
			Grade(const std::vector<std::size_t>& columns, std::size_t num = 1, double precision = 1.0) :
				Project1To1RoutineImpl<Grade>(columns),
				_num(num),
				_precision(precision)
			{
			}

			void operator()(const Cell& op, Cell& out)
			{
				double d = static_cast<double>(op);
				double base = std::pow(10.0, int(std::log10(d) - _num + 1)) * _precision;

				out = long(d / base) * base;
			}

		private:
			std::size_t _num;
			double _precision;
	};
}

#endif /* GRADE_H_ */
