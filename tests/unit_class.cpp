#include <catch.hpp>
#include <sstream>

#include "unit_class.hpp"

TEST_CASE("creating empty unit_class")
{
    unit_t testUnit;
    REQUIRE( testUnit.name_() == "<empty>" );
    REQUIRE( testUnit.mail_() == "<empty>" );
    REQUIRE( testUnit.pass_() == "<empty>" );
    REQUIRE( testUnit.desc_() == "<empty>" );
    REQUIRE( testUnit.link_() == "<empty>" );
}


TEST_CASE("creating unit_class")
{
    unit_t testUnit("a","b","c","d","e");
    REQUIRE( testUnit.name_() == "a" );
    REQUIRE( testUnit.mail_() == "b" );
    REQUIRE( testUnit.pass_() == "c" );
    REQUIRE( testUnit.desc_() == "d" );
    REQUIRE( testUnit.link_() == "e" );
}



TEST_CASE("creating copy unit_class")
{
    unit_t copyUnit("a","b","c","d","e");
    unit_t testUnit(copyUnit);
    REQUIRE( testUnit.name_() == "a" );
    REQUIRE( testUnit.mail_() == "b" );
    REQUIRE( testUnit.pass_() == "c" );
    REQUIRE( testUnit.desc_() == "d" );
    REQUIRE( testUnit.link_() == "e" );
}

TEST_CASE("reading matrix")
{
    std::string input
    {
        "name: a\n"
        "login: b\n"
        "password: c\n"
        "description: d\n"
        "link: e\n"    
    };
    
    unit_t testUnit("a","b","c","d","e");

    std::ostringstream ostream;
    testUnit.unitOutput( ostream );
    
    REQUIRE( input == ostream.str() );
    
    REQUIRE( testUnit.generatePassword(6,"",false) );
    std::string passT = testUnit.pass_();
            
    REQUIRE( passT.length() == 6 );
}
