#pragma once
#ifndef AMFITEM_HPP
#define AMFITEM_HPP

#include <vector>
#include "amf.hpp"

enum AmfMarker {
	AMF_UNDEFINED,
	AMF_NULL,
	AMF_FALSE,
	AMF_TRUE,
	AMF_INTEGER,
	AMF_DOUBLE,
	AMF_STRING,
	AMF_XMLDOC,        // unsupported
	AMF_DATE,          // unsupported
	AMF_ARRAY,         // unsupported
	AMF_OBJECT,        // unsupported
	AMF_XML,           // unsupported
	AMF_BYTEARRAY,
	AMF_VECTOR_INT,    // unsupported
	AMF_VECTOR_UINT,   // unsupported
	AMF_VECTOR_DOUBLE, // unsupported
	AMF_VECTOR_OBJECT, // unsupported
	AMF_DICTIONARY     // unsupported
};

class AmfItem {
public:

	virtual std::vector<u8> serialize() const = 0;
};

#endif