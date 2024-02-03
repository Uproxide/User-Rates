#ifndef MANAGER_H
#define MANAGER_H
#include <vector>
#include <string>
#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <matjson.hpp>

using namespace geode::prelude;

class Manager {
    public:
    inline static int starsAmnt;

    inline static void setStarsShit(int userStars)
    {
        starsAmnt = userStars;
    }
};

#endif