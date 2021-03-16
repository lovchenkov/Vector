#include <chrono>
#include <iostream>

#include <deque>
#include <list>
#include <vector>

template <class T>
class Vector {
private:
    T* _data;
    int _size, _capacity;
public:
    Vector() {
        _capacity = 1;
        _size = 0;
        _data = new T[_capacity];
    }

    Vector(int n) {
        _size = n;
        _capacity = 2*n;
        _data = new T[_capacity];
    }

    Vector(int n, T base) {
        _data = new T[2*n];
        for(int i = 0; i < n; i ++){
            _data[i] = base;
        }
        _size = n;
        _capacity = 2*n;
    }

    void push_back(const T& x){
        if(_size < _capacity){
            _data[_size] = x;
            _size ++;
        }else{
            _capacity *= 2;
            T* _temp = new T[_capacity];
            for(int i = 0; i < _size; i ++){
                _temp[i] = _data[i];
            }
            _temp[_size] = x;
            if(_size > 0){
                delete _data;
            }
            _data = _temp;
            _size ++;
        }
    }

    void pop_back(){
        if(_size == 0){
            //Error
        }else{
            if(_size * 2 > _capacity){
            _size --;
        }else{
            _size --;
            _capacity /= 2;
            T* _temp = new T[_capacity];
            for(int i = 0; i < _size; i ++){
                _temp[i] = _data[i];
            }
            if(_size > 0){
                delete _data;
            }
            _data = _temp;

        }

        }
    }

    int size() {
        return _size;
    }

    int capacity() {
        return _capacity;
    }

    void resize(int n) {
        T* temp = new T[2*n];
        for(int i = 0; i < n; i ++){
            if(i < _size){
                temp[i] = _data[i];
            }else{
            }
        }
        if(_size > 0){
            delete _data;
        }
        _data = temp;
        if(_capacity < n){
            _capacity = 2*n;
        }
        _size = n;
    }

    void resize(int n, T x) {
        T* temp = new T[2*n];
        for(int i = 0; i < n; i ++){
            if(i < _size){
                temp[i] = _data[i];
            }else{
                temp[i] = x;
            }
        }
        _data = temp;
        if(_size > 0){
            delete _data;
        }
        if(_capacity < n){
            _capacity = 2*n;
        }
        _size = n;
    }


    ~Vector() {
        if(_size > 0){
            delete _data;
        }
    }

    bool empty(){
        if(_size == 0){
            return true;
        }
        return false;
    }

    T& operator[](const int i) {
        return _data[i];
    }

    T& operator[](const int i) const {
        return _data[i];
    }

    void clear(){
        if(_size > 0){
            delete _data;
            _data = new T[1];
            _size = 0;
            _capacity = 1;
        }
    }

    void reserve(int n){
        _capacity = 2*n;
    }

};

template <class T>
int benchmark_vector(Vector<T>& c)
{
    const int N = 1000000;

    int res = 0;

    for (int j = 0; j < 20; ++j)
    {
        for (int i = 0; i < N / 2; ++i)
        {
            c.push_back(i + j);
        }

        for (int i = 0; i < c.size(); ++i)
        {
            res += c[i];
        }

        c.resize(N / 4);

        for (int i = 0; i < c.size(); ++i)
        {
            res += c[i];
        }

        c.resize(N);

        for (int i = 0; i < c.size(); ++i)
        {
            res += c[i];
        }

        for (int i = 0; i < N / 2; ++i)
        {
            c.pop_back();
        }

        for (int i = 0; i < c.size(); ++i)
        {
            res += c[i];
        }

        for (int i = 0; i < N / 2; ++i)
        {
            c.push_back(i + j);
        }

        for (int i = 0; i < c.size(); ++i)
        {
            res += c[i];
        }

        c.clear();
    }

    return res;
}

template <class T>
int benchmark(T& c)
{
    const int N = 1000000;

    int res = 0;

    for (int j = 0; j < 20; ++j)
    {
        for (int i = 0; i < N / 2; ++i)
        {
            c.push_back(i + j);
        }

        for (int i : c)
        {
            res += i;
        }

        c.resize(N / 4);

        for (int i : c)
        {
            res += i;
        }

        c.resize(N);

        for (int i : c)
        {
            res += i;
        }

        for (int i = 0; i < N / 2; ++i)
        {
            c.pop_back();
        }

        for (int i : c)
        {
            res += i;
        }

        for (int i = 0; i < N / 2; ++i)
        {
            c.push_back(i + j);
        }

        for (int i : c)
        {
            res += i;
        }

        c.clear();
    }

    return res;
}

template <class X, class Y>
void doCheckEqual(const X& actual, const Y& expected, size_t line)
{
    if (actual != expected)
    {
        std::cout << "at line " << line << ": " << actual << " != " << expected << '\n';
    }
}

#define checkEqual(x, y) do { doCheckEqual((x), (y), __LINE__); } while(0)
#define checkTrue(cond) do { if (!(cond)) std::cout << "at line " << __LINE__ << ": " << #cond << '\n'; } while(0)

class Timer
{
public:
    Timer()
        : start_(std::chrono::high_resolution_clock::now())
    {
    }

    ~Timer()
    {
        const auto finish = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};

int main()
{
    {
        Vector<int> v;

        checkTrue(v.empty());
        checkEqual(v.size(), 0);

        v.push_back(1);

        checkTrue(!v.empty());
        checkEqual(v.size(), 1);
        checkEqual(v[0], 1);

        v.pop_back();

        checkTrue(v.empty());
        checkEqual(v.size(), 0);

        v.push_back(3);
        v.push_back(2);
        v.push_back(1);

        checkTrue(!v.empty());
        checkEqual(v.size(), 3);
        checkEqual(v[0], 3);
        checkEqual(v[1], 2);
        checkEqual(v[2], 1);

        v.reserve(10000);
        checkEqual(v.size(), 3);
        checkTrue(v.capacity() >= 10000);

        const auto c = v.capacity();

        v.resize(2);
        checkEqual(v.size(), 2);
        checkEqual(v.capacity(), c);
        checkEqual(v[0], 3);
        checkEqual(v[1], 2);

        v.resize(3);
        checkEqual(v.size(), 3);
        checkEqual(v.capacity(), c);
        checkEqual(v[0], 3);
        checkEqual(v[1], 2);
    }

    int res = 0;

    {
        std::vector<int> v;
        res += benchmark(v);
    }

    {
        std::cout << "Vector<int>: ";
        Timer t;
        Vector<int> v;
        res += benchmark_vector(v);
    }

    {
        std::cout << "std::vector<int>: ";
        Timer t;
        std::vector<int> v;
        res += benchmark(v);
    }

    {
        std::cout << "std::deque<int>: ";
        Timer t;
        std::deque<int> v;
        res += benchmark(v);
    }

    {
        std::cout << "std::list<int>: ";
        Timer t;
        std::list<int> v;
        res += benchmark(v);
    }

    return res;
}
