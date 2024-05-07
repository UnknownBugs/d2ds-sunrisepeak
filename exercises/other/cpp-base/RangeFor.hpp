#ifndef RANGE_BASE_FOR_HPP_D2DS
#define RANGE_BASE_FOR_HPP_D2DS

#include <common/common.hpp>

namespace d2ds {
// show your code

class PyRange {
public:
    PyRange(int start, int stop, int step = 1) {

        mLen_e =  (stop - start) / step;

        d2ds_assert(start < stop);
        d2ds_assert(step > 0);
        d2ds_assert(mLen_e <= 100);

        for (int i = 0; i < mLen_e; i++) {
            mArr_e[i] = start;
            start = start + step;
        }
    }

public:
    const int * begin() const {
        return mArr_e;
    }

    const int * end() const {
        return mArr_e + mLen_e;
    }

private:
    int mLen_e;
    int mArr_e[100];
};


}

#endif