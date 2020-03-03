var myDate=new Date();
var year = (year_point == "") ? myDate.getFullYear() : year_point;	//年
var month = (month_point == "") ? myDate.getMonth() + 1 : month_point = (month_point.charAt(0) == '0') ? month_point.substring(1, month_point.length) : month_point;	//月
var date = (date_point == "") ? myDate.getDate() : date_point = (date_point.charAt(0) == '0') ? date_point.substring(1, date_point.length) : date_point;	//日
var new_date = new Date(year,month,1);                //取当年当月中的第一天
var last_date = (new Date(new_date.getTime()-1000*60*60*24)).getDate();//获取当月最后一天日期
var table_date = "";
var row_s = 1;
var row_e = 10;


$(function(){
	load_date();
});
function last_d(){
	var new_year = year;    //取当前的年份
	var change_month = month;
	var new_month = change_month--;
	if (change_month < 1) {
		new_month = parseInt(new_month);
		new_month += 12;
		new_year--;            //年份减
	}
	new_date = new Date(new_year,new_month-1,1);                //取当年当月中的第一天
	last_date = (new Date(new_date.getTime()-1000*60*60*24)).getDate();//获取当月最后一天日期
	year = new_year;
	month = parseInt(new_month) - 1;
	table_date = "";
	row_s = 1;
    row_e = 10;
	load_date();
}
function next_d(){
	var new_year = year;    //取当前的年份
	var change_month = month;
	var new_month = change_month++;//取下一个月的第一天，方便计算（最后一天不固定）
	if(change_month > 12)  {          //如果当前大于12月，则年份转到下一年
	   new_month = parseInt(new_month);
	   new_month -=12;        //月份减
	   new_year++;            //年份增
	}
	new_date = new Date(new_year,new_month+1,1);                //取当年当月中的第一天
	last_date = (new Date(new_date.getTime()-1000*60*60*24)).getDate();//获取当月最后一天日期
	year = new_year;
	month = parseInt(new_month) + 1;
	table_date = "";
	row_s = 1;
    row_e = 10;
	load_date();
}
function load_date(){
	$('.month').html(year+'年'+month+'月');
	$('.tab04 tr').next().remove();
	var len = (last_date == 30 || last_date == 29 || last_date == 28) ? 4 : 4;
	for (var n = 1;n <= len;n++) {	//显示行数
		table_date += (n % 2 == 0) ? '<tr class="tab04_rowbg">' : '<tr>';
		for (var i = row_s;i <= row_e+1;i++) {
			if (i > row_e) {
				row_s = row_s + 10;	//11
				row_e = row_e + 10;		//20
				break;
			} else {
				if (i <= last_date) {
					month_u = (month <= 9) ? "0" + month : month;
					date_u = (i <= 9) ? "0" + i : i;
					//var url = "index.php?tp=calendar&t="+year+"-"+month_u+"-"+date_u+"";
					var url = "http://kf.265g.com/"+year+"-"+month_u+"-"+date_u+".html";
					if (i == date) {
						table_date += '<td><a target="_blank" href="'+url+'" style="background:#666; text-decoration:none; color:#fff;">'+i+'</a></td>';
					} else {
						table_date += '<td><a target="_blank" href="'+url+'">'+i+'</a></td>';
					}
				} else {
					table_date += '<td>&nbsp;</td>';
				}
			}
		}
		table_date += '</tr>';
	}
	$('.tab04').append(table_date);
}