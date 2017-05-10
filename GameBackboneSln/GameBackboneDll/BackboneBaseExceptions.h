#pragma once

#include <exception>

/// <summary>
/// Exception thrown when a GameRegion attempts to disassociate a
/// non-associated GameRegion
/// </summary>
/// <seealso cref="std::exception" />
class GameRegion_BadDissociation : public std::exception
{
public:
	virtual const char* what () const override {
		return "Attempting to remove a non-associated object is not allowed";
	}
};