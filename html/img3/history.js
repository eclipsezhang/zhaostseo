$(function(){
	$(".kf_li_new").hover(function(){
        	history();
		$(".li_kf_li_new").toggle();
	});
});

function getCookie(name)//取cookies函数        
{
    var arr = document.cookie.match(new RegExp("(^| )"+name+"=([^;]*)(;|$)"));
    if(arr != null) return unescape(arr[2]); return null;
}

function history(obj){
	var myhistory = getCookie('history');
	if(myhistory != null){
		if ($('#history_status').val() == '1') {
			$('#history_status').val('0');
			$.ajax({
				type: "POST",
				url: 'index.php?tp=ajax',
				data: 'methods=history',
				success: function(result){
					$('#history_status').val('1');
					$('.showhistory').html(result);
				}
			});
		}
	} else {
		$('.showhistory').html('<ul><li>没有记录</li></ul>');
	}
}

function clearhistory(obj){
	$('.showhistory').html('<ul><li>没有记录</li></ul>');
	$.ajax({
		type: "POST",
		url: 'index.php?tp=ajax',
		data: 'methods=delhistory',
		success: function(result){}
	});
}