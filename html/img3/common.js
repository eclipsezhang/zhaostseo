function setHome(obj) {
	try {
		obj.style.behavior = "url(#default#homepage)";
		obj.setHomePage("http://www.zhaost.com");
	} catch(e) {
		alert("此操作被浏览器拒绝！请在浏览器地址栏输入“about:config”");
	}
}

function AddFavorite() {
	try {
		window.external.addFavorite(location.href, document.title);
	} catch (e) {
		try {
			window.sidebar.addPanel(document.title, location.href, '');
		} catch (e) {
			alert("加入收藏失败，请使用Ctrl+D进行添加");
		}
	}
}

function AddWebgameFavorite() {
	try {
		var params = window.location.href.replace(/http\:\/\//g, '').split("/");
		url = 'http://' + params[0] + '/' + params[1] + '/' + params[2] + '/';
		window.external.addFavorite(url, document.title);
	} catch (e) {
		try {
			window.sidebar.addPanel(document.title, url, '');
		} catch (e) {
			alert("加入收藏失败，请使用Ctrl+D进行添加");
		}
	}
}
