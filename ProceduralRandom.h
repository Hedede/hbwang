#ifndef PROCEDURALRANDOM_H
#define PROCEDURALRANDOM_H

#include "print.h"
#include "random.h"

// DO NOT fix any type conversion compiler warnings in here,
// because it will likely fuck up the hash output
void InitializeProceduralRandom(CLGMRandom& rng, double x, double y, unsigned int seed)
{
    auto SomeHashFunc = [](unsigned int xh, unsigned int zh, unsigned int seed) {
        unsigned v3 = (seed >> 13) ^ (xh - zh - seed);
        unsigned v4 = (v3 << 8) ^ (zh - v3 - seed);
        unsigned v5 = (v4 >> 13) ^ (seed - v3 - v4);
        unsigned v6 = (v5 >> 12) ^ (v3 - v4 - v5);
        unsigned v7 = (v6 << 16) ^ (v4 - v6 - v5);
        unsigned v8 = (v7 >> 5) ^ (v5 - v6 - v7);
        unsigned v9 = (v8 >> 3) ^ (v6 - v7 - v8);
        return (((v9 << 10) ^ (v7 - v9 - v8)) >> 15) ^ (v8 - v9 - ((v9 << 10) ^ (v7 - v9 - v8)));
    };

    auto xh = ((seed ^ 11887) & 0xFFF) + 0.0 + x;
    auto yh = (((seed ^ 2468753007) >> 12) & 0xFFF) + 0.0 + y;

    bool h = fabs(yh) >= 102400.0 || fabs(xh) <= 1.0;

    unsigned xh1 = (long long)(xh * 134217727.0);
    unsigned yh1 = (long long)(h ? yh * 134217727.0 : (yh * 3483.328 + xh1) * yh);

    auto hash = SomeHashFunc(xh1, yh1, seed);

    rng.SetSeed(hash / 4294967295.0 * 2147483639.0 + 1.0);

    for (int i = 0; i < (seed & 3); ++i)
        rng.Next();
}

#if 0
[6.41476] InitProceduralRandom: [pos: 0.000000,0.000000] [seed: 2074577201]
[6.41477] SomeHashFunc: xh: -268437342, zh: -589716220, seed, 2074577201, h: -762622000
[6.41479] InitProceduralRandom: result: 1734419884.000000

[7.05238] InitProceduralRandom: [pos: 347893.000000,90737.000000] [seed: 2074577201]
[7.0524] SomeHashFunc: xh: -1745180243, zh: 216991270, seed, 2074577201, h: 326686004
[7.05241] InitProceduralRandom: result: 411768779.000000

[7.053] InitProceduralRandom: [pos: 347893.000000,90743.000000] [seed: 2074577201]
[7.05302] SomeHashFunc: xh: -1745180243, zh: -2079503632, seed, 2074577201, h: 1530297928
[7.05303] InitProceduralRandom: result: 1997120642.000000

[10.8364] InitProceduralRandom: [pos: 267.000000,-98.000000] [seed: 2074577201]
[10.8364] SomeHashFunc: xh: 1207957399, zh: -361979132, seed, 2074577201, h: -1933081356
[10.8364] InitProceduralRandom: result: 1440683159.000000

[10.8367] InitProceduralRandom: [pos: 304.000000,-91.000000] [seed: 2074577201]
[10.8367] SomeHashFunc: xh: 1879046002, zh: -1070840473, seed, 2074577201, h: -681150690
[10.8367] InitProceduralRandom: result: 1360167864.000000

[11.0732] InitProceduralRandom: [pos: -540.000000,-134.000000] [seed: 373025045]
[11.0732] SomeHashFunc: xh: -268436830, zh: -1203658668, seed, 373025045, h: -1630593588
[11.0732] InitProceduralRandom: result: 1097093984.000000

[11.0734] InitProceduralRandom: [pos: -578.000000,-124.000000] [seed: 373025045]
[11.0734] SomeHashFunc: xh: -1073743160, zh: 431128000, seed, 373025045, h: -816209492
[11.0734] InitProceduralRandom: result: 1552077460.000000

[11.0794] InitProceduralRandom: [pos: 282.000000,-9.000000] [seed: 373025045]
[11.0794] SomeHashFunc: xh: -1610614932, zh: 221779076, seed, 373025045, h: -587498166
[11.0794] InitProceduralRandom: result: 1210901421.000000
#endif

void test_proc_random()
{
    CLGMRandom rng;
    InitializeProceduralRandom(rng, 0.0, 0.0, 2074577201);
    println("{} {}", 1734419884, rng.seed);
    InitializeProceduralRandom(rng, 347893, 90737, 2074577201);
    println("{} {}", 411768779, rng.seed);
    InitializeProceduralRandom(rng, 347893, 90743, 2074577201);
    println("{} {}", 1997120642, rng.seed);
    InitializeProceduralRandom(rng, 267, -98, 2074577201);
    println("{} {}", 1440683159, rng.seed);
    InitializeProceduralRandom(rng, 304, -91, 2074577201);
    println("{} {}", 1360167864, rng.seed);
    InitializeProceduralRandom(rng, -540, -134, 373025045);
    println("{} {}", 1097093984, rng.seed);
    InitializeProceduralRandom(rng, -578, -124, 373025045);
    println("{} {}", 1552077460, rng.seed);
    InitializeProceduralRandom(rng, 282, -9, 373025045);
    println("{} {}", 1210901421, rng.seed);
}

#endif // PROCEDURALRANDOM_H
