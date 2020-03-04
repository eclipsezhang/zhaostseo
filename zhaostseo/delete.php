<?php

include_once 'common.inc';

// ��ǩ
$id = $_GET['id'];
$type = $_GET['type'];
$unixtime = $_GET['unixtime'];
$sign = $_GET['sign'];

$mysign = md5($id . $unixtime . SIGN_KEY);

// if ($sign != $mysign) {
//     echo json_encode(array('status' => 2, 'msg' => iconv('GB2312', 'UTF-8', 'ǩ������')));
//     exit;
// }

$list_id = explode(',', $id);
$list_type = explode(',', $type);

// ������ҳ
{
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

// ɾ���ļ�
{
	foreach ($list_id as $key => $id) {
		$type = $list_type[$key];

		switch ($type) {
	        case 1:
	            $file_name = NEW_ARTICLES . "_{$id}.html";
	            break;

	        case 2:
	            $file_name = GAME_EVALUATION . "_{$id}.html";
	            break;

	        case 3:
	            $file_name = GAME_DATA . "_{$id}.html";
	            break;

	        case 4:
	            $file_name = PLAYER_ATT . "_{$id}.html";
	            break;
	        
	        default:
	            echo json_encode(array('status' => 2, 'msg' => iconv('GB2312', 'UTF-8', '�Ҳ���ָ������')));
	            exit;
	    }

		if (file_exists(PATH . $file_name)) {
			unlink(PATH . $file_name);
		}
	}
}

echo json_encode(array('status' => 1, 'msg' => 'success'));
exit;
