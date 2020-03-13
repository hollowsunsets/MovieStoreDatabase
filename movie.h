#ifndef MOVIE_H
#define MOVIE_H

#include "item.h"

// Movies are a type of Item carried by a Store
// the Movie class defines an abstract movie
// with required fields but no groupcode
class Movie : public Item {
  public:
    Movie();
   
    // constructor using input line format
    Movie(std::istream& s);

    // constructor using explicit parameters
    Movie(int stock, const std::string &director,
          const std::string &title, int year);

    virtual char get_typecode() const = 0;
    
    // factory interface for constructing movie 
    virtual Item* create_item(std::istream& s) = 0;
    
    // implemented suitably in Item
    // virtual bool operator<(const Item &m) const;
    // virtual bool operator>(const Item &m) const;
    // virtual bool operator==(const Item &m) const;

  protected:
    std::string director;
    std::string title;
    int year;  
};

class ComedyMovie : public Movie {
  public:
    ComedyMovie(std::istream& s) : Movie(s){};

    char get_typecode() const { return 'F'; }
    
    // Comedy Movies are sorted by Title, then Year
    std::string get_key() const;

    Item* create_item(std::istream& s);
    
    // taken care of with get_key 
    // virtual bool operator<(const Item&);
    // virtual bool operator>(const Item&);
    // virtual bool operator==(const Item&);

  protected:
    // const static char typecode = 'F';
};

class DramaMovie : public Movie {
  public:
    DramaMovie(std::istream& s) : Movie(s){};

    char get_typecode() const { return 'D'; }
    // Drama Movies are sorted by Director, then Title
    // return sorting key
    std::string get_key() const;

    Item* create_item(std::istream& s);
    
    // virtual bool operator<(const Item&);
    // virtual bool operator>(const Item&);
    // virtual bool operator==(const Item&);

  protected:
    // const static char typecode = 'D';
};

// the ClassicMovie derived class
// has additional fields
class ClassicMovie : public Movie {
  public:
    // constructor using input line format
    ClassicMovie(std::istream& s);

    // constructor using explicit parameters
    ClassicMovie(int stock, const std::string &director,
                 const std::string &title, const std::string &major_actor,
                 int month, int year);

    char get_typecode() const { return 'C'; }

    // Classic Movies are sorted by Release Date, then Major Actor
    // return sorting key
    std::string get_key() const;

    Item* create_item(std::istream& s);

    // virtual bool operator<(const Item&);
    // virtual bool operator>(const Item&);
    // virtual bool operator==(const Item&);
  
  protected:
    // const static char typecode = 'C';

    std::string major_actor;
    int month;
};

#endif // MOVIE_H
