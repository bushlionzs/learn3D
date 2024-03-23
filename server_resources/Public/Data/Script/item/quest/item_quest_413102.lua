--ҩ��

--MisDescBegin
x413102_g_ScriptId = 413102
x413102_g_MissionId = 1004
x413102_g_MissionKind = 13
x413102_g_LevelLess	= 	15 
x413102_g_Name	="�����" 
x413102_g_DemandItem ={{id=11990007,num=4}}
x413102_g_ExtTarget={{type=20,n=1,target="�õ�4������֩����"}}
x413102_g_MissionHelp =	""
x413102_g_MissionName="���ص�֩����"
x413102_g_MissionInfo="    ������ܴ����ĸ����ص�֩�������Ҳ��������ġ�"  --��������
x413102_g_MissionCompleted="    �ܺõ�ʩ�����ϣ�������Ľ�����"					--�������npc˵���Ļ�
x413102_g_ContinueInfo=""
x413102_g_BonusMoney1 =40
x413102_g_BonusMoney2 =0
x413102_g_BonusMoney3 =0
x413102_g_BonusItem	=	{}
x413102_g_BonusChoiceItem ={10016002,10026002,10036002,10046002,10056002,10066002,10352002,10362002,10372002,10382002,10392002,10402002}
x413102_g_ExpBonus = 0

--MisDescEnd

--**********************************

--������ں���

--**********************************

function x413102_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�

	if GetItemCount(sceneId,selfId,x413102_g_DemandItem[1].id) > 3 then
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId,x413102_g_MissionCompleted)
		    if x413102_g_BonusMoney1 > 0 then
					AddQuestMoneyBonus1(sceneId, x413102_g_BonusMoney1 )
			end
			for i=0, 11 do
				if GetZhiye( sceneId, selfId)==i then
						local ii =i+1
					    AddQuestItemBonus(sceneId, x413102_g_BonusChoiceItem[ii], 1)
				end
			end
		EndQuestEvent()
        DispatchQuestContinueInfo(sceneId, selfId, targetId, x413102_g_ScriptId, x413102_g_MissionId)
 	elseif GetItemCount(sceneId,selfId,x413102_g_DemandItem[1].id) < 4 then
  		BeginQuestEvent(sceneId)
        AddQuestText(sceneId,x413102_g_MissionInfo)
		EndQuestEvent()
        DispatchQuestEventList(sceneId, selfId, targetId)
  
  end
end



--**********************************

--�о��¼�

--**********************************

function x413102_ProcEnumEvent(sceneId, selfId, targetId, MissionId)


	if  x413102_CheckPushList(sceneId, selfId, targetId) > 0 then
		AddQuestNumText(sceneId, x413102_g_ScriptId, x413102_g_MissionName,8)
	end
	
end



--**********************************

--����������

--**********************************

function x413102_ProcAcceptCheck(sceneId, selfId, targetId)

					return 1

end


--**********************************

--���鿴����

--**********************************

function x413102_CheckPushList(sceneId, selfId, targetId)
        		if IsQuestHaveDone(sceneId, selfId, x413102_g_MissionId) == 0 then
        		           		return 1
       	end
       return 0
	
end

--**********************************

--����

--**********************************

function x413102_ProcAccept(sceneId, selfId)

	                                                  
     	                                    
	     
end



--**********************************

--����

--**********************************

function x413102_ProcQuestAbandon(sceneId, selfId, MissionId)

	

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x413102_CheckSubmit( sceneId, selfId, targetId)
	

end



--**********************************

--�ύ

--**********************************

function x413102_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)

		--AddExp(sceneId, selfId, x413102_g_ExpBonus)
		
		for i=0, 11 do
			if GetZhiye( sceneId, selfId)==i then
					local ii =i+1
					
					BeginAddItem(sceneId)
					AddItem( sceneId, x413102_g_BonusChoiceItem[ii], 1 )
					local ret = EndAddItem(sceneId,selfId)
					if ret > 0 then
						
						AddItemListToPlayer(sceneId,selfId)
						AddMoney( sceneId, selfId, 1, x413102_g_BonusMoney1 )
						DelItem(sceneId, selfId, x413102_g_DemandItem[1].id, x413102_g_DemandItem[1].num)
						QuestCom(sceneId, selfId, x413102_g_MissionId)
					else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"��Ʒ���������޷��õ�������Ʒ��")
						EndQuestEvent(sceneId)
						DispatchQuestTips(sceneId,selfId)
					end
			end
		end
	
	

	
end



--**********************************

--ɱ����������

--**********************************

function x413102_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	 

end



--**********************************

--���������¼�

--**********************************

function x413102_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x413102_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end

