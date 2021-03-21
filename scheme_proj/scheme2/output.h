#pragma once

#include <iostream>
#include "Sxpressions.h"
void write(std::ostream& os, Expression *expr);
void writeList(std::ostream& os, Expression *list); 
std::ostream& operator<<(std::ostream& os, Expression* expr);
std::ostream& operator<<(std::ostream& os, const Expression& expr);
