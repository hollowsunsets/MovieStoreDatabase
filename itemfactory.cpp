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
        break;
    case 'D':
        return DramaMovie::create_item(ss);
        break;
    case 'C':
        return ClassicMovie::create_item(ss);
        break;
    default:
        std::cerr << "Invalid Item Code: " << typecode << std::endl;
        return NULL;
    }
}

// transforms item data from commands to a valid sorting key
// returns either a key according to the item key if successful
// or the empty string if the movie type is unknown
std::string ItemFactory::item_data_to_key(const std::string& s) {
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
        return ComedyMovie::data_to_key(ss);
    case 'D':
        return DramaMovie::data_to_key(ss);
    case 'C':
        return ClassicMovie::data_to_key(ss);
    default:
        std::cerr << "Invalid Item Code: " << typecode << std::endl;
        return "";
    }
}
    
