--MisDescBegin 
x300804_g_ScriptId 					= 	300804
x300804_g_MissionName				= 	"����ܻ�" 
x300804_g_MissionInfo				= 	"Ѳ��������Ϣ" 
--MisDescEnd

function x300804_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300804_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y����᡿����ܻ�#r#W"
		local Readme_2 = "  1��#G��ȡ����#W�����#G75������#W��Ա���Խ�ȡ�����񡣴���������������ʱ��#G����#W������ٴν�ȡ��\n\t��������󣬿ɼ�����ȡ����ֱ��������ɡ�#r"
		local Readme_3 = "  2��#G��������#W��ҵ�#G��Ṧ��#WС��50�㣬ÿ���ܻ�����������#G100��#W���������������Ṧ�µ����ӣ���������Ҳ�����ӣ����Ϊÿ�ֿ����#G200��#W������#r"
		local Readme_4 = "  3��#G�������ࣺ#W�ܻ������Ϊ���š��ռ���Ʒ��ɱ��������ʽ��#r"
		local Readme_5 = "  4��#G��������#W�ɹ��������������þ޶��#G���齱��#W��"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300804_g_ScriptId, -1 );
end 

function x300804_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300804_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300804_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300804_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300804_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300804_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300804_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300804_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300804_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end