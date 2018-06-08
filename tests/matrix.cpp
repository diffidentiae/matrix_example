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
    std::string input{
        "3, 3\n"
        "3 3 3\n"
        "3 3 3\n"
        "3 3 3" };
      matrix_t matrix_1, matrix_2;
    std::istringstream istream_1{ input_1 };
    std::istringstream istream_2{ input_2 };
    REQUIRE(matrix_1.read(istream_1));
    REQUIRE(matrix_2.read(istream_2));
    
    REQUIRE(matrix_1.rows() == 3);
    REQUIRE(matrix_1.collumns() == 3);
        
    REQUIRE(matrix_2.rows() == 3);
    REQUIRE(matrix_2.collumns() == 3);
	  
    std::ostringstream stream;
    (matrix_1 + matrix_2).write(stream);
    REQUIRE(stream.str() == input )ж
}
TEST_CASE("operator -")

{

    std::string input_1{

        "3, 3\n"
        "3 3 3\n"
        "3 3 3\n"
        "3 3 3" };

    std::string input_2{

        "3, 3\n"
        "2 2 2\n"
        "2 2 2\n"
        "2 2 2" };

    std::string input{

        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1" };

    
    matrix_t matrix_1,matrix_2;
    std::istringstream istream1{ input_1 };
    std::istringstream istream2{ input_2 };
    REQUIRE( matrix_1.read( istream1 ) );
    REQUIRE( matrix_2.read( istream2 ) );
    REQUIRE_NOTHROW(matrix_1=matrix_1-matrix_2); 

    std::ostringstream ostream;
    matrix_1.write( ostream );
    REQUIRE( input == ostream.str() );

}

TEST_CASE("operator *")

{

    std::string input_1{

        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1" };

    std::string input_2{

        "3, 3\n"
        "2 2 2\n"
        "2 2 2\n"
        "2 2 2" };

    std::string input{

        "3, 3\n"
        "6 6 6\n"
        "6 6 6\n"
        "6 6 6" };

    matrix_t matrix_1,matrix_2;
    std::istringstream istream1{ input_1 };
    std::istringstream istream2{ input_2 };
    REQUIRE( matrix_1.read( istream1 ) );
    REQUIRE( matrix_2.read( istream2 ) );
    REQUIRE_NOTHROW(matrix_1*=matrix_2);

    std::ostringstream ostream;
    matrix_1.write( ostream );
    REQUIRE( input == ostream.str() );

}



TEST_CASE("operator +=")

{

    std::string input_1{

        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1" };

    std::string input_2{

        "3, 3\n"
        "2 2 2\n"
        "2 2 2\n"
        "2 2 2" };

    std::string input{

        "3, 3\n"
        "3 3 3\n"
        "3 3 3\n"
        "3 3 3" };

    matrix_t matrix_1,matrix_2;
    std::istringstream istream1{ input_1 };
    std::istringstream istream2{ input_2 };
    REQUIRE( matrix_1.read( istream1 ) );
    REQUIRE( matrix_2.read( istream2 ) );
    REQUIRE_NOTHROW(matrix_1+=matrix_2); 

    std::ostringstream ostream;
    matrix_1.write( ostream );
    REQUIRE( input == ostream.str() );

}



TEST_CASE("operator -=")

{

    std::string input_1{

        "3, 3\n"
        "3 3 3\n"
        "3 3 3\n"
        "3 3 3" };

    std::string input_2{

        "3, 3\n"
        "2 2 2\n"
        "2 2 2\n"
        "2 2 2" };

    std::string input{

        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1" };

    matrix_t matrix_1,matrix_2;
    std::istringstream istream1{ input_1 };
    std::istringstream istream2{ input_2 };
    REQUIRE( matrix_1.read( istream1 ) );
    REQUIRE( matrix_2.read( istream2 ) );
    REQUIRE_NOTHROW(matrix_1-=matrix_2);
	
    std::ostringstream ostream;
    matrix_1.write( ostream );
    REQUIRE( input == ostream.str() );

}



TEST_CASE("operator *=")

{

    std::string input_1{

        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1" };

    std::string input_2{

        "3, 3\n"
        "2 2 2\n"
        "2 2 2\n"
        "2 2 2" };

    std::string input{

        "3, 3\n"
        "6 6 6\n"
        "6 6 6\n"
        "6 6 6" };

    matrix_t matrix_1,matrix_2;
    std::istringstream istream1{ input_1 };
    std::istringstream istream2{ input_2 };
    REQUIRE( matrix_1.read( istream1 ) );
    REQUIRE( matrix_2.read( istream2 ) );

    matrix_1*=matrix_2;
    std::ostringstream ostream;
    matrix_1.write( ostream );
    REQUIRE( input == ostream.str() );

}
