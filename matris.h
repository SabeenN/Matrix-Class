#ifndef MATRIS_H
#define MATRIS_H

using namespace std;
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <initializer_list>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <cstring>

template <class T>
class Matris{
public:
   // constructors:
   Matris(){}
   Matris(int rows, int cols): m_rows(rows), m_cols(cols), m_capacity(cols*rows){}
   explicit Matris(int some): m_rows(some), m_cols(some),m_capacity(some*some){}

   explicit Matris(initializer_list<T> listt){
     double sqrd=sqrt(listt.size());
     int sqri=sqrd;
     if (sqrd != sqri){
       throw std::out_of_range("Not a squre matrix");
     }
     m_rows=sqri;
     m_cols=sqri;
     m_capacity=sqri*sqri;
     m_vec = new T [m_capacity];
     for_each(listt.begin(), listt.end(), [this](T n){m_vec[n-1]=n;});
   }

// Copy constructor
   Matris(const Matris<T>& rhs): m_rows(rhs.m_rows), m_cols(rhs.m_cols), m_capacity(rhs.m_capacity){
     if (m_vec != nullptr){
       delete [] m_vec;
     }
     m_vec = new T [m_capacity];
     for (int i=0; i<m_capacity; i++){
       m_vec[i] = rhs.m_vec[i];
     }
   }

 //Destructor
   virtual ~Matris() {delete [] m_vec;}

 //Move constructor
   Matris(Matris<T>&& other): m_rows(other.m_rows),m_cols(other.m_cols),m_capacity(other.m_capacity){
     for (int i=0; i<m_capacity; i++) {
       m_vec[i] = other.m_vec[i];
     }
     delete [] other.m_vec;
     other.m_vec=nullptr;
   }

//Move assignment
   Matris<T>& operator=(Matris<T>&& right);

//Copy-assignment
   Matris<T>& operator=(const Matris<T>& right);

   // Mathemathical matrix operation
   Matris<T>& operator+=(const Matris<T>& right);
   Matris<T>& operator-=(const Matris<T>& right);
   Matris<T>& operator*=(const Matris<T>& right);
   Matris<T> operator+(const Matris<T>& right);
   Matris<T> operator-(const Matris<T>& right);
   Matris<T> operator*(const Matris<T>& right);
   //Scalar operations
   Matris<T> operator*(const T& right);
   Matris<T> operator+(const T& right);
   Matris<T> operator-(const T& right);

   // Accessors
   T& operator()(const int& row, const int& col);
   T& operator()(const int& row, const int& col) const;

   // Other useful methods
   void reset();//
   void insert_row(int position);
   void append_row(int position);
   void remove_row(int position);
   void insert_column(int position);
   void append_column(int position);
   void remove_column(int position);

   void transpose();
   T * begin();
   auto * end();

  int rows() const;
  int cols() const;

private:
   int m_rows=0;
   int m_cols=0;
   int m_capacity=0;
   T * m_vec= new T [m_capacity]();
};

// copy assignement operator
template <class T>
Matris<T>& Matris<T>::operator=(const Matris<T>& right){//
  if (&right == this){
     return *this;
   }
   int new_rows = right.rows();
   int new_cols = right.cols();
   this->m_rows = new_rows;
   this->m_cols = new_cols;
   if (this->m_vec == nullptr){
     this->m_vec = new T[new_rows*new_cols];
   }else{
     delete [] this->m_vec;
     this->m_vec = new T[new_rows*new_cols];
   }
   this->m_capacity=new_cols*new_rows;
   for (int i=0; i<new_rows; i++) {
     for (int j=0; j<new_cols; j++) {
       int index=(i*new_cols) + j;
       this->m_vec[index]= right(i,j);
     }
   }
   return *this;
}
// move-assignment
template <class T>
Matris<T>& Matris<T>::operator=(Matris<T>&& right){
  if (&right == this){
     return *this;}
   int new_rows = right.rows();
   int new_cols = right.cols();
   this->m_rows = new_rows;
   this->m_cols = new_cols;
   this->m_capacity=new_cols*new_rows;
   if (this->m_vec == nullptr){
     this->m_vec = new T[m_capacity];
   }else{
     delete [] this->m_vec;
     this->m_vec = new T[m_capacity];
   }
   for (int i=0; i<new_rows; i++) {
     for (int j=0; j<new_cols; j++) {
       int index=(i*new_cols) + j;
       this->m_vec[index]= right(i,j);
     }
   }
   return *this;
}

//Matrix/scalar operations
template <class T>
Matris<T>& Matris<T>::operator+=(const Matris<T>& right){
    int rows = right.rows();
    int cols = right.cols();
    T temp;
    for (int i=0; i<rows; i++) {
      for (int j=0; j<cols; j++) {
        int index=(i*cols)  + j;
        temp=this->m_vec[index];
        this->m_vec[index] = temp + right(i,j);
      }
    }
  return *this;
}

template <class T>
Matris<T>& Matris<T>::operator-=(const Matris<T>& right){
  int rows = right.rows();
  int cols = right.cols();
  T temp;
  for (int i=0; i<rows; i++) {
    for (int j=0; j<cols; j++) {
      int index=(i*cols) + j;
      temp=this->m_vec[index];
      this->m_vec[index] = temp-right(i,j);
    }
  }
  return *this;
}

template <class T>
Matris<T>& Matris<T>::operator*=(const Matris<T>& right){
  Matris<T> resultat = (*this) * right;
  (*this) = resultat;
  return *this;
}

template <class T>
Matris<T> Matris<T>::operator+(const Matris<T>& right){
  Matris<T> resultat;
  resultat = *this;
  resultat += right;
  return resultat;
}

template <class T>
Matris<T> Matris<T>::operator-(const Matris<T>& right){
  Matris<T> resultat;
  resultat = (*this);
  resultat -= right;
  return resultat;
}

template <class T>
Matris<T> Matris<T>::operator*(const Matris<T>& right){
  int rows = right.rows();
  int cols = right.cols();
  int leftcols=this->m_cols;
  Matris<T> result(rows,cols);
  for (int k=0; k<cols; k++) {
   for ( int i=0; i<rows; i++) {
    for ( int j=0; j<leftcols; j++) {
         int index=(i*leftcols) + j;
         result(i,k) += this->m_vec[index] * right(j,k);
      }
    }
  }
  return result;
}

template <class T>
Matris<T> Matris<T>::operator+(const T& right){
  int rows = this->m_rows;
  int cols = this->m_cols;
  Matris<T> resultat(rows,cols);
  for (int i=0; i<rows; i++) {
    for (int j=0; j<cols; j++) {
      int index=(i*cols) + j;
      resultat(i,j) = this->m_vec[index] + right;
    }
  }
  return resultat;
}

template <class T>
Matris<T> Matris<T>::operator-(const T& right) {
  int rows = this->m_rows;
  int cols = this->m_cols;
  Matris<T> resultat(rows,cols);
  for (int i=0; i<rows; i++) {
    for (int j=0; j<cols; j++) {
      int index=(i*cols) + j;
      resultat(i,j) = this->m_vec[index] - right;
    }
  }
  return resultat;
}

template <class T>
Matris<T> Matris<T>::operator*(const T & right){
  int rows = this->m_rows;
  int cols = this->m_cols;
  Matris<T> resultat(rows,cols);
  for ( int i=0; i<rows; i++) {
    for ( int j=0; j<cols; j++) {
       int index = (i * cols) + j;
       resultat(i,j) = this->m_vec[index] * right;
    }
  }
  return resultat;
}

template <class T>
T& Matris<T>::operator()(const int& row, const int& col) const{
  int index= ((row)*(this->m_cols))+col;
  return this->m_vec[index];
}

template <class T>
T& Matris<T>::operator()(const int& row, const int& col){
  int index= ((row)*(this->m_cols))+col;
  return this->m_vec[index];
}

template <class T>
void Matris<T>::reset(){
   T defVal= T();
   int rows=this->m_rows;
   int cols=this->m_cols;
   for ( int i=0; i<rows; i++) {
     for ( int j=0; j<cols; j++) {
       int index= (i*cols) + j;
       this->m_vec[index]=defVal;
     }
   }
}

template <class T>
 void Matris<T>::insert_row(int position){
     append_row(position-1);
}

template <class T>
void Matris<T>::append_row(int position){
  int oldRows=this->m_rows;
  int oldCols=this->m_cols;
  int oldCap=oldCols*oldRows;
  this->m_rows=oldRows+1;
  this->m_capacity=(this->m_rows)*oldCols;

  //RESIZING --------------
  T * tempArr=new T[this->m_capacity];
  for (int i=0; i<oldCap; i++){
    tempArr[i]=this->m_vec[i];
  }
  delete [] this->m_vec;
  this->m_vec= new T[this->m_capacity];
  for (int i=0; i<oldCap; i++){
    this->m_vec[i]=tempArr[i];
  }
  //---------------------
  for ( int i=oldRows-1; i>position-1; i--) {
    for ( int j=0; j<oldCols; j++) {
      T back=this->m_vec[(i-1)*oldCols+j];
      T cur=this->m_vec[i*oldCols+j];
      this->m_vec[(i+1)*oldCols+j]=cur;
      this->m_vec[i*oldCols+j]=back;
      }
  }
  for ( int j=0; j<oldCols; j++) {
     this->m_vec[(position)*oldCols+j]=0;
  }
}

template <class T>
void Matris<T>::remove_row(int position){
  int rows=this->m_rows;
  int cols=this->m_cols;
  this->m_rows=rows-1;
  this->m_capacity=(rows-1)*cols;
  T temp;
  for (int i=position-1; i<rows; i++) {
    for (int j=0; j<cols; j++) {
      temp=this->m_vec[((i+1)*cols)+j];
      this->m_vec[(i*cols)+j]=temp;
      }
    }
}

template <class T>
void Matris<T>::insert_column(int position){
  transpose();
  insert_row(position);
  transpose();
}

template <class T>
void Matris<T>::append_column(int position){
    transpose();
    append_row(position);
    transpose();
}

template <class T>
void Matris<T>::remove_column(int position){
    transpose();
    remove_row(position);
    transpose();
}

template <class T>
void Matris<T>::transpose(){
    int oldCols=this->m_cols;
    int oldRows=this->m_rows;
    Matris<T> resultat(oldCols,oldRows);
    for (int i=0; i<oldRows; i++) {
      for (int j=0; j<oldCols; j++) {
        int index=(i*oldCols) + j;
        resultat(j,i)=this->m_vec[index];
      }
    }
    *this=resultat;
}

template <class T>
T * Matris<T>::begin(){
     T * val = &this->m_vec[0];
     return val;
  }

template <class T>
auto * Matris<T>::end(){
     int endIndex=(this->m_rows*this->m_cols);
     T * val = &(this->m_vec[endIndex]);
     return val;
}

template <class T>
int Matris<T>::rows() const{
   return this->m_rows;
 }

template <class T>
int Matris<T>::cols() const{
 return this->m_cols;
}


template <class T>
bool operator==(const Matris<T>& left,const Matris<T>& right){
  int counter=0;
  int lrows=left.rows();
  int lcols=left.cols();
  int rrows=right.rows();
  int rcols=right.cols();
  int totalelements=lrows*lcols;
  if ((lrows!=rrows) && (lcols!=rcols)){
    return false;
  }else{
    for (int i=0; i<lrows; i++) {
      for (int j=0; j<lcols; j++){
        if (left(i,j)==right(i,j)){
          counter++;
        }
      }
    }
    if (counter == totalelements){
      return true;
    }
    return false;
  }
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Matris<T>& c){
  int rows=c.rows();
  int cols=c.cols();
  for (int i=0; i<rows; i++) {
    for (int j=0; j<cols; j++) {
        os << c(i,j) << " ";
    }
    os << std::endl;
  }
  return os;
}

template <class T>
std::istream& operator>>(std::istream& is, Matris<T>& c){
  int rows= c.rows();
  int cols= c.cols();
  for(int i=0; i<rows; i++){
    for(int j=0; j<cols; j++)
      {
       is >> c(i,j);
      }
    }
   return is;
}

//Returns an identity matrix
Matris<int> identity(int size){
  Matris <int> idMat(size);
  for (int i=0; i<size; i++) {
    for (int j=0; j<size; j++) {
      if (j==i){
      idMat(i,j)=1;
    }else{
      idMat(i,j)=0;
      }
    }
  }
  return idMat;
}


#endif
