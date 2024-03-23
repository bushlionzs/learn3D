
x561101_g_ScriptId = 561101
x561101_g_MissionName = "��ȡ��������"

--һ�������ʾ�Ľ�Ʒ��
x561101_g_MaxOnceAwardNum = 5	

--��Ʒ�������
x561101_g_MaxAwardCount = 2000

x561101_g_GetAwardScript = 561103

--�����NPC��
function x561101_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x561101_g_ScriptId,x561101_g_MissionName,3,-1)
	
end



--�������ť������������ִ�д˽ű�
function x561101_ProcEventEntry( sceneId, selfId, targetId,state,index )	

	if index == -1 then
		
		for i=0, x561101_g_MaxOnceAwardNum-1 do
			SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_INDEX1+i, -1 )
			SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_DB_INDEX1+i, -1 )
			SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_NUM1+i, -1 )
		end

		--��ѯ��Ʒ��Ϣ
		QueryAwardInfo( sceneId, selfId )
		--��¼��ǰ�콱NPCID���Ա��ڷ��ض�λ
		SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_NPCID,targetId  )

	else
		CallScriptFunction( x561101_g_GetAwardScript, "ProcEventEntry", sceneId, selfId ,targetId,state,index) 
	end

end

--��ʾ��Ʒ��Ϣ
function x561101_OnShowAwardInfo( sceneId, selfId, awardNum, awardType )

	if GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_NPCID ) ~= -1 then
			
		if awardNum < 1 then
			--û�н���
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y��Ʒ��ȡ")
			AddQuestText(sceneId,"\t�ܱ�Ǹ��û�в�ѯ�����Ľ�����¼�����Ժ�������")
			EndQuestEvent(sceneId)
			DispatchQuestEventList( sceneId,selfId,GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_NPCID ) )
			return 
		end

		BeginQuestEvent(sceneId)

        local bShow = 0
		for i=0, x561101_g_MaxOnceAwardNum-1 do
			--�жϽ�Ʒ�����Ƿ���Ч
			local index = GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_INDEX1+i )

			if index >= 0 and index < x561101_g_MaxAwardCount then
			
				if awardType == 1 then
					--CDKEY�콱�� ����Ҫ����ڴβ���
					local haveSpace = CallScriptFunction( x561101_g_GetAwardScript, "HaveBagSpace", sceneId, selfId ,RD_HUMAN_AWARE_INDEX1+i, RD_HUMAN_CURR_AWARD_NPCID ) 
					if haveSpace == 1 then
						local dbIndex = GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_INDEX1+i+x561101_g_MaxOnceAwardNum )
						SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX, dbIndex )
	
						CallScriptFunction( x561101_g_GetAwardScript, "ProcAccept", sceneId, selfId )
					end
					
					return 
				end
				
				local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--���������ӱ��еõ�����
				local ItemNum = GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_NUM1+i )

				if ItemNum > 1 then
					title = format("%s * %d",title,ItemNum)
				end
				if bShow == 0 then
    				AddQuestText(sceneId,"#Y��Ʒ��ȡ")
    				AddQuestText(sceneId,"\t��������ȡ���½�Ʒ��")
    				bShow = 1
				end
				AddQuestNumText(sceneId,x561101_g_ScriptId,title,0,RD_HUMAN_AWARE_INDEX1+i)
			end
		end

		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_NPCID ) )
	end

end

--�����ȷ����
function x561101_ProcAcceptCheck( sceneId, selfId, NPCId )
	
	--BeginQuestEvent(sceneId);AddQuestText(sceneId,"��ťA��Ӧ����������");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)	
	--Msg2Player(sceneId,selfId,"��ťA��Ӧ����������",8,2)

end



--**********************************
--����
--**********************************
function x561101_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x561101_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x561101_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x561101_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x561101_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x561101_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x561101_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x561101_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end