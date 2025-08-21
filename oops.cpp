// C++ OOP — from Basics to Advanced (single-file, commented playground)
// ---------------------------------------------------------------------
// HOW TO USE
//   • Compile:   g++ -std=c++17 -Wall -Wextra -pedantic main.cpp && ./a.out
//   • Purpose:   One self-contained file that DEMOS most OOP features in C++
//   • Style:     Every topic has short NOTES above it. Outputs show what happens.
//   • Tip:       Read top-to-bottom and run often. Tweak values to experiment.
//
// Covered topics (high-level):
//   1) Scope resolution operator :: (global, namespace, class static, base-qualifying)
//   2) Classes & objects, encapsulation, access specifiers
//   3) Constructors (default/param/copy/move), initializer lists, destructors
//   4) Rule of 3/5/0, copy vs. move, assignment operators
//   5) const-correctness, mutable, this pointer, method chaining
//   6) friend functions/classes
//   7) Inheritance (public/protected/private), overriding, virtual, override/final, virtual dtor
//   8) Abstract classes & interfaces (pure virtual)
//   9) Dynamic polymorphism (virtual dispatch) + RTTI (typeid, dynamic_cast)
//  10) Multiple inheritance & virtual inheritance (diamond)
//  11) Operator overloading (+, -, *, /, <<, >>, ==, <, explicit conversions)
//  12) Composition vs Aggregation vs Association
//  13) RAII & smart pointers (unique_ptr/shared_ptr/weak_ptr), enable_shared_from_this
//  14) Nested classes, pointer-to-member functions
//  15) Ref-qualifiers for member functions (& and &&)
//  16) Static polymorphism (CRTP) — OOP-adjacent pattern
//  17) Exceptions in ctors/dtors (noexcept dtor), basic guidelines
//  18) enum class vs old enum (scoped)
//  19) Iterators with scope resolution of nested types
//
// NOTE: This file is dense by design—aimed at revision + exploration.
//       It does not replace a full textbook, but it touches almost all OOP levers you’ll use in practice.

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>
#include <typeinfo>
#include <stdexcept>
#include <cstdio>
using namespace std;

// ---------------------------------------------------------------
// 1) SCOPE RESOLUTION OPERATOR '::'
//    • Access a global that is shadowed by a local
//    • Access names inside a namespace
//    • Refer to class static members
//    • Qualify a base-class function from a derived object
// ---------------------------------------------------------------
int gx = 7; // global variable

namespace DemoNS { int value = 42; }

class Foo {
public:
    static int sx;           // declaration of static data member
    void bar();              // member function declared
};
int Foo::sx = 100;           // definition of static data member (once)
void Foo::bar() {            // definition using scope resolution
    cout << "Foo::bar() called\n";
}

class BaseSR {
public: void func(){ cout << "BaseSR::func()\n"; } };
class DerivedSR : public BaseSR {
public: void func(){ cout << "DerivedSR::func()\n"; } };

// ---------------------------------------------------------------
// 2) ENCAPSULATION + RULE OF 5 + CONST-CORRECTNESS + FRIEND + CHAINING
//    • Private data, getters/setters, friend for streaming
//    • Full special member set: copy/move ctor, copy/move assign, dtor
//    • const methods can be called on const objects
//    • this-pointer used to chain calls
// ---------------------------------------------------------------
class Point {
    double x_, y_;
    static int live_; // how many live objects
public:
    // ctors
    Point() : x_(0), y_(0) { ++live_; }
    Point(double x, double y) : x_(x), y_(y) { ++live_; }
    Point(const Point& o) : x_(o.x_), y_(o.y_) { ++live_; }
    Point(Point&& o) noexcept : x_(o.x_), y_(o.y_) { o.x_ = o.y_ = 0; ++live_; }

    // assignments
    Point& operator=(const Point& o) { if(this!=&o){ x_=o.x_; y_=o.y_; } return *this; }
    Point& operator=(Point&& o) noexcept { if(this!=&o){ x_=o.x_; y_=o.y_; o.x_=o.y_=0; } return *this; }

    ~Point(){ --live_; }

    // getters are const-correct
    double x() const { return x_; }
    double y() const { return y_; }

    // setters
    void set_x(double x){ x_ = x; }
    void set_y(double y){ y_ = y; }

    // method chaining using *this
    Point& translate(double dx, double dy){ x_ += dx; y_ += dy; return *this; }

    static int live() { return live_; }

    friend ostream& operator<<(ostream& os, const Point& p){ return os << '(' << p.x_ << ',' << p.y_ << ')'; }
};
int Point::live_ = 0;

// ---------------------------------------------------------------
// 3) CONST + MUTABLE: read-only methods that can update caches/counters
// ---------------------------------------------------------------
class Counter {
    int value_;
    mutable int calls_ = 0; // mutable permits modification in const methods (use sparingly!)
public:
    explicit Counter(int v=0): value_(v){}
    int value() const { ++calls_; return value_; }
    int calls() const { return calls_; }
    void inc(){ ++value_; }
};

// ---------------------------------------------------------------
// 4) FRIEND FUNCTIONS / CLASSES: controlled escape hatch to private
// ---------------------------------------------------------------
class SecretBox {
    string secret_ = "s3cr3t";
    friend class FriendPeek;        // grants FriendPeek access to private
    friend void reveal(const SecretBox&); // grants a free function access
public:
    string masked() const { return string(secret_.size(),'*'); }
};
class FriendPeek { public: string peek(const SecretBox& b){ return b.secret_; } };
void reveal(const SecretBox& b){ cout << "reveal(): " << b.secret_ << '\n'; }

// ---------------------------------------------------------------
// 5) ABSTRACT CLASSES (pure virtual) + VIRTUAL DESTRUCTOR
//    • Interface-like base with pure virtual function(s)
//    • Always make base destructors virtual if deleting via base pointer
// ---------------------------------------------------------------
class Animal {
public:
    virtual ~Animal() = default;   // ensure proper cleanup via base*
    virtual string speak() const = 0; // pure virtual => abstract
};
class Dog : public Animal { public: string speak() const override { return "woof"; } };
class Cat : public Animal { public: string speak() const override { return "meow"; } };

// ---------------------------------------------------------------
// 6) MULTIPLE INHERITANCE — implementing multiple interfaces
// ---------------------------------------------------------------
struct ISerializable { virtual ~ISerializable()=default; virtual string serialize() const = 0; };
struct IPrintable   { virtual ~IPrintable()=default;   virtual void print(ostream&) const = 0; };

class User : public ISerializable, public IPrintable {
    string name_; int age_{};
public:
    User(string name, int age): name_(move(name)), age_(age) {}
    string serialize() const override { return string("{\"name\":\"")+name_+"\",\"age\":"+to_string(age_)+"}"; }
    void print(ostream& os) const override { os << "User("<<name_<<","<<age_<<")"; }
};

// ---------------------------------------------------------------
// 7) VIRTUAL INHERITANCE (diamond) — one shared base subobject
//    • Without 'virtual', Base would appear twice causing ambiguity
//    • With 'virtual', only one Base part exists in the most-derived
// ---------------------------------------------------------------
class VBase {
public:
    int id{0};
    VBase(){ cout << "VBase()\n"; }
    virtual ~VBase(){ cout << "~VBase()\n"; }
};
class Left  : virtual public VBase { public: Left(){  cout << "Left()\n";  } ~Left(){  cout << "~Left()\n";  } };
class Right : virtual public VBase { public: Right(){ cout << "Right()\n"; } ~Right(){ cout << "~Right()\n"; } };
class Diamond : public Left, public Right { public: Diamond(){ cout << "Diamond()\n"; } ~Diamond(){ cout << "~Diamond()\n"; } };

// ---------------------------------------------------------------
// 8) OPERATOR OVERLOADING — Rational number demo
//    • Arithmetic, comparison, stream << >>, explicit conversion to double
// ---------------------------------------------------------------
class Rational {
    long long num_, den_;
    void normalize(){
        long long g = std::gcd(num_, den_);
        if(g) { num_ /= g; den_ /= g; }
        if(den_ < 0) { den_ = -den_; num_ = -num_; }
    }
public:
    Rational(long long n=0, long long d=1): num_(n), den_(d){ if(den_==0) throw invalid_argument("den=0"); normalize(); }
    // leave copy/move as defaults — rule of 0 works here

    friend Rational operator+(const Rational& a, const Rational& b){ return Rational(a.num_*b.den_ + b.num_*a.den_, a.den_*b.den_); }
    friend Rational operator-(const Rational& a, const Rational& b){ return Rational(a.num_*b.den_ - b.num_*a.den_, a.den_*b.den_); }
    friend Rational operator*(const Rational& a, const Rational& b){ return Rational(a.num_*b.num_, a.den_*b.den_); }
    friend Rational operator/(const Rational& a, const Rational& b){ if(b.num_==0) throw domain_error("divide by zero"); return Rational(a.num_*b.den_, a.den_*b.num_); }

    friend bool operator==(const Rational& a, const Rational& b){ return a.num_==b.num_ && a.den_==b.den_; }
    friend bool operator<(const Rational& a, const Rational& b){ return a.num_*b.den_ < b.num_*a.den_; }

    friend ostream& operator<<(ostream& os, const Rational& r){ return os << r.num_ << "/" << r.den_; }
    friend istream& operator>>(istream& is, Rational& r){ char slash; long long n,d; if(is>>n>>slash>>d && slash=='/'){ r = Rational(n,d);} else is.setstate(ios::failbit); return is; }

    explicit operator double() const { return static_cast<double>(num_) / static_cast<double>(den_); }
};

// ---------------------------------------------------------------
// 9) COMPOSITION vs AGGREGATION vs ASSOCIATION
//    • Car owns Engine (composition) — destroyed together
//    • House refers to Person (aggregation) — does not manage lifetime
// ---------------------------------------------------------------
class Engine { public: void start(){ cout << "Engine started\n"; } };
class Car {
    unique_ptr<Engine> engine_; // composition: strong ownership
public:
    Car(): engine_(make_unique<Engine>()) {}
    void start(){ engine_->start(); }
};

class Person; // fwd
class House {  // aggregation: has-a Person*, but doesn't own it
    Person* owner_ = nullptr;
public:
    void setOwner(Person* p){ owner_ = p; }
    void showOwner();
};
class Person {
    string name_;
public:
    explicit Person(string n): name_(move(n)){}
    string name() const { return name_; }
};
inline void House::showOwner(){ cout << "House owner: " << (owner_? owner_->name(): string("none")) << '\n'; }

// ---------------------------------------------------------------
// 10) RAII + SMART POINTERS + enable_shared_from_this
//     • Manage resources via objects; destructors release automatically
// ---------------------------------------------------------------
struct FileCloser { void operator()(FILE* f) const { if(f) fclose(f); } };

class Logger : public enable_shared_from_this<Logger> {
    string name_;
    Logger(string n): name_(move(n)){}
public:
    static shared_ptr<Logger> create(string n){ return shared_ptr<Logger>(new Logger(move(n))); }
    void log(const string& msg){ cout << '[' << name_ << "] " << msg << '\n'; }
    shared_ptr<Logger> self(){ return shared_from_this(); }
};

// ---------------------------------------------------------------
// 11) NESTED CLASSES
// ---------------------------------------------------------------
class Outer {
public:
    class Inner {
        int v_;
    public:
        explicit Inner(int v): v_(v){}
        int get() const { return v_; }
    };
};

// ---------------------------------------------------------------
// 12) POINTER TO MEMBER FUNCTIONS
// ---------------------------------------------------------------
struct Button { void click(){ cout << "Button clicked\n"; } };
using PMF = void (Button::*)();
inline void call(Button& b, PMF f){ (b.*f)(); }

// ---------------------------------------------------------------
// 13) REF-QUALIFIERS (& and &&) — choose overload based on value category
// ---------------------------------------------------------------
class Buffer {
    vector<int> data_;
public:
    Buffer() = default;
    explicit Buffer(vector<int> v): data_(move(v)){}
    // rule of 0: let defaults handle special members

    string summary() const &  { return "Buffer(size=" + to_string(data_.size()) + ") lvalue"; }
    string summary() &&       { return "Buffer(size=" + to_string(data_.size()) + ") rvalue"; }
};

// ---------------------------------------------------------------
// 14) STATIC POLYMORPHISM (CRTP) — no virtual, compile-time dispatch
// ---------------------------------------------------------------
template <class Derived>
class ShapeStatic {
public:
    double area() const { return static_cast<const Derived*>(this)->area_impl(); }
};
class SquareStatic : public ShapeStatic<SquareStatic> {
    double s_{};
public:
    explicit SquareStatic(double s): s_(s){}
    double area_impl() const { return s_ * s_; }
};

// ---------------------------------------------------------------
// 15) EXCEPTIONS in CTOR / NOEXCEPT DTOR
// ---------------------------------------------------------------
class MightThrow {
    vector<int> big_;
public:
    MightThrow(size_t n){ big_.resize(n); /* may throw bad_alloc */ }
    ~MightThrow() noexcept { /* never throw from destructors */ }
};

// ---------------------------------------------------------------
// 16) ENUM CLASS (scoped enum) — avoids name pollution & implicit int
// ---------------------------------------------------------------
enum class Color { Red, Green, Blue };
string to_string(Color c){ switch(c){ case Color::Red: return "Red"; case Color::Green: return "Green"; case Color::Blue: return "Blue";} return "?"; }

int main(){
    cout << "\n==== 1) Scope Resolution Operator :: ====" << '\n';
    int gx = 10; // local shadows global
    cout << "Global gx via ::gx => " << ::gx << '\n';
    cout << "Namespace DemoNS::value => " << DemoNS::value << '\n';

    vector<int> arr{1,2,3};
    vector<int>::iterator it = arr.begin(); // nested type via ::
    cout << "First element via iterator => " << *it << '\n';

    Foo f; f.bar();
    cout << "Foo::sx => " << Foo::sx << '\n';

    DerivedSR dsr; dsr.BaseSR::func(); dsr.func();

    cout << "\n==== 2) Point (encapsulation, Rule of 5, chaining) ====" << '\n';
    Point p1; Point p2(3,4); Point p3 = p2; Point p4 = move(p2);
    cout << "live Points => " << Point::live() << '\n';
    cout << "p3 => " << p3 << ", p4 => " << p4 << '\n';
    p4.translate(1, -2).translate(0.5, 0.5); cout << "p4 after chain => " << p4 << '\n';

    cout << "\n==== 3) const + mutable ====" << '\n';
    const Counter c(5); cout << "c.value() => " << c.value() << ", calls() => " << c.calls() << '\n';

    cout << "\n==== 4) friend demo ====" << '\n';
    SecretBox box; FriendPeek peek;
    cout << "masked => " << box.masked() << '\n';
    cout << "FriendPeek.peek => " << peek.peek(box) << '\n';
    reveal(box);

    cout << "\n==== 5) Abstract + virtual dtor + dynamic polymorphism ====" << '\n';
    vector<unique_ptr<Animal>> zoo;
    zoo.emplace_back(make_unique<Dog>());
    zoo.emplace_back(make_unique<Cat>());
    for(const auto& a : zoo) cout << "Animal says => " << a->speak() << '\n';

    cout << "\n==== 6) Multiple inheritance (interfaces) ====" << '\n';
    User u{"Ada", 30};
    cout << "serialize => " << u.serialize() << '\n';
    cout << "print => "; u.print(cout); cout << '\n';

    cout << "\n==== 7) Virtual inheritance (diamond) ====" << '\n';
    {
        Diamond dia;           // watch construction order
        dia.id = 99;           // single shared VBase subobject
        cout << "dia.id => " << dia.id << '\n';
    } // watch destruction order

    cout << "\n==== 8) Operator overloading (Rational) ====" << '\n';
    Rational r1(1,3), r2(2,5);
    cout << "r1 => " << r1 << ", r2 => " << r2 << '\n';
    cout << "r1 + r2 => " << (r1 + r2) << '\n';
    cout << "r1 * r2 => " << (r1 * r2) << '\n';
    cout << "(double)r1 => " << static_cast<double>(r1) << '\n';

    cout << "\n==== 9) Composition vs Aggregation ====" << '\n';
    Car car; car.start();
    Person alice{"Alice"}; House h; h.setOwner(&alice); h.showOwner();

    cout << "\n==== 10) RAII + smart pointers ====" << '\n';
    auto log = Logger::create("main"); log->log("hello world");
    weak_ptr<Logger> weak = log;
    cout << "weak.expired()? => " << boolalpha << weak.expired() << '\n';
    log.reset();
    cout << "after reset, weak.expired()? => " << weak.expired() << '\n';

    // File RAII (commented to avoid filesystem writes in some environments)
    // unique_ptr<FILE, FileCloser> fp(fopen("demo.txt","w"));
    // if(fp) fprintf(fp.get(), "RAII file write\n");

    cout << "\n==== 11) Nested classes ====" << '\n';
    Outer::Inner inner{123};
    cout << "Inner.get() => " << inner.get() << '\n';

    cout << "\n==== 12) Pointer to member functions ====" << '\n';
    Button b; PMF pmf = &Button::click; call(b, pmf);

    cout << "\n==== 13) Ref-qualifiers (&, &&) ====" << '\n';
    Buffer buf(vector<int>{1,2,3});
    cout << "lvalue call => " << buf.summary() << '\n';
    cout << "rvalue call => " << Buffer(vector<int>{4,5}).summary() << '\n';

    cout << "\n==== 14) Static polymorphism (CRTP) ====" << '\n';
    SquareStatic sq(5.0); cout << "SquareStatic.area() => " << sq.area() << '\n';

    cout << "\n==== 15) Exceptions in ctor / noexcept dtor ====" << '\n';
    try{ MightThrow mt(1'000'000); cout << "MightThrow constructed.\n"; }
    catch(const bad_alloc&){ cout << "Allocation failed in ctor.\n"; }

    cout << "\n==== 16) enum class ====" << '\n';
    Color c = Color::Green; cout << "Color => " << to_string(c) << '\n';

    // Bonus: RTTI demo with dynamic_cast/typeid
    cout << "\n==== Bonus: RTTI (typeid / dynamic_cast) ====" << '\n';
    Animal* a = new Dog; cout << "typeid(*a).name() => " << typeid(*a).name() << ", speak => " << a->speak() << '\n';
    if(auto d = dynamic_cast<Dog*>(a)) cout << "dynamic_cast to Dog* OK\n"; else cout << "dynamic_cast failed\n";
    delete a;

    cout << "\n(All demos done.)\n";
    return 0;
}
