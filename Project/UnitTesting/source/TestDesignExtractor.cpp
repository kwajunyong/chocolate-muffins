#include <cppunit\config\SourcePrefix.h>

#include "TestDesignExtractor.h"

void TestDesignExtractor::setUp()
{}

void TestDesignExtractor::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestDesignExtractor);

void TestDesignExtractor::testExtract()
{
	PKB* pkb;

	pkb = parser.parse("..\\source\\Simple\\Unit Test\\DesignExtractor\\Extract1.txt");
	CPPUNIT_ASSERT_THROW_MESSAGE("Called procedure does not exist", extractor.extract(pkb), ParseException);
	
	pkb = parser.parse("..\\source\\Simple\\Unit Test\\DesignExtractor\\Extract2.txt");
	CPPUNIT_ASSERT_THROW_MESSAGE("Recursive procedure call", extractor.extract(pkb), ParseException);

	pkb = parser.parse("..\\source\\Simple\\Unit Test\\DesignExtractor\\Extract3.txt");
	CPPUNIT_ASSERT_THROW_MESSAGE("Transitively recursive procedure call", extractor.extract(pkb), ParseException);

	pkb = parser.parse("..\\source\\Simple\\Unit Test\\DesignExtractor\\Extract4.txt");
	CPPUNIT_ASSERT_NO_THROW_MESSAGE("Success", extractor.extract(pkb));
}