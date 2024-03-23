--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x910017_g_ScriptId = 910017

--�����Ƕ�̬**************************************************************

--�����ı�����
x910017_g_MissionName="110������װ"


x910017_g_ZhiYeItemBonus1={{id=10014001,num=1},{id=10074001,num=1},{id=10204001,num=1},{id=10214001,num=1},{id=10224001,num=1},{id=10234001,num=1}}
x910017_g_ZhiYeItemBonus2={{id=10244001,num=1},{id=10254001,num=1},{id=10264001,num=1},{id=10274001,num=1},{id=10284001,num=1},{id=10294001,num=1}}

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x910017_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
			local zhiye = GetZhiye(sceneId, selfId)
			
			local ret
			BeginAddItem(sceneId)
				for i, item in x910017_g_ZhiYeItemBonus1 do
					if i < 3 then
						AddItem( sceneId,item.id+10000*zhiye-1000+2, item.num )
					else
						AddItem( sceneId,item.id+10*zhiye-1000+2, item.num )
					end
				end			
			ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				BeginAddItem(sceneId)
					for i, item in x910017_g_ZhiYeItemBonus2 do
						AddItem( sceneId,item.id+10*zhiye-1000+2, item.num )
					end
				ret = EndAddItem(sceneId,selfId)
				--���ְҵ��Ʒ
				if ret > 0 then
					AddItemListToPlayer(sceneId,selfId)
					BeginQuestEvent(sceneId)
						local strText = "������һ��110������װ"
						AddQuestText(sceneId,strText);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					AddQuestText(sceneId,"����110������װ�����պ��ˣ�")
				else
				--ְҵ��Ʒû�мӳɹ�
					BeginQuestEvent(sceneId)
						local strText = "�����ռ䲻�㣬�޷����ȫ����Ʒ��"
						AddQuestText(sceneId,strText);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					AddQuestText(sceneId,"����һ����110������װ��")
				end	
			else
				BeginQuestEvent(sceneId)
					local strText = "�����ռ䲻�㣬�޷������Ʒ��"
					AddQuestText(sceneId,strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				AddQuestText(sceneId,"�������±�������������ȡ��װ�ɣ�")
			end							
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end

--**********************************
--�о��¼�
--**********************************
function x910017_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x910017_g_ScriptId,x910017_g_MissionName);
end



--**********************************
--����
--**********************************
function x910017_ProcAccept( sceneId, selfId )
end

--**********************************
--����
--**********************************
function x910017_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x910017_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x910017_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x910017_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x910017_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x910017_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x910017_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
