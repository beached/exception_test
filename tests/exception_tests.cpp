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
#include <cstdlib>
#include <iostream>

#include <daw/daw_benchmark.h>
#include <daw/daw_random.h>

#include "exception.h"
#include "non_exception.h"

#define TEST_SIZE 10'000'000

intmax_t ex_test( std::vector<intmax_t> const &rnd_data ) noexcept {
	intmax_t error_count = 0;
	intmax_t result = 0;
	for( size_t n = 0; n < TEST_SIZE; ++n ) {
		try {
			switch( daw::randint<char>( 1, 4 ) ) {
			case 0:
				result = daw::ex_func_0( result, rnd_data[n] );
				break;
			case 1:
				result = daw::ex_func_1( result, rnd_data[n] );
				break;
			case 2:
				result = daw::ex_func_2( result, rnd_data[n] );
				break;
			case 3:
				result = daw::ex_func_3( result, rnd_data[n] );
				break;
			case 4:
				result = daw::ex_func_4( result, rnd_data[n] );
				break;
			}
		} catch( daw::ex_tag const & ) {
			++error_count;
			if( error_count > 1'000'000 ) {
				break;
			}
		}
	}
	return result;
}

intmax_t non_ex_test( std::vector<intmax_t> const &rnd_data ) noexcept {
	intmax_t result = 0;
	intmax_t error_count = 0;
	for( size_t n = 0; n < TEST_SIZE; ++n ) {
		intmax_t error_number = 0;
		switch( daw::randint<char>( 1, 4 ) ) {
		case 0:
			result = non_ex_func_0( result, rnd_data[n], error_number );
			break;
		case 1:
			result = non_ex_func_1( result, rnd_data[n], error_number );
			break;
		case 2:
			result = non_ex_func_2( result, rnd_data[n], error_number );
			break;
		case 3:
			result = non_ex_func_3( result, rnd_data[n], error_number );
			break;
		case 4:
			result = non_ex_func_4( result, rnd_data[n], error_number );
			break;
		}
		if( error_number != 0 ) {
			++error_count;
			if( error_count > 1'000'000 ) {
				break;
			}
		}
	}
	return result;
}

int main( int, char ** ) {
	using namespace daw;
	auto const rnd_data = daw::make_random_data<intmax_t>( TEST_SIZE * 2, 1, 100 );

	double t1 = daw::benchmark( [&rnd_data]( ) {
		auto result = non_ex_test( rnd_data );
		daw::do_not_optimize( result );
	} );

	double t2 = daw::benchmark( [&rnd_data]( ) {
		auto result = ex_test( rnd_data );
		daw::do_not_optimize( result );
	} );

	std::cout << "Error Code time: " << utility::format_seconds( t1, 2 ) << '\n';
	std::cout << "Exception time: " << utility::format_seconds( t2, 2 ) << '\n';

	return EXIT_SUCCESS;
}

