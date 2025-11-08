<!DOCTYPE html>
<html> 
<body>
<link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
<?php

/* Verify parameter course_code */
if (!isset($_REQUEST["fiscal_code"]) || trim($_REQUEST["fiscal_code"]) == ""){
    echo '<p> ERRORE: Codice fiscale mancante o vuoto. </p>';
    exit;
}

$fiscal_code = $_REQUEST["fiscal_code"];

/* Establish DB connection */
$conn = @mysqli_connect ( 'localhost', 'root', '', 'QUADERNO3' );

if (mysqli_connect_errno()) {
	echo "Failed to connect to MySQL: " . mysqli_connect_error ();
} 

/* String sanification for DB query */
$fiscal_code = mysqli_real_escape_string($conn, $fiscal_code); 

/* Query construction */
$query = "SELECT A.CodPodcast, I.Titolo, A.NumeroPuntata, A.DataUscita
          FROM APPARIZIONE A, INFO_PODCAST I
          WHERE A.CodPodcast = I.CodPodcast AND A.CodiceFiscalePartecipante = $fiscal_code
          AND A.CodPodcast <> (SELECT CodPodcast 
                               FROM PODCAST 
                               WHERE CodFiscalePresentatore = $fiscal_code)
          ORDER BY a.DataUscita ASC;";

/* Query execution */
$result = mysqli_query ( $conn, $query );
if (!$result){
    die ( 'Query error: ' . mysqli_error ( $conn ) );
}

/* Check if course found */
if (mysqli_num_rows ( $result ) > 0) {
    echo "<h1>Elenco valutazioni effettuate dall'utente: $fiscal_code</h1>";
    echo "<table class='w3-table-all w3-hoverable'>";

    /* Table header */
    echo "<thead><tr>";
    $i = 0;
    $field_names = [];
    while($i<mysqli_num_fields($result)) { 
        $meta=mysqli_fetch_field($result); 
        echo "<th>".$meta->name."</th>"; 
        array_push($field_names, $meta->name);
        $i++; 
    } 
    echo "</thead></tr>";
    
    /* Table content */
    while($row = mysqli_fetch_array($result)) {
        echo "<tr>";
        foreach ($field_names as $field){
            /* String sanification for HTML */
            $safe_html = htmlspecialchars($row[$field], ENT_QUOTES | ENT_SUBSTITUTE, 'utf-8');
            echo "<td>" . $safe_html . "</td>";
        }
        echo "</tr>";
    }
    echo "</table>";

} else {
    echo "<h1>Valutazione $fiscal_code non trovato.</h1>";
}


?>
</br>
<form method="get" action="file_1.php">
 <input type="submit" value="Effettua un altra ricerca">
</form>
<h4><a href="Homepage.html">Ritorna alla Home</a></h4>

</body>
</html>
