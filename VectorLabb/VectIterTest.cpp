#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
#include <crtdbg.h>

#include "VectorLabb\Vector.h"

#include <assert.h>

#include <iostream>
using std::cout;
using std::endl;

#include <algorithm>
//#include "Alg.hpp"

void TestIterInAlg() {

    static const int N = 26;
    Vector<char> v;
    v.reserve(N);
    for (int i = 0; i < N; ++i) {
        v.push_back('a' + i);
    }
    auto b = std::begin(v);
    auto e = std::end(v);

    std::random_shuffle(b, e);

    cout << v << endl;
    //std::stable_sort(b, e);
    std::sort(b, e);

    cout << v << endl;
}


/*	*it, ++it, it++, (it+i), it[i], == och !=	*/
void TestIterPart() {
    Vector<char> vecFooBar("FooBar");
    for (auto i = vecFooBar.begin(); i != vecFooBar.end(); i++)
        cout << *i;
    cout << " står det FooBar?" << endl;
    //    vecBar = "raboof";
    auto it = vecFooBar.begin();
    assert(*it == 'F');
    assert(*(it++) == 'F' && *it == 'o');
    *(++it) = 'y';
    assert(*++it == 'B');
    assert(*(it + 1) == 'a');
    assert(it[2] == 'r');
}


void TestFörGodkäntIter() {

    //-	typdefs för iterator
    Vector<char>::iterator iter;
    Vector<char> vec("hej");
    iter = vec.begin();

    //-	funktionerna begin, end.
    TestIterPart();

    //Iteratorerna ska kunna göra:
    //-	*it, ++it, it++, (it+i), it[i], == och !=
    // Här saknas en massa tester, jag provar bara att de finns!
    ++iter++;
    iter + (*iter) - (iter-iter);

    //-	default constructor, copy constructor och tilldelning (=) 
    Vector<char> s("foobar");
    iter = s.begin();
    *iter = 'a';
    assert(s == "aoobar");

}

