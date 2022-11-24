//
// Created by Konstantin on 2022/11/24.
//

#pragma once
#include <iostream>

namespace gbtl {
    template<typename T, size_t length> class vector {
    private:
        size_t m_Size;
        T ma_Components[length];
    };
}