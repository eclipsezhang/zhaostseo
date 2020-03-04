// tab 切换
function tab(){
    var tabs = document.querySelectorAll('.tabs p');
    var tables = document.querySelectorAll('.open-list-table');
    tables[0].style.display = 'block';
    for(var i=0,j=tabs.length;i<j;i++){
        (function(index){
            var tab = tabs[index];
            if(window.addEventListener){
                tab.addEventListener('click',function(e){
                    handlerTab(e,index);
                });
            }else{
                tab.attachEvent('onclick',function(e){
                    handlerTab(e,index);
                });
            }
        })(i)
    }
    function handlerTab(e,index){
        console.log(index);
        for(var i=0,j=tabs.length;i<j;i++){
            tabs[i].setAttribute('class','')
        }
        for(var i=0,j=tables.length;i<j;i++){
            var table = tables[i];
            if(index===i){
                table.style.display='block';
            }else{
                table.style.display='none';
            }
        }
        e.target.setAttribute('class','active');
    }
};