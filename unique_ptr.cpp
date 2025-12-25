// main_sh.cpp
#include <iostream>
#include <utility>
#include "shared_ptr.hpp"   // შენი sh_ptr header (շարքային անվանումն է թեր թե՞ sh_ptr.hpp)

struct Foo {
    int v;
    Foo(int x): v(x) { std::cout << "Foo("<<v<<") կառուցված\n"; }
    ~Foo() { std::cout << "Foo("<<v<<") ոչնչացված\n"; }
    void hello() const { std::cout << "Hello from Foo("<<v<<")\n"; }
    void inc() { ++v; std::cout << "Foo հիմա " << v << '\n'; }
};

int main(){
    using std::cout; using std::endl;

    cout << "=== Ստեղծում p1 ===\n";
    sh_ptr<Foo> p1(new Foo(10));
    cout << "p1.use_count() = " << p1.use_count() << "\n";
    p1->hello();

    cout << "\n=== Կնքում copy p1 -> p2 ===\n";
    sh_ptr<Foo> p2 = p1;                // copy ctor
    cout << "p1.use_count() = " << p1.use_count() << "  p2.use_count() = " << p2.use_count() << "\n";

    cout << "\n=== Փոխատ(assign) p3 = p2 ===\n";
    sh_ptr<Foo> p3;
    p3 = p2;                            // copy assignment
    cout << "p2.use_count() = " << p2.use_count() << "  p3.use_count() = " << p3.use_count() << "\n";

    cout << "\n=== reset p2 (չի նայում object-ին եթե դեռ ուրիշներ կան) ===\n";
    p2.reset();                         // decrease count, հնարավոր է ոչ vielä delete
    cout << "p1.use_count() = " << p1.use_count() << "  p2.use_count() = " << p2.use_count() << "\n";

    cout << "\n=== Move p1 -> p4 ===\n";
    sh_ptr<Foo> p4 = std::move(p1);     // move ctor
    cout << "p4.use_count() = " << p4.use_count() << "  p1.use_count() = " << p1.use_count() << "\n";
    if (p4) p4->hello();

    cout << "\n=== swap օբյեկտների ցուցադում ===\n";
    sh_ptr<Foo> a(new Foo(1));
    sh_ptr<Foo> b(new Foo(2));
    cout << "մինչ swap: a="<< a << " (count="<< a.use_count() <<") b="<< b << " (count="<< b.use_count() <<")\n";
    a.swap(b);
    cout << "հետո swap:  a="<< a << " (count="<< a.use_count() <<") b="<< b << " (count="<< b.use_count() <<")\n";

    cout << "\n=== unique() և use_count() ստուգումներ ===\n";
    cout << "a.unique() = " << a.unique() << "  b.unique() = " << b.unique() << "\n";

    cout << "\n=== main շրջան ավարտ ===\n";
    return 0;
}
