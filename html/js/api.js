function Api(){
    this.baseUrl = "http://47.96.79.199/opengame.do";
}

Api.prototype.formatTime = function(time){
    var date = new Date(time);
    var month = date.getMonth()+1;
    var day = date.getDate();
    var hour = date.getHours();
    var minute = date.getMinutes();
    return month+"月" +day+ '日 ' +hour+ ':' +minute;
}

Api.prototype.request = function(act,data){
    jQuery.support.cors = true;
    var response = $.ajax({
        url:this.baseUrl+'?act='+act,
        data:data||{},
        crossDomain: true,
        // headers: {
        //     'Access-Control-Allow-Origin': '*'
        // },
        async:false,
        success:function(data){
            console.log('success:'+data);
        },
        error:function(a,b,c){
            console.log('error',a,b,c)
        }
    });
    // console.log(response);
    var data = response.status===200?JSON.parse(response.responseText):''
    if(typeof data === 'object'){
        return data || [];
    }else{
        console.log('接口请求出错');
    }
}
// 新区推荐
Api.prototype.getNewZones = function(){
    var zones = this.request('newzone');
    var zones = zones['state']==1?zones['data']:[];
    var newzones = [];
    for(var i=0,j=zones.length;i<j;i++){
        zones[i].addtime = zones[i].adtime && zones[i].adtime.substring(11,13);
        newzones.push(zones[i]);
    };
    return newzones
}
// 推荐区服
Api.prototype.getRecommend = function(type){
    var zones = this.request('recommend',{
        type:type
    });
    var zones = zones['state']==1?zones['data']:[];
    var newzones = [];
    for(var i=0,j=zones.length;i<j;i++){
        zones[i].addtime = this.formatTime(zones[i].adtime);
        zones[i].gamedesc = zones[i]['gamedesc'] && zones[i]['gamedesc'].substring(0,35);
        newzones.push(zones[i]);
    };
    return newzones
}
// 新闻列表
Api.prototype.getNews = function(data){
    return this.request('newslist',{
        type:data.type || 1,
        pageindex:data.pageindex || 1,
        pagesize:data.pagesize || 1
    });
}
// 请求上一页下一页
Api.prototype.getPageCon = function(data){
    console.log(data)
    return this.request('beforeafter', {
        id: data.id,
        type: data.type
    })
}

