--MisDescBegin 
x300937_g_ScriptId 					= 	300937
x300937_g_MissionName				= 	"����ؽ��ܡ�" 
x300937_g_MissionInfo				= 	"���������ս˵����" 
--MisDescEnd

function x300937_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300937_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y���������ս����#r #r#W"
		local Readme_2  = "1���������ս����#Gÿ����16�㿪��#W��#G17�����#W��#r"
		local Readme_3  = "2����ÿ����16��00-17��00�ڼ䣬�뱨����������ͬ�ĳ�Ա��ɱ����ڵ����ͼ�ڣ���ñ��������ʱ��Ϊ���ռ���ߣ�ͬʱ��Ҫ�������ͼ�ڲ����������ҹ����ɱ��#r"
		local Readme_4  = "3��#G���������ս����ǰ#W������������������ͬ�����Ĺ����ɱ���ͼ�ڣ������ռ���߱����#r"
		local Readme_5  = "4��#G�����������ս����ʱ��ʱ#W����ɱ���ͼ�ڲ��ҳɹ�����ס��ռ������ͼ�ڵİ���ø���ص�ӵ��Ȩ��#r"
		local Readme_6  = "5�������ͼ�ڸ���������ʹ�ð���ټ�������ټ�������з���#r#r"
		local Readme_7  = "6�����ͼ��ÿ10���ӻ�ظ���Ѫ����5%��������������ʱ��û�а���ɱ���ͼ�ڣ�������Ϊ��ռ��״̬��#r"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6..Readme_7
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300937_g_ScriptId, -1 );
end 

function x300937_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300937_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300937_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300937_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300937_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300937_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300937_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300937_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300937_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end