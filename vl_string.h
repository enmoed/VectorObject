#ifndef _VL_STRING_H_
#define _VL_STRING_H_
#include "vl_vector.h"
#include "cstring"

template<size_t StaticCapacity = DFLT_SIZE>
class vl_string : public vl_vector<char, StaticCapacity> {
 public:
/**
 * Default constructor
 */
  vl_string(): vl_vector<char, StaticCapacity>(1,'\0') {}
/**
 * Copy constructor
 * @param cpy
 */
  vl_string(const vl_string<StaticCapacity> &cpy):
  vl_vector<char, StaticCapacity> (cpy){}
/**
 * Implicit constructor
 * @param word initializes string with word
 */
  vl_string(const char *word): vl_vector<char, StaticCapacity>
      (word,word+std::strlen(word)+1){}
/**
 * @return size of string
 */
  size_t size() const override
  {
    return vl_vector<char, StaticCapacity>::size()-1;
  }
/**
 * @return boolean if string is empty
 */
  bool empty () const override
  {
    return (size() == 0);
  }
/**
 * Inserts letter to back of string
 * @param letter
 */
  void push_back (const char &letter) override
  {
    vl_vector<char, StaticCapacity>::pop_back();
    vl_vector<char, StaticCapacity>::push_back(letter);
    vl_vector<char, StaticCapacity>::push_back('\0');
  }
/**
 * Removes letter from end of string
 */
  void pop_back() override
  {
    if (size()==0)
      {
        return;
      }
    vl_vector<char, StaticCapacity>::pop_back();
    vl_vector<char, StaticCapacity>::pop_back();
    vl_vector<char, StaticCapacity>::push_back('\0');
  }
/**
 * clears elements of string
 */
  void clear() override
  {
    vl_vector<char, StaticCapacity>::clear();
    vl_vector<char, StaticCapacity>::push_back('\0');
  }
/**
 * checks if word is in string
 * @param word
 * @return boolean if it does
 */
  bool contains(const char *word) const{return strstr(this->cbegin(),
                                               word) !=NULL;}
/**
 * Equalizes string to string argument
 * @param vec string argument
 * @return updated string vector
 */
  vl_string &operator= (const vl_string<StaticCapacity> &vec)
  {
    if (*this == vec)
      {
        return *this;
      }
    clear();
    vl_vector<char, StaticCapacity>::insert(this->cbegin(), vec.cbegin(),
                                            vec.cend()-1);
    return *this;
  }
/**
 * adds string vector to end of string vector
 * @param vec string to be added
 * @return updated string vector
 */
  vl_string &operator+= (const vl_string<StaticCapacity> &vec)
  {
    vl_vector<char, StaticCapacity>::insert(this->cend()-1, vec.cbegin(),
                                            vec.cend()-1);
    return *this;
  }
/**
 * adds string to end of string vector
 * @param word string to be added
 * @return updated string vector
 */
  vl_string &operator+= (const char *word)
  {
    vl_vector<char, StaticCapacity>::insert(this->cend()-1, word,
                                            word+(std::strlen(word)));
    return *this;
  }
/**
 * adds char to end of string vector
 * @param letter char to be added
 * @return updated string vector
 */
  vl_string &operator+= (const char &letter)
  {
    vl_vector<char, StaticCapacity>::insert(this->cend()-1, letter);
    return *this;
  }
/**
 * creates new string vector and adds string vector end of string vector
 * @param vec string vector to be added
 * @return new string vector
 */
  vl_string operator+ (const vl_string<StaticCapacity> &vec) const
  {
    vl_string<StaticCapacity> temp(*this);
    temp.insert(temp.cend()-1, vec.cbegin(), vec.cend()-1);
    return temp;
  }
/**
 * creates new string vector and adds string to end of string vector
 * @param word string to be added
 * @return new string vector
 */
  vl_string operator+ (const char *word) const
  {
    vl_string<StaticCapacity> temp(*this);
    temp.insert(temp.cend()-1, word, word+(std::strlen(word)));
    return temp;
  }
/**
 * creates new string vector and adds char to end of string vector
 * @param letter char to be added
 * @return new string vector
 */
  vl_string operator+ (const char &letter)
  {
    vl_string<StaticCapacity> temp(*this);
    temp.insert(temp.cend()-1, letter);
    return temp;
  }
/**
 * implicit casting
 * @return pointer to begin
 */
  operator const char * () const
  {
    return this->begin();
  }

};
#endif //_VL_STRING_H_
