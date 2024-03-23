-------------------------------------------------
-- 祝家庄2 npc对话： 五行对话(4)
-------------------------------------------------

x700049_CSP_B_BOSS4		=	38

x700049_g_ScriptId = 700049


x700049_Fuben_ScriptId = 700031

x700049_g_TalkTitle = "火曰炎上"
x700049_g_TalkContent = "\t 此物炽如烧炭，似乎内有灵气游动，不知打开会有什么东西出现。看来这就是扈三娘的五行异术的“火”。"

function x700049_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
	
	
	x700049_DispatchTalkInfo( sceneId, selfId, NPCId,which )
	
end


--**********************************

--列举事件

--**********************************

function x700049_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	local bCreatMonster2 = GetFubenData_Param(sceneId, x700049_CSP_B_BOSS4 ) ;


	if bCreatMonster2<=0 then
	
		AddQuestNumText(sceneId, x700049_g_ScriptId, x700049_g_TalkTitle,3,1)
	end
			
end



function x700049_DispatchTalkInfo( sceneId, selfId, NPCId, nParam )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y"..x700049_g_TalkTitle)
		AddQuestText(sceneId,x700049_g_TalkContent)
		

	EndQuestEvent()





	DispatchQuestInfo(sceneId, selfId, NPCId, x700049_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x700049_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x700049_ProcAccept( sceneId, selfId )

	
	CallScriptFunction( x700049_Fuben_ScriptId, "OnNpcTalk5", sceneId, selfId) ;
	
end

