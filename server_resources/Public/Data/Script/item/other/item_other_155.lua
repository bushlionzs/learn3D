--新手成长包	12030475 
------------------------------------------------------------------------------------------
--一般物品的默认脚本

x418155_item_key_array = {
	[ 12030475 ] = 1 , 
	[ 12030476 ] = 2 , 
	[ 12030477 ] = 3 ,
	[ 12030478 ] = 4 ,
	[ 12030479 ] = 5 ,
	[ 12030480 ] = 6 ,
	[ 12030481 ] = 7 ,
	[ 12030482 ] = 8 ,
}


x418155_item_random_list = {
	{ 10200020 , 10230020 , 10240020 , 10250020 , 10260020 , 10270020 },--新手蓝装
	{ 10246092 , 10286092 , 10296072 }--极品武器

};


x418155_item_array = {
	{ lv = 10 , clr_name = "#Y新手成长包（10级）" , item_list = "1把极品武器和小钱包。" },
	
	{ lv = 20 , clr_name = "#Y新手成长包（20级）" , item_list = "1件极品首饰，1件红虎披风，小钱包和10个世传水晶。" },
	
	{ lv = 30 , clr_name = "#Y新手成长包（30级）" , item_list = "10个初级龙眼石，1个垂耳兔降世符，小钱包，10个世传水晶和1个三番令。" },
	
	{ lv = 40 , clr_name = "#Y新手成长包（40级）" , item_list = "20个初级龙眼石，20瓶杰克丹尼，10个国传水晶，1个修行草和5个天王补心丹。" },
	
	{ lv = 50 , clr_name = "#Y新手成长包（50级）" , item_list = "10个中级龙眼石，30个国传水晶，20瓶杰克丹尼，5本还童书和3个藏宝令。" },
	
	{ lv = 60 , clr_name = "#Y新手成长包（60级）" , item_list = "20个中级龙眼石，小钱包，15瓶芝华士，5个龟鹿二仙胶和1个猎枭降世符。" },
	
	{ lv = 65 , clr_name = "#Y新手成长包（65级）" , item_list = "15个高级龙眼石，小钱包，10个神传水晶，5个紫檀木炭和1个次生钻石矿。" },
	
	{ lv = 70 , clr_name = "#Y新手成长包（70级）" , item_list = "30个高级龙眼石，小钱包，15个神传水晶，1个高级洗石剂和1个圣徒级洗石剂。" }
};



x418155_item_list = {

	{
		lv = 10 , array = 
		{
			{ metier = 0 , list = { { id = 12030476 , num = 1 } , { id = 10010020 , num = 1 } , { id = 12030319  , num = 1 } } } , 
			{ metier = 1 , list = { { id = 12030476 , num = 1 } , { id = 10020020 , num = 1 } , { id = 12030319  , num = 1 } } } , 
			{ metier = 2 , list = { { id = 12030476 , num = 1 } , { id = 10030020 , num = 1 } , { id = 12030319  , num = 1 } } } , 
			{ metier = 3 , list = { { id = 12030476 , num = 1 } , { id = 10040020 , num = 1 } , { id = 12030319  , num = 1 } } } , 
			{ metier = 4 , list = { { id = 12030476 , num = 1 } , { id = 10050020 , num = 1 } , { id = 12030319  , num = 1 } } } , 
			{ metier = 5 , list = { { id = 12030476 , num = 1 } , { id = 10060020 , num = 1 } , { id = 12030319  , num = 1 } } } , 
		  { metier = 6 , list = { { id = 12030476 , num = 1 } , { id = 10350002 , num = 1 } , { id = 12030319  , num = 1 } } } , 
			{ metier = 7 , list = { { id = 12030476 , num = 1 } , { id = 10360002 , num = 1 } , { id = 12030319  , num = 1 } } } , 
			{ metier = 8 , list = { { id = 12030476 , num = 1 } , { id = 10370002 , num = 1 } , { id = 12030319  , num = 1 } } } , 
			{ metier = 9 , list = { { id = 12030476 , num = 1 } , { id = 10380002 , num = 1 } , { id = 12030319  , num = 1 } } } , 
			{ metier = 10 , list = {{ id = 12030476 , num = 1 } , { id = 10390002 , num = 1 } , { id = 12030319  , num = 1 } } } , 
			{ metier = 11 , list = {{ id = 12030476 , num = 1 } , { id = 10400002 , num = 1 } , { id = 12030319  , num = 1 } } } ,
		}
	} ,

	{
		lv = 20 , array = 
		{
			{ metier = 0 , list = { { id = 12030477 , num = 1 } , { id = 10246092 , num = 1 } , { id = 11000200 , num = 10 } , { id = 12030320 , num = 1 }, { id = 10222001 , num = 1 } } } ,
			{ metier = 1 , list = { { id = 12030477 , num = 1 } , { id = 10246092 , num = 1 } , { id = 11000200 , num = 10 } , { id = 12030320 , num = 1 }, { id = 10222001 , num = 1 } } } ,
			{ metier = 2 , list = { { id = 12030477 , num = 1 } , { id = 10246092 , num = 1 } , { id = 11000200 , num = 10 } , { id = 12030320 , num = 1 }, { id = 10222001 , num = 1 } } } ,
			{ metier = 3 , list = { { id = 12030477 , num = 1 } , { id = 10246092 , num = 1 } , { id = 11000200 , num = 10 } , { id = 12030320 , num = 1 }, { id = 10222001 , num = 1 } } } ,
			{ metier = 4 , list = { { id = 12030477 , num = 1 } , { id = 10246092 , num = 1 } , { id = 11000200 , num = 10 } , { id = 12030320 , num = 1 }, { id = 10222001 , num = 1 } } } ,
			{ metier = 5 , list = { { id = 12030477 , num = 1 } , { id = 10246092 , num = 1 } , { id = 11000200 , num = 10 } , { id = 12030320 , num = 1 }, { id = 10222001 , num = 1 } } } ,
		  { metier = 6 , list = { { id = 12030477 , num = 1 } , { id = 10246092 , num = 1 } , { id = 11000200 , num = 10 } , { id = 12030320 , num = 1 }, { id = 10222001 , num = 1 } } } ,
			{ metier = 7 , list = { { id = 12030477 , num = 1 } , { id = 10246092 , num = 1 } , { id = 11000200 , num = 10 } , { id = 12030320 , num = 1 }, { id = 10222001 , num = 1 } } } ,
			{ metier = 8 , list = { { id = 12030477 , num = 1 } , { id = 10246092 , num = 1 } , { id = 11000200 , num = 10 } , { id = 12030320 , num = 1 }, { id = 10222001 , num = 1 } } } ,
			{ metier = 9 , list = { { id = 12030477 , num = 1 } , { id = 10246092 , num = 1 } , { id = 11000200 , num = 10 } , { id = 12030320 , num = 1 }, { id = 10222001 , num = 1 } } } ,
			{ metier = 10 , list = { { id = 12030477 , num = 1 } , { id = 10246092 , num = 1 } , { id = 11000200 , num = 10 } , { id = 12030320 , num = 1 }, { id = 10222001 , num = 1 } } } ,
			{ metier = 11 , list = { { id = 12030477 , num = 1 } , { id = 10246092 , num = 1 } , { id = 11000200 , num = 10 } , { id = 12030320 , num = 1 }, { id = 10222001 , num = 1 } } }
		}
	} ,
	

	{
		lv = 30 , array = 
		{
			{ metier = 0 , list = { { id = 12030478 , num = 1 } , { id = 11050001 , num = 10 } , { id = 12030321 , num = 1 } , { id = 11000200 , num = 10 } , { id = 11990011 , num = 1 }, { id = 12050257 , num = 1 } } } ,
			{ metier = 1 , list = { { id = 12030478 , num = 1 } , { id = 11050001 , num = 10 } , { id = 12030321 , num = 1 } , { id = 11000200 , num = 10 } , { id = 11990011 , num = 1 }, { id = 12050257 , num = 1 } } } ,
			{ metier = 2 , list = { { id = 12030478 , num = 1 } , { id = 11050001 , num = 10 } , { id = 12030321 , num = 1 } , { id = 11000200 , num = 10 } , { id = 11990011 , num = 1 }, { id = 12050257 , num = 1 } } } ,
			{ metier = 3 , list = { { id = 12030478 , num = 1 } , { id = 11050001 , num = 10 } , { id = 12030321 , num = 1 } , { id = 11000200 , num = 10 } , { id = 11990011 , num = 1 }, { id = 12050257 , num = 1 } } } ,
			{ metier = 4 , list = { { id = 12030478 , num = 1 } , { id = 11050001 , num = 10 } , { id = 12030321 , num = 1 } , { id = 11000200 , num = 10 } , { id = 11990011 , num = 1 }, { id = 12050257 , num = 1 } } } ,
			{ metier = 5 , list = { { id = 12030478 , num = 1 } , { id = 11050001 , num = 10 } , { id = 12030321 , num = 1 } , { id = 11000200 , num = 10 } , { id = 11990011 , num = 1 }, { id = 12050257 , num = 1 } } } ,
		  { metier = 6 , list = { { id = 12030478 , num = 1 } , { id = 11050001 , num = 10 } , { id = 12030321 , num = 1 } , { id = 11000200 , num = 10 } , { id = 11990011 , num = 1 }, { id = 12050257 , num = 1 } } } ,
			{ metier = 7 , list = { { id = 12030478 , num = 1 } , { id = 11050001 , num = 10 } , { id = 12030321 , num = 1 } , { id = 11000200 , num = 10 } , { id = 11990011 , num = 1 }, { id = 12050257 , num = 1 } } } ,
			{ metier = 8 , list = { { id = 12030478 , num = 1 } , { id = 11050001 , num = 10 } , { id = 12030321 , num = 1 } , { id = 11000200 , num = 10 } , { id = 11990011 , num = 1 }, { id = 12050257 , num = 1 } } } ,
			{ metier = 9 , list = { { id = 12030478 , num = 1 } , { id = 11050001 , num = 10 } , { id = 12030321 , num = 1 } , { id = 11000200 , num = 10 } , { id = 11990011 , num = 1 }, { id = 12050257 , num = 1 } } } ,
			{ metier = 10 , list = { { id = 12030478 , num = 1 } , { id = 11050001 , num = 10 } , { id = 12030321 , num = 1 } , { id = 11000200 , num = 10 } , { id = 11990011 , num = 1 }, { id = 12050257 , num = 1 } } } ,
			{ metier = 11 , list = { { id = 12030478 , num = 1 } , { id = 11050001 , num = 10 } , { id = 12030321 , num = 1 } , { id = 11000200 , num = 10 } , { id = 11990011 , num = 1 }, { id = 12050257 , num = 1 } } }
		}
	} ,
	
	
	{
		lv = 40 , array = 
		{
			{ metier = 0 , list = { { id = 12030479 , num = 1 } , { id = 12030011 , num = 20 } , { id = 12010201 , num = 5 } , { id = 11050001 , num = 20 } , { id = 12041101 , num = 1 } , { id = 11000201 , num = 10 } } } , 
			{ metier = 1 , list = { { id = 12030479 , num = 1 } , { id = 12030011 , num = 20 } , { id = 12010201 , num = 5 } , { id = 11050001 , num = 20 } , { id = 12041101 , num = 1 } , { id = 11000201 , num = 10 } } } , 
			{ metier = 2 , list = { { id = 12030479 , num = 1 } , { id = 12030011 , num = 20 } , { id = 12010201 , num = 5 } , { id = 11050001 , num = 20 } , { id = 12041101 , num = 1 } , { id = 11000201 , num = 10 } } } , 
			{ metier = 3 , list = { { id = 12030479 , num = 1 } , { id = 12030011 , num = 20 } , { id = 12010201 , num = 5 } , { id = 11050001 , num = 20 } , { id = 12041101 , num = 1 } , { id = 11000201 , num = 10 } } } , 
			{ metier = 4 , list = { { id = 12030479 , num = 1 } , { id = 12030011 , num = 20 } , { id = 12010201 , num = 5 } , { id = 11050001 , num = 20 } , { id = 12041101 , num = 1 } , { id = 11000201 , num = 10 } } } , 
			{ metier = 5 , list = { { id = 12030479 , num = 1 } , { id = 12030011 , num = 20 } , { id = 12010201 , num = 5 } , { id = 11050001 , num = 20 } , { id = 12041101 , num = 1 } , { id = 11000201 , num = 10 } } } ,
		  { metier = 6 , list = { { id = 12030479 , num = 1 } , { id = 12030011 , num = 20 } , { id = 12010201 , num = 5 } , { id = 11050001 , num = 20 } , { id = 12041101 , num = 1 } , { id = 11000201 , num = 10 } } } , 
			{ metier = 7 , list = { { id = 12030479 , num = 1 } , { id = 12030011 , num = 20 } , { id = 12010201 , num = 5 } , { id = 11050001 , num = 20 } , { id = 12041101 , num = 1 } , { id = 11000201 , num = 10 } } } , 
			{ metier = 8 , list = { { id = 12030479 , num = 1 } , { id = 12030011 , num = 20 } , { id = 12010201 , num = 5 } , { id = 11050001 , num = 20 } , { id = 12041101 , num = 1 } , { id = 11000201 , num = 10 } } } , 
			{ metier = 9 , list = { { id = 12030479 , num = 1 } , { id = 12030011 , num = 20 } , { id = 12010201 , num = 5 } , { id = 11050001 , num = 20 } , { id = 12041101 , num = 1 } , { id = 11000201 , num = 10 } } } , 
			{ metier = 10 , list = { { id = 12030479 , num = 1 } , { id = 12030011 , num = 20 } , { id = 12010201 , num = 5 } , { id = 11050001 , num = 20 } , { id = 12041101 , num = 1 } , { id = 11000201 , num = 10 } } } , 
			{ metier = 11 , list = { { id = 12030479 , num = 1 } , { id = 12030011 , num = 20 } , { id = 12010201 , num = 5 } , { id = 11050001 , num = 20 } , { id = 12041101 , num = 1 } , { id = 11000201 , num = 10 } } }
		}
	} ,
	
	
	{
		lv = 50 , array = 
		{
			{ metier = 0 , list = { { id = 12030480 , num = 1 }, { id = 11050002 , num = 10 }, { id = 11000201 , num = 30 } , { id = 12030011 , num = 20 } , { id = 11990015 , num = 3 } , { id = 12054300 , num = 5 } } } , 
			{ metier = 1 , list = { { id = 12030480 , num = 1 }, { id = 11050002 , num = 10 }, { id = 11000201 , num = 30 } , { id = 12030011 , num = 20 } , { id = 11990015 , num = 3 } , { id = 12054300 , num = 5 } } } , 
			{ metier = 2 , list = { { id = 12030480 , num = 1 }, { id = 11050002 , num = 10 }, { id = 11000201 , num = 30 } , { id = 12030011 , num = 20 } , { id = 11990015 , num = 3 } , { id = 12054300 , num = 5 } } } , 
			{ metier = 3 , list = { { id = 12030480 , num = 1 }, { id = 11050002 , num = 10 }, { id = 11000201 , num = 30 } , { id = 12030011 , num = 20 } , { id = 11990015 , num = 3 } , { id = 12054300 , num = 5 } } } , 
			{ metier = 4 , list = { { id = 12030480 , num = 1 }, { id = 11050002 , num = 10 }, { id = 11000201 , num = 30 } , { id = 12030011 , num = 20 } , { id = 11990015 , num = 3 } , { id = 12054300 , num = 5 } } } , 
			{ metier = 5 , list = { { id = 12030480 , num = 1 }, { id = 11050002 , num = 10 }, { id = 11000201 , num = 30 } , { id = 12030011 , num = 20 } , { id = 11990015 , num = 3 } , { id = 12054300 , num = 5 } } } ,
		  { metier = 6 , list = { { id = 12030480 , num = 1 }, { id = 11050002 , num = 10 }, { id = 11000201 , num = 30 } , { id = 12030011 , num = 20 } , { id = 11990015 , num = 3 } , { id = 12054300 , num = 5 } } } , 
			{ metier = 7 , list = { { id = 12030480 , num = 1 }, { id = 11050002 , num = 10 }, { id = 11000201 , num = 30 } , { id = 12030011 , num = 20 } , { id = 11990015 , num = 3 } , { id = 12054300 , num = 5 } } } , 
			{ metier = 8 , list = { { id = 12030480 , num = 1 }, { id = 11050002 , num = 10 }, { id = 11000201 , num = 30 } , { id = 12030011 , num = 20 } , { id = 11990015 , num = 3 } , { id = 12054300 , num = 5 } } } , 
			{ metier = 9 , list = { { id = 12030480 , num = 1 }, { id = 11050002 , num = 10 }, { id = 11000201 , num = 30 } , { id = 12030011 , num = 20 } , { id = 11990015 , num = 3 } , { id = 12054300 , num = 5 } } } , 
			{ metier = 10 , list = { { id = 12030480 , num = 1 }, { id = 11050002 , num = 10 }, { id = 11000201 , num = 30 } , { id = 12030011 , num = 20 } , { id = 11990015 , num = 3 } , { id = 12054300 , num = 5 } } } , 
			{ metier = 11 , list = { { id = 12030480 , num = 1 }, { id = 11050002 , num = 10 }, { id = 11000201 , num = 30 } , { id = 12030011 , num = 20 } , { id = 11990015 , num = 3 } , { id = 12054300 , num = 5 } } }
		}
	} ,
	
	
	{
		lv = 60 , array = 
		{
			{ metier = 0 , list = { { id = 12030481 , num = 1 } , { id = 12030322 , num = 1 } , { id = 12030013 , num = 15 } , { id = 11050002 , num = 20 } , { id = 12010301 , num = 5 } , { id = 12050227 , num = 1 } } } ,
			{ metier = 1 , list = { { id = 12030481 , num = 1 } , { id = 12030322 , num = 1 } , { id = 12030013 , num = 15 } , { id = 11050002 , num = 20 } , { id = 12010301 , num = 5 } , { id = 12050227 , num = 1 } } } ,
			{ metier = 2 , list = { { id = 12030481 , num = 1 } , { id = 12030322 , num = 1 } , { id = 12030013 , num = 15 } , { id = 11050002 , num = 20 } , { id = 12010301 , num = 5 } , { id = 12050227 , num = 1 } } } ,
			{ metier = 3 , list = { { id = 12030481 , num = 1 } , { id = 12030322 , num = 1 } , { id = 12030013 , num = 15 } , { id = 11050002 , num = 20 } , { id = 12010301 , num = 5 } , { id = 12050227 , num = 1 } } } ,
			{ metier = 4 , list = { { id = 12030481 , num = 1 } , { id = 12030322 , num = 1 } , { id = 12030013 , num = 15 } , { id = 11050002 , num = 20 } , { id = 12010301 , num = 5 } , { id = 12050227 , num = 1 } } } ,
			{ metier = 5 , list = { { id = 12030481 , num = 1 } , { id = 12030322 , num = 1 } , { id = 12030013 , num = 15 } , { id = 11050002 , num = 20 } , { id = 12010301 , num = 5 } , { id = 12050227 , num = 1 } } } ,
		  { metier = 6 , list = { { id = 12030481 , num = 1 } , { id = 12030322 , num = 1 } , { id = 12030013 , num = 15 } , { id = 11050002 , num = 20 } , { id = 12010301 , num = 5 } , { id = 12050227 , num = 1 } } } ,
			{ metier = 7 , list = { { id = 12030481 , num = 1 } , { id = 12030322 , num = 1 } , { id = 12030013 , num = 15 } , { id = 11050002 , num = 20 } , { id = 12010301 , num = 5 } , { id = 12050227 , num = 1 } } } ,
			{ metier = 8 , list = { { id = 12030481 , num = 1 } , { id = 12030322 , num = 1 } , { id = 12030013 , num = 15 } , { id = 11050002 , num = 20 } , { id = 12010301 , num = 5 } , { id = 12050227 , num = 1 } } } ,
			{ metier = 9 , list = { { id = 12030481 , num = 1 } , { id = 12030322 , num = 1 } , { id = 12030013 , num = 15 } , { id = 11050002 , num = 20 } , { id = 12010301 , num = 5 } , { id = 12050227 , num = 1 } } } ,
			{ metier = 10 , list = { { id = 12030481 , num = 1 } , { id = 12030322 , num = 1 } , { id = 12030013 , num = 15 } , { id = 11050002 , num = 20 } , { id = 12010301 , num = 5 } , { id = 12050227 , num = 1 } } } ,
			{ metier = 11 , list = { { id = 12030481 , num = 1 } , { id = 12030322 , num = 1 } , { id = 12030013 , num = 15 } , { id = 11050002 , num = 20 } , { id = 12010301 , num = 5 } , { id = 12050227 , num = 1 } } }
		}
	} ,
	
	
	{
		lv = 65 , array = 
		{
			{ metier = 0 , list = { { id = 12030482 , num = 1 } ,{ id = 12030323 , num = 1 } ,{ id = 11050003 , num = 15 } , { id = 11000501 , num = 5 } , { id = 11000202 , num = 10 } , { id = 11990114 , num = 1 } } } ,
			{ metier = 1 , list = { { id = 12030482 , num = 1 } ,{ id = 12030323 , num = 1 } ,{ id = 11050003 , num = 15 } , { id = 11000501 , num = 5 } , { id = 11000202 , num = 10 } , { id = 11990114 , num = 1 } } } ,
			{ metier = 2 , list = { { id = 12030482 , num = 1 } ,{ id = 12030323 , num = 1 } ,{ id = 11050003 , num = 15 } , { id = 11000501 , num = 5 } , { id = 11000202 , num = 10 } , { id = 11990114 , num = 1 } } } ,
			{ metier = 3 , list = { { id = 12030482 , num = 1 } ,{ id = 12030323 , num = 1 } ,{ id = 11050003 , num = 15 } , { id = 11000501 , num = 5 } , { id = 11000202 , num = 10 } , { id = 11990114 , num = 1 } } } ,
			{ metier = 4 , list = { { id = 12030482 , num = 1 } ,{ id = 12030323 , num = 1 } ,{ id = 11050003 , num = 15 } , { id = 11000501 , num = 5 } , { id = 11000202 , num = 10 } , { id = 11990114 , num = 1 } } } ,
			{ metier = 5 , list = { { id = 12030482 , num = 1 } ,{ id = 12030323 , num = 1 } ,{ id = 11050003 , num = 15 } , { id = 11000501 , num = 5 } , { id = 11000202 , num = 10 } , { id = 11990114 , num = 1 } } } ,
		  { metier = 6 , list = { { id = 12030482 , num = 1 } ,{ id = 12030323 , num = 1 } ,{ id = 11050003 , num = 15 } , { id = 11000501 , num = 5 } , { id = 11000202 , num = 10 } , { id = 11990114 , num = 1 } } } ,
			{ metier = 7 , list = { { id = 12030482 , num = 1 } ,{ id = 12030323 , num = 1 } ,{ id = 11050003 , num = 15 } , { id = 11000501 , num = 5 } , { id = 11000202 , num = 10 } , { id = 11990114 , num = 1 } } } ,
			{ metier = 8 , list = { { id = 12030482 , num = 1 } ,{ id = 12030323 , num = 1 } ,{ id = 11050003 , num = 15 } , { id = 11000501 , num = 5 } , { id = 11000202 , num = 10 } , { id = 11990114 , num = 1 } } } ,
			{ metier = 9 , list = { { id = 12030482 , num = 1 } ,{ id = 12030323 , num = 1 } ,{ id = 11050003 , num = 15 } , { id = 11000501 , num = 5 } , { id = 11000202 , num = 10 } , { id = 11990114 , num = 1 } } } ,
			{ metier = 10 , list = { { id = 12030482 , num = 1 } ,{ id = 12030323 , num = 1 } ,{ id = 11050003 , num = 15 } , { id = 11000501 , num = 5 } , { id = 11000202 , num = 10 } , { id = 11990114 , num = 1 } } } ,
			{ metier = 11 , list = { { id = 12030482 , num = 1 } ,{ id = 12030323 , num = 1 } ,{ id = 11050003 , num = 15 } , { id = 11000501 , num = 5 } , { id = 11000202 , num = 10 } , { id = 11990114 , num = 1 } } }
		}
	} ,
	
	
	{
		lv = 70 , array = 
		{
			{ metier = 0 , list = { { id = 11050003 , num = 30 } , { id = 12030323 , num = 1 } , { id = 11000202 , num = 15 } , { id = 11000902 , num = 1 } , { id = 11000903 , num = 1 } } } ,
			{ metier = 1 , list = { { id = 11050003 , num = 30 } , { id = 12030323 , num = 1 } , { id = 11000202 , num = 15 } , { id = 11000902 , num = 1 } , { id = 11000903 , num = 1 } } } ,
			{ metier = 2 , list = { { id = 11050003 , num = 30 } , { id = 12030323 , num = 1 } , { id = 11000202 , num = 15 } , { id = 11000902 , num = 1 } , { id = 11000903 , num = 1 } } } ,
			{ metier = 3 , list = { { id = 11050003 , num = 30 } , { id = 12030323 , num = 1 } , { id = 11000202 , num = 15 } , { id = 11000902 , num = 1 } , { id = 11000903 , num = 1 } } } ,
			{ metier = 4 , list = { { id = 11050003 , num = 30 } , { id = 12030323 , num = 1 } , { id = 11000202 , num = 15 } , { id = 11000902 , num = 1 } , { id = 11000903 , num = 1 } } } ,
			{ metier = 5 , list = { { id = 11050003 , num = 30 } , { id = 12030323 , num = 1 } , { id = 11000202 , num = 15 } , { id = 11000902 , num = 1 } , { id = 11000903 , num = 1 } } } ,
		  { metier = 6 , list = { { id = 11050003 , num = 30 } , { id = 12030323 , num = 1 } , { id = 11000202 , num = 15 } , { id = 11000902 , num = 1 } , { id = 11000903 , num = 1 } } } ,
			{ metier = 7 , list = { { id = 11050003 , num = 30 } , { id = 12030323 , num = 1 } , { id = 11000202 , num = 15 } , { id = 11000902 , num = 1 } , { id = 11000903 , num = 1 } } } ,
			{ metier = 8 , list = { { id = 11050003 , num = 30 } , { id = 12030323 , num = 1 } , { id = 11000202 , num = 15 } , { id = 11000902 , num = 1 } , { id = 11000903 , num = 1 } } } ,
			{ metier = 9 , list = { { id = 11050003 , num = 30 } , { id = 12030323 , num = 1 } , { id = 11000202 , num = 15 } , { id = 11000902 , num = 1 } , { id = 11000903 , num = 1 } } } ,
			{ metier = 10 , list = { { id = 11050003 , num = 30 } , { id = 12030323 , num = 1 } , { id = 11000202 , num = 15 } , { id = 11000902 , num = 1 } , { id = 11000903 , num = 1 } } } ,
			{ metier = 11 , list = { { id = 11050003 , num = 30 } , { id = 12030323 , num = 1 } , { id = 11000202 , num = 15 } , { id = 11000902 , num = 1 } , { id = 11000903 , num = 1 } } }
		}
	}
};


x418155_random_size = 10;
x418155_array_size = 8;
x418155_random_item_id = 10200020;
x418155_title_enabled_color = "";
x418155_title_disabled_color = "#cb4b4b4";


--**********************************
--事件交互入口
--**********************************
function x418155_ProcEventEntry( sceneId, selfId, bagIndex )
-- 不需要这个接口，但要保留空函数
end

--**********************************
--这个物品的使用过程是否类似于技能：
--系统会在执行开始时检测这个函数的返回值，如果返回失败则忽略后面的类似技能的执行。
--返回1：技能类似的物品，可以继续类似技能的执行；返回0：忽略后面的操作。
--**********************************
function x418155_IsSkillLikeScript( sceneId, selfId)
	return 1; --这个脚本需要动作支持
end

--**********************************
--直接取消效果：
--系统会直接调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：已经取消对应效果，不再执行后续操作；返回0：没有检测到相关效果，继续执行。
--**********************************
function x418155_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

--**********************************
--条件检测入口：
--系统会在技能检测的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：条件检测通过，可以继续执行；返回0：条件检测失败，中断后续执行。
--**********************************
function x418155_OnConditionCheck( sceneId, selfId )
	
	--校验使用的物品
	
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end
	return 1; --不需要任何条件，并且始终返回1。
end

--**********************************
--消耗检测及处理入口：
--系统会在技能消耗的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：消耗处理通过，可以继续执行；返回0：消耗检测失败，中断后续执行。
--注意：这不光负责消耗的检测也负责消耗的执行。
--**********************************
function x418155_OnDeplete( sceneId, selfId )
	
	
	--if(DepletingUsedItem(sceneId, selfId)) == 1 then
	--	return 1;
	--end
	--return 0;
	
	return 1;
end




--**********************************
--只会执行一次入口：
--聚气和瞬发技能会在消耗完成后调用这个接口（聚气结束并且各种条件都满足的时候），而引导
--技能也会在消耗完成后调用这个接口（技能的一开始，消耗成功执行之后）。
--返回1：处理成功；返回0：处理失败。
--注：这里是技能生效一次的入口
--**********************************
function x418155_OnActivateOnce( sceneId, selfId, impactId )
	CallScriptFunction( 418155, "OnEnumerate", sceneId, selfId, selfId, 0)
end


function x418155_get_item_table_id( sceneId , selfId )
	local bag_id = GetBagIndexOfUsedItem( sceneId , selfId );
	
	if ( bag_id == nil ) then
		return nil
	end
	
	local item_id = GetItemIDByIndexInBag( sceneId , selfId , bag_id );
	
	if ( item_id == nil ) then
		return nil
	end
	
	return item_id
end


function x418155_get_item_key( sceneId , selfId )
	local item_id = x418155_get_item_table_id( sceneId , selfId );
	
	if ( item_id == nil ) then
		return	nil
	end
	
	local key = x418155_item_key_array[ item_id ];
	
	if ( key == nil ) or ( key > getn( x418155_item_array ) ) then
		return nil
	end
	
	return key
end

function x418155_get_random_key( level )
	if ( level == 10 ) then
		return 1
	end
	
	if ( level == 20 ) then
		return 2;
	end
	
	return nil
end


function x418155_OnEnumerate( sceneId, selfId, NPCId, MissionId)

	local tb_id = x418155_get_item_key( sceneId , selfId );
	
	if ( tb_id == nil ) then
		return
	end
	
	local lv = GetLevel( sceneId , selfId );
	
	BeginQuestEvent(sceneId);
	AddQuestText( sceneId , "\t《成吉思汗》专门为新手准备的礼物，当您达到相应的等级，即可获得成长礼包中的礼物。\n\t玩家在打开礼包时，需要注意自己的背包空间，已使用的礼包为灰色，未使用的礼包为白色。" );
	
	for i,s in x418155_item_array do
	
		local clr = nil;
		if ( i < tb_id ) then
			clr = x418155_title_disabled_color;
		else
			clr = x418155_title_enabled_color;
		end
		
		AddQuestNumText( sceneId , 10262 , clr.."新手成长包("..tostring( s.lv ).."级)" , 3 , i );
	end
	
	EndQuestEvent( sceneId)
	DispatchQuestEventList( sceneId, selfId, selfId)
end




function x418155_ProcEventEntry( sceneId, selfId, targetId, scriptid, extid)
	
	BeginQuestEvent( sceneId)
	
	local clr_name = x418155_item_array[ extid ].clr_name;
	local item_list = x418155_item_array[ extid ].item_list;
	local cur_metier = GetZhiye( sceneId , selfId );
	
	AddQuestText( sceneId , "\t您目前选择的是"..clr_name.."#W，点击确定您将获得"..item_list );
	
	--添加图标

	local list = x418155_item_list[ extid ].array;
	local lv = x418155_item_list[ extid ].lv;
	
	for i , s in list do
	--职业匹配
		if s.metier == cur_metier then
			for j , u in s.list do
			
				local num = u.num;
				local id = u.id;
				if ( id ~= nil ) then
					if( j <= getn( s.list ) ) then
						local flag = 0;
						for k , r in x418155_item_key_array do
							if ( k == id ) then
								flag = 1;
							end
						end
						if ( flag == 0 ) then
							AddQuestItemBonus( sceneId, id, num);
						end
						
					else
						if ( extid == getn( x418155_item_array ) ) then
							AddQuestItemBonus( sceneId, id, num);
						end
					end
				else
					--随机显示
					local random_key = x418155_get_random_key( lv );
					
					if ( random_key ~= nil ) then
					
						local copy = {};
						local ref = x418155_item_random_list[ random_key ];
						
						for x = 1 , x418155_array_size do
							copy[ x ] = ref[ x ];
						end
						local copy_l = getn( copy );
					
						for k = 1 , num do
							for i = 1 , copy_l do
								local r = random( 1 , copy_l );
								local r_id = copy[ r ];
								
								if r_id ~= -1 then
									copy[ r ] = -1;
									AddQuestItemBonus( sceneId , r_id , 1 );
									break
								end
							end
						end
						
					end
				end
			end	
		end
	end

	SetPlayerRuntimeData( sceneId, selfId, RD_ROOKIE_BOX, extid)
	EndQuestEvent();
	DispatchQuestInfoNM( sceneId, selfId, targetId,418155,10262);
end



function x418155_output_msg( sceneId, selfId , msg )
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,msg)
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
end


function x418155_ProcQuestAccept( sceneId, selfId, targetId, missionId )

	local extid = GetPlayerRuntimeData( sceneId, selfId, RD_ROOKIE_BOX);
	local tb_id = x418155_get_item_key( sceneId , selfId );
	
	if ( tb_id == nil ) then
		return
	end
	
	if ( extid == nil ) or 
	   ( extid > x418155_array_size ) then
	   return
	end
	
	if ( tb_id > extid ) then
		Msg2Player( sceneId, selfId, "您已经领取过该级别礼品", 8, 3 )
		return
	end
	
	if ( tb_id < extid ) then
		local key_lv = x418155_item_list[ tb_id ].lv;
		Msg2Player( sceneId, selfId, "您需要先领取"..tostring( key_lv ).."级的礼包", 8, 3 );
		return
	end

	local lv = x418155_item_list[ extid ].lv;
	local cur_lv =GetLevel( sceneId , selfId );
	local cur_metier = GetZhiye( sceneId , selfId );
	
	--判断级别
	if cur_lv < lv then
		Msg2Player( sceneId, selfId, "您还没有达到该级别", 8, 3 )
		return
	end
	
	--判断是否该包
	
	
	BeginAddItem(sceneId);
	
	local list = x418155_item_list[ extid ].array;
	local get_num = 0;
	
	for i , s in list do
		--职业匹配
		if s.metier == cur_metier then
		
			for j , u in s.list do
				
				--赋予道具
				local num = u.num;
				local id = u.id;
				
				if id == nil then

					--随机道具
					local random_key = x418155_get_random_key( lv );
					
					if ( random_key ~= nil ) then
					
						local copy = {};
						local ref = x418155_item_random_list[ random_key ];
						
						for x = 1 , x418155_array_size do
							copy[ x ] = ref[ x ];
						end

						local copy_l = getn( copy );
					
						for k = 1 , num do
							for i = 1 , copy_l do
								local r = random( 1 , copy_l );
								local r_id = copy[ r ];
								
								if r_id ~= nil then
									copy[ r ] = nil;
									AddBindItem( sceneId , r_id , 1 );
									get_num = get_num + 1;
									break
								end
							end
						end
						
					end

					
				else
					--不随机
					AddBindItem( sceneId , id , num );
					get_num = get_num + 1;
				end
				
			end
			
		end
	end
	
	
	local ret = EndAddItem(sceneId,selfId);
	
	if get_num == 0 then
		x418155_output_msg( sceneId,selfId,"获取道具失败！" );
	end
	
	if ( ret > 0 ) then
	
		if(DepletingUsedItem(sceneId, selfId)) == 1 then
			x418155_output_msg( sceneId,selfId,"打开礼包，获得了礼包道具" );
			AddItemListToPlayer(sceneId,selfId);
		else
			x418155_output_msg( sceneId,selfId,"使用物品异常" );
		end
	else
		x418155_output_msg( sceneId,selfId,"背包已满，无法得到物品！您需要至少有"..tostring( get_num ).."个背包空间！" );
	end
	



	
	
end





--**********************************
--引导心跳处理入口：
--引导技能会在每次心跳结束时调用这个接口。
--返回：1继续下次心跳；0：中断引导。
--注：这里是技能生效一次的入口
--**********************************
function x418155_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end




