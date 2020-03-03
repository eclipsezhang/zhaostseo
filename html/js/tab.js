// tab 切换
function tab(){
    var tabs = document.querySelectorAll('.tabs p');
    var tables = document.querySelectorAll('.open-list-table');
    tables[0].style.display = 'block';
    tabs.forEach(function(tab,index){
        if(window.addEventListener){
            tab.addEventListener('click',function(e){
                handlerTab(e,index);
            });
        }else{
            tab.attachEvent('onclick',function(e){
                handlerTab(e,index);
            });
        }
    });
    function handlerTab(e,index){
        tabs.forEach(function(tab){
            tab.setAttribute('class','')
        });
        tables.forEach(function(table,_index){
            if(index===_index){
                table.style.display='block';
            }else{
                table.style.display='none';
            }
        });
        e.target.setAttribute('class','active');
    }
};