





x280000_g_scriptId = 280000 
--x280000_g_Impact1 = 7528 --Ч��ID�������Ӻ���
x280000_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}


function x280000_ProcEventEntry( sceneId, selfId, BagIndex )
			local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, -1 )
    
    if bCplay == 1 then
   -- LuaScenceM2Player (sceneId,  selfId,  "�����Ǻܴ���ģ�", -1, 5, -1)
    LuaScenceM2Near(sceneId,  selfId, "�غ�����Ȱũɣ�����浱��Ϊ���ߡ�", 5, -1)

			
    end

    return bCplay
		
	

end




function x280000_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x280000_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x280000_OnConditionCheck( sceneId, selfId )
	return 0
end

function x280000_OnDeplete( sceneId, selfId )

	return 0
end

function x280000_OnActivateOnce( sceneId, selfId )
end

function x280000_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
