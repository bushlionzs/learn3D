x920001_g_ScriptId = 920001

--上一个任务的ID
--g_MissionIdPre =



--任务文本描述
x920001_g_MissionName="科举22"

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x920001_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本
		QuizAsk(sceneId, selfId, 1, 20, 20); 
end

--**********************************
--列举事件
--**********************************
function x920001_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x920001_g_ScriptId,x920001_g_MissionName);
end


--********************
--检测接受条件
--**********************************
function x920001_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x920001_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x920001_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x920001_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x920001_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x920001_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x920001_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x920001_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x920001_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

--处理答案
function x920001_OnAnswer( sceneId, selfId, nStepIndex, questIndex, answerIndex)
		local nCount;
		local nCode;
		--检查题答案
		--print( "x920001_OnAnswer1111")
		nCode = QuizCheck(sceneId, questIndex, answerIndex);
		--print( "x920001_OnAnswer222"..nCode)
		--得到答对或错几道题
		if (nCode == 0) then
		--print( "x920001_OnAnswer333")
				nCount = GetQuizWrongCount(sceneId, selfId);
				nCount = nCount + 1;
				SetQuizWrongCount( sceneId, selfId, nCount);
		elseif (nCode == 1) then
		--print( "x920001_OnAnswer444")
				nCount = GetQuizRightCount(sceneId, selfId);
				nCount = nCount + 1;
				SetQuizRightCount( sceneId, selfId, nCount);
		end
		--给客户端回传结果
		--print( "x920001_OnAnswer5555")
		QuizResult(sceneId, selfId, nStepIndex, nCode, nCount);
		nStepIndex = nStepIndex + 1;
		if nStepIndex <= 20 then
			QuizAsk(sceneId, selfId, nStepIndex, 20, 20);
		end
		--print( "x920001_OnAnswer666")
end