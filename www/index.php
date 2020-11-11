<?php
$dbh = new PDO('pgsql:dbname=myDb;host=172.20.0.2', 'postgres', 'test');
$stmt = $dbh->prepare("SELECT * FROM public.users;");
$stmt->execute();
while ($result=$stmt->fetch(PDO::FETCH_ASSOC)){
    var_dump($result); echo "</br>";
}
//var_dump ($stmt->fetch(PDO::FETCH_ASSOC));
echo "Welcome, welcome";
?>
