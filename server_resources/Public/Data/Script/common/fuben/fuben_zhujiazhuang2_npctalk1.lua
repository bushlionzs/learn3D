-------------------------------------------------
-- 祝家庄2 npc对话： 时迁对话
-------------------------------------------------

x700045_CSP_B_MONSTER2		=	40

x700045_g_ScriptId = 700045


x700045_Fuben_ScriptId = 700031

x700045_g_TalkTitle = "解救时迁"
x700045_g_TalkContent = "\t哎呀，不好，你们怎么进来了，刚才我被困在袋中时听那扈三娘和祝家兄弟商量，要将金银细软搬到别处，同时在祝家庄内设下天罗地网，要拿咱弟兄向官府讨赏，大家快些分开走，迟了恐怕难逃虎口！"

function x700045_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
	
	
	x700045_DispatchTalkInfo( sceneId, selfId, NPCId,which )
	
end


--**********************************

--列举事件

--**********************************

function x700045_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	local bCreatMonster2 = GetFubenData_Param(sceneId, x700045_CSP_B_MONSTER2 ) ;


	if bCreatMonster2<=0 then
	
		AddQuestNumText(sceneId, x700045_g_ScriptId, x700045_g_TalkTitle,3,1)
	end
			
end



function x700045_DispatchTalkInfo( sceneId, selfId, NPCId, nParam )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y"..x700045_g_TalkTitle)
		AddQuestText(sceneId,x700045_g_TalkContent)
		

	EndQuestEvent()





	DispatchQuestInfo(sceneId, selfId, NPCId, x700045_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x700045_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x700045_ProcAccept( sceneId, selfId )

	
	CallScriptFunction( x700045_Fuben_ScriptId, "OnNpcTalk1", sceneId, selfId) ;
	
end

