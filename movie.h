#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include "item.h"

// Movies are a type of Item carried by a Store
// the Movie class defines an abstract movie
// with required fields but no groupcode
class Movie : protected Item {
 public:
  Movie(int stock, const std::string &director,
        int year, const std::string &title);

  virtual bool operator<(const Item &m) const;
  virtual bool operator>(const Item &m) const;
  virtual bool operator==(const Item &m) const;

 protected:
  std::string director;
  std::string title;
  int year;
  
};

class ComedyMovie : protected Movie {
 public:
  // Comedy Movies are sorted by Title, then Year
  virtual bool operator<(const Item&);
  virtual bool operator>(const Item&);
  virtual bool operator==(const Item&);

 protected:
  const static char typecode = 'F';
};

class DramaMovie : protected Movie {
 public:
  // Drama Movies are sorted by Director, then Title
  virtual bool operator<(const Item&);
  virtual bool operator>(const Item&);
  virtual bool operator==(const Item&);

 protected:
  const static char typecode = 'D';
};

// the ClassicMovie derived class
// has additional fields
class ClassicMovie : protected Movie {
 public:
  ClassicMovie(int stock, const std::string &director,
               const std::string &title, const std::string &major_actor,
               int month, int year);

  // Classic Movies are sorted by Release Date, then Major Actor
  virtual bool operator<(const Item&);
  virtual bool operator>(const Item&);
  virtual bool operator==(const Item&);
  
 protected:
  const static char typecode = 'C';

  std::string major_actor;
  int month;
};

#endif // MOVIE_H
