--MisDescBegin 
x300773_g_ScriptId 					= 	300719
x300773_g_MissionName				= 	"��������츳" 
x300773_g_MissionInfo				= 	"Ѳ��������Ϣ" 
--MisDescEnd

function x300719_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300719_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y����᡿��������츳#r#W"
		local Readme_2 = "  1��#G�����츳�о���#W�������츳���ļ���ֻ�а����ܹ��о���ֻ�е�������ڰ���о�����ؼ��ܵ�ʱ�򣬲��ܽ��м���ѧϰ��#r"
		local Readme_3 = "  2��#G�����츳ѧϰ��#W������츳�ﵽ10��ʱ�����Կ�ʼ�������츳�����ɣ��������츳�����ɵĵȼ����츳�ȼ���أ�����Ҫһ�����츳�ȼ�������ɡ������츳�����ɡ�ѧϰ�����츳��Ҫ�ﹱ��������������ѧϰʱ����Ҫ����������������ÿ���������ĵİﹱ��������������ͬ��#r"
		local Readme = Readme_1..Readme_2..Readme_3
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300773_g_ScriptId, -1 );
end 

function x300719_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300719_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300719_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300719_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300719_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300719_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300719_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300719_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300719_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end