var lazyload = {
 
     cfg:{loadfunc:null},
          
     load:function(){
		 		//alert(this.cfg.loadfunc);
              if(typeof eval(this.cfg.loadfunc) == 'function'){
                       this.destroy();//注销滚动条事件
                       eval(this.cfg.loadfunc+'();');//调用处理函数
                       return;
              }
              //alert('请确认加载函数是否已经定义?');
     },
 
     setcfg:function(a){//a 为array
           if(typeof a == 'object'){//判断a 是否为数组
               for(var key in a){
                    this.cfg[key] = a[key];//将配置的值赋给lazyload对象的配置参数
               }
               return;
      }
          alert('请确认配置参数格式是否正确?');
     },
 
     register:function(){//初始化 给浏览器绑定滚动事件
          if(window.attachEvent){//IE
                   window.attachEvent("onscroll",this.scroll,false);
          }else{//FF
                   window.addEventListener("scroll",this.scroll,false);
          }
     }
     ,
     scroll:function(){//滚动条 开始滚动 并计算是否到达底部
           //判断滚动条滚到了网页最底部
           //var a = document.documentElement.scrollTop==0? document.body.clientHeight :             document.documentElement.clientHeight;
           //var b = document.documentElement.scrollTop==0? document.body.scrollTop :             document.documentElement.scrollTop;
           //var c = document.documentElement.scrollTop==0? document.body.scrollHeight :             document.documentElement.scrollHeight;
  			//c = c - 200;
           //if(a+b == c){
		   //if(a+b >= c - 7800){
		   var clientHeight = $(window).height(),
		   scrollTop = $(window).scrollTop(),
		   scrollHeight = $(document).height();	//屏幕高度
		   if(clientHeight + scrollTop >=  scrollHeight-2800 ){
                lazyload.load();//开始加载
           }
     }
     ,
     destroy:function(){//注销onscroll事件 防止加载数据的时候继续加载
              if(window.attachEvent){//ff
                   window.detachEvent("onscroll",this.scroll,false);  
              }else{//ie
                       window.removeEventListener("scroll",this.scroll,false);
              }
     }
 
};

var lazyloadpage = 1;

function loadcomment(){
	//alert("ok");
	this.lazyloadpage++;
  	 //请求加载内容
     //加载完毕后 内容更新  重新注册事件
     $.ajax({
          type: "POST",
		  url: 'index.php?tp=index',
		  data: 'method=getTodayList&page='+this.lazyloadpage,
          success:function(content){
              $('.tab01').append(content);
              lazyload.register();
			  initclock();
      	  }
	 });
}

/*window.onload = function(){
     lazyload.setcfg({
              loadfunc : "loadcomment",//加载数据的方法名
     });
     lazyload.register();//注册滚动条事件
}*/

function pageOnLoad(){
	lazyload.setcfg({
              loadfunc : "loadcomment",//加载数据的方法名
     });
     lazyload.register();//注册滚动条事件
}