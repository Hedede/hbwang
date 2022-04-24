#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <string>

//
#include "random.h"

#define STB_HBWANG_RAND() myrand()

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" // http://nothings.org/stb_image.c
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" // http://nothings.org/stb/stb_image_write.h
#define STB_HERRINGBONE_WANG_TILE_IMPLEMENTATION
#include "stb_herringbone_wang_tile.h"

using namespace std::string_literals;
void genwang(std::string filename, unsigned char* data, int xs, int ys, int w, int h)
{
    stbhw_tileset ts;
    if (xs < 1 || xs > 1000) {
        fprintf(stderr, "xsize invalid or out of range\n");
        exit(1);
    }
    if (ys < 1 || ys > 1000) {
        fprintf(stderr, "ysize invalid or out of range\n");
        exit(1);
    }

    stbhw_build_tileset_from_image(&ts, data, w * 3, w, h);
    // allocate a buffer to create the final image to
    int yimg = ys + 4;
    auto buff = static_cast<unsigned char*>(malloc(3 * xs * yimg));
    stbhw_generate_image(&ts, NULL, buff, xs * 3, xs, yimg);
    stbi_write_png(filename.c_str(), xs, yimg, 3, buff, xs * 3);
    stbhw_free_tileset(&ts);
    free(buff);
}

int main(int argc, char** argv)
{
    if (argc != 5) {
        fprintf(stderr, "Usage: mapgen {tile-file} {xsize} {ysize} {seed}\n"
                        "generates file named 'test_map.png'\n");
        exit(1);
    }
    int w, h;

    unsigned char* data = stbi_load(argv[1], &w, &h, NULL, 3);

    if (data == NULL) {
        fprintf(stderr, "Error opening or parsing '%s' as an image file\n",
            argv[1]);
        exit(1);
    }

    int xs = atoi(argv[2]);
    int ys = atoi(argv[3]);
    printf("Tileset: %s\n", argv[1]);
    printf("Output size: %dx%d\n", xs, ys);

    auto seed = atoi(argv[4]);
    printf("Using seed: %d\n", seed);
    wang_seed = seed;
    {
        CLGMRandom rnd(seed);

        // int num = seed + x - 11 * (x / 11) - 12 * (seed / 12);
        int num = xs % 11 + seed % 12;
        printf("Some number: %d\n", num);
        while (num-- > 0) {
            rnd.Next();
        }

        double newSeed = rnd.Next() * 2147483645.0;
        printf("Adjusted seed: %d\n", int(newSeed));

        auto filename = std::string(argv[1]);
        filename = filename.substr(0, filename.size() - 4);
        filename = filename + std::to_string(seed) + ".png";

        random.SetSeed(newSeed);
        genwang(filename, data, xs, ys, w, h);
    }

    free(data);

    return 0;
}
