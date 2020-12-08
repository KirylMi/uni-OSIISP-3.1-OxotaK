<?php
$dbh = new PDO('pgsql:dbname=myDb;host=172.20.0.2', 'postgres', 'test');
$stmt = $dbh->prepare("SELECT * FROM \"oxotaK\".drinks;");
$stmt->execute();
while ($result=$stmt->fetch(PDO::FETCH_ASSOC)){
    ob_start();
    fpassthru($result['photo']);
    $dat= ob_get_contents();
    ob_end_clean();
    $dat= "data:image/*;base64," . base64_encode($dat);
    echo "<img src='".$dat."'";
    var_dump($result['photo']); echo "</br>";
}
//var_dump ($stmt->fetch(PDO::FETCH_ASSOC));
echo "Welcome, welcome";
?>
