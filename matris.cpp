#include "matris.h"

using namespace std;
//A simple test:

int main (){
  stringstream ss, kk,result1, result2;

  ss << "1 1 1"<<endl<<"2 2 2"<<endl<<"3 3 3"<<endl<<"4 4 4"<<endl;
  Matris<int> one(4,3);
  ss >> one;
  kk << "1 0 1"<<endl<<"2 0 2"<<endl<<"3 0 3"<<endl<<"4 0 4"<<endl;
  Matris<int> two(4,3);
  kk >> two;

  result1<<"3 1 3"<<endl<<"6 2 6"<<endl<<"9 3 9"<<endl<<"12 4 12"<<endl;
  Matris<int> result1M(4,3);
  result1 >> result1M;

  result2<<"2 3 2"<<endl<<"2 4 2"<<endl<<"2 5 2"<<endl<<"2 6 2"<<endl;
  Matris<int> result2M(4,3);
  result2>>result2M;

  Matris<int> copyconsMat1= one+(two*2);
  Matris<int> copyconsMat2= (one+1)-(two-1);
  if (copyconsMat1==result1M)
    cout<<true<<endl;
  else
    cout<<false<<endl;

  return 0;
}
