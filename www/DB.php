<?

require_once("vendor/autoload.php");

$dotenv = Dotenv\Dotenv::createImmutable(__DIR__);
$dotenv->load();

class DB{
    public $db;
    public $scema;
    public function __construct(){
        $this->schema = getenv("Schema");
        $this->db = new PDO("pgsql:dbname=".getenv('DatabaseName').";host=".getenv('HostName'),getenv('UserName'),getenv('Password'));
        $this->db->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);
    }
    public function getAllDrinks(){
        $stmt = $this->db->prepare("SELECT * FROM \"".$this->schema."\".drinks");
        $result = $stmt->execute();
        return $stmt;
    }
    public function getAllMarks(){
        $stmt = $this->db->prepare("SELECT * FROM \"".$this->schema."\".reviews");
        $result = $stmt->execute();
        return $stmt;
    }



}


?>