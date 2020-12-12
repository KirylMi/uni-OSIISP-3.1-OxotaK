<?
function getImage($bytes){
    $retStr = "";
    ob_start();
    fpassthru($bytes);
    $dat= ob_get_contents();
    ob_end_clean();
    $dat= "data:image/*;base64," . base64_encode($dat);
    $retStr.="<img style=\"margin:0 auto;display:block;\" src='".$dat."'/>";
    return $retStr;
    //     var_dump($result['photo']); echo "</br></br>";
}