#ifndef DOWNGRADER_H
#define DOWNGRADER_H

#include <set>
#include <vector>

// Hate including this in the header file, but without it the
// MissionType structs may be the wrong size.
// Replace with using pointers? -- rnyoakum
#include "Buzz_inc.h"


/**
 * This class takes a base, or seed, mission instance and generates
 * a cyclical list of "downgraded" mission instances that share the
 * crew and hardware.
 *
 * The Options class is designed for a dense input where all missions
 * have downgrade options provided.
 */
class Downgrader
{
public:
    class Options
    {
    public:
        Options();
        ~Options();

        int add(int mission, int code);
        const std::set<int> downgrades(int mission) const;
    private:
        std::vector< std::set<int> > mDowngrades;
    };

    Downgrader(const struct MissionType &mission,
               const std::set<int> &downgrades);
    Downgrader(const struct MissionType &mission, const Options downgrades);
    ~Downgrader();

    struct MissionType current() const;
    struct MissionType next();
private:
    const struct MissionType mBasis;
    struct MissionType mCurrent;
    std::vector<int> mCodes;
    std::vector<int>::iterator mIndex;
    int mDuration;
};


#endif // DOWNGRADER_H
