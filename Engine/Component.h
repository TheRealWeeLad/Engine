#pragma once
#include <iostream>
class Component
{
public:
	virtual void update() {};
};

inline std::ostream& operator<<(std::ostream& stream, const Component& v)
{
	stream << 1;
	return stream;
}