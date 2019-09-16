/*
 * ========================= PineTree.h ==========================
 *                          -- tpr --
 *                                        CREATE -- 2019.09.13
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 */
#ifndef TPR_GO_PINE_TREE_H
#define TPR_GO_PINE_TREE_H

//-------------------- CPP --------------------//
#include <string>
#include <vector>
#include <functional>

//-------------------- Engine --------------------//
#include "tprAssert.h"
#include "GameObj.h"
#include "GameObjMesh.h"
#include "AnimFrameSet.h"
#include "MapAltitude.h"
#include "Density.h"
#include "ParamBinary.h"
#include "animSubspeciesId.h"


namespace gameObjs{//------------- namespace gameObjs ----------------


class PineTree{
public:
    PineTree() = default;
    //--- 延迟init ---//
    static void init_in_autoMod(GameObj &goRef_,
                            const ParamBinary &dyParams_ );

private:                            
    static void bind( GameObj &goRef_ );
    static void rebind( GameObj &goRef_ );

    //--- callback ---//
    static void OnRenderUpdate( GameObj &goRef_ ); 
    static void OnLogicUpdate( GameObj &goRef_ ); 
    static void OnActionSwitch( GameObj &goRef_, ActionSwitchType type_ );
};


}//------------- namespace gameObjs: end ----------------
#endif 
