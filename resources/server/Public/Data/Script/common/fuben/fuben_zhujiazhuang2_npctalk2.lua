-------------------------------------------------
-- 祝家庄2 npc对话： 五行对话（1）
-------------------------------------------------

x700046_CSP_B_BOSS1		=	35

x700046_g_ScriptId = 700046


x700046_Fuben_ScriptId = 700031

x700046_g_TalkTitle = "金曰从革"
x700046_g_TalkContent = "\t 此物金光闪烁，似乎内有灵气游动，不知打开会有什么东西出现。看来这就是扈三娘的五行异术的“金”。"

function x700046_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
	
	
	x700046_DispatchTalkInfo( sceneId, selfId, NPCId,which )
	
end


--**********************************

--列举事件

--**********************************

function x700046_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	local bCreatMonster2 = GetFubenData_Param(sceneId, x700031_CSP_B_BOSS1 ) ;


	if bCreatMonster2<=0 then
	
		AddQuestNumText(sceneId, x700046_g_ScriptId, x700046_g_TalkTitle,3,1)
	end
			
end



function x700046_DispatchTalkInfo( sceneId, selfId, NPCId, nParam )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y"..x700046_g_TalkTitle)
		AddQuestText(sceneId,x700046_g_TalkContent)
		

	EndQuestEvent()





	DispatchQuestInfo(sceneId, selfId, NPCId, x700046_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x700046_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x700046_ProcAccept( sceneId, selfId )

	
	CallScriptFunction( x700046_Fuben_ScriptId, "OnNpcTalk2", sceneId, selfId) ;
	
end

