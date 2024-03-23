-- �������������ĩ����

x701030_g_ScriptId 		= 701030
x701030_g_ScriptName	= "�ύ������"

x701030_g_SubmitItem	= 11990011

x701030_g_TitleInfo		= "\t���Ƿ���������������������˼���淨����ȡ�᣿��Ҫ���գ����ҡ���Ƥ���ͺ��ˣ�ֻҪ�㽻����һ��#G������#W�Ҿ��ܸ������������������Ӧ�ľ��顣��Ȼ��ô����#Yռ��һ��������������#W��\n\t��ô������Ը�⽻����һ��#G������#W�����%d�㾭����\n \n#GС��ʾ��\n\tһ��ֻ���ύһ�������\n\t�н��������͢���Ч��ʱ�ύ�����齱���ᷭ����"

						
function x701030_ProcEventEntry(sceneId, selfId, NPCId, MissionId,idExt)	--����������ִ�д˽ű�
	local level = GetLevel(sceneId,selfId)
	BeginQuestEvent(sceneId)
		--������Ϣ
		local exp =level*163350
		if level < 70 then
			exp =3256200
		elseif level < 75 then
			exp =3499200
		elseif level < 80 then
			exp =12577950
		elseif level < 85 then
			exp =level*163350
		end				
		AddQuestText(sceneId,"#Y"..x701030_g_ScriptName.."#W")
		AddQuestText(sceneId,format(x701030_g_TitleInfo,exp))
		
	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x701030_g_ScriptId, x701030_g_ScriptId)
end

--�о��¼�
function x701030_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	local week = GetWeek()
	if week == 0 or week == 6 then
		AddQuestNumText(sceneId,x701030_g_ScriptId,x701030_g_ScriptName,3,0)
	end
end

function x701030_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

--��ȷ����
function x701030_ProcAccept( sceneId, selfId )
	local week = GetWeek()
	if week == 1 or week == 2 or week == 3 or week == 4 or week == 5 then
				Msg2Player(sceneId, selfId,format("�ύ#{_ITEM%d}ʧ�ܣ�������������������", x701030_g_SubmitItem), 0, 2)
				Msg2Player(sceneId, selfId,format("�ύ#{_ITEM%d}ʧ�ܣ�������������������", x701030_g_SubmitItem), 0, 3)
				return
	end			

	local level = GetLevel(sceneId,selfId)
	if level <65 then
		Msg2Player( sceneId, selfId, "�ܱ�Ǹ����ȼ����ͣ��ύʧ��", 8, 3)
		Msg2Player( sceneId, selfId, "�ܱ�Ǹ����ȼ����ͣ��ύʧ��", 8, 2)
		return
	end

	if level >84 then
		Msg2Player( sceneId, selfId, "�ܱ�Ǹ����ȼ����ߣ��ύʧ��", 8, 3)
		Msg2Player( sceneId, selfId, "�ܱ�Ǹ����ȼ����ߣ��ύʧ��", 8, 2)
		return
	end

	if HaveItemInBag(sceneId, selfId, x701030_g_SubmitItem) <= 0 then
		local msg = format("�ܱ�Ǹ����û��#{_ITEM%d}���ύʧ��", x701030_g_SubmitItem)
		Msg2Player( sceneId, selfId, msg, 8, 3)
		Msg2Player( sceneId, selfId, msg, 8, 2)
		return
	end
	
	local weekcount = 0
	local dayCount = 0
	
	local weekIndex = GetWeekIndex()
	local lastWeek = GetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_DATE[1],MD_FUBEN_QIULONGDAO_DATE[2],MD_FUBEN_QIULONGDAO_DATE[3])
	if lastWeek == weekIndex then
		weekcount = GetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_DAYCOUNT[1],MD_FUBEN_QIULONGDAO_DAYCOUNT[2],MD_FUBEN_QIULONGDAO_DAYCOUNT[3] )
	end
			
	local today = GetDayOfYear()
	local lastDay = GetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAY[1],MD_FUBEN_QIULONGDAO_TODAY[2],MD_FUBEN_QIULONGDAO_TODAY[3] )
	if today == lastDay then	
		dayCount = GetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAYCOUNT[1],MD_FUBEN_QIULONGDAO_TODAYCOUNT[2],MD_FUBEN_QIULONGDAO_TODAYCOUNT[3] )
	end
	
	if weekcount > 18 or dayCount > 6 then
		local msg = "�ܱ�Ǹ���������Ѿ�û��ʣ�����������"
		Msg2Player( sceneId, selfId, msg, 8, 3)
		Msg2Player( sceneId, selfId, msg, 8, 2)
		return
	end
	
	local date = GetQuestData(sceneId, selfId, MD_FUBEN_WEEKEND_SANFAN_DATE[1],MD_FUBEN_WEEKEND_SANFAN_DATE[2],MD_FUBEN_WEEKEND_SANFAN_DATE[3])
	if today == date then
		local msg = "�ܱ�Ǹ��һ��ֻ���ύһ��������"
		Msg2Player( sceneId, selfId, msg, 8, 3)
		Msg2Player( sceneId, selfId, msg, 8, 2)
		return
	end
	
	if weekIndex ~= lastWeek then
		SetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_DATE[1], MD_FUBEN_QIULONGDAO_DATE[2], MD_FUBEN_QIULONGDAO_DATE[3], weekIndex)
		SetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_DAYCOUNT[1], MD_FUBEN_QIULONGDAO_DAYCOUNT[2], MD_FUBEN_QIULONGDAO_DAYCOUNT[3], 3)
	else
		SetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_DAYCOUNT[1], MD_FUBEN_QIULONGDAO_DAYCOUNT[2], MD_FUBEN_QIULONGDAO_DAYCOUNT[3], weekcount+3)
	end
	
	if today ~= lastDay then
		SetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAY[1], MD_FUBEN_QIULONGDAO_TODAY[2], MD_FUBEN_QIULONGDAO_TODAY[3], today)
		SetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAYCOUNT[1], MD_FUBEN_QIULONGDAO_TODAYCOUNT[2], MD_FUBEN_QIULONGDAO_TODAYCOUNT[3], 3)
	else
		SetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAYCOUNT[1], MD_FUBEN_QIULONGDAO_TODAYCOUNT[2], MD_FUBEN_QIULONGDAO_TODAYCOUNT[3], dayCount+3)
	end
	
	SetQuestData(sceneId, selfId, MD_FUBEN_WEEKEND_SANFAN_DATE[1], MD_FUBEN_WEEKEND_SANFAN_DATE[2], MD_FUBEN_WEEKEND_SANFAN_DATE[3], today)
	
	DelItem(sceneId, selfId, x701030_g_SubmitItem, 1)
	
	local exp =level*163350
		if level < 70 then
			exp =3256200
		elseif level < 75 then
			exp =3499200
		elseif level < 80 then
			exp =12577950
		elseif level < 85 then
			exp =level*163350
		end				
	if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
		AddExp(sceneId, selfId, exp*2)
		Msg2Player(sceneId, selfId,format("�ύ������ɹ�������������»����#G����%d#cffcf00��",exp*2), 0, 2)
		Msg2Player(sceneId, selfId,format("�ύ������ɹ�������������»����#G����%d#cffcf00��",exp*2), 0, 3)
	else	
		AddExp(sceneId, selfId, exp)
		Msg2Player(sceneId, selfId,format("�ύ������ɹ��������#G����%d#cffcf00��",exp), 0, 2)
		Msg2Player(sceneId, selfId,format("�ύ������ɹ��������#G����%d#cffcf00��",exp), 0, 3)
	end
end