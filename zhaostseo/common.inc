<?php

define("PATH", '../html/');
define("TPL_PATH", '../html/tpl/');
define("FTP_HOST", '127.0.0.1'); // ftp_host
define("FTP_PORT", '21'); // ftp_port
define("FTP_USER", 'root'); // ftp_user
define("FTP_PASS", '123456'); // ftp_pass
define("FTP_DIR", '/'); // ftp_dir
define('STORE_DB_HOST', "rm-bp10ol5669dc95m0nho.sqlserver.rds.aliyuncs.com,3433");
define('STORE_DB_USER', "hygame_test");
define('STORE_DB_PASS', 'hN2uv9110dpg');
define('STORE_DB_NAME', "hygame");
define("GAMEURL", 'http://115.238.225.54/opengame.do');
define("VERURL", 'http://115.238.225.54/gamevertype.do');
define('GAMEFILE', 'opengame.xml');
define('VERFILE', 'gamever.xml');
define("KEY", 'cfcf7a1d8e0b993572071865cc0eff5e');
define("TPL", 'tpl_index.html');
define('DETAIL_TPL', 'tpl_detail.html');
define('LIST_TPL', 'tpl_list.html');
define("FILE", 'list.html');
define("LIST_FILE", 'list.html');
define("SIGN_KEY", 'ndyz93wjmaqu3342o5mflkqxravr88nh');
define('IMG_PATH', 'https://oss-cn-hangzhou.aliyuncs.com/image-storage/');
define('NEW_ARTICLES', 'new_articles'); // 最新资讯 new_articles_id.html
define('GAME_EVALUATION', 'game_evaluation'); // 游戏测评 game_evaluation_id.html
define('GAME_DATA', 'game_data'); // 游戏资料 game_data_id.html
define('PLAYER_ATT', 'player_att'); // 玩家关注 player_att_id.html

function getStoreDBLink() {
    $storeDBLink = mssql_connect(STORE_DB_HOST, STORE_DB_USER, STORE_DB_PASS);

    mssql_select_db(STORE_DB_NAME, $storeDBLink);

    if (!$storeDBLink) {
        $msg = "mssql_error" . $storeDBLink;
        echo json_encode(array('status' => 2, 'msg' => $msg));
        exit;
    }

    return $storeDBLink;
}

function queryByStore($sql) {
    $conn = getStoreDBLink();

    $ret = mssql_query($sql, $conn);

    $array = array();

    while ($item = mssql_fetch_array($ret)) {
        $array[] = $item;
    }

    return $array;
}

// 首页
function createIndexHtml($data, $verlist) {
    $str = "";
    $str2 = "";
    $str173uu = "";
    $str173uu_new = "";
    $topad = "";
    $strtopad = "";
    $daystart = strtotime(date('Y-m-d 00:00:00'));
    $dayend = strtotime(date('Y-m-d 23:59:59'));
    $m = 0;
    $tempday = "";

    for ($i = 0; $i < count($data); $i++) {
        //套黄设置
        $strImg = "";
        $strUseCrown = "";
        $strTest = "";
        $bgColor = "#ffffff";

        if ($data[$i]['IsYellow'] == "1") {
            $bgColor = "#fffbba";
            $strTest = "-<span style=\"color:red\">推荐</span>";

            //新区推荐
            if ($data[$i]['IsNew'] == "1") {
                $strImg = "<img src=\"images/new.gif\" class=\"hotpic\" />";
            } else {
                $strImg = "<img src=\"images/hot.gif\" class=\"hotpic\" />";
            }
        }

        //新服设置
        if ($data[$i]['IsNew'] == "1") {
            $strImg = "<img src=\"images/new.gif\" class=\"hotpic\" />";
        }

        //推荐设置
        if ($data[$i]['Recommend'] == "1") {
            $strImg = "<img src=\"images/hot.gif\" class=\"hotpic\" />";
        }

        //授权年限
        if ((int) $data[$i]['UseCrown'] >= 1) {
            $strUseCrown = "<img title=\"" . (int) $data[$i]['UseCrown'] . "年臻品,值得信赖!\" src=\"images/crown_" . (int) $data[$i]['UseCrown'] . ".png\"/>";
        }

        //客户端标识
        $strServerType = "";
        $strServerTypeImg = "";
        if ($data[$i]['ServerType'] == "1") //端游
        {
            $strServerType = "pc";
            $strServerTypeImg = "<img src=\'images/pc.png\' border=\'0\'>";
        } else if ($data[$i]['ServerType'] == "2") //手游
        {
            $strServerType = "m";
            $strServerTypeImg = "<img src=\'images/m.png\' border=\'0\'>";
        } else if ($data[$i]['ServerType'] == "3") //页游(暂未开放)
        {
            $strServerType = "h5";
            $strServerTypeImg = "<img src=\'images/h5.png\' border=\'0\'>";
        } else if ($data[$i]['ServerType'] == "4") //互通
        {
            if ($data[$i]['ClientTypeAD'] == "3") {
                //端游+手游
                $strServerType = "pcm";
                $data[$i]['H5GameWeb'] = "";
                $strServerTypeImg = "<img src=\'images/pc_m(2).png\' border=\'0\'>";
            } else if ($data[$i]['ClientTypeAD'] == "5") {
                //H5+端游
                $strServerType = "pcm";
                $data[$i]['GameWeb'] = '';
                $strServerTypeImg = "<img src=\'images/pc_m(2).png\' border=\'0\'>";
            } else if ($data[$i]['ClientTypeAD'] == "6") {
                //H5+手游
                $strServerType = "pcm";
                $data[$i]['DlqDownAddr'] = '';
                $strServerTypeImg = "<img src=\'images/pc_m(2).png\' border=\'0\'>";
            } else if ($data[$i]['ClientTypeAD'] == "7") {
                //端游+手游+H5
                $strServerType = "pcm";
                $strServerTypeImg = "<img src=\'images/pc_m(2).png\' border=\'0\'>";

            }

        }

        $GameName = cutstr($data[$i]['GameName'], 0, 20);
        $GameDesc = cutstr($data[$i]['GameDesc'], 0, 55);
        $GameDesc2 = cutstr($data[$i]['GameDesc'], 0, 35);
        //固顶设置
        if ($data[$i]["IsTop"] == "1") {
            $topad = "<tr onmouseover=\\\"this.style.backgroundColor='#F3F3F3'\\\" onmouseout=\\\"this.style.backgroundColor='#ffffff'\\\" style=\\\"background-color:#ffffff;\\\" align=\\\"center\\\">";
            $topad .= "<td><a href=\\\"" . $data[$i]['GameWeb'] . "\\\" target=\\\"_blank\\\">" . $data[$i]['GroupName'] . "</a></td>";
            $topad .= "<td title=\\\"" . $data[$i]['GameName'] . "\\\"><a href=\\\"" . $data[$i]['GameWeb'] . "\\\" target=\\\"_blank\\\">" . $GameName . "</a><img class='pc' src='images/pc.png'  border='0'/><img class='m' src='images/m.png' border='0'/><img class='m' src='images/pc_m(2).png' border='0'/></td>";
            $topad .= "<td style=\\\"color:red\\\">全天固顶推荐</td>";
            $topad .= "<td title=\\\"" . $data[$i]['GameDesc'] . "\\\">" . $GameDesc . "</td>";

            //开始游戏
            if ($data[$i]['ServerType'] == "4") //互通，打开层。
            {
                $topad .= "<td><a href=\"javascript:;\" onclick=\"StarGmae(this,'" . $data[$i]['DlqDownAddr'] . "','" . $data[$i]['GameWeb'] . "','" . $data[$i]['H5GameWeb'] . "','','start')\" class=\"pn pnc\" style=\"padding:5px;\"><span>开始游戏</span></a></td>";
            } else if ($data[$i]['ServerType'] == "1") //端游，直接下载登录器。
            {
                $topad .= "<td><a href=\"" . $data[$i]['DlqDownAddr'] . "\" class=\"pn pnc\" style=\"padding:5px;\"  onclick=\"_czc.push(['_trackEvent',  '下载', '下载端游', '端游','5','xiazai']);\"><span>开始游戏</span></a></td>";
            } else //手游、页游，访问游戏网站。
            {
                $topad .= "<td><a href=\"" . $data[$i]['GameWeb'] . "\" target=\"_blank\" class=\"pn pnc\" style=\"padding:5px;\"><span>开始游戏</span></a></td>";
            }

            $topad .= "<td><a href=\\\"" . $data[$i]['GameWeb'] . "\\\" target=\\\"_blank\\\" class=\\\"pn pnd\\\" style=\\\"padding:5px;\\\"   onclick=\"_czc.push(['_trackEvent',  '点击', '进入GM游戏官网', '游戏网站','5','dianji']);\"><span>点击查看</span></a></td>";
            $topad .= "</tr>";

            $strtopad .= "TopAdList[" . $m . "] = \"" . $topad . "\"\r\n";
            $m++;
            continue;
        }

        //子导航条
        $day = date('Y-m-d', strtotime($data[$i]['StartTime']));

        if ($tempday == "") {
            $tempday = $day;
        } else {
            if ($day != $tempday && $data[$i]['IsYellow'] != "1") {
                if (strtotime($data[$i]['StartTime']) > strtotime(date('Y-m-d 00:00:00', time())) && strtotime($tempday . ' 00:00:00') <= strtotime(date('Y-m-d 00:00:00', time()))) {
                    $str .= "<tr>";
                    $str .= "<td colspan=\"6\" bgcolor=\"#ff6600\" align=\"center\" ><span style=\"color:#ffffff;\"><strong>↓未来即将开的区↓</strong></span></td>";
                    $str .= "</tr>";

                    $str2 .= "<tr>";
                    $str2 .= "<td colspan=\"6\" bgcolor=\"#ff6600\" align=\"center\" ><span style=\"color:#ffffff;\"><strong>↓未来即将开的区↓</strong></span></td>";
                    $str2 .= "</tr>";
                } else if (strtotime($data[$i]['StartTime']) < strtotime(date('Y-m-d 23:59:59', time())) && strtotime($tempday . ' 00:00:00') >= strtotime(date('Y-m-d 00:00:00', time()))) {
                    $str .= "<tr>";
                    $str .= "<td colspan=\"6\" bgcolor=\"#ff6600\" align=\"center\" ><span style=\"color:#ffffff;\"><strong>↓历史已开的区↓</strong></span></td>";
                    $str .= "</tr>";

                    $str2 .= "<tr>";
                    $str2 .= "<td colspan=\"6\" bgcolor=\"#ff6600\" align=\"center\" ><span style=\"color:#ffffff;\"><strong>↓历史已开的区↓</strong></span></td>";
                    $str2 .= "</tr>";
                }

                $tempday = $day;
            }
        }

        $str .= "<tr  onmouseover=\"this.style.backgroundColor='#F3F3F3'\" onmouseout=\"this.style.backgroundColor='" . $bgColor . "'\" style=\"background-color:" . $bgColor . ";\" align=\"center\" VerTypeID=\"" . $data[$i]['VerTypeID'] . "\" AuthYear=\"" . $data[$i]['AuthYear'] . "\">";
        $str .= "<td><a href=\"" . $data[$i]['GameWeb'] . "\" target=\"_blank\">" . $data[$i]['GroupName'] . " " . $strImg . $strUseCrown . "</a></td>";
        $str .= "<td title=\"" . $data[$i]['GameName'] . "\" class=\"serverName\" type=\"" . $strServerType . "\"><a href=\"" . $data[$i]['GameWeb'] . "\" target=\"_blank\">" . $GameName . "</a><img class='pc' src='images/pc.png'  border='0'/><img class='m' src='images/m.png' border='0'/><img class='m' src='images/pc_m(2).png' border='0'/></td>";
        $str .= "<td style=\"color:red\">" . date('m/d/H点i分开放', strtotime($data[$i]['StartTime'])) . "</td>";
        $str .= "<td title=\"" . $data[$i]['GameDesc'] . "\">" . $GameDesc . $strTest . "</td>";

        //开始游戏
        if ($data[$i]['ServerType'] == "4") //互通，打开层。
        {
            $str .= "<td><a href=\"javascript:;\" onclick=\"StarGmae(this,'" . $data[$i]['DlqDownAddr'] . "','" . $data[$i]['GameWeb'] . "','" . $data[$i]['H5GameWeb'] . "','','start')\" class=\"pn pnc\" style=\"padding:5px;\"><span>开始游戏</span></a></td>";
            $str .= "<td><a href=\"" . $data[$i]['GameWeb'] . "\" target=\"_blank\" class=\"pn pnd\" style=\"padding:5px;\" onclick=\"_czc.push(['_trackEvent',  '点击', '进入GM游戏官网', '游戏网站','5','dianji']);\"><span>点击查看</span></a></td>";
        } else if ($data[$i]['ServerType'] == "1") //端游，直接下载登录器。
        {
            $str .= "<td><a href=\"" . $data[$i]['DlqDownAddr'] . "\" class=\"pn pnc\" style=\"padding:5px;\" onclick=\"_czc.push(['_trackEvent',  '下载', '下载端游', '端游','5','xiazai']);\"><span>开始游戏</span></a></td>";
            $str .= "<td><a href=\"" . $data[$i]['GameWeb'] . "\" target=\"_blank\" class=\"pn pnd\" style=\"padding:5px;\" onclick=\"_czc.push(['_trackEvent',  '点击', '进入GM游戏官网', '游戏网站','5','dianji']);\"><span>点击查看</span></a></td>";
        } else if ($data[$i]['ServerType'] == "3") //H5
        {
            $str .= "<td><a href=\"" . $data[$i]['H5GameWeb'] . "\" class=\"pn pnc\" style=\"padding:5px;\" onclick=\"_czc.push(['_trackEvent',  '打开', '打开H5游戏页面', 'H5游戏','5','da开']);\"><span>开始游戏</span></a></td>";
            $str .= "<td><a href=\"" . $data[$i]['H5GameWeb'] . "\" target=\"_blank\" class=\"pn pnd\" style=\"padding:5px;\" onclick=\"_czc.push(['_trackEvent',  '点击', '进入GM游戏官网', '游戏网站','5','dianji']);\"><span>点击查看</span></a></td>";
        } else //手游、页游，访问游戏网站。
        {
            $str .= "<td><a href=\"" . $data[$i]['GameWeb'] . "\" target=\"_blank\" class=\"pn pnc\" style=\"padding:5px;\"><span>开始游戏</span></a></td>";
            $str .= "<td><a href=\"" . $data[$i]['GameWeb'] . "\" target=\"_blank\" class=\"pn pnd\" style=\"padding:5px;\" onclick=\"_czc.push(['_trackEvent',  '点击', '进入GM游戏官网', '游戏网站','5','dianji']);\"><span>点击查看</span></a></td>";
        }

        $str .= "</tr>";

        $str2 .= "<tr onmouseover=\"this.style.backgroundColor='#F3F3F3'\" onmouseout=\"this.style.backgroundColor='" . $bgColor . "'\" style=\"background-color:" . $bgColor . ";\" align=\"center\" VerTypeID=\"" . $data[$i]['VerTypeID'] . "\" AuthYear=\"" . $data[$i]['AuthYear'] . "\">";
        $str2 .= "<td><a href=\"" . $data[$i]['DlqDownAddr'] . "\" target=\"_blank\">" . $data[$i]['GroupName'] . " " . $strImg . $strUseCrown . "</a></td>";
        $str2 .= "<td title=\"" . $data[$i]['GameName'] . "\"><a href=\"" . $data[$i]['DlqDownAddr'] . "\" target=\"_blank\">" . $GameName . "</a></td>";
        $str2 .= "<td style=\"color:red;\">" . date('m/d/H点i分开放', strtotime($data[$i]['StartTime'])) . "</td>";
        $str2 .= "<td title=\"" . $data[$i]['GameDesc'] . "\">" . $GameDesc . $strTest . "</td>";
        $str2 .= "<td><a href=\"" . $data[$i]['DlqDownAddr'] . "\" class=\"pn pnc\" style=\"padding:5px;\"><span>开始游戏</span></a></td>";
        $str2 .= "<td><a href=\"" . $data[$i]['GameWeb'] . "\" target=\"_blank\" class=\"pn pnd\" style=\"padding:5px;\"><span>点击查看</span></a></td>";
        $str2 .= "</tr>";

        if (strtotime($data[$i]['StartTime']) >= strtotime(date('Y-m-d 00:00:00', time())) && strtotime($data[$i]['StartTime']) < strtotime(date('Y-m-d 23:59:59', time()))) {
            $str173uu .= "<tr onmouseover=\"this.style.backgroundColor='#F3F3F3'\" onmouseout=\"this.style.backgroundColor='" . $bgColor . "'\" style=\"background-color:" . $bgColor . ";\" align=\"center\" VerTypeID=\"" . $data[$i]['VerTypeID'] . "\" AuthYear=\"" . $data[$i]['AuthYear'] . "\">";
            $str173uu .= "<td><a href=\"" . $data[$i]['DlqDownAddr'] . "\" target=\"_blank\">" . $data[$i]['GroupName'] . " " . $strImg . $strUseCrown . "</a></td>";
            $str173uu .= "<td title=\"" . $data[$i]['GameName'] . "\"><a href=\"" . $data[$i]['DlqDownAddr'] . "\" target=\"_blank\">" . $GameName . "</a></td>";
            $str173uu .= "<td style=\"color:red; font-weight:bold;\">" . date('H:i', strtotime($data[$i]['StartTime'])) . "</td>";
            $str173uu .= "<td title=\"" . $data[$i]['GameDesc'] . "\">" . $GameDesc2 . $strTest . "</td>";
            $str173uu .= "<td><a href=\"" . $data[$i]['DlqDownAddr'] . "\" class=\"pn pnc\" style=\"padding:5px;\"><span>开始游戏</span></a></td>";
            $str173uu .= "</tr>";
        }

        if ($i <= 20) {
            $str173uu_new .= "document.write('<tr class=\"yellow\" onMouseOver=\"this.style.backgroundColor=\\'#ffe1e1\\'\" onMouseOut=\"this.style.backgroundColor=\\'#fbffb9\\'\">');";
            $str173uu_new .= "document.write('<td><a href=\"" . $data[$i]['GameWeb'] . "\" target=\"_blank\">" . $data[$i]['GroupName'] . " " . $strImg . $strUseCrown . "</a></td>');";

            if ($data[$i]['ServerType'] == "4") //互通，打开层。
            {
                $str173uu_new .= "document.write('<td><a href=\"javascript:;\" onclick=\"StarGmae(this,\'" . $data[$i]['DlqDownAddr'] . "\',\'" . $data[$i]['GameWeb'] . "\',\'" . $data[$i]['H5GameWeb'] . "\')\">" . $GameName . " " . $strServerTypeImg . "</a></td>');";
            } else if ($data[$i]['ServerType'] == "1") //端游，直接下载登录器。
            {
                $str173uu_new .= "document.write('<td title=\"" . $data[$i]['GameName'] . "\"><a href=\"" . $data[$i]['DlqDownAddr'] . "\">" . $GameName . " " . $strServerTypeImg . "</a></td>');";
            } else //手游、页游，访问游戏网站。
            {
                $str173uu_new .= "document.write('<td title=\"" . $data[$i]['GameName'] . "\"><a href=\"" . $data[$i]['GameWeb'] . "\" target=\"_blank\">" . $GameName . " " . $strServerTypeImg . "</a></td>');";
            }

            $str173uu_new .= "document.write('<td class=\"red\">" . date('H:i', strtotime($data[$i]['StartTime'])) . "</td><td title=\"" . $data[$i]['GameDesc'] . "\">" . $GameDesc2 . $strTest . "</td>');";

            if ($data[$i]['ServerType'] == "4") //互通，打开层。
            {
                $str173uu_new .= "document.write('<td><a href=\"javascript:;\" class=\"pnc\" onclick=\"StarGmae(this,\'" . $data[$i]['DlqDownAddr'] . "\',\'" . $data[$i]['GameWeb'] . "\',\'" . $data[$i]['H5GameWeb'] . "\')\"><span>开始游戏</span></a></td>');";
            } else if ($data[$i]['ServerType'] == "1") //端游，直接下载登录器。
            {
                $str173uu_new .= "document.write('<td><a href=\"" . $data[$i]['DlqDownAddr'] . "\" class=\"pnc\"><span>开始游戏</span></a></td>');";
            } else //手游、页游，访问游戏网站。
            {
                $str173uu_new .= "document.write('<td><a href=\"" . $data[$i]['GameWeb'] . "\" class=\"pnc\" target=\"_blank\"><span>开始游戏</span></a></td>');";
            }

            $str173uu_new .= "document.write('</tr>');";
        }
    }

    $tplstr = getfile(TPL);

    // 版本类型
    $vertype = "";

    for ($j = 0; $j < count($verlist); $j++) {
        $class = "";

        if ($verlist[$j]['HiLight']) {
            $class = "class=\"hilite\"";
        }

        $vertype .= "<li " . $class . "><a href=\"javascript:void(0);\" onclick=\"showGame(" . $verlist[$j]['VerID'] . ");\">" . $verlist[$j]['VerName'] . "</a></li>";
    }

    $tplstr = str_replace('{strTopAd}', $strtopad, $tplstr);
    $tplstr = str_replace('{TopAdNum}', $m, $tplstr);
    $tplstr = str_replace('{vertype}', $vertype, $tplstr);
    $tplstr = str_replace('{DATA}', $str, $tplstr);
    $tplstr = str_replace('{datetime}', date('Y-m-d H:i:s', time()), $tplstr);

    // zhaostseo
    $tplstr = str_replace('{swiper-wrapper}', createSwiperWrapper(), $tplstr);
    $tplstr = str_replace('{bl-imags}', createBlImags(), $tplstr);
    $tplstr = str_replace('{new-articles}', createNewsList(1, 5, NEW_ARTICLES), $tplstr);
    $tplstr = str_replace('{game-evaluation}', createNewsList(2, 10, GAME_EVALUATION), $tplstr);
    $tplstr = str_replace('{game-data}', createNewsList(3, 10, GAME_DATA), $tplstr);
    $tplstr = str_replace('{player-att}', createNewsList(4, 10, PLAYER_ATT), $tplstr);

    return $tplstr;
}

// 首页 swiper-wrapper
function createSwiperWrapper() {
    // type = 0 slideimg
    $sql = "select top 1 slideimg from hy_zhaostnews where type = 0";

    $slideimg_list = queryByStore($sql);
    $slideimg_list = $slideimg_list[0]['slideimg'];
    $slideimg_list = explode(',', $slideimg_list);

    $html = '';

    foreach ($slideimg_list as $slideimg) {
        $slideimg = IMG_PATH . $slideimg;
        $html .= "<div class=\"swiper-slide\" style=\"background-image: url({$slideimg});\"></div>";
    }

    return $html;
}

// 首页 图片 bl-imags
function createBlImags() {
    // type = 0 img
    $sql = "select top 1 img from hy_zhaostnews where type = 0";

    $img_list = queryByStore($sql);
    $img_list = $img_list[0]['img'];
    $img_list = explode(',', $img_list);

    $html = '';

    $i = 0;

    foreach ($img_list as $img) {
        if ($i == 4) {
            break;
        }
        $i++;
        $img = IMG_PATH . $img;
        $html .= "<img src=\"{$img}\" alt=\"\" srcset=\"\">";
    }

    return $html;
}

// 首页 news
function createNewsList($type, $num, $news_name) {
    // 最新资讯 new-articles type=1 num=5
    // 游戏测评 game-evaluation type=2 num=10
    // 游戏资料 game-data type=3 num=10
    // 玩家关注 player-att type=4 num=10

    switch ($type) {
        case 1:
            $position = '最新资讯'; // new_articles_id.html
            break;

        case 2:
            $position = '游戏测评'; // game_evaluation_id.html
            break;

        case 3:
            $position = '游戏资料'; // game_data_id.html
            break;

        case 4:
            $position = '玩家关注'; // player_att_id.html
            break;
        
        default:
            echo json_encode(array('status' => 2, 'msg' => iconv('GB2312', 'UTF-8', '找不到指定类型')));
            exit;
    }

    $sql = "select top {$num} id, title, newstime from hy_zhaostnews where type = {$type} order by newstime desc, id desc";

    $news_list = queryByStore($sql);

    $html = '';

    $i = 0;

    foreach ($news_list as $news) {
        $id = $news['id'];
        $title = $news['title'];
        $newstime = date('Y-m-d', strtotime($news['newstime']));

        $html .= "<li><p><a onclick=\"_hmt.push(['_trackEvent', '打开', '打开{$position}新闻', '新闻标题']);\" href=\"./{$news_name}_{$id}.html\">{$title}</a></p><span>{$newstime}</span></li>";
    }

    return $html;
}

// 新闻详情页面
function createDetails($id, $position, $news_name) {
    // {title} {newstime} {content {page-box} {meta} {position}
    global $type;

    $sql = "select top 1 title, newstime, convert(text, newscontent) as newscontent, keywords from hy_zhaostnews where id = {$id}";
    $news = queryByStore($sql);

    $title = $news[0]['title'] . '-找神途';
    $newstime = date('Y-m-d', strtotime($news[0]['newstime']));
    $content = htmlspecialchars_decode($news[0]['newscontent']);
    $keywords = $news[0]['keywords'];
    $description = substr($content, 0, 80);

    $prev_sql = "select top 1 id, title from hy_zhaostnews where ((id != {$id} and newstime > '{$newstime}') or (id > {$id} and newstime = '{$newstime}')) and type = {$type} order by newstime asc, id asc"; // 上一页
    $prev_news = queryByStore($prev_sql);

    $next_sql = "select top 1 id, title from hy_zhaostnews where ((id != {$id} and newstime < '{$newstime}') or (id < {$id} and newstime = '{$newstime}')) and type = {$type} order by newstime desc, id desc"; // 下一页
    $next_news = queryByStore($next_sql);

    $meta = "<meta name=\"keywords\" content=\"{$keywords}\"/>
    <meta name=\"description\" content=\"{$description}\"/>";

    if ($prev_news) {
        $prev_news_id = $prev_news[0]['id'];
        $prev_news_title = $prev_news[0]['title'];

        $prev_html = "<p>
            <span>上一篇：</span>
            <a href=\"./{$news_name}_{$prev_news_id}.html\">{$prev_news_title}</a>
        </p>";
    } else {
        $prev_html = "<p>
            <span>上一篇：</span>
            <a href=\"javascript:void(0)\">没有了</a>
        </p>";
    }

    if ($next_news) {
        $next_news_id = $next_news[0]['id'];
        $next_news_title = $next_news[0]['title'];

        $next_html = "<p>
            <span>下一篇：</span>
            <a href=\"./{$news_name}_{$next_news_id}.html\">{$next_news_title}</a>
        </p>";
    } else {
        $next_html = "<p>
            <span>下一篇：</span>
            <a href=\"javascript:void(0)\">没有了</a>
        </p>";
    }

    $page_box = "<div class=\"page-box\">
        <div class=\"near-news\">
            {$prev_html}
            {$next_html}
        </div>
        <a class=\"gotolist\" href=\"list_{$news_name}.html\">返回列表</a>
    </div>";

    $tplstr = getfile(DETAIL_TPL);

    $tplstr = str_replace('{meta}', $meta, $tplstr);
    $tplstr = str_replace('{position}', $position, $tplstr);
    $tplstr = str_replace('{title}', $title, $tplstr);
    $tplstr = str_replace('{newstime}', $newstime, $tplstr);
    $tplstr = str_replace('{content}', $content, $tplstr);
    $tplstr = str_replace('{page-box}', $page_box, $tplstr);
    $tplstr = str_replace('{newsname}', $news_name, $tplstr);

    global $active_new_articles;
    global $active_game_evaluation;
    global $active_game_data;
    global $active_player_att;

    $tplstr = str_replace('{active_new_articles}', $active_new_articles, $tplstr);
    $tplstr = str_replace('{active_game_evaluation}', $active_game_evaluation, $tplstr);
    $tplstr = str_replace('{active_game_data}', $active_game_data, $tplstr);
    $tplstr = str_replace('{active_player_att}', $active_player_att, $tplstr);

    return $tplstr;
}

function saveFile($content, $filename) {
    if (file_exists(PATH . $filename)) {
        unlink(PATH . $filename);
    }

    $fp = fopen(PATH . $filename, 'a');
    flock($fp, LOCK_EX);
    fwrite($fp, $content);
    flock($fp, LOCK_UN);
    fclose($fp);

    return 1;
}

function ftpUpload($filename, $path) {
    $ftp_connection = ftp_connect(FTP_HOST, FTP_PORT, 3);

    if (!$ftp_connection) {
        return $ftp_connection;
    }

    $ftp_login = ftp_login($ftp_connection, FTP_USER, FTP_PASS);

    if (!$ftp_login) {
        return $ftp_login;
    }

    ftp_pasv($ftp_connection, true);

    $ftp_chdir = ftp_chdir($ftp_connection, FTP_DIR);

    if ($ftp_chdir && ftp_pwd($ftp_connection) == FTP_DIR) {
        $ret = ftp_put($ftp_connection, $filename, $path, FTP_BINARY);

        return $ret;
    }

    ftp_close($ftp_connection);
}

function curlGet($url, $referer = '', $fllow_location = true, $timeout = 30, $proxy_host = '', $proxy_port = 0) {
    global $gamecontent;
    global $vercontent;

    $ch = curl_init($url);
    curl_setopt($ch, CURLOPT_USERAGENT, "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1;  Embedded Web Browser from: http://bsalsa.com/; CIBA)");
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, $fllow_location);
    curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 5);
    curl_setopt($ch, CURLOPT_TIMEOUT, $timeout);
    curl_setopt($ch, CURLOPT_REFERER, $referer);
    curl_setopt($ch, CURLOPT_ENCODING, "utf-8");
    $buf = curl_exec($ch);
    curl_close($ch);

    if (substr($buf, 2, 3) == "xml") {
        $buf = iconv("gbk", "gbk//IGNORE", $buf);
        if (strstr($url, "opengame")) {
            $gamecontent = ParseGame($buf);
            // savefile($buf, GAMEFILE);
        } else {
            $vercontent = ParseVer($buf);
            // savefile($buf, VERFILE);
        }
        return 1;
    } else {
        return $buf;
    }
}

function ParseGame($xmlStr) {
    global $toplist;
    global $topsort;

    $templist = array();
    $list = array();
    $resort = false;
    $i = 0;
    $m = 0;
    preg_match_all('|<item(.*)/>|iU', $xmlStr, $match_arr, PREG_PATTERN_ORDER);
    $GameList = $match_arr[1];

    for ($j = 0; $j < count($GameList); $j++) {
        preg_match('|GameID="(.*)"|iU', $GameList[$j], $match_arr2);
        $GameID = $match_arr2[1];

        preg_match('|GroupName="(.*)"|iU', $GameList[$j], $match_arr2);
        $GroupName = $match_arr2[1];

        preg_match('|GameName="(.*)"|iU', $GameList[$j], $match_arr2);
        $GameName = $match_arr2[1];

        preg_match('|StartTime="(.*)"|iU', $GameList[$j], $match_arr2);
        $StartTime = $match_arr2[1];

        preg_match('|GameDesc="(.*)"|iU', $GameList[$j], $match_arr2);
        $GameDesc = $match_arr2[1];

        preg_match('|DlqDownAddr="(.*)"|iU', $GameList[$j], $match_arr2);
        $DlqDownAddr = $match_arr2[1];

        preg_match('|GroupDir="(.*)"|iU', $GameList[$j], $match_arr2);
        $GroupDir = $match_arr2[1];

        preg_match('|GameWeb="(.*)"|iU', $GameList[$j], $match_arr2);
        $GameWeb = $match_arr2[1];

        preg_match('|Recommend="(.*)"|iU', $GameList[$j], $match_arr2);
        $Recommend = $match_arr2[1];

        preg_match('|IsNew="(.*)"|iU', $GameList[$j], $match_arr2);
        $IsNew = $match_arr2[1];

        preg_match('|IsYellow="(.*)"|iU', $GameList[$j], $match_arr2);
        $IsYellow = $match_arr2[1];

        preg_match('|IsTop="(.*)"|iU', $GameList[$j], $match_arr2);
        $IsTop = $match_arr2[1];

        preg_match('|UseCrown="(.*)"|iU', $GameList[$j], $match_arr2);
        $UseCrown = $match_arr2[1];

        preg_match('|AuthYear="(.*)"|iU', $GameList[$j], $match_arr2);
        $AuthYear = $match_arr2[1];

        preg_match('|VerTypeID="(.*)"|iU', $GameList[$j], $match_arr2);
        $VerTypeID = $match_arr2[1];

        preg_match('|ServerType="(.*)"|iU', $GameList[$j], $match_arr2);
        $ServerType = $match_arr2[1];

        preg_match('|H5GameWeb="(.*)"|iU', $GameList[$j], $match_arr2);
        $H5GameWeb = $match_arr2[1];

        preg_match('|ClientTypeAD="(.*)"|iU', $GameList[$j], $match_arr2);
        $ClientTypeAD = $match_arr2[1];

        $GameWeb = urldecode($GameWeb);
        $H5GameWeb = urldecode($H5GameWeb);

        $templist[$i]['GameID'] = $GameID;
        $templist[$i]['GroupName'] = $GroupName;
        $templist[$i]['GameName'] = $GameName;
        $templist[$i]['StartTime'] = $StartTime;
        $templist[$i]['GameDesc'] = $GameDesc;
        $templist[$i]['DlqDownAddr'] = $DlqDownAddr;
        $templist[$i]['GroupDir'] = $GroupDir;
        $templist[$i]['GameWeb'] = $GameWeb;
        $templist[$i]['Recommend'] = $Recommend;
        $templist[$i]['IsNew'] = $IsNew;
        $templist[$i]['IsYellow'] = $IsYellow;
        $templist[$i]['IsTop'] = $IsTop;
        $templist[$i]['UseCrown'] = $UseCrown;
        $templist[$i]['AuthYear'] = $AuthYear;
        $templist[$i]['VerTypeID'] = $VerTypeID;
        $templist[$i]['ServerType'] = $ServerType;
        $templist[$i]['H5GameWeb'] = $H5GameWeb;
        $templist[$i]['ClientTypeAD'] = $ClientTypeAD;

        if ($i == 0) {
            if (count($toplist) == 0 || strtotime($toplist[0]['StartTime']) != strtotime($templist[$i]['StartTime'])) {
                $topsort = array();
                $topsort[$i] = (int) $templist[$i]['GameID'];
                $resort = true;
            } else {
                reverse();
            }

            $toplist = array();

            $toplist[$i] = $templist[$i];
        } else {
            if (strtotime($toplist[0]['StartTime']) == strtotime($templist[$i]['StartTime'])) {
                $toplist[$i] = $templist[$i];

                if ($resort) {
                    $topsort[$i] = (int) $templist[$i]['GameID'];
                }
            } else {
                $list[$m] = $templist[$i];
                $m++;
            }
        }

        $i++;
    }

    return $list;
}

function ParseVer($xmlStr) {
    $list = array();
    $i = 0;
    preg_match_all('|<item(.*)/>|isU', $xmlStr, $match_arr, PREG_PATTERN_ORDER);
    $VerList = $match_arr[1];

    for ($j = 0; $j < count($VerList); $j++) {
        preg_match('|VerID="(.*)"|iU', $VerList[$j], $match_arr2);
        $VerID = $match_arr2[1];

        preg_match('|VerName="(.*)"|iU', $VerList[$j], $match_arr2);
        $VerName = $match_arr2[1];

        preg_match('|VerImg="(.*)"|iU', $VerList[$j], $match_arr2);
        $VerImg = $match_arr2[1];

        preg_match('|HiLight="(.*)"|iU', $VerList[$j], $match_arr2);
        $HiLight = $match_arr2[1];

        preg_match('|DlqShow="(.*)"|iU', $VerList[$j], $match_arr2);
        $DlqShow = $match_arr2[1];

        $list[$i]['VerID'] = $VerID;
        $list[$i]['VerName'] = $VerName;
        $list[$i]['VerImg'] = $VerImg;
        $list[$i]['HiLight'] = $HiLight;
        $list[$i]['DlqShow'] = $DlqShow;

        $i++;
    }

    return $list;
}

function cutStr($string, $start, $length) {
    if (strlen($string) > $length) {
        $str = "";
        $len = $start + $length;
        for ($i = $start; $i < $len; $i++) {
            if (ord(substr($string, $i, 1)) > 0xa0) {
                $str .= substr($string, $i, 2);
                $i++;
            } else {
                $str .= substr($string, $i, 1);
            }
        }
        return $str . '...';
    } else {
        return $string;
    }
}

function reverse() {
    global $topsort;

    $temparr = array();

    for ($i = 0; $i < count($topsort); $i++) {
        if ($i == count($topsort) - 1) {
            $temparr[$i] = $topsort[0];
        } else {
            $temparr[$i] = $topsort[$i + 1];
        }
    }

    $topsort = $temparr;
}

function syncSort() {
    global $toplist;
    global $topsort;

    $templist = $toplist;

    if (count($templist) > count($topsort)) {
        for ($i = 0; $i < count($templist); $i++) {
            if (!in_array($templist[$i]['GameID'], $topsort)) {
                array_push($topsort, $templist[$i]['GameID']);
            }
        }
    } else if (count($templist) < count($topsort)) {
        for ($i = 0; $i < count($topsort); $i++) {
            $IsContain = 0;
            for ($j = 0; $j < count($templist); $j++) {
                if ((int) $topsort[$i] == (int) $templist[$j]['GameID']) {
                    $IsContain = 1;
                }
            }

            if (!$IsContain) {
                array_splice($topsort, $i, 1);
            }
        }
    }
}

function getFile($filename) {
    if (!file_exists(TPL_PATH . $filename)) {
        echo json_encode(array('status' => 2, 'msg' => iconv('GB2312', 'UTF-8', '文件不存在')));
        exit;
    } else {
        $str = file_get_contents(TPL_PATH . $filename);
        return $str;
    }
}