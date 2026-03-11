#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// --- THE SHOP POPUP LOGIC ---
class CursedShopLayer : public Popup<> {
protected:
    bool setup() override {
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        this->setTitle("Cursed Black Market");

        // 1. The V-Buck Currency (1000037107.png)
        auto vbuck = CCSprite::create("1000037107.png"_spr); 
        if (vbuck) {
            vbuck->setPosition({winSize.width / 2 - 100, winSize.height / 2 + 40});
            vbuck->setScale(0.3f);
            m_mainLayer->addChild(vbuck);
        }

        // 2. The Nuclear Bomb Button (1000037113.jpg)
        auto nukeMeme = CCSprite::create("1000037113.jpg"_spr);
        if (nukeMeme) {
            nukeMeme->setScale(0.35f);
            auto nukeBtn = CCMenuItemSpriteExtra::create(
                nukeMeme, this, menu_selector(CursedShopLayer::onTryBuyNuke)
            );
            auto nukeMenu = CCMenu::create();
            nukeMenu->addChild(nukeBtn);
            nukeMenu->setPosition({winSize.width / 2 + 70, winSize.height / 2 + 40});
            m_mainLayer->addChild(nukeMenu);
        }

        // 3. Staring Rat for atmosphere (1000037110.jpg)
        auto rat = CCSprite::create("1000037110.jpg"_spr);
        if (rat) {
            rat->setPosition({winSize.width / 2 - 120, winSize.height / 2 - 80});
            rat->setScale(0.2f);
            m_mainLayer->addChild(rat);
        }

        return true;
    }

    // This runs when you click the Nuke
    void onTryBuyNuke(CCObject*) {
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        
        // Play an explosion sound
        FMODAudioEngine::sharedEngine()->playEffect("explode_11.ogg");

        // Show the Broke Cat (1000037111.jpg)
        auto brokeCat = CCSprite::create("1000037111.jpg"_spr);
        if (brokeCat) {
            brokeCat->setPosition({winSize.width / 2, winSize.height / 2 - 20});
            brokeCat->setScale(0.4f);
            m_mainLayer->addChild(brokeCat);
        }

        // Show Plankton judging you (1000037108.jpg)
        auto plankton = CCSprite::create("1000037108.jpg"_spr);
        if (plankton) {
            plankton->setPosition({winSize.width / 2 + 120, winSize.height / 2 - 80});
            plankton->setScale(0.25f);
            m_mainLayer->addChild(plankton);
        }
    }

public:
    static CursedShopLayer* create() {
        auto ret = new CursedShopLayer();
        if (ret && ret->init(400.f, 280.f)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};

// --- PUTTING THE BUTTON ON THE MENU ---
class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto rightMenu = this->getChildByID("right-side-menu");

        // Use the Silly Cat as the button (1000037112.jpg)
        auto catSprite = CCSprite::create("1000037112.jpg"_spr);
        if (!catSprite) {
            catSprite = CCSprite::createWithSpriteFrameName("GJ_shopBtn_001.png");
        } else {
            catSprite->setScale(0.15f); 
        }

        auto shopBtn = CCMenuItemSpriteExtra::create(
            catSprite, this, menu_selector(MyMenuLayer::onCursedShop)
        );
        shopBtn->setID("cursed-shop-button"_spr);

        if (rightMenu) {
            rightMenu->addChild(shopBtn);
            rightMenu->updateLayout();
        }

        return true;
    }

    void onCursedShop(CCObject* sender) {
        CursedShopLayer::create()->show();
    }
};
