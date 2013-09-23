#include <cppunit\config\SourcePrefix.h>

#include "TestParser.h"

void TestParser::setUp()
{}

void TestParser::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestParser);

void TestParser::testParse()
{
	CPPUNIT_ASSERT_THROW_MESSAGE("Unable to find/open file", parser.parse("..\\source\\Simple\\Unit Test\\Parser\\Parse0.txt"), ParseException);

	CPPUNIT_ASSERT_THROW_MESSAGE("Duplicate procedure names", parser.parse("..\\source\\Simple\\Unit Test\\Parser\\Parse1.txt"), ParseException);

	CPPUNIT_ASSERT_THROW_MESSAGE("Token does not match with keyword", parser.parse("..\\source\\Simple\\Unit Test\\Parser\\Parse2.txt"), ParseException);
	
	CPPUNIT_ASSERT_THROW_MESSAGE("Name should contains only letters & digits with a letter as beginning, constant should contain only digits", parser.parse("..\\source\\Simple\\Unit Test\\Parser\\Parse3.txt"), ParseException);
	
	CPPUNIT_ASSERT_THROW_MESSAGE("Unable to parse statements", parser.parse("..\\source\\Simple\\Unit Test\\Parser\\Parse4.txt"), ParseException);
	
	CPPUNIT_ASSERT_THROW_MESSAGE("Mismatched parentheses", parser.parse("..\\source\\Simple\\Unit Test\\Parser\\Parse5.txt"), ParseException);
	
	CPPUNIT_ASSERT_THROW_MESSAGE("Unable to parse expression", parser.parse("..\\source\\Simple\\Unit Test\\Parser\\Parse6.txt"), ParseException);
	
	CPPUNIT_ASSERT_THROW_MESSAGE("Unnecessary token", parser.parse("..\\source\\Simple\\Unit Test\\Parser\\Parse7.txt"), ParseException);

	CPPUNIT_ASSERT_NO_THROW_MESSAGE("Success", parser.parse("..\\source\\Simple\\Unit Test\\Parser\\Parse8.txt"));
}