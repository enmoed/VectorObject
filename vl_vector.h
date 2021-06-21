#define DFLT_SIZE 16
#define NEW_VEC_DEFAULT_SIZE 0
#define EMPTY 0
#define INDEX_FAIL "Error: Invalid vector index"
#define CAP_C_NUM 1.5



template<typename T, size_t StaticCapacity=DFLT_SIZE>
class vl_vector{
 public:

  typedef T* iterator;
  typedef const T* const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  iterator begin() {return _vec;}
  iterator end() {return _vec+_vec_size;}
  const_iterator begin() const{return _vec;}
  const_iterator end() const {return _vec+_vec_size;}
  const_iterator cbegin() const {return _vec;}
  const_iterator cend() const {return _vec+_vec_size;}
  reverse_iterator rbegin(){return reverse_iterator(end());}
  reverse_iterator rend(){return reverse_iterator(begin());}
  const_reverse_iterator rbegin() const{return const_reverse_iterator(end());}
  const_reverse_iterator rend() const {return const_reverse_iterator(begin());}
  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(end());}
  const_reverse_iterator crend() const {
    return const_reverse_iterator(begin());}


  vl_vector();
  vl_vector(const vl_vector<T, StaticCapacity> &cpy_vec);
  template<class ForwardIterator>
  vl_vector(ForwardIterator first, ForwardIterator last);
  vl_vector(size_t count, T v);
  ~vl_vector(){if(_vec_cap>StaticCapacity){delete [] _vec;}}
  size_t size() const {return _vec_size;}
  size_t capacity() const {return _vec_cap;}
  bool empty() const {return _vec_size <= EMPTY;}
  T at(int index) const;
  T &at(int index);
  void push_back(T new_item);
  iterator insert (const_iterator it, T new_elem)
  {
    size_t dist = std::distance(cbegin(),it);
    if (_vec_size == _vec_cap){
        cap_c(1);
      }
    std::move_backward(it, cend(), end()+1);
    _vec[dist] = new_elem;
    return begin()+dist;
  }
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
  void pop_back();
  iterator erase(const_iterator it)
  {
    size_t start = std::distance(cbegin(),it);
    std::move(begin()+start+1, end(), begin()+start);
    pop_back();
    return begin()+start;
  }
  iterator erase(const_iterator first, const_iterator last)
  {
    size_t dist = std::distance(first,last);
    size_t start = std::distance(cbegin(),first);
    std::move_backward(first, last, end()+dist);
    _vec_size-=dist;
    if(_vec_size<=StaticCapacity)
      {
        restore_vec();
      }
    return begin()+start;
  }
  void clear();
  T* data() const;
  bool contains(const T &variable) const;
  vl_vector<T, StaticCapacity> &operator=(const vl_vector<T, StaticCapacity>
      &vec);
  T operator[](int index) const;
  T &operator[](int index);
  bool operator==(const vl_vector<T, StaticCapacity> &vec) const;
  bool operator!=(const vl_vector<T, StaticCapacity> &vec) const {return
                                                            !((*this)==vec);}


 private:
  size_t _vec_size;
  size_t _vec_cap;
  T *_vec;
  void cap_c(int elem_amount);
  void restore_vec();

};

template<typename T, size_t StaticCapacity>
vl_vector<T, StaticCapacity>::vl_vector () :_vec_size(NEW_VEC_DEFAULT_SIZE),
_vec_cap(StaticCapacity)
{
  T stack_arr[StaticCapacity];
  _vec = stack_arr;
}

template<typename T, size_t StaticCapacity>
vl_vector<T, StaticCapacity>::vl_vector (const vl_vector<T,
                                         StaticCapacity> &cpy_vec) :
    _vec_size(NEW_VEC_DEFAULT_SIZE),
    _vec_cap(StaticCapacity)
{
  T stack_arr[StaticCapacity];
  _vec = stack_arr;
  insert(begin(), cpy_vec.cbegin(), cpy_vec.cend());
}

template<typename T, size_t StaticCapacity>
template<class ForwardIterator>
vl_vector<T, StaticCapacity>::vl_vector
(ForwardIterator first,ForwardIterator last) : _vec_size(NEW_VEC_DEFAULT_SIZE),
                                               _vec_cap(StaticCapacity)
{
  T stack_arr[StaticCapacity];
  _vec = stack_arr;
  insert(begin(), first, last);
}

template<typename T, size_t StaticCapacity>
vl_vector<T, StaticCapacity>::vl_vector (const size_t count, T v):
    _vec_size(count),
    _vec_cap(StaticCapacity)
{
  T stack_arr[StaticCapacity];
  _vec = stack_arr;
  if (_vec_size > _vec_cap){
      cap_c(count);
    }
  std::fill(begin(), end(), v);
}

template<typename T, size_t StaticCapacity>
void vl_vector<T, StaticCapacity>::push_back (T new_item)
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
  _vec_cap = (CAP_C_NUM)*(_vec_size+elem_amount);
}

template<typename T, size_t StaticCapacity>
T vl_vector<T, StaticCapacity>::at (int index) const
{
  if (index >= (int) _vec_cap || index < EMPTY)
    {
      throw std::out_of_range(INDEX_FAIL);
    }
  return _vec[index];
}
template<typename T, size_t StaticCapacity>
T &vl_vector<T, StaticCapacity>::at (int index)
{
  if (index >= (int) _vec_cap || index < EMPTY)
    {
      throw std::out_of_range(INDEX_FAIL);
    }
  return _vec[index];
}

template<typename T, size_t StaticCapacity>
void vl_vector<T, StaticCapacity>::pop_back ()
{
  _vec_size--;
  if(_vec_cap>StaticCapacity && _vec_size<=StaticCapacity)
    {
      restore_vec();
    }
}

template<typename T, size_t StaticCapacity>
void vl_vector<T, StaticCapacity>::restore_vec ()
{
  T temp[StaticCapacity];
  for (size_t i=0; i<StaticCapacity; i++)
    {
      temp[i] = _vec[i];
    }
  delete [] _vec;
  _vec = temp;
  _vec_cap = StaticCapacity;
}
template<typename T, size_t StaticCapacity>
void vl_vector<T, StaticCapacity>::clear ()
{
  if(_vec_size>StaticCapacity)
    {
      delete [] _vec;
      T stack_arr[StaticCapacity];
      _vec = stack_arr;
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
  if (_vec_size == vec._vec_size && _vec_cap== vec._vec_cap)
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
