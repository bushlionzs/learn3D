--ע�⣺

--��Ʒ���ܵ��߼�ֻ��ʹ�û������ܺͽű���ʵ��

--�ű�:

--�����ǽű�����:


--3001.lua
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�



--Ч����ID
x417004_g_Impact1 = 7043
x417004_g_Impact_OK			=	7058
x417004_g_Impact_Failed	=	7059

--**********************************
--�¼��������
--**********************************
function x417004_ProcEventEntry( sceneId, selfId, bagIndex,rorf )
	if rorf == 1 then
		local str
		local multExp = GetWanFaExpMult( sceneId, selfId )
	--�����û��ָ����buff,����У����Ӷ౶���飬������ٶ౶����
		if IsHaveSpecificImpact( sceneId, selfId, x417004_g_Impact1 ) > 0 then
			multExp = multExp - 0.1
			if multExp < 1.0 then multExp = 1.0 end
			str = "�㱻�׻����ˣ�"
			SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x417004_g_Impact_Failed, 0)
		else
			multExp = multExp + 0.03
			str = "��ɹ�������׻���"
			
			local bonusExp = floor(GetLevel( sceneId, selfId ) * 80 * multExp)
			AddExp( sceneId,selfId, bonusExp )
			str = str.."��þ��飺"..bonusExp
			SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x417004_g_Impact_OK, 0)
		end
		SetWanFaExpMult(  sceneId, selfId,  multExp )
		
		str = str.."��ǰ���鱶�ʣ�"..format("%.2f", multExp)

		BeginQuestEvent( sceneId )
		AddQuestText( sceneId, str )
		EndQuestEvent()
		DispatchQuestTips( sceneId, selfId )
	end
end


