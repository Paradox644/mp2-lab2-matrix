//// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE) throw - 1;
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        for (int i = 0; i < sz; i++) {
            pMem[i] = v.pMem[i];
        }
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        pMem = nullptr;
        swap(*this, v);
    }
    ~TDynamicVector()
    {
        delete[]pMem;
        sz = 0;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v) return *this;
        delete[]pMem;
        sz = v.sz;
        pMem = new T[sz];
        for (int i = 0; i < sz; i++)
            pMem[i] = v.pMem[i];
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        swap(*this, v);
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        if (ind<0 || ind> sz) { throw - 1; }
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        if (ind<0 || ind> sz) { throw - 1; }
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind < 0 || ind > sz) { throw - 1; }
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind < 0 || ind > sz) { throw - 1; }
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return 0;
        for (int i = 0; i < sz; i++)
            if (pMem[i] != v.pMem[i]) return 0;
        return 1;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector tdv(sz);
        for (int i = 0; i < sz; i++) {
            tdv.pMem[i] = pMem[i] + val;
        }
        return tdv;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector tdv(sz);
        for (int i = 0; i < sz; i++) {
            tdv.pMem[i] = pMem[i] - val;
        }
        return tdv;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector tdv(sz);
        for (int i = 0; i < sz; i++) {
            tdv.pMem[i] = pMem[i] * val;
        }
        return tdv;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) { throw - 1; }
        TDynamicVector tdv(sz);
        for (int i = 0; i < sz; i++)
            tdv.pMem[i] = pMem[i] + v.pMem[i];
        return tdv;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz) { throw - 1; }
        TDynamicVector tdv(sz);
        for (int i = 0; i < sz; i++)
            tdv.pMem[i] = pMem[i] - v.pMem[i];
        return tdv;
    }
    T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
    {
        if (sz != v.sz) { throw - 1; }
        T temp = T();
        for (int i = 0; i < sz; i++)
            temp += pMem[i] * v.pMem[i];
        return temp;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};



// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s == 0)
          throw out_of_range("Matrix size should be greater than zero");
      if (s > MAX_MATRIX_SIZE) throw - 1;
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  { 
      if (sz != m.sz) return 0;
      for (int i = 0; i < sz; i++)
          if (pMem[i] != m.pMem[i])
              return 0;
      return 1;
  }
bool operator!=(const TDynamicMatrix& m) const noexcept 
{
     return !(*this == m);
}
  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
    TDynamicMatrix tdm(sz);
    for (int i = 0; i < sz; i++) 
        tdm.pMem[i] = pMem[i] * val;
    return tdm;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      
      if (sz != v.sz) { throw - 1; }
      TDynamicMatrix tdm(sz);
      for (int i = 0; i < sz; i++) {
        tdm.pMem[i] = pMem[i] * v;
      }
      return tdm;
    }
      

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) { throw - 1; }
      TDynamicMatrix tdm(sz);

      for (int i = 0; i < sz; i++)
        tdm.pMem[i] = pMem[i] + m.pMem[i];
    return tdm;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
     if (sz != m.sz) { throw - 1; }
      TDynamicMatrix tdm(sz);

      for (int i = 0; i < sz; i++)
        tdm.pMem[i] = pMem[i] - m.pMem[i];
    return tdm;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    if (sz != m.sz) { throw -1; }
      TDynamicMatrix tdm(sz);
      for (int i = 0; i < sz; i++)
          for (int j = 0; j < sz; j++)
            for (int k=0; k<sz; k++) 
                tdm.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
    return tdm;

  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
    for (int i=0; i< v.sz; i++)
        istr>>v[i];
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
    for (int i=0; i< v.sz; i++)
        ostr << v[i] << "\n";
    return ostr;
  }
};

#endif
