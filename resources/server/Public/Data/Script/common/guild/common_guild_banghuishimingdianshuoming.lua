--MisDescBegin 
x300789_g_ScriptId 					= 	300789
x300789_g_MissionInfo				= 	"Ѳ��������Ϣ" 
--MisDescEnd

function x300789_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300789_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y����᡿���ʹ����#r#W"
		local Readme_2 = "  1��#Gʹ�����ã�#Wʹ����ͨ�����ļ������ᰵս�����ս�����籭������á�#r"
		local Readme_3 = "  2��#Gʹ������ʾ��#Wǰ�����ִ����ᵱǰʹ���㣬�������ִ���ǰ���ȼ�������ʹ���㡣#r"
		local Readme_4 = "  3��#Gʹ������;��#Wÿ���С���ĩ����ݰ��ȼ�����ʹ���㲢��ʣ��ʹ������0��#r"
		local Readme_5 = "  4��#Gʹ����Ӱ�죺#W����ᵱǰʹ����ﵽ���ȼ�������ʹ���㣬�ڽ����գ�ÿ��15�պ�ÿ�����һ���24�㣩��������#G�߶��ᾭ��#W������#r"
		--local Readme_6 = "  5��#G��������Ӱ�죺#Wÿ����һ����Ա��ʹ����+1��ÿ�뿪��������һ����Ա��ʹ����-2��#r"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300789_g_ScriptId, -1 );
end 

function x300789_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300789_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300789_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300789_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300789_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300789_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300789_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300789_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300789_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end