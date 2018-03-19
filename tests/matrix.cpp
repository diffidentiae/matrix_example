#include <catch.hpp>
#include <sstream>

#include "matrix.hpp"

TEST_CASE("creating matrix")
{
    matrix_t matrix;
    REQUIRE( matrix.rows() == 0 );
    REQUIRE( matrix.collumns() == 0 );
}

TEST_CASE("reading matrix")
{
    std::string input{
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t matrix;
    std::istringstream istream{ input };
    
    REQUIRE( matrix.read( istream ) );
    REQUIRE( matrix.rows() == 3 );
    REQUIRE( matrix.collumns() == 3 );
    
    std::ostringstream ostream;
    matrix.write( ostream );
    
    REQUIRE( input == ostream.str() );
}

TEST_CASE("add matrix")
{
    std::string input_1
    {
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    std::string input_2
    {
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1" };
      matrix_t matrix_1, matrix_2;
    std::istringstream istream_1{ input_1 };
    std::istringstream istream_2{ input_2 };
    REQUIRE(matrix1.read(istream_1));
    REQUIRE(matrix2.read(istream_2));
    
    REQUIRE(matrix_1.rows() == 3);
    REQUIRE(matrix_1.collumns() == 3);
        
    REQUIRE(matrix_2.rows() == 3);
    REQUIRE(matrix_2.collumns() == 3);
	
    REQUIRE( matrix_1.collumns() == matrix_2.collumns() && matrix_1.rows() == matrix_2.rows() );
	  
    std::ostringstream stream;
    (matrix_1 + matrix_2).write(stream);
}
