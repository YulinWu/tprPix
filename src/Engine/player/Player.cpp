/*
 * ====================== Player.cpp =======================
 *                          -- tpr --
 *                                        CREATE -- 2018.12.10
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 *   hold data about player
 * ----------------------------
 */
#include "pch.h"
#include "Player.h"

//-------------------- Engine --------------------//
#include "input.h" 
#include "GameKey.h"
#include "dyParams.h"
#include "create_goes.h"
#include "GoSpecFromJson.h"


#include "esrc_camera.h" 
#include "esrc_gameObj.h" 



using namespace std::placeholders;

//#include "tprDebug.h" //- tmp

/* ===========================================================
 *                   get_goRef
 * -----------------------------------------------------------
 */
GameObj &Player::get_goRef() const {
    return esrc::get_goRef( this->goid );
}


void Player::set_moveSpeedLvl( SpeedLevel lvl_ )noexcept{

    auto &playerGoRef = esrc::get_goRef( this->goid );
    auto &cirGoRef = esrc::get_goRef( this->playerGoCircle_goid );
    playerGoRef.move.moveSpeedLvl.set_newVal( lvl_ );
    cirGoRef.move.moveSpeedLvl.set_newVal( lvl_ );
}


/* ===========================================================
 *                   bind_go
 * -----------------------------------------------------------
 * -- 这个函数有漏洞
 */
void Player::bind_go( goid_t goid_ ){


    //--- first bind ---//
    if( this->goid == NULLID ){

        //-- bind new go --//
        tprAssert( goid_ != NULLID );
        auto &newGoRef = esrc::get_goRef( goid_ );
        newGoRef.isControlByPlayer = true;
        this->goid = goid_;

        //-- create playerGoCircle --//
        // 和 常规go 一样， playerGoCircle 也会被登记到 chunk 上，但不参与 碰撞检测
        glm::dvec2 newGoDPos = newGoRef.get_dpos();


        auto goDataUPtr = GoDataForCreate::create_new_goDataForCreate(  
                                                    dpos_2_mpos(newGoDPos),
                                                    newGoDPos,
                                                    GoSpecFromJson::str_2_goSpeciesId("playerGoCircle"),
                                                    GoAssemblePlanSet::str_2_goLabelId(""),
                                                    NineDirection::Center,
                                                    BrokenLvl::Lvl_0
                                                    );
        this->playerGoCircle_goid = gameObjs::create_a_Go( goDataUPtr.get() );


        
        //-- playerGoCircle 的数据同步 --
        GameObj &playerGoCircleRef = esrc::get_goRef( this->playerGoCircle_goid );
        playerGoCircleRef.move.moveSpeedLvl.reset( newGoRef.move.moveSpeedLvl.get_newVal() ); //- 同步 speedLv

    }else{
        //-- 解绑旧go --//
        GameObj &oldGoRef = esrc::get_goRef( this->goid );
        oldGoRef.isControlByPlayer = false;

        //=== 检测 chunk 中的 go数据 是否被 实例化到 mem态 ===//
        //...

        //-- bind new go --//
        tprAssert( goid_ != NULLID );
        GameObj &newGoRef = esrc::get_goRef( goid_ );
        newGoRef.isControlByPlayer = true;
        this->goid = goid_;

        //-- reset playerGoCircle mpos --//
    }

}


/* ===========================================================
 *                  handle_inputINS   
 * -----------------------------------------------------------
 *  玩家输入的鼠键 -> inputIns -> 游戏指令
 *  本函数获得 inputIns，将其转换为 游戏指令，并传输给 player.go
 * -------
 *  每一渲染帧都会被调用
 */
void Player::handle_inputINS( const InputINS &inputINS_ ){

    //  此处会有很多 处理 _inputINS 数据的操作
    //  在未来展开...

    GameObj &goRef = esrc::get_goRef( this->goid );
    goRef.move.set_newCrawlDirAxes( inputINS_.get_dirAxes() );
}

