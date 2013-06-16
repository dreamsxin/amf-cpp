#include "amftest.hpp"

#include "gtest/gtest.h"

#include "amf.hpp"
#include "types/amfinteger.hpp"

static void isEqual(const std::vector<u8>& expected, int value) {
	ASSERT_EQ(expected, AmfInteger(value).serialize());
}

TEST(IntegerSerializationTest, PositiveInteger1Byte) {
	isEqual(v8 { 0x04, 0x00 }, 0);
	isEqual(v8 { 0x04, 0x01 }, 1);
	isEqual(v8 { 0x04, 0x7E }, 0x7e);
	isEqual(v8 { 0x04, 0x7F }, 0x7f);
}

TEST(IntegerSerializationTest, PositiveInteger2Byte) {
	isEqual(v8 { 0x04, 0x81, 0x00 }, 0x80);
	isEqual(v8 { 0x04, 0x87, 0x7E }, 0x3fe);
	isEqual(v8 { 0x04, 0x87, 0x7F }, 0x3ff);
	isEqual(v8 { 0x04, 0x88, 0x00 }, 0x400);
}

TEST(IntegerSerializationTest, PositiveInteger3Byte) {
	isEqual(v8 { 0x04, 0xFF, 0xFF, 0x7E }, 0x1ffffe);
	isEqual(v8 { 0x04, 0xFF, 0xFF, 0x7F }, 0x1fffff);
}

TEST(IntegerSerializationTest, PositiveInteger4Byte) {
	isEqual(v8 { 0x04, 0x80, 0xC0, 0x80, 0x00 }, 0x200000);
	isEqual(v8 { 0x04, 0xBF, 0xFF, 0xFF, 0xFE }, 0xffffffe);
	isEqual(v8 { 0x04, 0xBF, 0xFF, 0xFF, 0xFF }, 0xfffffff);
}

TEST(IntegerSerializationTest, PositiveIntegerLarge) {
	isEqual(v8 { 0x05, 0x41, 0xBF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00 }, 0x1ffffffe);
	isEqual(v8 { 0x05, 0x41, 0xBF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00 }, 0x1fffffff);
	isEqual(v8 { 0x05, 0x41, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 0x20000000);
	isEqual(v8 { 0x05, 0x41, 0xDF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00 }, 0x7ffffffe);
	isEqual(v8 { 0x05, 0x41, 0xDF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00 }, 0x7fffffff);
	isEqual(v8 { 0x05, 0x41, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 0x10000000);
}

TEST(IntegerSerializationTest, NegativeInteger) {
	isEqual(v8 { 0x04, 0xFF, 0xFF, 0xFF, 0xFF }, -1);
	isEqual(v8 { 0x04, 0xFF, 0xFF, 0xFF, 0xFE }, -2);
	isEqual(v8 { 0x04, 0xFF, 0xFF, 0xFF, 0xFD }, -3);
	isEqual(v8 { 0x04, 0xFF, 0xFF, 0xFF, 0xFC }, -4);
	isEqual(v8 { 0x04, 0xFF, 0xFF, 0xFF, 0xF9 }, -7);
	isEqual(v8 { 0x04, 0xFF, 0xFF, 0xFF, 0xF8 }, -8);
	isEqual(v8 { 0x04, 0xFF, 0xFF, 0xFF, 0xE1 }, -31);
	isEqual(v8 { 0x04, 0xFF, 0xFF, 0xFF, 0xE0 }, -32);
	isEqual(v8 { 0x04, 0xFF, 0xFF, 0xFF, 0x81 }, -127);
	isEqual(v8 { 0x04, 0xFF, 0xFF, 0xFF, 0x80 }, -128);
	isEqual(v8 { 0x04, 0xFF, 0xFF, 0xFF, 0x7F }, -129);
	isEqual(v8 { 0x04, 0xFF, 0xFF, 0xC0, 0x01 }, -16383);
	isEqual(v8 { 0x04, 0xFF, 0xFF, 0xC0, 0x00 }, -16384);
	isEqual(v8 { 0x04, 0xFF, 0xFF, 0xBF, 0xFF }, -16385);
	isEqual(v8 { 0x04, 0xFF, 0xC0, 0x80, 0x01 }, -2097151);
	isEqual(v8 { 0x04, 0xFF, 0xC0, 0x80, 0x00 }, -2097152);
	isEqual(v8 { 0x04, 0xFF, 0xBF, 0xFF, 0xFF }, -2097153);
	isEqual(v8 { 0x04, 0xC0, 0x80, 0x80, 0x01 }, -268435455);
	isEqual(v8 { 0x04, 0xC0, 0x80, 0x80, 0x00 }, -268435456);
}

TEST(IntegerSerializationTest, NegativeIntegerLarge) {
	isEqual(v8 { 0x05, 0xC1, 0xB0, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 }, -268435457);
	isEqual(v8 { 0x05, 0xC1, 0xDC, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00 }, -1879048193);
	isEqual(v8 { 0x05, 0xC1, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, -2147483648);
}
