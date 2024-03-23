
-------------------------
--***********************
--Const
--***********************
-------------------------

x800006_g_ScriptId 					= 800006
x800006_g_MissionName				= "����������Ҫ���"

-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x800006_ProcEnumEvent(sceneId, selfId, targetId, eventId, index)
	AddQuestNumText(sceneId, x800006_g_ScriptId, x800006_g_MissionName,3);
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x800006_ProcEventEntry(sceneId, selfId, targetId)
	BeginQuestEvent(sceneId);
	local Readme_0 = "#Y����������Ҫ���#W#r"
	local Readme_1 = "\t�ڳɼ�˼���У�#G���Ѷ�#W�ܸߵ�#G��Ů˫��#W���Խ�Ϊ���ޡ�#r"
	local Readme_2 = "\t˫������#G���ǰ��#W����2����ӣ�#r"
	local Readme_3 = "\t˫���ȼ�����Ϊ#G40������#W��#r"
	local Readme_4 = "\t˫�����Եĺ��Ѷ���#G1000��#W����#r"
	local Readme_5 = "\t�з������б�����#G����#W�ſ����#r"
	local Readme_6 = "\t�з�������#G131��421������#W�ſ���顣#r"
	local Readme_7 = "\t��Ů˫������#Gͬʱ����#W��ͬʱ#G�������#W������ɽ�顣#r #r"
	local Readme_8 = "\t����������������������Ϳ��Խ���ˡ�#r"
	local Readme_9 = "\t#R��������Ҫ���ܡ�Ѱ�Һ��������񣬲�ͨ�����̩ɽ��#G��Եħ��#R��#G��Եħʥ#R�������������ʱ����ĵ��ߣ����ص����ҵ�#G�������#R���кϳɲ��ܻ�ú�����"
	local Readme = Readme_0..Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6..Readme_7..Readme_8..Readme_9

	
	AddQuestText(sceneId, Readme);
	EndQuestEvent();
	DispatchQuestInfo(sceneId, selfId, targetId, x800006_g_ScriptId, -1);
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x800006_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x800006_ProcAccept(sceneId, selfId, targetId)

end