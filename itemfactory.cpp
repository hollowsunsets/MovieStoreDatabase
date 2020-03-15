#include "itemfactory.h"
#include <sstream>

Item* ItemFactory::create_item(std::istream& stream) {
    std::string s;
    std::getline(stream, s, '\n');
    return create_item(s);
}

Item* ItemFactory::create_item(const std::string& s) {
    std::istringstream ss(s);
    while (ss.peek() == ' ') {
        ss.ignore(1, ' ');
    }

    char typecode = ss.get();
    ss.ignore(1, ',');
    while (ss.peek() == ' ') {
        ss.ignore(1, ' ');
    }
    switch (typecode) {
    case 'F':
        return ComedyMovie::create_item(ss);
    case 'D':
        return DramaMovie::create_item(ss);
    case 'C':
        return ClassicMovie::create_item(ss);
    default:
        std::cerr << "Invalid Video Code: " << typecode << std::endl;
        return NULL;
    }
}
    
