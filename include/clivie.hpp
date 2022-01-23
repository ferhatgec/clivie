// MIT License
//
// Copyright (c) 2022 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#ifndef CLIVIE_CLIVIE_HPP
#define CLIVIE_CLIVIE_HPP

#include <iostream>
#include <string>
#include "../libs/climage/include/climage.hpp"

class clivie {
    std::string file_data;
    climage parse;
public:
    unsigned res_x = 128, res_y = 128, scale = 16;
public:
    clivie() = default; ~clivie() = default;

    void run(std::string const file_name) noexcept;
};

#endif // CLIVIE_CLIVIE_HPP
