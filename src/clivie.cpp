// MIT License
//
// Copyright (c) 2022 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#include <fstream>
#include "../include/clivie.hpp"
#include "../libs/sdl4cpp/sdl4cpp/sdl4.hpp"
#include "../libs/sdl4cpp/sdl4cpp/video.hpp"
#include "../libs/sdl4cpp/sdl4cpp/timer.hpp"

void clivie::run(std::string const file_name) noexcept {
    std::ifstream stream(file_name);

    for(std::string temp; std::getline(stream, temp);
        this->file_data.append(temp + "\n")); stream.close();

    this->parse.parse(this->file_data);

    sdl4::video::window::window wnd;
    sdl4::video::window::renderer::renderer renderer;

    if(sdl4::init(SDL_INIT_VIDEO) != 0) return;

    if(wnd.create_window_and_renderer(this->res_x,
                                      this->res_y,
                                      0,
                                      &renderer) == 0) {
        unsigned x = 0, y = 0, i = 0;
        for(auto& line: this->parse.layer) {
            va: for(auto& child: line) {
                renderer.set_render_draw_color(child.r, child.g, child.b, SDL_ALPHA_OPAQUE);
                renderer.render_draw_point(x, y);

                for(unsigned f = 0; f < this->scale; f++)
                    renderer.render_draw_point(++x, y);

            } ++i; x = 0; ++y; if(i < this->scale) goto va; i = 0;
        }

        renderer.render_present();
        sdl4::timer::delay(3500);
    }

    sdl4::quit();
}

int main(int argc, char const* const* argv) noexcept {
    if(argc < 2) {
        std::cout << "clivie - climage viewer\n"
                    "------\n" <<
                    argv[0] << " {file}\n" <<
                    argv[0] << " {file} {x} {y} {scale_ratio}\n";
        return 1;
    }

    clivie x;

    if(argc > 3) {
        x.res_x = std::atoi(argv[2]);
        x.res_y = std::atoi(argv[3]);
        if(argc > 4) x.scale = std::atoi(argv[4]);
    }

    x.run(std::string(argv[1]));
}