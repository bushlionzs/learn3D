





x400214_g_scriptId = 400214 
--x400214_g_Impact1 = 7528 --Ч��ID�������Ӻ���
x400214_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
x400214_g_doing =0

function x400214_ProcEventEntry( sceneId, selfId, BagIndex )
			local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, -1 )
    
    if bCplay == 1 then
    CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 4 )
    CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 5 )
    	--if x400214_g_doing==0 then
      --							x888888_PlayEffect( sceneId, selfId, 4 )
    	--		    			x400214_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
			--							x400214_g_doing =2
			--							--x400214_g_acceptid =selfId         
    	--		          x400214_g_PROTECTINFO.StartTime = GetCurrentTime()
			--							x400214_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 400214, "OnScneneTimer", 1)   			
    	--		end
			
    end

    return bCplay
		
	

end

--function x400214_OnScneneTimer(sceneId)
--	if x400214_g_doing==2   then
--		if GetCurrentTime() - x400214_g_PROTECTINFO.StartTime >= 6   then
--						x888894_StopEffect( sceneId, selfId, 4 )
--						
--						x400214_g_doing = 3
--						print(1111111111)
--		end
--
--	elseif x400214_g_doing==3 then
--			if GetCurrentTime() - x400214_g_PROTECTINFO.StartTime >= 8   then
--			x400214_g_doing=12
--			x400214_CloseTimer(sceneId, x400214_g_PROTECTINFO.ScneneTimerIndex)
--			end
--	end
--end
--
--
----**********************************
----�رռ�ʱ��
----**********************************
--function x400214_CloseTimer( sceneId, TimerIndex )
--	StopTimer(sceneId, TimerIndex)
--	x400214_g_doing =0
--	x400214_g_acceptid =0
--	x400214_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0, PlayerNum = 0, PlayerId= {0,0,0,0,0,0}}
--end



function x400214_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400214_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400214_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400214_OnDeplete( sceneId, selfId )

	return 0
end

function x400214_OnActivateOnce( sceneId, selfId )
end

function x400214_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
