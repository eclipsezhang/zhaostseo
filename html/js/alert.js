	function StarGmae(dom, pcurl, murl, h5url, sywndlq,source) {//开始游戏
		var actionMap = {
			right:'',
			lastzones:'【最新开区】',
			temorrowzones:'【明日开区】',
			classiczones:'【经典老区】'
		}
		var html = '';
		var height = '';
		var i = 0;
		if (pcurl && murl || murl && h5url || pcurl && h5url) {
			var M = {};
			if (pcurl) {
				html += "<a style='margin-top:15px;display:block; class='dy' href='" + pcurl + "' onclick=\"_hmt.push(['_trackEvent','下载'，'点击下载端游"+actionMap[source]+"','端游下载'])\"><img src='img/pcd.png' alt=''></a>";
				i++;
			}
			if (murl) {
				i++;
				if (sywndlq) {
					html += "<a style='margin-top:15px;display:block; class='sy' href='javascript:;' onclick='register(this)'><img src='img/syd.png' alt=''></a>";
				} else {
					html += "<a style='margin-top:15px;display:block; class='sy' target='_blank' href='" + murl + "' onclick=\"_hmt.push(['_trackEvent','下载'，'打开代理手游网站"+actionMap[source]+"','手游下载'])\"><img src='img/syd.png' alt=''></a>";
				}
			}
			if (h5url) {
				html += "<a style='margin-top:15px;display:block; class='h5' target='_blank' href='" + h5url + "' onclick=\"_hmt.push(['_trackEvent','下载'，'打开H5游戏"+actionMap[source]+"','h5下载'])\"><img src='img/h5d.png' alt=''></a>";
				i++;
			}
			//M.dialog6.close()
			var html = "<div class='fieldset' style='padding-top:10px;'>" + html + "</div>";
			M.dialog6 = jqueryAlert({
				'title': '',
				'style': 'pc',
				//'content' :  "<div class='fieldset'><a class='dy' href='"+dom.getAttribute('tarurl')+"'>端游</a><a class='sy' href='"+dom.getAttribute('tarurl')+"'>手游</a><img src='images/tk.png' border='0'/></div>",
				'content': html,
				'width': '300px',
				'height': i === 3 ? '295px' : '220px',
				'modal': true,
				'buttons': {
					'关闭': function () { },
				}
			})
			M.dialog6.show();
			$('.alert-btn-close').html('×');
			$('.alert-btn-box').html('');
		} else if (murl) {
			//window.open(dom.getAttribute('tarurl'))
			window.open(murl)
			M.dialog.close()
		} else {
			window.location.href = pcurl;
			//window.location.href=dom.getAttribute('tarurl');
			M.dialog.close()
		}
	}