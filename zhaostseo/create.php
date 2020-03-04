<?php

include_once 'common.inc';

// 验签
$id = $_GET['id'];
$unixtime = $_GET['unixtime'];
$sign = $_GET['sign'];

$mysign = md5($id . $unixtime . SIGN_KEY);

// if ($sign != $mysign) {
//     echo json_encode(array('status' => 2, 'msg' => iconv('GB2312', 'UTF-8', '签名错误')));
//     exit;
// }

$sql = "select top 1 type, newstime from hy_zhaostnews where id = {$id}";
$ret = queryByStore($sql);

if (!$ret) {
    echo json_encode(array('status' => 2, 'msg' => iconv('GB2312', 'UTF-8', '不存在生成的内容')));
    exit;
}

$type = $ret[0]['type'];
$newstime = $ret[0]['newstime'];

$active_index = '';
$active_new_articles = '';
$active_game_evaluation = '';
$active_game_data = '';
$active_player_att = '';

// 更新首页
{
    $active_index = 'active';

    $toplist = array();
    $topsort = array();

    $gameret = curlGet(GAMEURL . "?sign=" . md5(KEY . time()) . "&unixtime=" . time());
    $verret = curlGet(VERURL . "?sign=" . md5(KEY . time()) . "&unixtime=" . time());

    if ($gameret == "1" && $verret == "1") {
        syncSort();

        $templist = array();

        for ($i = 0; $i < count($topsort); $i++) {
            for ($j = 0; $j < count($toplist); $j++) {
                if ((int) $toplist[$j]['GameID'] == (int) $topsort[$i]) {
                    $templist[$i] = $toplist[$j];
                    continue;
                }
            }
        }

        $toplist = $templist;
        $gamecontent = array_merge($toplist, $gamecontent);
        $html = createIndexHtml($gamecontent, $vercontent);

        savefile($html, FILE);
    } else {
        echo json_encode(array('status' => 2, 'msg' => iconv('GB2312', 'UTF-8', '读取列表失败')));
        exit;
    }
}

if ($type != 0) {
    // 查询相邻的上一条新闻
    $prev_sql = "select top 1 id from hy_zhaostnews where id > {$id} and newstime >= '{$newstime}' and type = {$type} order by newstime desc, id desc";
    $prev_news = queryByStore($prev_sql);

    switch ($type) {
        case 1:
            $active_new_articles = 'active';
            $position = '最新资讯'; // new_articles_id.html

            if ($prev_news) {
                $prev_id = $prev_news[0]['id'];
                $html = createDetails($prev_id, $position, NEW_ARTICLES);
                savefile($html, NEW_ARTICLES . "_{$prev_id}.html");
            }

            $html = createDetails($id, $position, NEW_ARTICLES);
            savefile($html, NEW_ARTICLES . "_{$id}.html");
            break;

        case 2:
            $active_game_evaluation = 'active';
            $position = '游戏测评'; // game_evaluation_id.html

            if ($prev_news) {
                $prev_id = $prev_news[0]['id'];
                $html = createDetails($prev_id, $position, GAME_EVALUATION);
                savefile($html, GAME_EVALUATION . "_{$prev_id}.html");
            }

            $html = createDetails($id, $position, GAME_EVALUATION);
            savefile($html, GAME_EVALUATION . "_{$id}.html");
            break;

        case 3:
            $active_game_data = 'active';
            $position = '游戏资料'; // game_data_id.html

            if ($prev_news) {
                $prev_id = $prev_news[0]['id'];
                $html = createDetails($prev_id, $position, GAME_DATA);
                savefile($html, GAME_DATA . "_{$prev_id}.html");
            }

            $html = createDetails($id, $position, GAME_DATA);
            savefile($html, GAME_DATA . "_{$id}.html");
            break;

        case 4:
            $active_player_att = 'active';
            $position = '玩家关注'; // player_att_id.html

            if ($prev_news) {
                $prev_id = $prev_news[0]['id'];
                $html = createDetails($prev_id, $position, PLAYER_ATT);
                savefile($html, PLAYER_ATT . "_{$prev_id}.html");
            }

            $html = createDetails($id, $position, PLAYER_ATT);
            savefile($html, PLAYER_ATT . "_{$id}.html");
            break;
        
        default:
            echo json_encode(array('status' => 2, 'msg' => iconv('GB2312', 'UTF-8', '找不到指定类型')));
            exit;
    }
}

echo json_encode(array('status' => 1, 'msg' => 'success'));
exit;
