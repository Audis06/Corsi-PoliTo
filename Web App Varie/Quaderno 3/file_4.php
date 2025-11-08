<!DOCTYPE html>
<html>
<style>
.rosso {color:white;
        background-color:#f44336!important;
        font-family:'Times New Roland';
        }
</style>
<style>
.verde {color:white;
        background-color:#4CAF50!important;
        font-family:'Times New Roland';
        }
</style>
<body>
<?php 
if(!isset($_REQUEST["CodiceFiscaleChef"])or 
   !isset($_REQUEST["Titolo"]) || trim($_REQUEST["Titolo"]) == ""or
   !isset($_REQUEST["NumeroPuntata"])or
   !isset($_REQUEST["Data"])or
   !isset($_REQUEST["OraInizio"])or
   !isset($_REQUEST["OraFine"]))
   {
    echo "<div class = 'rosso'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: inserire tutti i dati richiesti</p>
    </div>";
    exit;   
   }
   
$fiscal_code = $_REQUEST["CodiceFiscaleChef"];
$Titolo = $_REQUEST["Titolo"];
$NumeroPuntata = $_REQUEST["NumeroPuntata"];
$Data = $_REQUEST["Data"];
$OraInizio = $_REQUEST["OraInizio"];
$OraFine = $_REQUEST["OraFine"];

if($Titolo=="")
 echo "<div class = 'rosso'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Titolo non valido</p>
    </div>";
    if($NumeroPuntata=="")
 echo "<div class = 'rosso'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Numero puntata non valida</p>
    </div>";
    if($Data=="")
 echo "<div class = 'rosso'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Data non valida</p>
    </div>";
    if($OraInizio=="")
 echo "<div class = 'rosso'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Ora inizio non valida</p>
    </div>";
    if($OraFine=="")
 echo "<div class = 'rosso'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: OraFine non valida</p>
    </div>";


$conn = @mysqli_connect ( 'localhost', 'root', '', 'QUADERNO3' );
if (mysqli_connect_errno()) {
	echo "Failed to connect to MySQL: " . mysqli_connect_error ();
}

$fiscal_code = mysqli_real_escape_string($conn, $fiscal_code); 

$query = "SELECT CodiceFiscaleChef
            FROM CHEF
            WHERE CodiceFiscaleChef='$fiscal_code'";

/* Query execution */
$result = mysqli_query ( $conn, $query );
/*Debug*/
/*$obj = $result->fetch_object();
echo $obj->CodiceFiscaleChef;*/

if (!$result){
   die ( 'Query error: ' . mysqli_error ( $conn ) );
}

if (mysqli_num_rows ( $result ) < 1){
   $Nome = $_REQUEST["Nome"];
   $Cognome = $_REQUEST["Cognome"];
   $Nazione = $_REQUEST["Nazione"];
   $Età = $_REQUEST["Età"];
   
   if($Nome=="")
 echo "<div class = 'rosso'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Nome non valido</p>
    </div>";
    if($Cognome=="")
 echo "<div class = 'rosso'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Cognome non valido</p>
    </div>";
    if($Nazione=="")
 echo "<div class = 'rosso'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Nazione non valida</p>
    </div>";
    if($Età=="")
 echo "<div class = 'rosso'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Età non valido</p>
    </div>";

    if(!is_numeric($Età))
    {
        echo "<div class = 'rosso'>
        <h2>Errore di inserimento!</h2>
        <p>Errore: L'età deve essere un valore numerico</p>
        </div>";
        exit;
    }

    if(mysqli_query($conn,"INSERT INTO CHEF(CodiceFiscaleChef,Nome, Cognome, Nazione, Età)
    VALUES('$fiscal_code', '$Nome','$Cognome','$Nazione','$Età');"))
    {
        echo "<div class = 'verde'>
        <h2>Inserimento avvenuto!</h2>
        <p>Inserimento nuovo chef con codice fiscale $fiscal_code.</p>
        </div>";
    }
    else
    {
        echo "<div class = 'rosso'>
        <h2>Errore di inserimento!</h2>
        <p>Errore: Non è stato possibile inserire i dati
        perchè si è verificato un errore:</p>
        </div>";
        echo mysqli_error($conn);
        exit;
    }

   $Titolo=mysqli_real_escape_string($conn, $Titolo);
   $sql = "SELECT CodProgramma
            FROM PROGRAMMATV
            WHERE Titolo='$Titolo'";
/* Query execution */
   $codP = mysqli_query ( $conn, $sql );

   $CodProgramma = $codP->fetch_object();

   $Cod=mysqli_real_escape_string($conn, $CodProgramma->CodProgramma);
   mysqli_set_charset($conn, 'utf8mb4');

   if(mysqli_query($conn,"INSERT INTO APPARIZIONE(CodiceFiscaleChef,CodProgramma,NumeroPuntata,Data,OraInizio,OraFine)
    VALUES('$fiscal_code', '$Cod','$NumeroPuntata', '$Data', '$OraInizio', '$OraFine');"))
    {
        echo "<div class = 'verde'>
        <h2>Inserimento avvenuto!</h2>
        <p>Inserimento apparizione di $fiscal_code.</p>
        </div>";
    }
    else
    {
        echo "<div class = 'rosso'>
        <h2>Errore di inserimento!</h2>
        <p>Errore: Non è stato possibile inserire i dati
        perchè si è verificato un errore:</p>
        </div>";
        echo mysqli_error($conn);
        exit;
    }
    mysqli_close($conn);
}
$Titolo=mysqli_real_escape_string($conn, $Titolo);
   $sql = "SELECT CodProgramma
            FROM PROGRAMMATV
            WHERE Titolo='$Titolo'";
/* Query execution */
   $codP = mysqli_query ( $conn, $sql );

   $CodProgramma = $codP->fetch_object();

   $Cod=mysqli_real_escape_string($conn, $CodProgramma->CodProgramma);
   mysqli_set_charset($conn, 'utf8mb4');

   if(mysqli_query($conn,"INSERT INTO APPARIZIONE(CodiceFiscaleChef,CodProgramma,NumeroPuntata,Data,OraInizio,OraFine)
    VALUES('$fiscal_code', '$Cod','$NumeroPuntata', '$Data', '$OraInizio', '$OraFine');"))
    {
        echo "<div class = 'verde'>
        <h2>Inserimento avvenuto!</h2>
        <p>Inserimento apparizione di $fiscal_code.</p>
        </div>";
    }
    else
    {
        echo "<div class = 'rosso'>
        <h2>Errore di inserimento!</h2>
        <p>Errore: Non è stato possibile inserire i dati
        perchè si è verificato un errore:</p>
        </div>";
        echo mysqli_error($conn);
        exit;
    }
    mysqli_close($conn);
 ?>
 </br>
 <form method="get" action="file_3.php">
 <input type="submit" value="Effettua un altro inserimento">
 </form>
 <h4><a href="Homepage.html">Ritorna alla Home</a></h4>
 </body>
 </html>
