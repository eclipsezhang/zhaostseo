	function StarGmae(dom, pcurl, murl, h5url, sywndlq,source) {//��ʼ��Ϸ
		var actionMap = {
			right:'',
			lastzones:'�����¿�����',
			temorrowzones:'�����տ�����',
			classiczones:'������������'
		}
		var html = '';
		var height = '';
		var i = 0;
		if (pcurl && murl || murl && h5url || pcurl && h5url) {
			var M = {};
			if (pcurl) {
				html += "<a style='margin-top:15px;display:block; class='dy' href='" + pcurl + "'><img src='img/pcd.png' alt='' onclick=\"_hmt.push(['_trackEvent','����','������ض���"+actionMap[source]+"','��������']);\"></a>";
				i++;
			}
			if (murl) {
				i++;
				if (sywndlq) {
					html += "<a style='margin-top:15px;display:block; class='sy' href='javascript:;' onclick='register(this)'><img src='img/syd.png' alt=''></a>";
				} else {
					html += "<a style='margin-top:15px;display:block; class='sy' target='_blank' href='" + murl + "'><img src='img/syd.png' alt='' onclick=\"_hmt.push(['_trackEvent','����','�򿪴���������վ"+actionMap[source]+"','��������']);\"></a>";
				}
			}
			if (h5url) {
				html += "<a style='margin-top:15px;display:block; class='h5' target='_blank' href='" + h5url + "'><img src='img/h5d.png' alt='' onclick=\"_hmt.push(['_trackEvent','����','��H5��Ϸ"+actionMap[source]+"','h5����']);\"></a>";
				i++;
			}
			//M.dialog6.close()
			var html = "<div class='fieldset' style='padding-top:10px;'>" + html + "</div>";
			M.dialog6 = jqueryAlert({
				'title': '',
				'style': 'pc',
				//'content' :  "<div class='fieldset'><a class='dy' href='"+dom.getAttribute('tarurl')+"'>����</a><a class='sy' href='"+dom.getAttribute('tarurl')+"'>����</a><img src='images/tk.png' border='0'/></div>",
				'content': html,
				'width': '300px',
				'height': i === 3 ? '295px' : '220px',
				'modal': true,
				'buttons': {
					'�ر�': function () { },
				}
			})
			M.dialog6.show();
			$('.alert-btn-close').html('��');
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