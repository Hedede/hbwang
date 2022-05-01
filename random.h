
class CLGMRandom {
public:
    void SetSeed(double seed);

    CLGMRandom()
        : seed(0)
    {
    }
    CLGMRandom(double seed) { SetSeed(seed); }

    double operator()() { return Next(); }

    //! returns a random between 0 and 1
    double Next();

    float Randomf(float low, float high)
    {
        return low + ((high - low) * (float)Next());
    }

    int Random(int low, int high)
    {
        return low + (int)((double)(high - low + 1) * (double)Next());
    }

    int RandomSafe(int range0, int range1)
    {
        return Random(range0 < range1 ? range0 : range1,
            range0 > range1 ? range0 : range1);
    }

    float RandomfSafe(float range0, float range1)
    {
        return Randomf(range0 < range1 ? range0 : range1,
            range0 > range1 ? range0 : range1);
    }

    double seed;
};

inline void CLGMRandom::SetSeed(double s)
{
    if (s >= 2147483647.0)
        s = s / 2.0;

    seed = s;
    Next();
}

inline double CLGMRandom::Next()
{
    // poro_assert( seed );
    //  m = 2147483647 = 2^31 - 1; a = 16807;
    //  127773 = m div a; 2836 = m mod a
    long iseed = (long)seed;
    long hi = iseed / 127773L; // integer division
    long lo = iseed - hi * 127773L; // modulo
    iseed = 16807 * lo - 2836 * hi;
    if (iseed <= 0)
        iseed += 2147483647L;
    seed = (double)iseed;
    return seed * 4.656612875e-10;
}
