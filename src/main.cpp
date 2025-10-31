#include "Geode/ui/Notification.hpp"
#include "Geode/utils/cocos.hpp"
#include "Geode/utils/general.hpp"
#include <Geode/Geode.hpp>
#include <Geode/binding/CCMenuItemSpriteExtra.hpp>
#include <Geode/binding/EditorPauseLayer.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>
#include <Geode/binding/EditorUI.hpp>

using namespace cocos2d;
using namespace geode::log;

class $modify(EditorPauseLayerExt, EditorPauseLayer)
{
    void onCopyObjectString(CCObject*)
    {
        auto selected = geode::cocos::CCArrayExt<GameObject*>(this->m_editorLayer->m_editorUI->getSelectedObjects());
        if(selected.size() == 0)
        {
            geode::Notification::create("Select an object to copy string", geode::NotificationIcon::Info)->show();
            return;
        }

        std::string tocopy;
        for(const auto& obj : selected)
        {
            tocopy += obj->getSaveString(m_editorLayer);
            tocopy += ';';
        }
        
        geode::utils::clipboard::write(tocopy);
        geode::Notification::create("Copied objects to clipboard", geode::NotificationIcon::Success)->show();
    }
    
    bool init(LevelEditorLayer* p0)
    {
        if (!EditorPauseLayer::init(p0)) return false;

        auto spr = CCSprite::createWithSpriteFrameName("GJ_copyBtn2_001.png");
        auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(EditorPauseLayerExt::onCopyObjectString));
        btn->setID("copy-object-string"_spr);
        auto menu = getChildByID("guidelines-menu");

        if(!menu) return true;

        menu->addChild(btn);
        menu->updateLayout();
        return true;
    }
};