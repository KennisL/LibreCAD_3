#include "uitests.h"

LuaInterface* startLC() {
    auto luaInterface = new LuaInterface;

    luaInterface->hideUI(true);
    luaInterface->initLua();

    return luaInterface;
}

lc::Document_SPtr createDocument() {
    auto storageManager = std::make_shared<lc::StorageManagerImpl>();
    return std::make_shared<lc::DocumentImpl>(storageManager);
};

CadMdiChild* getMdiChild(lua_State* L) {
    auto mdiArea = LuaIntf::Lua::getGlobal<QMdiArea*>(L, "mdiArea");

    if(mdiArea->subWindowList().count() == 0) {
        LuaIntf::LuaRef(L, "new_file")();
    }

    mdiArea->setActiveSubWindow(mdiArea->subWindowList().at(0));

    return dynamic_cast<CadMdiChild*>(mdiArea->subWindowList().at(0)->widget());
}
