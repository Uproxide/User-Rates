#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/binding/ProfilePage.hpp>
#include <matjson.hpp>

using namespace geode::prelude;

class $modify(ProfilePage) {
    public: 

    int usrID;
    int usrStars;

    bool init(int p0, bool p1) {
        if (!ProfilePage::init(p0, p1)) return false;

        web::AsyncWebRequest()
            .fetch("https://projectbdash.com/userrates/getUserStats.php?UserID=" + std::to_string(p1))
            .text()
            .then([this](std::string const& str) {
                parseRequestString(str);
            })
            .expect([this](std::string const& error) {
				// error :(
            });

        return true;
    }

    private:
    inline void parseRequestString(std::string str) {
        auto json = matjson::parse(str);

        if (json.is_array()) {
            auto& firstObject = json[0];

           if (firstObject.contains("userID") && firstObject.contains("userStars")) {
				usrID = firstObject["userID"].as<int>();
				usrStars = firstObject["userStars"].as<int>();
                auto usrStar = CCSprite::createWithSpriteFrameName("GJ_starsIcon_001.png");
                usrStar->setColor(ccc3(0, 255, 0));
                auto userstarsLabel = CCLabelBMFont::create(std::to_string(usrStars).c_str(), "bigFont.fnt");
                userstarsLabel->setColor(ccc3(0, 255, 0));
                
                this->addChild(usrStar);
                this->addChild(userstarsLabel);
            }
			else
			{
				// no crashy plz
			}
        }
    }
};