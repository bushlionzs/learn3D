-------------------------------------------------
-- �ֽ𸱱�
-------------------------------------------------
x700082_g_ScriptId = 700082



x700082_g_Fuben_list = { 
							{name="�����顿����ף��ׯ",		scriptid = 700030, starttime=0*60+0, endtime=24*60, levelmin=75, levelmax=100},
							{name="�����顿���������",		scriptid = 700003, starttime=0*60+0, endtime=24*60, levelmin=60, levelmax=100},
							{name="�����顿���������",		scriptid = 700024, starttime=0*60+0, endtime=24*60, levelmin=40, levelmax=100},
							{name="�����顿����������",		scriptid = 700028, starttime=0*60+0, endtime=24*60, levelmin=20, levelmax=100},
							
						}



x700082_g_Fuben_EnterInfoList = {
									"\t��ʱǨ���ʹºš������顱�����ںú�˳�����룬��æʩչ�����Ƿ������ӳ�������ף��ׯ�ڻ������أ�����������ʱǨ�������ȴδ���ӳ���ӡ���\n#Y����ʱ�䣺#Wȫ�쿪��\n#Y������ʾ��#W3�����ϵĶ��飬���ܽ���ø�����#Gͬʱÿ����Ա���Ͻ�1�������#R��Ҫ�Ź��κ�һ�����������ܻᵼ�����޷��������а�\n#Y����˵����#W���һ�α�����������Ի��#G������ͨף��ׯ3�������ľ��齱�������ս����ּ���ҲΪ��ͨף��ׯ������3������Ҳ��������һ�����пɽ����ף��ׯ3������������",

									"\tǰ�գ���������һ���Σ����μ��Լ������������۴���һ���챦����ɽ���񺣣�����֪ƾ����ɱ���ɽ������ơ�\n\t�����������������ҵ�Ѱ���Ǵ�˵�еĽ�ɽ���񺣣����Ҷ෽̽�飬���ڲ�������������ɽ��������ǧ˿���Ƶ���ϵ��������ʦ��������Ѿ����д������ĵ����ǽ��������\n\t���Ƿ�����������ĵ��ӻر�����������ھ�Ȼ�����Ǵ�Ԫ�����ʿ������������ɽ�������˻��ڣ���ͼ����ʦ������\n#Y����ʱ�䣺#Wȫ�쿪�ţ�\n#Y������ʾ��#W3�����ϵĶ��飬���ܽ���ø�����#Gͬʱÿ����Ա���Ͻ�1�������#R��Ҫ�Ź��κ�һ�����������ܻᵼ�����޷��������а�\n#Y����˵����#W���һ�α�����������Ի��#G������ͨ�����3�������ľ��齱�������ս����ּ���ҲΪ��ͨ��������3������Ҳ��������һ�����пɽ���Ĳ����3������������",

									"\t�ν��ս�����֮�������������䣬�����ͻȻ�������˶�������֮�У��ҵ�����赵���ֻҪ�ܹ����������ں����֮�еİ�λ���۵Ļ��Ǿ��ܹ���͸�����Ԥ��δ������֮�¡�\n#Y����ʱ�䣺#Wȫ�쿪�ţ�\n#Y������ʾ��#W3�����ϵĶ��飬���ܽ���ø�����#Gͬʱÿ����Ա���Ͻ�1�������#R��Ҫ�Ź��κ�һ�����������ܻᵼ�����޷��������а�\n#Y����˵����#W���һ�α�����������Ի��#G������ͨ�����3�������ľ��齱�������ս����ּ���ҲΪ��ͨ����赸�����3������Ҳ��������һ�����пɽ���ĺ����3������������",

									"\t�Դӹ����񽫾�ս��������������������������������ħ���������У����������������ǰ���µĽ������ʱ������ƽ���ʧЧ��һ����ħ������������������������ŷ����������ã����õĽ����������˽��ֳֻ�����������ԭ��ؽ��ܵ���֮�֡�\n\t��٩��������ǰ�������������游��������ս�ܵ�ԭ�򣬲�ȡ����ʧ�ġ������������������ʱ�򣬼�����ҪһȺ���ո�ǿ������ʮ�����ʿ����������������Ѩ����ħ���������ûء�������������\n#Y����ʱ�䣺#Wȫ�쿪�ţ�\n#Y������ʾ��#W3�����ϵĶ��飬���ܽ���ø�����#Gͬʱÿ����Ա���Ͻ�1�������#R��Ҫ�Ź��κ�һ�����������ܻᵼ�����޷��������а�\n#Y����˵����#W���һ�α�����������Ի��#G������ͨ������3�������ľ��齱�������ս����ּ���ҲΪ��ͨ������������3������Ҳ��������һ�����пɽ����������3������������"																	
								 
								 }



function x700082_ProcEventEntry(sceneId, selfId, NPCId, MissionId,nIndex)	--����������ִ�д˽ű�
	
	if GetGameOpenById(1022)<=0 then
		x700082_ShowTips(sceneId, selfId, "�˻�ѹر�")
		return 0
	end

	if nIndex==nil then
		return 0
	end


	x700082_DispatchXianJinFubenInfo( sceneId, selfId, NPCId,nIndex )
	
end


--**********************************

--�о��¼�

--**********************************

function x700082_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

	if GetGameOpenById(1022)<=0 then
		
		return 0;
	end
	
	if IsPlayerStateNormal(sceneId,selfId ) <= 0 then
		return
	end


	local nIndex = 0




	local nLevel  = GetLevel(sceneId,selfId)


	for i,item in x700082_g_Fuben_list do
		nIndex = nIndex+1
		if nLevel>=item.levelmin and nLevel<=item.levelmax then
			AddQuestNumText(sceneId, x700082_g_ScriptId, item.name,14,nIndex)
		end
	end

	

	

	
	
	
			
end







function x700082_DispatchXianJinFubenInfo( sceneId, selfId, NPCId, nIndex )

	SetQuestData(sceneId, selfId, MD_XIANJIN_FUBEN_TALK_PARAM[1], MD_XIANJIN_FUBEN_TALK_PARAM[2],MD_XIANJIN_FUBEN_TALK_PARAM[3], nIndex );
	
	BeginQuestEvent(sceneId)

		
		AddQuestText(sceneId,"#Y"..x700082_g_Fuben_list[nIndex].name)
		AddQuestText(sceneId,x700082_g_Fuben_EnterInfoList[nIndex])
		
		

	EndQuestEvent()





	DispatchQuestInfo(sceneId, selfId, NPCId, x700082_g_ScriptId, -1);

	
	
end


---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x700082_ProcAcceptCheck( sceneId, selfId, NPCId )

	if GetGameOpenById(1022)<=0 then
		
		return 0
	end

    return 1
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x700082_ProcAccept( sceneId, selfId )

	
	if GetGameOpenById(1022)<=0 then
		
		return 0
	end

	x700082_OnNpcTalkEnterFuben_XJ( sceneId, selfId)
	
end


------------------------------------------------------------------------
-- ��ȡbuff�ӿ�
----------------------------------------------------------------------

function x700082_OnNpcTalkEnterFuben_XJ( sceneId, selfId)

	if GetGameOpenById(1022)<=0 then
		x700082_ShowTips(sceneId, selfId, "�˻�ѹر�")
		return 0
	end

	local nIndex = GetQuestData(sceneId, selfId, MD_XIANJIN_FUBEN_TALK_PARAM[1], MD_XIANJIN_FUBEN_TALK_PARAM[2],MD_XIANJIN_FUBEN_TALK_PARAM[3] );

	CallScriptFunction(FUBEN_COMMON_SCRIPT, "OnRequestEnterFuben", sceneId, selfId, 1, 0, x700082_g_Fuben_list[nIndex].scriptid);
	

	
end


function x700082_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end
