#ifndef TEMPLATE_HPP_D2DS
#define TEMPLATE_HPP_D2DS

namespace d2ds {
// show your code

template <typename T>
T max(T a, T b) {
    return a > b ? a : b; 
}

template <typename T>
class Box {
public:
    Box() : mVal_e{} { }

    T get_value() const {
        return mVal_e;
    }

    void set_value(const T &val) {
        mVal_e = val;
    }

private:
    T mVal_e;
};


}

#endif