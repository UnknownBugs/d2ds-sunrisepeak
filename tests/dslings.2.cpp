// dslings.2.cpp - readonly
//
// 描述:
//  通过实现一个MaxVal类型(保存最大值), 来介绍dslings的"编译器驱动开发"
//  即根据编译器的错误提示来完成这个训练流程的演示Demo, 并且通常为了降低难度会把一个'数据结构'的实现分成多个检测模块.
//  如: dslings.0.cpp dslings.1.cpp dslings.2.cpp
//
// 目标/要求:
//  - 不修改该代码检测文件
//  - 在exercises/dslings.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include <tests/common.hpp>
#include <exercises/dslings.hpp>

int main() {

    d2ds::MaxValue mVal(2);

    d2ds_assert_eq(mVal.get(), 2);

    mVal.set(-1);
    d2ds_assert_eq(mVal.get(), 2);

    mVal.set(100);
    d2ds_assert_eq(mVal.get(), 100);

// random test
    dstruct::Array<int, 10> data;
    d2ds::randomDataGenerator(data, 0, 200);
    d2ds::ds_print(data);

    int maxVal = 0;
    for (int i = 0; i < data.size(); i++) {
        mVal.set(data[i]);
        if (data[i] > maxVal) {
            maxVal = data[i];
        }
    }

    d2ds_assert_eq(mVal.get(), maxVal);

    return 0;
}