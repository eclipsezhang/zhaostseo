

//+++++++++++++++++++++++++++弹出层显示效果++++++++++++++++++++++++++++//
var ischeck = false;
var temp_op = 0;
var boxname = '';

function showbox(box,op){
	boxname = box;
	$("#op").val(op);
	if (temp_op == 0) {temp_op = op;}
	boxinit(op);	//初始化设置
	show_box_center();
	show_b(box);
}

function boxinit(op){
	$("#gamename").val('请输入游戏名、平台名');
}

function show_b(obj){
	$('.'+obj).css("left",(($(document).width())/2-(parseInt($('.'+obj).width())/2))+"px");
	$('.'+obj).css('top',$(document).scrollTop()+(window.screen.availHeight/2-120));
	$('.'+obj).show();
}

function show_box_center(){
	if($("#dd_light").length==0){
		 var html='<div id=dd_light style="display:none;z-index: 9998;filter: alpha(opacity=30);left: 0px;position: absolute;top: 0px;background-color: #000;moz-opacity: 0.3;opacity: .30;"></div>';
		 $('body').append(html);
		 $('#dd_light').css('width',document.body.scrollWidth+'px');
		 $('#dd_light').css('height',document.body.scrollHeight+'px');
	}
	$('#dd_light').show();
}

function hidewindow_box(box){
	ischeck = false;
	$('.'+box).hide();
	$('#dd_light').hide();
}

window.onscroll=function (){	//弹出层实现随滚动条的变换而变换
	if (ischeck) {			//默认false不弹出
		showbox(boxname,temp_op);
	}
}
//+++++++++++++++++++++++++++弹出层显示效果++++++++++++++++++++++++++++//

document.write('<script src="http://kf.265g.com/cache/gameList" type="text/javascript"><'+'/script>');



$(function()
{
	$("form#searchBar1  input.sch_txt01").focus().autocomplete(gameList, {width : 270});
	$("form#searchBar1  input.sch_txt01").blur();
	$("form#searchBar2  input.sch_lay_txt01").focus().autocomplete(gameList, {width : 320});
	$(".btn_sch").click(function(){
		$.getScript("");
		if ($("#gname").val() == "请输入关键词，搜索后页面内套红显示") {
			$("#gname").val("");
		}
		$("form#searchBar1").submit();	
	});
	$(".btn_lay_sch").click(function(){
		$.getScript("");
		if ($("#gamename").val() == "请输入关键词，搜索后页面内套红显示") {
			$("#gamename").val("");
		}
		$("form#searchBar2").submit();	
	});
});

$(function(){
	var topTab = $(".tab07 a");
	topTab.click(function(){
		var j = topTab.index($(this)[0]);	
		topTab.eq(j).addClass("tab07_ahov").siblings().removeClass();
		if (j == 0) {
			$(".daojishi").show();
			$(".li_rec").hide();
		} else if (j == 1) {
			$(".daojishi").hide();
			$(".li_rec").eq(0).show();
			$(".li_rec").eq(1).hide();
		} else if (j == 2) {
			$(".daojishi").hide();
			$(".li_rec").eq(1).show();
			$(".li_rec").eq(0).hide();
		}
	});
});

$(function(){
				$('#blocknav').show();
				var blocknavPosition = function() { 	
	$('#blocknav').css("left",Math.ceil($(".wrap").eq(0).offset().left - 56) + "px");
	setTimeout(blocknavPosition,100);
	}; 	
	blocknavPosition(); 
	var offset_x=( $(window).width()-1024)/2-48;
	//scrollAd();
	//$(window).scroll(scrollAd);
	//$('.qlink_layer').css("right",offset_x);
})


function showkflist(p){
	if(p==0)
	{
	$('#blocknav').show();
	$('#blocknav ul li a').removeClass('mini_nav_ahov');
	$('#blocknav ul li a').first().addClass('mini_nav_ahov');

	}
	else
	{
	$('#blocknav').hide();
	}
    $.ajax({
        type: "POST",
        url: 'index.php?tp=index',
        data: 'page='+p+'&method=getlist',
        success: function(result){
			//alert(result);
            $('.mod_tab01').html(result);
			scroll(0,200);
			initclock();
        }
    });
}


	
function showkfgametypelist(n){
	$.ajax({
        type: "POST",
        url: 'index.php?tp=index',
        data: 'num='+n+'&method=getgametypelist',
        success: function(result){
			//alert(result);
            $('.mod_tab01').html(result);
			scroll(0,348);
        }
    });
}

/*$(function(){
	var offset_x=( $(window).width()-960)/2-48;
	scrollAd();
	$(window).scroll(scrollAd);
	$('.qlink_layer').css("right",offset_x);
})
function scrollAd(){
	var offset = $(window).height() - $('.qlink_layer').height() + $(document).scrollTop()-120;
	$('.qlink_layer').animate({top:offset},{duration:800,queue:false});
}*/

/*$(function(){
	var offset_x=( $(window).width()-1004)/2-48;
	scrollAd();
	$(window).scroll(scrollAd);
	$('.qlink_layer').css("right",offset_x);
})
function scrollAd(){
	var offset = $(window).height() - $('.qlink_layer').height() + $(document).scrollTop()-180;
	$('.qlink_layer').animate({top:offset},{duration:800,queue:false});
}*/


$(function(){
    var tab_a=$('.tab_acc a');
    tab_a.mouseover(function(){
        var j=tab_a.index($(this)[0]);
        tab_a.eq(j).addClass('Ahov').siblings().removeClass();
        $('#div_zhff>ul').eq(j).show().siblings().hide();
    });
});


$(function(){
	$(".tab01").click(function(){
		$.getScript("");					   
	});
});
function CurentTime()
    { 
        var now = new Date();
       
        var year = now.getFullYear();       //年
        var month = now.getMonth() + 1;     //月
        var day = now.getDate();            //日
       
        var hh = now.getHours();            //时
        var mm = now.getMinutes();          //分
       
        var clock = year + "-";
       
        if(month < 10)
            clock += "0";
       
        clock += month + "-";
       
        if(day < 10)
            clock += "0";
           
        clock += day + " ";
       
        return(clock); 
    } 
	var __qqClockShare = 
{
   content: "265gfshttp://kf.265g.com/",
   time: "",
   advance: 0,//表示提前多少时间
   url: "http://kf.265g.com/",
   icon: "3_1"
};

$(function(){
initclock();
});

function initclock()
{
$(".mod_tab01 tr").find('td:eq(2)').hover(function(){
	$(this).css('cursor','pointer');
	$(this).find('span').eq(0).hide();
	$(this).find('span').eq(1).show();
}
,
function(){
	 $(this).find('span').eq(0).show();
	 $(this).find('span').eq(1).hide();
}
);
$(".mod_tab01 tr").find('td:eq(2)').bind("click",function(){
	var yycs=$(this).parent().find('td').eq(5).text();
	var gamename=$(this).parent().find('td').eq(0).text();
	var fuqm=$(this).parent().find('td').eq(4).text();
	var  hmtime=$(this).find('span').eq(0).text().split(' ');
	var flag=$(this).parent().last().attr('class');
	if(flag=='a03_sty')
	{
		var urladdress=$(this).parent().find('td').eq(3).find('a').attr("href");
	}
	else
	{
		var urladdress=$(this).parent().find('td').eq(4).find('a').attr("href");
	}
	__qqClockShare.content=yycs+'《'+gamename+'》'+fuqm+urladdress;
	__qqClockShare.url=urladdress;
	__qqClockShare.time=CurentTime()+hmtime[1];
	window.open("http://qzs.qq.com/snsapp/app/bee/widget/open.htm#content=" + encodeURIComponent(__qqClockShare.content) +"&time=" + encodeURIComponent(__qqClockShare.time) +"&advance=" + __qqClockShare.advance +"&url=" + encodeURIComponent(__qqClockShare.url));
});
} 
$(function(){
  $('#blocknav ul li a').click(function() {
	
	$('#blocknav ul li a').removeClass('mini_nav_ahov');
		$(this).addClass('mini_nav_ahov');

		var name=$(this).attr("value");  


	    $(".tab01 tr").removeClass('bgtr');
       $("."+name).addClass('bgtr');  
		//var href = '#'+$(this).attr("href");

		//alert(href);

		href = '#'+name

		//var pos = $(href).offset().top-42;

		var pos = $(href).offset().top;

		//if( !$("html,body").is(":animated") ){
	$("html,body").animate({scrollTop: pos}, 1000);
	return false;
		//}
		
    });
});