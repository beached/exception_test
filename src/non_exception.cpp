// The MIT License (MIT)
//
// Copyright (c) 2017 Darrell Wright
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files( the "Software" ), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <cstdint>
#include "non_exception.h"

intmax_t non_ex_func_0( intmax_t x, intmax_t, intmax_t &error_no ) {
	error_no = -1;
	return x;
}

intmax_t non_ex_func_1( intmax_t x, intmax_t y, intmax_t &error_no ) {
	error_no = 0;
	return x + y;
}

intmax_t non_ex_func_2( intmax_t x, intmax_t, intmax_t &error_no ) {
	error_no = 0;
	return x * x;
}

intmax_t non_ex_func_3( intmax_t x, intmax_t y, intmax_t &error_no ) {
	error_no = 0;
	return ( x * x ) % 5 + y;
}

intmax_t non_ex_func_4( intmax_t x, intmax_t y, intmax_t &error_no ) {
	error_no = 0;
	return ( x + x ) / 3 + y;
}
