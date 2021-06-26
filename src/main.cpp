#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "custom-types/shared/register.hpp"

#include "UnityEngine/SceneManagement/Scene.hpp"
#include "UnityEngine/AudioClip.hpp"
#include "System/IO/File.hpp"
#include "GlobalNamespace/NoteCutSoundEffect.hpp"
#include "Clock.hpp"
#include "main.hpp"

using namespace ClockMod;
using namespace GlobalNamespace;

// Holds the ModInfo object for this mod. This object is set in void setup()
static ModInfo modInfo;
bool hasInitialized = false;
Logger& getLogger() {
    static auto logger = new Logger(modInfo, LoggerOptions(false, true));
    return *logger;
}

Configuration& getConfig() {
    static Configuration config(modInfo);
    return config;
}

Clock* c = nullptr;
MAKE_HOOK_OFFSETLESS(SceneManager_Internal_ActiveSceneChanged, void, UnityEngine::SceneManagement::Scene prevScene, UnityEngine::SceneManagement::Scene nextScene) {
    SceneManager_Internal_ActiveSceneChanged(prevScene, nextScene);
    if(prevScene.IsValid() && nextScene.IsValid()) {
        std::u16string nextSceneName(csstrtostr(nextScene.get_name()));
        
        if(nextSceneName == u"MainMenu"){
            if (!hasInitialized) {
                auto gameObject = GameObject::New_ctor(il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("Clock"));
                c = gameObject->AddComponent<Clock*>();
                GameObject::DontDestroyOnLoad(gameObject);
                hasInitialized = true;
                c->CreateClock();
                c->InvokeRepeating(il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("UpdateClock"), 0.0f, 0.9f);
            }
            c->SetClockPosition(ClockMod::MENU);
        } else if (nextSceneName == u"GameCore"){
            c->SetClockPosition(ClockMod::GAME);
        }
    }
}

extern "C" void setup(ModInfo& info) {
    // Set the ID and version of this mod
    info.id = "clockmod";
    info.version = "0.0.1";
    modInfo = info;

    getLogger().info("Modloader name: %s", Modloader::getInfo().name.c_str());
    getConfig().Load();
    getLogger().info("Completed setup!");
}


extern "C" void load() {
    getLogger().debug("Load clockmod!");
    il2cpp_functions::Init();
    custom_types::Register::AutoRegister();


    INSTALL_HOOK_OFFSETLESS(getLogger(), SceneManager_Internal_ActiveSceneChanged, il2cpp_utils::FindMethodUnsafe("UnityEngine.SceneManagement", "SceneManager", "Internal_ActiveSceneChanged", 2));

    getLogger().debug("Initialized Clockmod!");
}