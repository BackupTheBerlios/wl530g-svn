<head>
<title>WL520g Web Manager</title>
<meta http-equiv="Content-Type" content="text/html; charset=euc-kr">
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" type="text/css" href="style.css" media="screen"></link>
<script language="JavaScript" type="text/javascript" src="overlib.js"></script>
<script language="JavaScript" type="text/javascript" src="general.js"></script>
</head>  
<div id="overDiv" style="position:absolute; visibility:hidden; z-index:1000;"></div>    
<body onLoad="load_body()" onunLoad="return unload_body();">
<form method="GET" name="form" action="apply.cgi">
<!-- Table for the conntent page -->	    
<table width="666" border="0" cellpadding="0" cellspacing="0">     	      
    	
<input type="hidden" name="current_page" value="Advanced_DDNS_Content.asp"><input type="hidden" name="next_page" value="SaveRestart.asp"><input type="hidden" name="next_host" value=""><input type="hidden" name="sid_list" value="LANHostConfig;"><input type="hidden" name="group_id" value=""><input type="hidden" name="modified" value="0"><input type="hidden" name="action_mode" value=""><input type="hidden" name="first_time" value=""><input type="hidden" name="action_script" value="">
<tr>
<td>
<table width="666" border="1" cellpadding="0" cellspacing="0" bordercolor="E0E0E0">
<tr class="content_header_tr">
<td class="content_header_td_title" colspan="2">IP 컨피규레이션 - 기타</td>
</tr>
<tr>
<td class="content_header_td" onMouseOver="return overlib('만일 UpnP를 활성화하고 있는 경우에는 Windows XP등의 운영 시스템이 자동으로 WL520g를 발견합니다. 그리고 운영시스템이 게임, 비디오 컨퍼런스등 여러 종류의 인터넷 어플리케이션에 대하여 자동으로 WL520g의 컨피규레이션을 할 수 있도록 합니다.', LEFT);" onMouseOut="return nd();">UpnP를 활성화하겠습니까?
           </td><td class="content_input_td"><input type="radio" value="1" name="upnp_enable" class="content_input_fd" onClick="return change_common_radio(this, 'LANHostConfig', 'upnp_enable', '1')" <% nvram_match_x("LANHostConfig","upnp_enable", "1", "checked"); %>>Yes</input><input type="radio" value="0" name="upnp_enable" class="content_input_fd" onClick="return change_common_radio(this, 'LANHostConfig', 'upnp_enable', '0')" <% nvram_match_x("LANHostConfig","upnp_enable", "0", "checked"); %>>No</input></td>
</tr>
<tr>
<td class="content_header_td" onMouseOver="return overlib('본 기능은 WL520g의 로그 메시지를 기록하기 위하여 원격서버를 할당할 수 있도록 합니다. 공란으로 두면 시스템이 WL520g에만 최대 1024개의 메시지를 기록하게 됩니다.', LEFT);" onMouseOut="return nd();">원격 로그 서버:
           </td><td class="content_input_td"><input type="text" maxlength="15" class="content_input_fd" size="15" name="log_ipaddr" value="<% nvram_get_x("LANHostConfig","log_ipaddr"); %>" onBlur="return validate_ipaddr(this, 'log_ipaddr')" onKeyPress="return is_ipaddr(this)" onKeyUp="change_ipaddr(this)"></td>
</tr>
<tr>
<td class="content_header_td" onMouseOver="return overlib('본 필드항목은 사용자가 위치한 지역의 시간영역을 표시합니다.', LEFT);" onMouseOut="return nd();">시간영역:
           </td><td class="content_input_td"><select name="time_zone" class="content_input_fd" onChange="return change_common(this, 'LANHostConfig', 'time_zone')"><option class="content_input_fd" value="UCT12" <% nvram_match_x("LANHostConfig","time_zone", "UCT12","selected"); %>>(GMT-12:00) Eniwetok, Kwajalein</option><option class="content_input_fd" value="UCT11" <% nvram_match_x("LANHostConfig","time_zone", "UCT11","selected"); %>>(GMT-11:00) Midway Island, Samoa</option><option class="content_input_fd" value="UCT10" <% nvram_match_x("LANHostConfig","time_zone", "UCT10","selected"); %>>(GMT-10:00) Hawaii</option><option class="content_input_fd" value="NAST9NADT" <% nvram_match_x("LANHostConfig","time_zone", "NAST9NADT","selected"); %>>(GMT-09:00) Alaska</option><option class="content_input_fd" value="PST8PDT" <% nvram_match_x("LANHostConfig","time_zone", "PST8PDT","selected"); %>>(GMT-08:00) Pacific Time (US, Canada)</option><option class="content_input_fd" value="MST7MDT" <% nvram_match_x("LANHostConfig","time_zone", "MST7MDT","selected"); %>>(GMT-07:00) Mountain Time (US, Canada)</option><option class="content_input_fd" value="MST7" <% nvram_match_x("LANHostConfig","time_zone", "MST7","selected"); %>>(GMT-07:00) Arizona</option><option class="content_input_fd" value="CST6CDT_1" <% nvram_match_x("LANHostConfig","time_zone", "CST6CDT_1","selected"); %>>(GMT-06:00) Central Time (US, Canada)</option><option class="content_input_fd" value="CST6CDT_2" <% nvram_match_x("LANHostConfig","time_zone", "CST6CDT_2","selected"); %>>(GMT-06:00) Saskatchewan</option><option class="content_input_fd" value="CST6CDT_3" <% nvram_match_x("LANHostConfig","time_zone", "CST6CDT_3","selected"); %>>(GMT-06:00) Guadalajara, Mexico City</option><option class="content_input_fd" value="CST6CDT_3_1" <% nvram_match_x("LANHostConfig","time_zone", "CST6CDT_3_1","selected"); %>>(GMT-06:00) Monterrey</option><option class="content_input_fd" value="MST7MDT" <% nvram_match_x("LANHostConfig","time_zone", "MST7MDT","selected"); %>>(GMT-07:00) Chihuahua, La Paz, Mazatlan</option><option class="content_input_fd" value="UCT6" <% nvram_match_x("LANHostConfig","time_zone", "UCT6","selected"); %>>(GMT-06:00) Central America</option><option class="content_input_fd" value="EST5EDT" <% nvram_match_x("LANHostConfig","time_zone", "EST5EDT","selected"); %>>(GMT-05:00) Eastern Time (US, Canada)</option><option class="content_input_fd" value="UCT5_1" <% nvram_match_x("LANHostConfig","time_zone", "UCT5_1","selected"); %>>(GMT-05:00) Indiana (East)</option><option class="content_input_fd" value="UCT5_2" <% nvram_match_x("LANHostConfig","time_zone", "UCT5_2","selected"); %>>(GMT-05:00) Bogota, Lima, Quito</option><option class="content_input_fd" value="AST4ADT" <% nvram_match_x("LANHostConfig","time_zone", "AST4ADT","selected"); %>>(GMT-04:00) Atlantic Time (Canada)</option><option class="content_input_fd" value="UCT4_1" <% nvram_match_x("LANHostConfig","time_zone", "UCT4_1","selected"); %>>(GMT-04:00) Caracas, La Paz</option><option class="content_input_fd" value="UCT4_2" <% nvram_match_x("LANHostConfig","time_zone", "UCT4_2","selected"); %>>(GMT-04:00) Santiago</option><option class="content_input_fd" value="NST3.30NDT" <% nvram_match_x("LANHostConfig","time_zone", "NST3.30NDT","selected"); %>>(GMT-03:30) Newfoundland</option><option class="content_input_fd" value="EBST3EBDT_1" <% nvram_match_x("LANHostConfig","time_zone", "EBST3EBDT_1","selected"); %>>(GMT-03:00) Brasilia</option><option class="content_input_fd" value="UCT3" <% nvram_match_x("LANHostConfig","time_zone", "UCT3","selected"); %>>(GMT-03:00) Buenos Aires, Georgetown</option><option class="content_input_fd" value="EBST3EBDT_2" <% nvram_match_x("LANHostConfig","time_zone", "EBST3EBDT_2","selected"); %>>(GMT-03:00) Greenland</option><option class="content_input_fd" value="NORO2" <% nvram_match_x("LANHostConfig","time_zone", "NORO2","selected"); %>>(GMT-02:00) Mid-Atlantic</option><option class="content_input_fd" value="EUT1EUTDST" <% nvram_match_x("LANHostConfig","time_zone", "EUT1EUTDST","selected"); %>>(GMT-01:00) Azores</option><option class="content_input_fd" value="UCT1" <% nvram_match_x("LANHostConfig","time_zone", "UCT1","selected"); %>>(GMT-01:00) Cape Verde Is.</option><option class="content_input_fd" value="GMT0BST_1" <% nvram_match_x("LANHostConfig","time_zone", "GMT0BST_1","selected"); %>>(GMT) Greenwich Mean Time</option><option class="content_input_fd" value="GMT0BST_2" <% nvram_match_x("LANHostConfig","time_zone", "GMT0BST_2","selected"); %>>(GMT) Casablanca, Monrovia</option><option class="content_input_fd" value="UCT-1_1" <% nvram_match_x("LANHostConfig","time_zone", "UCT-1_1","selected"); %>>(GMT+01:00) Belgrade, Bratislava, Budapest</option><option class="content_input_fd" value="UCT-1_1_1" <% nvram_match_x("LANHostConfig","time_zone", "UCT-1_1_1","selected"); %>>(GMT+01:00) Ljubljana, Prague</option><option class="content_input_fd" value="UCT-1_2" <% nvram_match_x("LANHostConfig","time_zone", "UCT-1_2","selected"); %>>(GMT+01:00) Sarajevo, Skopje, Sofija</option><option class="content_input_fd" value="UCT-1_2_1" <% nvram_match_x("LANHostConfig","time_zone", "UCT-1_2_1","selected"); %>>(GMT+01:00) Vilnius, Warsaw, Zagreb</option><option class="content_input_fd" value="MET-1METDST" <% nvram_match_x("LANHostConfig","time_zone", "MET-1METDST","selected"); %>>(GMT+01:00) Brussels, Copenhagen</option><option class="content_input_fd" value="MET-1METDST_1" <% nvram_match_x("LANHostConfig","time_zone", "MET-1METDST_1","selected"); %>>(GMT+01:00) Madrid, Paris</option><option class="content_input_fd" value="MEZ-1MESZ" <% nvram_match_x("LANHostConfig","time_zone", "MEZ-1MESZ","selected"); %>>(GMT+01:00) Amsterdam, Berlin, Bern</option><option class="content_input_fd" value="MEZ-1MESZ_1" <% nvram_match_x("LANHostConfig","time_zone", "MEZ-1MESZ_1","selected"); %>>(GMT+01:00) Rome, Stockholm, Vienna</option><option class="content_input_fd" value="UCT-1_3" <% nvram_match_x("LANHostConfig","time_zone", "UCT-1_3","selected"); %>>(GMT+01:00) West Central Africa</option><option class="content_input_fd" value="ET-2EETDST" <% nvram_match_x("LANHostConfig","time_zone", "ET-2EETDST","selected"); %>>(GMT+02:00) Bucharest</option><option class="content_input_fd" value="EST-2EDT" <% nvram_match_x("LANHostConfig","time_zone", "EST-2EDT","selected"); %>>(GMT+02:00) Cairo</option><option class="content_input_fd" value="UCT-2_1" <% nvram_match_x("LANHostConfig","time_zone", "UCT-2_1","selected"); %>>(GMT+02:00) Helsinki, Riga, Tallinn</option><option class="content_input_fd" value="UCT-2_2" <% nvram_match_x("LANHostConfig","time_zone", "UCT-2_2","selected"); %>>(GMT+02:00) Athens, Istanbul, Minsk</option><option class="content_input_fd" value="IST-2IDT" <% nvram_match_x("LANHostConfig","time_zone", "IST-2IDT","selected"); %>>(GMT+02:00) Jerusalem</option><option class="content_input_fd" value="SAST-2" <% nvram_match_x("LANHostConfig","time_zone", "SAST-2","selected"); %>>(GMT+02:00) Harare, Pretoria</option><option class="content_input_fd" value="MST-3MDT" <% nvram_match_x("LANHostConfig","time_zone", "MST-3MDT","selected"); %>>(GMT+03:00) Moscow, St. Petersburg</option><option class="content_input_fd" value="MST-3MDT_1" <% nvram_match_x("LANHostConfig","time_zone", "MST-3MDT_1","selected"); %>>(GMT+03:00) Volgograd</option><option class="content_input_fd" value="UCT-3_1" <% nvram_match_x("LANHostConfig","time_zone", "UCT-3_1","selected"); %>>(GMT+03:00) Kuwait, Riyadh</option><option class="content_input_fd" value="UCT-3_2" <% nvram_match_x("LANHostConfig","time_zone", "UCT-3_2","selected"); %>>(GMT+03:00) Nairobi</option><option class="content_input_fd" value="IST-3IDT" <% nvram_match_x("LANHostConfig","time_zone", "IST-3IDT","selected"); %>>(GMT+03:00) Baghdad</option><option class="content_input_fd" value="UCT-3.30" <% nvram_match_x("LANHostConfig","time_zone", "UCT-3.30","selected"); %>>(GMT+03:30) Tehran</option><option class="content_input_fd" value="UCT-4_1" <% nvram_match_x("LANHostConfig","time_zone", "UCT-4_1","selected"); %>>(GMT+04:00) Abu Dhabi, Muscat</option><option class="content_input_fd" value="UCT-4_2" <% nvram_match_x("LANHostConfig","time_zone", "UCT-4_2","selected"); %>>(GMT+04:00) Baku, Tbilisi, Yerevan</option><option class="content_input_fd" value="UCT-4.30" <% nvram_match_x("LANHostConfig","time_zone", "UCT-4.30","selected"); %>>(GMT+04:30) Kabul</option><option class="content_input_fd" value="RFT-5RFTDST" <% nvram_match_x("LANHostConfig","time_zone", "RFT-5RFTDST","selected"); %>>(GMT+05:00) Ekaterinburg</option><option class="content_input_fd" value="UCT-5" <% nvram_match_x("LANHostConfig","time_zone", "UCT-5","selected"); %>>(GMT+05:00) Islamabad, Karachi, Tashkent</option><option class="content_input_fd" value="UCT-5.30" <% nvram_match_x("LANHostConfig","time_zone", "UCT-5.30","selected"); %>>(GMT+05:30) Calcutta, Chennai</option><option class="content_input_fd" value="UCT-5.30_1" <% nvram_match_x("LANHostConfig","time_zone", "UCT-5.30_1","selected"); %>>(GMT+05:30) Mumbai, New Delhi</option><option class="content_input_fd" value="UCT-5.45" <% nvram_match_x("LANHostConfig","time_zone", "UCT-5.45","selected"); %>>(GMT+05:45) Kathmandu</option><option class="content_input_fd" value="UCT-6" <% nvram_match_x("LANHostConfig","time_zone", "UCT-6","selected"); %>>(GMT+06:00) Astana, Dhaka</option><option class="content_input_fd" value="UCT-5.30" <% nvram_match_x("LANHostConfig","time_zone", "UCT-5.30","selected"); %>>(GMT+06:00) Sri Jayawardenepura</option><option class="content_input_fd" value="RFT-6RFTDST" <% nvram_match_x("LANHostConfig","time_zone", "RFT-6RFTDST","selected"); %>>(GMT+06:00) Almaty, Novosibirsk</option><option class="content_input_fd" value="UCT-6.30" <% nvram_match_x("LANHostConfig","time_zone", "UCT-6.30","selected"); %>>(GMT+06:30) Rangoon</option><option class="content_input_fd" value="UCT-7" <% nvram_match_x("LANHostConfig","time_zone", "UCT-7","selected"); %>>(GMT+07:00) Bangkok, Hanoi, Jakarta</option><option class="content_input_fd" value="RFT-7RFTDST" <% nvram_match_x("LANHostConfig","time_zone", "RFT-7RFTDST","selected"); %>>(GMT+07:00) Krasnoyarsk</option><option class="content_input_fd" value="CST-8" <% nvram_match_x("LANHostConfig","time_zone", "CST-8","selected"); %>>(GMT+08:00) Beijing, Hong Kong</option><option class="content_input_fd" value="CST-8_1" <% nvram_match_x("LANHostConfig","time_zone", "CST-8_1","selected"); %>>(GMT+08:00) Chongqing, Urumqi</option><option class="content_input_fd" value="SST-8" <% nvram_match_x("LANHostConfig","time_zone", "SST-8","selected"); %>>(GMT+08:00) Kuala Lumpur, Singapore</option><option class="content_input_fd" value="CCT-8" <% nvram_match_x("LANHostConfig","time_zone", "CCT-8","selected"); %>>(GMT+08:00) Taipei</option><option class="content_input_fd" value="WAS-8WAD" <% nvram_match_x("LANHostConfig","time_zone", "WAS-8WAD","selected"); %>>(GMT+08:00) Perth</option><option class="content_input_fd" value="UCT_8" <% nvram_match_x("LANHostConfig","time_zone", "UCT_8","selected"); %>>GMT+08:00) Irkutsk, Ulaan Bataar</option><option class="content_input_fd" value="KST-9KDT" <% nvram_match_x("LANHostConfig","time_zone", "KST-9KDT","selected"); %>>(GMT+09:00) Seoul</option><option class="content_input_fd" value="JST" <% nvram_match_x("LANHostConfig","time_zone", "JST","selected"); %>>(GMT+09:00) Osaka, Sapporo, Tokyo</option><option class="content_input_fd" value="RFT-9RFTDST" <% nvram_match_x("LANHostConfig","time_zone", "RFT-9RFTDST","selected"); %>>(GMT+09:00) Yakutsk</option><option class="content_input_fd" value="CST-9.30CDT" <% nvram_match_x("LANHostConfig","time_zone", "CST-9.30CDT","selected"); %>>(GMT+09:30) Darwin</option><option class="content_input_fd" value="UCT-9.30" <% nvram_match_x("LANHostConfig","time_zone", "UCT-9.30","selected"); %>>(GMT+09:30) Adelaide</option><option class="content_input_fd" value="UCT-10_1" <% nvram_match_x("LANHostConfig","time_zone", "UCT-10_1","selected"); %>>(GMT+10:00) Canberra, Melbourne, Sydney</option><option class="content_input_fd" value="UCT-10_2" <% nvram_match_x("LANHostConfig","time_zone", "UCT-10_2","selected"); %>>(GMT+10:00) Brisbane</option><option class="content_input_fd" value="TST-10TDT" <% nvram_match_x("LANHostConfig","time_zone", "TST-10TDT","selected"); %>>(GMT+10:00) Hobart</option><option class="content_input_fd" value="RFT-10RFTDST" <% nvram_match_x("LANHostConfig","time_zone", "RFT-10RFTDST","selected"); %>>(GMT+10:00) Vladivostok</option><option class="content_input_fd" value="UCT-10_5" <% nvram_match_x("LANHostConfig","time_zone", "UCT-10_5","selected"); %>>(GMT+10:00) Guam, Port Moresby</option><option class="content_input_fd" value="UCT-10_6" <% nvram_match_x("LANHostConfig","time_zone", "UCT-10_6","selected"); %>>(GMT+10:00) Canberra, Melbourne, Sydney</option><option class="content_input_fd" value="UCT-11" <% nvram_match_x("LANHostConfig","time_zone", "UCT-11","selected"); %>>(GMT+11:00) Magadan, Solomon Is.</option><option class="content_input_fd" value="UCT-11_1" <% nvram_match_x("LANHostConfig","time_zone", "UCT-11_1","selected"); %>>(GMT+11:00) New Caledonia</option><option class="content_input_fd" value="UCT-12" <% nvram_match_x("LANHostConfig","time_zone", "UCT-12","selected"); %>>(GMT+12:00) Fiji, Kamchatka, Marshall Is.</option><option class="content_input_fd" value="NZST-12NZDT" <% nvram_match_x("LANHostConfig","time_zone", "NZST-12NZDT","selected"); %>>(GMT+12:00) Auckland, Wellington</option><option class="content_input_fd" value="UCT-13" <% nvram_match_x("LANHostConfig","time_zone", "UCT-13","selected"); %>>(GMT+13:00) Nuku'alofa</option></select></td>
</tr>
<tr>
<td class="content_header_td" onMouseOver="return overlib('시스템 시간을 싱크로나이징하기 위하여 사용되는 NTP 서버', LEFT);" onMouseOut="return nd();">NTP 서버
           </td><td class="content_input_td"><input type="text" maxlength="256" class="content_input_fd" size="32" name="ntp_server0" value="<% nvram_get_x("LANHostConfig","ntp_server0"); %>" onKeyPress="return is_string(this)" onBlur="validate_string(this)"><a href="javascript:openLink('x_NTPServer1')" class="content_input_link" name="x_NTPServer1_link">NTP 링크
             </a></td>
</tr>
<tr class="content_section_header_tr">
<td class="content_section_header_td" colspan="2">DDNS 설정
            </td>
</tr>
<tr>
<td class="content_desc_td" colspan="2">유동DNS (DDNS)는 고정 IP주소가 아니더라도 서버가 특정한 이름을 갖고 인터넷으로 연결될 수 있도록 합니다. 현재 몇몇 DDNS 클라이언트는 WL520g에 내재되어 있습니다. 아래의 무료 트라이얼을 클릭하여 무료 트라이얼 계정을 오픈할 수 있습니다.
         </td>
</tr>
<tr>
<td class="content_header_td">DDNS 클라이언트를 활성화하겠습니까?
           </td><td class="content_input_td"><input type="radio" value="1" name="ddns_enable_x" class="content_input_fd" onClick="return change_common_radio(this, 'LANHostConfig', 'ddns_enable_x', '1')" <% nvram_match_x("LANHostConfig","ddns_enable_x", "1", "checked"); %>>Yes</input><input type="radio" value="0" name="ddns_enable_x" class="content_input_fd" onClick="return change_common_radio(this, 'LANHostConfig', 'ddns_enable_x', '0')" <% nvram_match_x("LANHostConfig","ddns_enable_x", "0", "checked"); %>>No</input></td>
</tr>
<tr>
<td class="content_header_td">서버:
           </td><td class="content_input_td"><select name="ddns_server_x" class="content_input_fd" onChange="return change_common(this, 'LANHostConfig', 'ddns_server_x')"><option class="content_input_fd" value="WWW.DYNDNS.ORG" <% nvram_match_x("LANHostConfig","ddns_server_x", "WWW.DYNDNS.ORG","selected"); %>>WWW.DYNDNS.ORG</option><option class="content_input_fd" value="WWW.DYNDNS.ORG(CUSTOM)" <% nvram_match_x("LANHostConfig","ddns_server_x", "WWW.DYNDNS.ORG(CUSTOM)","selected"); %>>WWW.DYNDNS.ORG(CUSTOM)</option><option class="content_input_fd" value="WWW.DYNDNS.ORG(STATIC)" <% nvram_match_x("LANHostConfig","ddns_server_x", "WWW.DYNDNS.ORG(STATIC)","selected"); %>>WWW.DYNDNS.ORG(STATIC)</option><option class="content_input_fd" value="WWW.TZO.COM" <% nvram_match_x("LANHostConfig","ddns_server_x", "WWW.TZO.COM","selected"); %>>WWW.TZO.COM</option><option class="content_input_fd" value="WWW.ZONEEDIT.COM" <% nvram_match_x("LANHostConfig","ddns_server_x", "WWW.ZONEEDIT.COM","selected"); %>>WWW.ZONEEDIT.COM</option></select><a href="javascript:openLink('x_DDNSServer')" class="content_input_link" name="x_DDNSServer_link">무료 트라이얼
             </a></td>
</tr>
<tr>
<td class="content_header_td" onMouseOver="return overlib('본 필드항목은 유동 DNS 서비스 로그인을 식별하기 위하여 사용합니다.', LEFT);" onMouseOut="return nd();">사용자 이름 또는 이메일 주소:
           </td><td class="content_input_td"><input type="text" maxlength="32" class="content_input_fd" size="32" name="ddns_username_x" value="<% nvram_get_x("LANHostConfig","ddns_username_x"); %>" onKeyPress="return is_string(this)" onBlur="validate_string(this)"></td>
</tr>
<tr>
<td class="content_header_td" onMouseOver="return overlib('본 필드항목은 유동 DNS 서비스 로그인을 위한 비밀번호로 사용합니다.', LEFT);" onMouseOut="return nd();">비밀번호 또는DDNS 키:
           </td><td class="content_input_td"><input type="password" maxlength="64" class="content_input_fd" size="32" name="ddns_passwd_x" value="<% nvram_get_x("LANHostConfig","ddns_passwd_x"); %>" onBlur="validate_string(this)"></td>
</tr>
<tr>
<td class="content_header_td" onMouseOver="return overlib('본 필드항목은 유동 DNS 서비스 등록과 공시 호스트 이름을 나타냅니다.', LEFT);" onMouseOut="return nd();">호스트 이름:
           </td><td class="content_input_td"><input type="text" maxlength="32" class="content_input_fd" size="32" name="ddns_hostname_x" value="<% nvram_get_x("LANHostConfig","ddns_hostname_x"); %>" onKeyPress="return is_string(this)" onBlur="validate_string(this)"></td>
</tr>
<tr>
<td class="content_header_td" onMouseOver="return overlib('본 필드항목은 와일드카드를 가진 도메인 이름이 사용자의 IP주소로도 제한될 지의 여부를 결정합니다.', LEFT);" onMouseOut="return nd();">와일드카드를 활성화하겠습니까?
           </td><td class="content_input_td"><input type="radio" value="1" name="ddns_wildcard_x" class="content_input_fd" onClick="return change_common_radio(this, 'LANHostConfig', 'ddns_wildcard_x', '1')" <% nvram_match_x("LANHostConfig","ddns_wildcard_x", "1", "checked"); %>>Yes</input><input type="radio" value="0" name="ddns_wildcard_x" class="content_input_fd" onClick="return change_common_radio(this, 'LANHostConfig', 'ddns_wildcard_x', '0')" <% nvram_match_x("LANHostConfig","ddns_wildcard_x", "0", "checked"); %>>No</input></td>
</tr>
<tr>
<td class="content_header_td" onMouseOver="return overlib('이 버튼으로 DDNS  데이터베이스를 수동 업데이트할 수 있습니다. 자동DDNS 업데이트가 실패한 경우만 이용 가능합니다. 시스템 로그에서 DDNS 업데이트의 현재상태를 알 수 있습니다.', LEFT);" onMouseOut="return nd();">수동 업데이트:
           </td><td class="content_input_td"><input type="hidden" maxlength="15" class="content_input_fd_ro" size="12" name="" value="<% nvram_get_f("ddns.log","DDNSStatus"); %>"><input type="submit" maxlength="15" class="content_input_fd_ro" onClick="return onSubmitApply('ddnsclient')" size="12" name="LANHostConfig_x_DDNSStatus_button" value="업데이트"></td>
</tr>
</table>
</td>
</tr>
<tr>
<td>
<table width="666" border="2" cellpadding="0" cellspacing="0" bordercolor="E0E0E0"></table>
</td>
</tr>
<tr>
<td>
<table width="666" border="2" cellpadding="0" cellspacing="0" bordercolor="E0E0E0"></table>
</td>
</tr>
<tr>
<td>
<table width="666" border="2" cellpadding="0" cellspacing="0" bordercolor="E0E0E0"></table>
</td>
</tr>
<tr>
<td>		
<table width="666" border="1" cellpadding="0" cellspacing="0" bordercolor="B0B0B0">
<tr bgcolor="#CCCCCC"><td colspan="3"><font face="arial" size="2"><b>&nbsp</b></font></td></tr>
<tr bgcolor="#FFFFFF">  
   <td id ="Confirm" height="25" width="34%">  
   <div align="center"><font face="Arial"> <input class=inputSubmit onMouseOut=buttonOut(this) onMouseOver="buttonOver(this)" onClick="onSubmitCtrl(this, ' Restore ')" type="submit" value=" 복구 " name="action"></font></div> 
   </td>  
   <td height="25" width="33%">  
   <div align="center"><font face="Arial"> <input class=inputSubmit onMouseOut=buttonOut(this) onMouseOver="buttonOver(this)" onClick="onSubmitCtrl(this, ' Finish ')" type="submit" value=" 마침 " name="action"></font></div> 
   </td>
   <td height="25" width="33%">  
   <div align="center"><font face="Arial"> <input class=inputSubmit onMouseOut=buttonOut(this) onMouseOver="buttonOver(this)" onClick="onSubmitCtrl(this, ' Apply ')" type="submit" value=" 적용 " name="action"></font></div> 
   </td>    
</tr>
</table>
</td>
</tr>

<tr>
<td>
<table width="666" border="1" cellpadding="0" cellspacing="0" bordercolor="B0B0B0">
<tr>
    <td colspan="2" width="616" height="25" bgcolor="#FFBB00"></td> 
</tr>                   
<tr bgcolor="#FFFFFF">
    <td class="content_header_td_15" align="left">복구: </td>
    <td class="content_input_td_padding" align="left">상기 설정을 취소하고 설정복구를 유효화합니다.</td>
</tr>
<tr bgcolor="#FFFFFF">
    <td class="content_header_td_15" align="left">마침: </td>
    <td class="content_input_td_padding" align="left">모든 설정을 확인하고 WL520g를 지금 다시 시작합니다.</td>
</tr>
<tr bgcolor="#FFFFFF">
    <td class="content_header_td_15" align="left">적용: </td>
    <td class="content_input_td_padding" align="left">상기설정을 확인하고 계속합니다.</td>
</tr>
</table>
</td>
</tr>

</table>
</form>
</body>
