#define DFLT_SIZE 16
#define NEW_VEC_DEFAULT_SIZE 0
#define EMPTY 0
#define INDEX_FAIL "Error: Invalid vector index"
#define CAP_C_NUM 1.5
#include "iostream"




template<typename T, size_t StaticCapacity=DFLT_SIZE>
class vl_vector{
 public:
/**
 * iterator typedefs
 */
  typedef T* iterator;
  typedef const T* const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

/**
 * begin iterator
 * @return
 */
  iterator begin() {return _vec;}

/**
 * end iterator
 * @return
 */
  iterator end() {return _vec+_vec_size;}

/**
 * begin iterator for const instance
 * @return
 */
  const_iterator begin() const{return _vec;}

/**
 * end iterator for const instance
 * @return
 */
  const_iterator end() const {return _vec+_vec_size;}

/**
 * const begin iterator
 * @return
 */
  const_iterator cbegin() const {return _vec;}

/**
 * const end iterator
 * @return
 */
  const_iterator cend() const {return _vec+_vec_size;}

/**
 * reverse begin iterator
 * @return
 */
  reverse_iterator rbegin(){return reverse_iterator(end());}

/**
 * reverse end iterator
 * @return
 */
  reverse_iterator rend(){return reverse_iterator(begin());}

/**
 * reverse begin iterator for const instance
 * @return
 */
  const_reverse_iterator rbegin() const{return const_reverse_iterator(end());}

/**
 * reverse end iterator for const instance
 * @return
 */
  const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

/**
 * const reverse begin iterator
 * @return
 */
  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(end());}

/**
 * const reverse end iterator
 * @return
 */
  const_reverse_iterator crend() const {
    return const_reverse_iterator(begin());}

/**
 * Default constructor of vector
 */
  vl_vector();

/**
 * Copy constructor
 * @param cpy_vec
 */
  vl_vector(const vl_vector<T, StaticCapacity> &cpy_vec);

/**
 * Constructor that sets initial vector to variables in iterator
 * @tparam ForwardIterator typedef Forward Iterator
 * @param first iterator that points to first variable
 * @param last iterator that points to the end of the iteration
 */
  template<class ForwardIterator>
  vl_vector(ForwardIterator first, ForwardIterator last);

/**
 * Constructor that sets "count" elements of vector to "v"
 * @param count number of elements
 * @param v element to set to
 */
  vl_vector(size_t count, T v);

/**
 * Destructor
 */
  ~vl_vector(){if(_vec_cap>StaticCapacity){delete [] _vec;}}

/**
 * @return amount of elements inserted in vector
 */
  size_t size() const {return _vec_size;}

/**
 * @return current capacity of vector
 */
  size_t capacity() const {return _vec_cap;}

/**
 * @return boolean depending on if vector currently has elements
 */
  bool empty() const {return _vec_size == EMPTY;}

/**
 * Gets element in vector at index given
 * @param index
 * @return returns copy of element
 */
  T at(int index) const;

/**
* Gets element in vector at index given
 * @param index
 * @return returns element
 */
  T &at(int index);

/**
 * adds new item to back of vector
 * @param new_item
 */
  void push_back(const T &new_item);

/**
 * inserts new item at iterator position given
 * @param it iterator of vector
 * @param new_elem
 * @return iterator pointing to new item
 */
  iterator insert (const_iterator it, T new_elem)
  {
    size_t dist = std::distance(cbegin(),it);
    if (_vec_size == _vec_cap){
        cap_c(1);
      }
    std::move_backward(begin()+dist, end(), end()+1);
    _vec[dist] = new_elem;
    _vec_size+=1;
    return begin()+dist;
  }

/**
 * inserts amount of elements at iterator given
 * @tparam ForwardIterator
 * @param position iterator pointing at where to insert new elements
 * @param first starting iterator of elements to insert
 * @param last end iterator of elements to insert
 * @return iterator pointing to beginning of new elements inserted
 */
  template<class ForwardIterator>
  iterator insert (const_iterator position, ForwardIterator first,
                   ForwardIterator last)
  {
    size_t dist = std::distance(first,last);
    size_t start = std::distance(cbegin(),position);
    if (_vec_size+dist>_vec_cap)
      {
        cap_c(dist);
      }
    std::move_backward(begin() + start, end(), end()+dist);
    _vec_size+=dist;
    std::copy(first, last, begin() + start);
    return begin() + start;
  }

/**
 * removes element from end of vector
 */
  void pop_back();

/**
 * erases element at iterator given
 * @param it iterator
 * @return iterator pointing to next element
 */
  iterator erase(const_iterator it)
  {
    size_t start = std::distance(cbegin(),it);
    std::move(begin()+start+1, end(), begin()+start);
    pop_back();
    return begin()+start;
  }

/**
 * erases elements between two first and last iterators
 * @param first iterator
 * @param last iterator
 * @return iterator pointing to next element
 */
  iterator erase(const_iterator first, const_iterator last)
  {
    size_t dist = std::distance(first,last);
    size_t start = std::distance(cbegin(),first);
    std::move(begin()+start+dist, end(), begin()+start);
    _vec_size-=dist;
    if(_vec_cap>StaticCapacity && _vec_size<=StaticCapacity)
      {
        restore_vec();
      }
    return begin()+start;
  }

/**
 * resets contents of vector
 */
  void clear();

/**
 * @return pointer vector elements
 */
  T* data() const;

/**
 * checks if variable is in vector
 * @param variable
 * @return boolean depending on if it is in vector
 */
  bool contains(const T &variable) const;

/**
 * equal operator for vector
 * @param vec
 * @return reference of vector
 */
  vl_vector<T, StaticCapacity> &operator=(const vl_vector<T, StaticCapacity>
                                          &vec);
/**
 * @param index
 * @return copy of element at index in vector
 */
  T operator[](int index) const;

/**
 * @param index
 * @return reference to element at index in vector
 */
  T &operator[](int index);

/**
 * checks if two vectors have same elements
 * @param vec
 * @return boolean depending on if it does
 */
  bool operator==(const vl_vector<T, StaticCapacity> &vec) const;

/**
 * checks if two vectors do not have same elements
 * @param vec
 * @return boolean depending on if it does
 */
  bool operator!=(const vl_vector<T, StaticCapacity> &vec) const {return
        !((*this)==vec);}


 private:
  size_t _vec_size;
  size_t _vec_cap;
  T *_vec;
  T _stat_vec[StaticCapacity];

/**
 * enlarges vector when needed according to special calculation
 * @param elem_amount amount of new elements to be added to vector
 */
  void cap_c(int elem_amount);

/**
 * restores vector to stack memory
 */
  void restore_vec();

};

template<typename T, size_t StaticCapacity>
vl_vector<T, StaticCapacity>::vl_vector () :_vec_size(NEW_VEC_DEFAULT_SIZE),
_vec_cap(StaticCapacity), _vec(_stat_vec){}

template<typename T, size_t StaticCapacity>
vl_vector<T, StaticCapacity>::vl_vector (const vl_vector<T,
    StaticCapacity> &cpy_vec) :
    _vec_size(NEW_VEC_DEFAULT_SIZE),
    _vec_cap(StaticCapacity), _vec(_stat_vec)
{
  insert(begin(), cpy_vec.cbegin(), cpy_vec.cend());
}

template<typename T, size_t StaticCapacity>
template<class ForwardIterator>
vl_vector<T, StaticCapacity>::vl_vector
    (ForwardIterator first,ForwardIterator last) : _vec_size
    (NEW_VEC_DEFAULT_SIZE), _vec_cap(StaticCapacity), _vec(_stat_vec)
{
  insert(begin(), first, last);
}

template<typename T, size_t StaticCapacity>
vl_vector<T, StaticCapacity>::vl_vector (const size_t count, T v):
    _vec_size(NEW_VEC_DEFAULT_SIZE),
    _vec_cap(StaticCapacity), _vec(_stat_vec)
{
  if (_vec_size + count> _vec_cap){
      cap_c(count);
    }
  _vec_size+= count;
  std::fill(begin(), end(), v);
}

template<typename T, size_t StaticCapacity>
void vl_vector<T, StaticCapacity>::push_back (const T &new_item)
{
  if (_vec_size == _vec_cap){
      cap_c(1);
    }
  _vec[_vec_size] = new_item;
  _vec_size++;
}

template<typename T, size_t StaticCapacity>
void vl_vector<T, StaticCapacity>::cap_c (int elem_amount)
{
  auto *temp = new T[int((CAP_C_NUM)*(_vec_size+elem_amount))];
  for (size_t i = 0; i<_vec_size; i++)
    {
      temp[i] = _vec[i];
    }
  if (_vec_cap != StaticCapacity)
    {
      delete [] _vec;
    }
  _vec = temp;
  _vec_cap = int((CAP_C_NUM)*(_vec_size+elem_amount));
}

template<typename T, size_t StaticCapacity>
T vl_vector<T, StaticCapacity>::at (int index) const
{
  if (index >= (int) _vec_size || index < EMPTY)
    {
      throw std::out_of_range(INDEX_FAIL);
    }
  return _vec[index];
}
template<typename T, size_t StaticCapacity>
T &vl_vector<T, StaticCapacity>::at (int index)
{
  if (index >= (int) _vec_size || index < EMPTY)
    {
      throw std::out_of_range(INDEX_FAIL);
    }
  return _vec[index];
}

template<typename T, size_t StaticCapacity>
void vl_vector<T, StaticCapacity>::pop_back ()
{
  if (_vec_size == EMPTY)
    {
      return;
    }
  _vec_size--;
  if(_vec_cap>StaticCapacity && _vec_size<=StaticCapacity)
    {
      restore_vec();
    }
}
template<typename T, size_t StaticCapacity>
void vl_vector<T, StaticCapacity>::restore_vec ()
{
  for (size_t i=0; i<StaticCapacity; i++)
    {
      _stat_vec[i] = _vec[i];
    }
  delete [] _vec;
  _vec = _stat_vec;
  _vec_cap = StaticCapacity;
}
template<typename T, size_t StaticCapacity>
void vl_vector<T, StaticCapacity>::clear ()
{
  if(_vec_size>StaticCapacity)
    {
      delete [] _vec;
      _vec = _stat_vec;
    }
  _vec_size = EMPTY;
  _vec_cap = StaticCapacity;
}

template<typename T, size_t StaticCapacity>
T *vl_vector<T, StaticCapacity>::data () const
{
  return _vec;
}

template<typename T, size_t StaticCapacity>
bool vl_vector<T, StaticCapacity>::contains (const T &variable) const
{
  for (size_t i=0; i<_vec_size; i++)
    {
      if(at(i)==variable)
        {
          return true;
        }
    }
  return false;
}
template<typename T, size_t StaticCapacity>
T vl_vector<T, StaticCapacity>::operator[] (const int index) const
{
  return _vec[index];
}

template<typename T, size_t StaticCapacity>
T &vl_vector<T, StaticCapacity>::operator[] (const int index)
{
  return _vec[index];
}

template<typename T, size_t StaticCapacity>
vl_vector<T, StaticCapacity> &vl_vector<T, StaticCapacity>::operator= (const
    vl_vector<T, StaticCapacity> &vec)
{
  if(this == &vec)
    {
      return *this;
    }
  clear();
  insert(begin(), vec.cbegin(), vec.cend());
  return *this;
}
template<typename T, size_t StaticCapacity>
bool
vl_vector<T, StaticCapacity>::operator == (const vl_vector<T,
    StaticCapacity> &vec) const
{
  if (_vec_size == vec._vec_size)
    {
      for (size_t i=0; i<_vec_size; i++)
        {
          if(_vec[i] != vec._vec[i])
            {
              return false;
            }
        }
      return true;
    }
  return false;
}

#ifndef _VL_VECTOR_H_
#define _VL_VECTOR_H_

#endif //_VL_VECTOR_H_
