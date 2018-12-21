#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
#include <crtdbg.h>

#include "VectorLabb\Vector.h"
#include <cassert>

using std::cout;

template <class T>
struct IsConstOrConstRef {
    static const bool value = std::is_const<std::remove_reference<T>::type>::value;
};

template <class T>
bool IsConstOrConstRefFun(T& x) {
    return std::is_const<std::remove_reference<T>::type>::value;
};

void AssertStrEqual(Vector<char>& lhs, const char* rhs) {
    size_t i;
    for (i = 0; i < lhs.getSize() && *rhs != '\0'; ++i) {
        assert(lhs[i] == rhs[i]);
        assert(rhs[i] != 0);
    }
    assert(i == lhs.getSize() && rhs[i] == '\0');
    assert(rhs[lhs.getSize()] == 0);
}

void TestPushBackReallocation() {
    Vector<char> vec("hej");
    assert(vec.getSize() <= vec.getCapacity());
    assert(vec.getSize() == 3);
    AssertStrEqual(vec, "hej");
    //we try to take 20 empty places: (size+1 < capacity)
    while (vec.getSize() + 20 >= vec.getCapacity() && vec.getSize() < 1000)
        vec.push_back('A' + rand() % 32);
    assert(vec.getSize() < 1000);	//If this fail it prbably the case that capacity is increased with a constant.

    auto internalBuf = &vec[0];
    auto cap = vec.getCapacity();
    auto siz = vec.getSize();
    size_t i;
    for (i = siz + 1; i <= cap; ++i) {
        vec.push_back(char(i) + 'a');
        assert(internalBuf == &vec[0]);
        assert(cap == vec.getCapacity());
        assert(i == vec.getSize());
    }
    vec.push_back(char(i));
    assert(internalBuf != &vec[0]);
    assert(cap < vec.getCapacity());
    assert(i == vec.getSize());
}

template<class C>
void TestRel(const C& lhs, const C& rhs,
    bool(*trueFun)(const C& lhs, const C& rhs),
    bool(*falseFun)(const C& lhs, const C& rhs)) {
    assert(trueFun(lhs, vhs));
    assert(falseFun(lhs, vhs));
}


void TestgetCapacity() {
    Vector<char> vecBar("Bar");
    const Vector<char> vecBarC("Bar");

    //-	getSize(), getCapacity() and reloccation test;
    TestPushBackReallocation();


    //	reserve()
    auto internalBuf = &vecBar[0];
    auto cap = vecBar.getCapacity();
    auto siz = vecBar.getSize();

	cout << "(" << cap << " | " << vecBar.getCapacity() << ")" << endl;
    vecBar.reserve(cap);
	cout << "(" << (int)internalBuf << " == " << (int)&vecBar[0] << " : " << (internalBuf == &vecBar[0]) << endl;
    assert(internalBuf == &vecBar[0]);
    assert(cap == vecBar.getCapacity());
    assert(siz == vecBar.getSize());

    vecBar.reserve(cap + 1);
    assert(internalBuf != &vecBar[0]);
    assert(cap < vecBar.getCapacity());
    assert(siz == vecBar.getSize());

    // shrink_to_fit
    vecBar = "hej";
    vecBar.reserve(10);
    internalBuf = &vecBar[0];
    cap = vecBar.getCapacity();
    siz = vecBar.getSize();

    vecBar.shrink_to_fit();
    assert(internalBuf != &vecBar[0]);
    assert(vecBar.getCapacity() == vecBar.getSize());
    //    AssertStrEqual(str, "hej");

    cout << "\nTestFörVälGodkänt klar\n";
}

void TestVector() {
    {
        Vector<char> vecFoo("Foo");
        const Vector<char> vecCFoo("Foo");
        Vector<char> vecBar("Bar");
        const Vector<char> vecBarC("Bar");
    }

    //-	Vector<char>()
    {
        Vector<char> vec0;	AssertStrEqual(vec0, "");
    }

    //Move constructor
    {
        Vector<char> a("foo");
        Vector<char> b(std::move(a));
        assert(b == "foo" && a.data() == nullptr);
    }

    //-	Vector<char>(char *)
    {
        Vector<char> v1("foo"); assert(v1 == "foo");
        Vector<char> vec(v1); assert(vec == "foo");
        Vector<char> v3("bar");  assert(v3 == "bar");
    }
    //-	Vector<char>(Copy constructor)
    {
        Vector<char> v1("foo"); assert(v1 == "foo");
        Vector<char> vecBar(v1); assert(vecBar == "foo");
        Vector<char> v3("bar");  assert(v3 == "bar");

        //-	~Vector<char>() Kom ihåg destruktorn!
        delete new Vector<char>("hej");

        //	-	operator =(Sträng sträng)
        vecBar = "hej";
        assert((vecBar = v3) == v3);
        assert((vecBar = vecBar) == v3);	//self assignment

                                            //Ej samma buffert
        vecBar = "hej";
        v3 = vecBar;
        vecBar[0] = 'x';
        assert(v3[0] == 'h');
        v3[1] = 'y'; assert(vecBar[1] == 'e');


        Vector<char> vec1("foo"), vec2("bar"), vec3("hej");
        vec3 = vecBar = vec1;
        assert(vec3 == vecBar);
        assert(vec1 == vecBar);

        //No extra realloc
        AssertStrEqual(vec1, "foo");
        auto xxx = vec1.data();
        Vector<char> tempRealloc("huj");
        vec1 = tempRealloc;
        assert(xxx == vec1.data());

    }
    //-	operator[](size_t i) som indexerar utan range check.
    {
        Vector<char> vecFoo("Foo");
        const Vector<char> vecCFoo("Foo");
        Vector<char> vecBar("Bar");
        const Vector<char> vecBarC("Bar");


        vecBar = "bar";
        vecBar[-1]; vecBar[1000];	//No error
        assert(vecBar[1] == 'a');
        vecBar[1] = 'y';
        assert(vecBar[1] == 'y');

        //-	operator[](size_t i) const.

        assert(IsConstOrConstRefFun(vecBarC[1]));
        assert(vecBarC[1] == 'a');
    }
    //-	at(size_t i) som indexerar med range check
    {
        Vector<char> vecBar("Bar");
        const Vector<char> vecBarC("Bar");

        try {
            vecBar.at(-1);
            assert(false);
        }
        catch (std::out_of_range&) {};
        try {
            vecBar.at(3);
            assert(false);
        }
        catch (std::out_of_range&) {};

        //- at indexerar

        //-	at(size_t i) 
        vecBar = "bar";
        assert(vecBar.at(1) == 'a');
        vecBar.at(1) = 'y';
        assert(vecBar.at(1) == 'y');

        assert(vecBarC.at(1) == 'a');
        assert(IsConstOrConstRefFun(vecBarC.at(1)));
    }

    // data
    {
        Vector<char> vecBar("Bar");
        const Vector<char> vecBarC("Bar");

        assert(vecBar.data() == &vecBar[0]);
        assert(!IsConstOrConstRefFun(*vecBar.data()));
        assert(IsConstOrConstRefFun(*vecBarC.data()));
    }

    //-	push_back(char c) lägger till ett tecken sist.
    {
        Vector<char> vecBar("Bar");
        const Vector<char> vecBarC("Bar");

        vecBar.push_back('a');
        assert(vecBar == "Bara");
    }


    // resize
    {
        Vector<char> vecBar("Bar");
        const Vector<char> vecBarC("Bar");
        //size up
        vecBar.shrink_to_fit();
        auto buf = vecBar.data();
        vecBar.resize(6);
		//cout << vecBar[4] << endl << "(" << vecBar.getSize() << " | " << vecBar.getCapacity() << ")" << endl; 
        assert(vecBar[2] == 'r' && vecBar[3] == 0 && vecBar[4] == 0 && vecBar[5] == 0);
        assert(buf != vecBar.data() && vecBar.getCapacity() >= 6 && vecBar.getSize() == 6);
        buf = vecBar.data();
        vecBar.resize(5);
        assert(buf == vecBar.data() && vecBar.getCapacity() >= 6 && vecBar.getSize() == 5);
    }

    //-	operator== 
    //testas överallt!

    {
#define RelTest(a, b, c, d)  a c b && !(a d b)

        Vector<char> vecAbcdef("Abcdef");
        Vector<char> vecBbcdef("Bbcdef");
        Vector<char> vecAbcdeF("AbcdeF");
        Vector<char> vecAbcdefg("Abcdefg");

		Vector<char> lol1("1234");
		Vector<char> lol2("1234");
		Vector<char> lol3("12345");
		Vector<char> lol4("1235");

		cout << lol1 << " == " << lol2 << " : " << (lol1 == lol2) << endl;
		cout << lol1 << " == " << lol3 << " : " << (lol1 == lol3) << endl;
		cout << lol1 << " == " << lol4 << " : " << (lol1 == lol4) << endl;

        { bool f = RelTest(vecAbcdef, vecAbcdef, == , != ); assert(f); }
        { bool f = RelTest(vecAbcdef, vecAbcdeF, != , == ); assert(f); }
        { bool f = RelTest(vecAbcdef, vecBbcdef, != , == ); assert(f); }
        { bool f = RelTest(vecAbcdef, vecAbcdefg, != , == ); assert(f); }
        { bool f = RelTest(vecAbcdefg, vecAbcdef, != , == ); assert(f); }

        { bool f = RelTest(vecAbcdef, vecAbcdef, == , <); assert(f); }
        { bool f = RelTest(vecAbcdef, vecAbcdeF, >, <); assert(f); }
        { bool f = RelTest(vecAbcdef, vecBbcdef, <, >); assert(f); }
        { bool f = RelTest(vecAbcdef, vecAbcdefg, <, >); assert(f); }

        { bool f = RelTest(vecAbcdef, vecAbcdef, <= , != ); assert(f); }
        { bool f = RelTest(vecAbcdef, vecAbcdeF, >= , <= ); assert(f); }
        { bool f = RelTest(vecAbcdef, vecBbcdef, <= , >= ); assert(f); }
        { bool f = RelTest(vecAbcdef, vecAbcdefg, <= , >= ); assert(f); }

        swap(vecAbcdef, vecAbcdefg);
        assert(vecAbcdef == "Abcdefg");
        assert(vecAbcdefg == "Abcdef");
    }

    TestgetCapacity();
}



