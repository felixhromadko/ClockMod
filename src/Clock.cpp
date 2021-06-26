#include "Clock.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/SystemClock.hpp"
#include "HMUI/CurvedCanvasSettings.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
#include "main.hpp"

using namespace QuestUI;
using namespace GlobalNamespace;
using namespace UnityEngine::UI;
using namespace ClockMod;
using namespace HMUI;

DEFINE_TYPE(ClockMod, Clock);

void Clock::ctor() {}
void Clock::CreateClock() {
   getLogger().debug("Creating Clock");

   canvas = BeatSaberUI::CreateCanvas();
   canvas->AddComponent<CurvedCanvasSettings*>()->SetRadius(100.0f);

   transform = canvas->GetComponent<RectTransform*>();
   transform->set_position(UnityEngine::Vector3(0.0f, 3.1f, 4.0f));
   transform->set_eulerAngles(UnityEngine::Vector3(-8.0f, 0.0f, 0.0f));

   VerticalLayoutGroup* layout = BeatSaberUI::CreateVerticalLayoutGroup(transform);
   GameObject* layoutGameObject = layout->get_gameObject();
   layoutGameObject->GetComponent<ContentSizeFitter*>()->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
   auto bgName = il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("round-rect-panel");
   layoutGameObject->AddComponent<Backgroundable*>()->ApplyBackgroundWithAlpha(bgName, 0.96f);
   layout->set_padding(RectOffset::New_ctor(3, 4, 2, 2));
   textObject = BeatSaberUI::CreateText(layout->get_transform(), "");
   textObject->set_alignment(TextAlignmentOptions::Center);
   textObject->set_fontSize(6.0f);
   Object::DontDestroyOnLoad(canvas);
}

void Clock::SetClockPosition(ClockPosition pos) {
   if (!transform) return;
   if (pos == MENU) {
      transform->set_position(UnityEngine::Vector3(0.0f, 3.1f, 4.0f));
      transform->set_eulerAngles(UnityEngine::Vector3(-8.0f, 0.0f, 0.0f));
   } else {
      transform->set_position(UnityEngine::Vector3(0.0f, 4.0f, 7.5f));
      transform->set_eulerAngles(UnityEngine::Vector3(-16.0f, 0.0f, 0.0f));
   }

}

void Clock::UpdateClock() {
   if (!textObject) return;
   System::DateTime time = SystemClock::get_now();
   Il2CppString* fTime = time.ToString(il2cpp_utils::newcsstr(u"HH:mm:ss"));
   textObject->set_text(fTime);
}