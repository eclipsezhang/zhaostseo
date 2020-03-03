<?php

include_once 'common.inc';

// ��ǩ
$id = $_GET['id'];
$unixtime = $_GET['unixtime'];
$sign = $_GET['sign'];

$mysign = md5($id . $unixtime . SIGN_KEY);

// if ($sign != $mysign) {
//     echo json_encode(array('status' => 2, 'msg' => iconv('GB2312', 'UTF-8', 'ǩ������')));
//     exit;
// }

$sql = "select top 1 type from hy_zhaostnews where id = {$id}";
$ret = queryByStore($sql);

if (!$ret) {
    echo json_encode(array('status' => 2, 'msg' => iconv('GB2312', 'UTF-8', '���������ɵ�����')));
    exit;
}

$type = $ret[0]['type'];

$active_index = '';
$active_new_articles = '';
$active_game_evaluation = '';
$active_game_data = '';
$active_player_att = '';

// ������ҳ
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
        echo json_encode(array('status' => 2, 'msg' => iconv('GB2312', 'UTF-8', '��ȡ�б�ʧ��')));
        exit;
    }
}

if ($type != 0) {
    switch ($type) {
        case 1:
            $active_new_articles = 'active';
            $position = '������Ѷ'; // new_articles_id.html
            $html = createDetails($id, $position, NEW_ARTICLES);
            savefile($html, NEW_ARTICLES . "_{$id}.html");
            break;

        case 2:
            $active_game_evaluation = 'active';
            $position = '��Ϸ����'; // game_evaluation_id.html
            $html = createDetails($id, $position, GAME_EVALUATION);
            savefile($html, GAME_EVALUATION . "_{$id}.html");
            break;

        case 3:
            $active_game_data = 'active';
            $position = '��Ϸ����'; // game_data_id.html
            $html = createDetails($id, $position, GAME_DATA);
            savefile($html, GAME_DATA . "_{$id}.html");
            break;

        case 4:
            $active_player_att = 'active';
            $position = '��ҹ�ע'; // player_att_id.html
            $html = createDetails($id, $position, PLAYER_ATT);
            savefile($html, PLAYER_ATT . "_{$id}.html");
            break;
        
        default:
            echo json_encode(array('status' => 2, 'msg' => iconv('GB2312', 'UTF-8', '�Ҳ���ָ������')));
            exit;
    }
}

echo json_encode(array('status' => 1, 'msg' => 'success'));
exit;
