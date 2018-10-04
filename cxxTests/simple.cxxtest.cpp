#include <cxxtest/TestSuite.h>

#include "matris.h"
#include <climits>
#include <sstream>

class MyTestSuite : public CxxTest::TestSuite {
  public:
    void test1() {
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

      TS_ASSERT_EQUALS(copyconsMat1,result1M);
      TS_ASSERT_EQUALS(copyconsMat2,result2M);

      Matris<int> idMat=identity(3);
      one.remove_row(4);
      Matris<int> copyconsMat3= one*idMat;
      TS_ASSERT_EQUALS(copyconsMat3,one);
      one *= idMat;
      TS_ASSERT_EQUALS(copyconsMat3,one);
      idMat += idMat;
      idMat -= idMat;
      one.reset();
      TS_ASSERT_EQUALS(idMat,one);
      TS_TRACE("Tested all scalar and matrix operations. Test suceeded");

    }

    void test2(){
      stringstream ss, kk, jj, ll;

      ss << "1 1 1"<<endl<<"2 2 2"<<endl<<"4 4 4"<<endl;
      Matris<int> one(3,3);
      ss >> one;
      Matris<int> two(one); //copy cons
      TS_ASSERT_EQUALS(one,two);

      one.insert_row(3);
      two.append_row(2);
      TS_ASSERT_EQUALS(one,two);

      one.remove_row(3);
      two.remove_row(3);
      TS_ASSERT_EQUALS(one,two);

      one.append_row(2);
      one(2,0)=3; one(2,1)=3; one(2,2)=3;

      kk << "1 1 0 1"<<endl<<"2 2 0 2"<<endl<<"3 3 0 3"<<endl<<"4 4 0 4"<<endl;
      Matris<int> three(4,4);
      kk >> three;

      Matris<int> four=one;
      four.insert_column(3);
      one.append_column(2);
      TS_ASSERT_EQUALS(one,three);
      TS_ASSERT_EQUALS(one,four);
      TS_ASSERT_EQUALS(three,four);


      two=move(one); //move assign
      two.remove_column(3);

      three.transpose();
      three.remove_row(3);
      three.transpose();

      TS_ASSERT_EQUALS(two,three);

      jj << " 0 1 1 1"<<endl<<"0 2 2 2"<<endl<<"0 3 3 3"<<endl<<"0 4 4 4"<<endl;
      Matris<int> five(4,4);
      jj >> five;
      three.insert_column(1);
      TS_ASSERT_EQUALS(three,five);

      Matris<int> six(move(five)); //move cons
      six.append_column(4);
      three.append_column(4);
      TS_ASSERT_EQUALS(three,six);

      initializer_list<int> s = {1, 2, 3, 4, 5, 6, 7, 8 , 9};

      Matris<int> squareM(s);
      ll << "1 2 3"<<endl<<"4 5 6"<<endl<<"7 8 9"<<endl;
      Matris<int> seven(3);
      ll >> seven;
      TS_ASSERT_EQUALS(squareM,seven);
      TS_TRACE("Tested all excel operations, e.g. appending/inserting/removing rows and columns. Tested Move/Copy assignment and Move/Copy cons. Test suceeded");
    }
    void test3(){
      stringstream ss,kk, sortedss;
      ss<<"34 43 677"<<endl<<"23 33 33"<<endl<<"934 2387 233"<<endl;
      Matris<int> k(3);
      ss>>k;
      k += k;
      ss<<"68 86 1354"<<endl<<"46 66 66"<<endl<<"1868 4774 466"<<endl;
      Matris<int> j(3);
      ss>>j;
      TS_ASSERT_EQUALS(k,j);

      k(0,1)=788;
      j(0,1)=67;
      int y=k(0,1); //const vers.
      TS_ASSERT_EQUALS(y,788);
      TS_ASSERT_EQUALS(j(0,1),67);
      TS_ASSERT_EQUALS(j.rows(),3);
      TS_ASSERT_EQUALS(k.cols(),3);

      sortedss<<"4774 1868 1354"<<endl<<"466 68 67"<<endl<<"66 66 46"<<endl;
      Matris<int> sortedj(3);
      sortedss>>sortedj;
      sort(j.begin(),j.end(),greater<int>());
      TS_ASSERT_EQUALS(j,sortedj);
      TS_TRACE("Tested accessor operators and iterators. Test suceeded");

    }

};
