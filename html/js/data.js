// 利用vue 做数据绑定
var app = new Vue({
    el: '#list-content',
    data:{
            news:[],
            showzones:[],
            newzones:[],
            lastzones:[],
            temorrowzones:[],
            classiczones:[],
            newzonepageindex:0,
            show:false,
            pagesize:10,
            totalPages:0,
            changeNewState:false
    },
    mounted:function() {
        //启动tab切换
        tab();
        //请求界面数据
        this.oApi = new Api();
        this.getAllData();
        this.show = true;
        //列表页数据
        this.type = document.querySelector('.active').getAttribute('type');
        this.type && this.getNews({type:this.type});
        this.pagetion(this.totalPages);
    },
    methods: {
        getAllData:function(){
            this.newzones = this.oApi.getNewZones();
            this.lastzones = this.oApi.getRecommend(1);
            this.temorrowzones = this.oApi.getRecommend(2);
            this.classiczones = this.oApi.getRecommend(3);
            this.showzones = this.newzones.slice(0,10);
            if(this.newzones.length>10){
                this.changeNewState = true;
                var that = this;
                setInterval(function(){
                    that.nextpage();
                },5000);
            }
        },
        nextpage:function(){
            this.show = false;
            var that = this;
            setTimeout(function(){
                that.newzonepageindex += 10;
                var showzones = that.newzones.slice(that.newzonepageindex,that.newzonepageindex+10);
                if(showzones.length>0){
                    that.showzones = showzones
                }else{
                    that.showzones = that.newzones.slice(0,10);
                    that.newzonepageindex = 0;
                }
                that.show = true;
            });
        },
        startGame:function(dom,pcurl,weburl,h5url,syd,source){
            var hmtMap = {
                right:{
                    category:'点击',
                    action:'弹出下载对话框',
                    label:'开始游戏'
                },
                lastzones:{
                    category:'点击',
                    action:'弹出下载对话框【最新开区】',
                    label:'开始游戏'
                },
                temorrowzones:{
                    category:'点击',
                    action:'弹出下载对话框【明日开区】',
                    label:'开始游戏'
                },
                classiczones:{
                    category:'点击',
                    action:'弹出下载对话框【经典老区】',
                    label:'开始游戏'
                }
            }
            _hmt.push(['_trackEvent',hmtMap[source]['category'],hmtMap[source]['action'],hmtMap[source]['label']]);
            StarGmae(dom,pcurl,weburl,h5url,syd,source)
        },
        getNews:function(data){
            var newsData = this.oApi.getNews({
                type:data.type,
                pageindex:data.pageindex||1,
                pagesize:this.pagesize
            });
            this.news = newsData['data'];
            this.totalPages = Math.ceil(newsData.total/this.pagesize);
        },
        pagetion:function(totalPages){
            if(totalPages==0) return false;
            var _this = this;
            this.$nextTick(function(){
                $.jqPaginator('#pagination', {
                    totalPages: totalPages,
                    visiblePages: 7,
                    currentPage: 1,
                    prev: '<li class="prev"><a href="javascript:;"><</a></li>',
                    next: '<li class="next"><a href="javascript:void(0);">></a></li>',
                    page: '<li class="bl_page"><a href="javascript:;">{{page}}</a></li>',
                    onPageChange: function (num, type) {
                        _this.getNews({
                            type:_this.type,
                            pageindex:num
                        });
                    }
                }); 
            });
        }
    },

});
