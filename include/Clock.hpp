#pragma once
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "custom-types/shared/macros.hpp" 
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

using namespace UnityEngine;
using namespace TMPro;
using namespace UnityEngine;

namespace ClockMod {
    enum ClockPosition {
        GAME,
        MENU
    };
}


DECLARE_CLASS_CODEGEN(ClockMod, Clock, UnityEngine::MonoBehaviour,
    private:
        DECLARE_INSTANCE_FIELD(GameObject*, canvas);
        DECLARE_INSTANCE_FIELD(RectTransform*, transform);
        DECLARE_INSTANCE_FIELD(TextMeshProUGUI*, textObject);
    public:
        void CreateClock();
        void SetClockPosition(ClockPosition);
        DECLARE_CTOR(ctor);
        DECLARE_SIMPLE_DTOR();

        DECLARE_INSTANCE_METHOD(void, UpdateClock);
)