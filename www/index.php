<?php
include_once("Functions.php");
include_once("DB.php");
$myDb = new DB;
?>
<html>

<head>
    <title>
        TITLE
    </title>
    <style>
        <?php include_once("imagesFlex.css"); ?>
    </style>
</head>

<body>
    <?php
    $drinksStmt = $myDb->getAllDrinks();
    $marks = $myDb->getAllMarks()->fetchAll();
    $currentMark = 0;
    $currentSum = 0;
    $amountOfMarks = 0;

    echo "<div class =flex-container>";

    while ($result = $drinksStmt->fetch()){
        
        echo "<div>";
        echo "<article class = centerised>".$result['name']."</article>";
        echo getImage($result['photo']);

        foreach($marks as $key=>$value){
            if ($value['drinks_id']==$result['id']){
                $currentSum+=$value['mark'];
                $amountOfMarks++;
                unset($marks[$key]);
            }
        }

        echo "<article class=centerised>";
        if ($currentSum==0){
            echo "TBRanked";
        }
        else{
            $currentMark = $currentSum/$amountOfMarks;
            echo $currentMark."/5 (".$amountOfMarks.") reviews";
        }
        echo "</article>";
        echo "</div>";
        
        $currentMark = 0;
        $currentSum = 0;
        $amountOfMarks = 0;
    }
    echo "</div>";
    // $dbh = new PDO('pgsql:dbname=myDb;host=172.20.0.2', 'postgres', 'test');
    // $stmt = $dbh->prepare("SELECT * FROM \"oxotaK\".drinks;");
    // $marks = $dbh->prepare("SELECT * FROM \"oxotaK\".reviews");
    // $marks->execute();
    // $stmt->execute();
    // $resultMarks = $marks->fetchAll();
    
    // while ($result=$stmt->fetch(PDO::FETCH_ASSOC)){
    //     ob_start();
    //     fpassthru($result['photo']);
    //     $dat= ob_get_contents();
    //     ob_end_clean();
    //     $dat= "data:image/*;base64," . base64_encode($dat);
    //     var_dump($result);
    //     echo "<img src='".$dat."'";
    //     var_dump($result['photo']); echo "</br></br>";

    // }
    // var_dump($resultMarks);
    // //var_dump ($stmt->fetch(PDO::FETCH_ASSOC));
    // echo "Welcome, welcome";
    ?>
</body>

</html>