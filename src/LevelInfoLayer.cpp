#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/binding/LevelInfoLayer.hpp>
#include <matjson.hpp>

using namespace geode::prelude;

class $modify(LevelInfoLayer) {
public:

	int stars;
	int difficulty;
	int rateGlow;

    bool init(GJGameLevel* p0, bool p1) {
        if (!LevelInfoLayer::init(p0, p1)) return false;

        web::AsyncWebRequest()
            .fetch("https://projectbdash.com/userrates/getRatedLevel.php?LevelID=" + std::to_string(p0->m_levelID))
            .text()
            .then([this](std::string const& str) {
                parseRequestString(str);
            })
            .expect([this](std::string const& error) {
				// error :(
            });

        return true;
    }

	void difficultyFunction(int glow, int difficultything)
	{
		// make the faces or smth :troll!:
		auto difficultyPosX = m_difficultySprite->getPositionX();
		auto difficultyPosY = m_difficultySprite->getPositionY();
		m_difficultySprite->setVisible(false);
		auto godlikeSprite = CCSprite::createWithSpriteFrameName("GJ_epicCoin3_001.png");
		auto legendarySprite = CCSprite::createWithSpriteFrameName("GJ_epicCoin2_001.png");
		auto epicSprite = CCSprite::createWithSpriteFrameName("GJ_epicCoin_001.png");
		auto featuredSprite = CCSprite::createWithSpriteFrameName("GJ_featuredCoin_001.png");
		// zee ordah
		featuredSprite->setZOrder(-1);
		epicSprite->setZOrder(-1);
		legendarySprite->setZOrder(-1);
		godlikeSprite->setZOrder(-1);
		// sprite positions (easy/auto/hard)
		featuredSprite->setPosition(ccp(15, 21.625));
		epicSprite->setPosition(ccp(15, 21.625));
		legendarySprite->setPosition(ccp(15, 21.625));
		godlikeSprite->setPosition(ccp(15, 21.625));

		if (difficultything == 0) // auto
		{
			auto difficultyFace = CCSprite::createWithSpriteFrameName("difficulty_auto_btn_001.png");
			this->addChild(difficultyFace);
			difficultyFace->setID("uproxide.user-rates/difficulty_face");
			difficultyFace->setPosition(ccp(difficultyPosX, difficultyPosY));
		}
		else if (difficultything == 1) // easy
		{
			auto difficultyFace = CCSprite::createWithSpriteFrameName("difficulty_01_btn_001.png");
			this->addChild(difficultyFace);
			difficultyFace->setID("uproxide.user-rates/difficulty_face");
			difficultyFace->setPosition(ccp(difficultyPosX, difficultyPosY));
		}
		else if (difficultything == 2) // normal
		{
			auto difficultyFace = CCSprite::createWithSpriteFrameName("difficulty_02_btn_001.png");
			this->addChild(difficultyFace);
			difficultyFace->setID("uproxide.user-rates/difficulty_face");
			difficultyFace->setPosition(ccp(difficultyPosX, difficultyPosY));
			featuredSprite->setPosition(ccp(21.5, 21.625));
			epicSprite->setPosition(ccp(21.5, 21.625));
			legendarySprite->setPosition(ccp(21.5, 21.625));
			godlikeSprite->setPosition(ccp(21.5, 21.625));
		}
		else if (difficultything == 6) // easy demon
		{
			auto difficultyFace = CCSprite::createWithSpriteFrameName("difficulty_07_btn2_001.png");
			this->addChild(difficultyFace);
			difficultyFace->setID("uproxide.user-rates/difficulty_face");
			difficultyFace->setPosition(ccp(difficultyPosX, difficultyPosY + 7));
			featuredSprite->setPosition(ccp(17.9, 31));
			epicSprite->setPosition(ccp(17.9, 31));
			legendarySprite->setPosition(ccp(17.9, 31));
			godlikeSprite->setPosition(ccp(17.9, 31));
		}
		else if (difficultything == 7) // medium demon
		{
			auto difficultyFace = CCSprite::createWithSpriteFrameName("difficulty_08_btn2_001.png");
			this->addChild(difficultyFace);
			difficultyFace->setID("uproxide.user-rates/difficulty_face");
			difficultyFace->setPosition(ccp(difficultyPosX, difficultyPosY + 7));
			featuredSprite->setPosition(ccp(20.25, 30.75));
			epicSprite->setPosition(ccp(20.25, 30.75));
			legendarySprite->setPosition(ccp(20.25, 30.75));
			godlikeSprite->setPosition(ccp(20.25, 30.75));
		}

		auto difficulty = static_cast<cocos2d::CCSprite*>(this->getChildByID("uproxide.user-rates/difficulty_face"));

		if (glow == 1)
		{
			difficulty->addChild(featuredSprite);
		}
		else if (glow == 2)
		{
			difficulty->addChild(epicSprite);
		}
		else if (glow == 3)
		{
			difficulty->addChild(legendarySprite);
		}
		else if (glow == 4)
		{
			difficulty->addChild(godlikeSprite);
		}
	}

private:
    inline void parseRequestString(std::string str) {
        auto json = matjson::parse(str);

        if (json.is_array()) {
            auto& firstObject = json[0];

           if (firstObject.contains("Stars") && firstObject.contains("Difficulty") && firstObject.contains("rateGlow")) {
				stars = firstObject["Stars"].as<int>();
				difficulty = firstObject["Difficulty"].as<int>();
				rateGlow = firstObject["rateGlow"].as<int>();

				m_starsLabel->setString(std::to_string(stars).c_str());
                m_starsLabel->setVisible(true);
                m_starsLabel->setColor(ccc3(0, 255, 0));

                m_starsIcon->setVisible(true);
                m_starsIcon->setColor(ccc3(0, 255, 0));

				difficultyFunction(rateGlow, difficulty);


            }
			else
			{
				// no crashy plz
			}
        }
    }
};
