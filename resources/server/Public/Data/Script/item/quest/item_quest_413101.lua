--ҩ��

--MisDescBegin
x413101_g_ScriptId = 413101
x413101_g_MissionId = 1003
x413101_g_MissionKind = 13
x413101_g_LevelLess	= 	15 
x413101_g_Name	="Ҥ��������" 
x413101_g_DemandItem ={{id=13010082,num=1}}
x413101_g_ExtTarget={{type=20,n=1,target="�õ�һ�����������"}}
x413101_g_MissionHelp =	""
x413101_g_MissionName="���߱�"
x413101_g_MissionInfo="\t�ҵĳ��߱ޱ������ڵ����ϵģ�����������������ˣ���Ҥ����������ҵ����ǣ����Ҷ�س��߱ްɡ�"  --��������
x413101_g_MissionCompleted="\t�õ�лл���ˣ�"					--�������npc˵���Ļ�
x413101_g_ContinueInfo=""
x413101_g_BonusMoney1 =1000
x413101_g_BonusMoney2 =0
x413101_g_BonusMoney3 =0
x413101_g_BonusItem	=	{}
x413101_g_BonusChoiceItem ={}
x413101_g_ExpBonus = 0

--MisDescEnd

--**********************************

--������ں���

--**********************************

function x413101_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�

	if GetItemCount(sceneId,selfId,x413101_g_DemandItem[1].id) > 0 then
				BeginQuestEvent(sceneId)
        AddQuestText(sceneId,x413101_g_MissionCompleted)
		    if x413101_g_BonusMoney1 > 0 then
		    local addmoney =x413101_g_BonusMoney1*GetLevel(sceneId, selfId)
							AddQuestMoneyBonus1(sceneId, addmoney )
				end
		    EndQuestEvent()
        DispatchQuestContinueInfo(sceneId, selfId, targetId, x413101_g_ScriptId, x413101_g_MissionId)
  elseif GetItemCount(sceneId,selfId,x413101_g_DemandItem[1].id) == 0 then
  			BeginQuestEvent(sceneId)
        AddQuestText(sceneId,x413101_g_MissionInfo)
		    EndQuestEvent()
        DispatchQuestEventList(sceneId, selfId, targetId)
  
  end
end



--**********************************

--�о��¼�

--**********************************

function x413101_ProcEnumEvent(sceneId, selfId, targetId, MissionId)


	if  x413101_CheckPushList(sceneId, selfId, targetId) > 0 then
		AddQuestNumText(sceneId, x413101_g_ScriptId, x413101_g_MissionName,8)
	end
	
end



--**********************************

--����������

--**********************************

function x413101_ProcAcceptCheck(sceneId, selfId, targetId)

					return 1

end


--**********************************

--���鿴����

--**********************************

function x413101_CheckPushList(sceneId, selfId, targetId)
        		           		return 1
      
	
end

--**********************************

--����

--**********************************

function x413101_ProcAccept(sceneId, selfId)

	                                                  
     	                                    
	     
end



--**********************************

--����

--**********************************

function x413101_ProcQuestAbandon(sceneId, selfId, MissionId)

	

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x413101_CheckSubmit( sceneId, selfId, targetId)
	

end



--**********************************

--�ύ

--**********************************

function x413101_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
		local addmoney =x413101_g_BonusMoney1*GetLevel(sceneId, selfId)
		--AddExp(sceneId, selfId, x413101_g_ExpBonus)
		AddMoney( sceneId, selfId, 0, addmoney )
		DelItem(sceneId, selfId, x413101_g_DemandItem[1].id, x413101_g_DemandItem[1].num)
	
	

	
end



--**********************************

--ɱ����������

--**********************************

function x413101_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	 

end



--**********************************

--���������¼�

--**********************************

function x413101_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x413101_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end


