-------------------------------------------------
-- 祝家庄2 npc对话： 五行对话(3)
-------------------------------------------------

x700048_CSP_B_BOSS3		=	37

x700048_g_ScriptId = 700048


x700048_Fuben_ScriptId = 700031

x700048_g_TalkTitle = "水曰润下"
x700048_g_TalkContent = "\t 此物晶莹剔透，似乎内有灵气游动，不知打开会有什么东西出现。看来这就是扈三娘的五行异术的“水”。"

function x700048_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
	
	
	x700048_DispatchTalkInfo( sceneId, selfId, NPCId,which )
	
end


--**********************************

--列举事件

--**********************************

function x700048_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	local bCreatMonster2 = GetFubenData_Param(sceneId, x700048_CSP_B_BOSS3 ) ;


	if bCreatMonster2<=0 then
	
		AddQuestNumText(sceneId, x700048_g_ScriptId, x700048_g_TalkTitle,3,1)
	end
			
end



function x700048_DispatchTalkInfo( sceneId, selfId, NPCId, nParam )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y"..x700048_g_TalkTitle)
		AddQuestText(sceneId,x700048_g_TalkContent)
		

	EndQuestEvent()





	DispatchQuestInfo(sceneId, selfId, NPCId, x700048_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x700048_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x700048_ProcAccept( sceneId, selfId )

	
	CallScriptFunction( x700048_Fuben_ScriptId, "OnNpcTalk4", sceneId, selfId) ;
	
end

