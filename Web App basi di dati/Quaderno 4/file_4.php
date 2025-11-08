<html>
<head>
<title>Inserimento nuovo utente</title>
</head>
<style>
.rosso { color:white;
 background-color:#f44336!important;
 font-family:'Times New Roland';
}
</style>
<style>
.verde { color:white;
 background-color:#4CAF50!important;
 font-family:'Times New Roland';
}
</style>
<body>

<?php

 /* CONTROLLO E LETTURA PARAMETRI*/

 if( !isset($_REQUEST["CodFisc"]) or
     !isset($_REQUEST["Nome"]) or
     !isset($_REQUEST["Cognome"]) or
     !isset($_REQUEST["AnnoDiNascita"])) {
    echo "<div class = 'rosso'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: inserire tutti i dati richiesti</p>
    </div>";
    exit;
 }

 $CodFisc=$_REQUEST["CodFisc"];
 $Nome=$_REQUEST["Nome"];
 $Cognome=$_REQUEST["Cognome"];
 $AnnoDiNascita=$_REQUEST["AnnoDiNascita"];

 if($CodFisc=="")
 echo "<div class = 'rosso'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Codice fiscale non valido</p>
    </div>";
    
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

    if($AnnoDiNascita=="")
 echo "<div class = 'rosso'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Anno di nascita non valido</p>
    </div>";

 if($CodFisc=="" || $Nome=="" || $Cognome=="" || $AnnoDiNascita=="")
 die();

    if(!is_numeric($AnnoDiNascita))
    {
        echo "<div class = 'rosso'>
        <h2>Errore di inserimento!</h2>
        <p>Errore: La data deve essere un valore numerico</p>
        </div>";
        exit;
    }

 /* CONNESSIONE AL DB*/
 $con = mysqli_connect('localhost','root','','QUADERNO4');

 if (mysqli_connect_errno())
 {
 echo "Failed to connect to MySQL: " . mysqli_connect_error();
 }

 mysqli_set_charset($con, 'utf8mb4');

 if(mysqli_query($con,"INSERT INTO UTENTE(CodFisc,Nome,Cognome,AnnoDiNascita)
 VALUES('$CodFisc', '$Nome', '$Cognome', '$AnnoDiNascita');"))
 {
 echo "<div class = 'verde'>
 <h2>Inserimento avvenuto!</h2>
 <p>L'utente $CodFisc è stato inserito nel database.</p>
 </div>";
 }
 else
 {
 echo "<div class = 'rosso'>
 <h2>Errore di inserimento!</h2>
 <p>Errore: Non è stato possibile inserire i dati
 perchè si è verificato un errore:</p>
 </div>";
 echo mysqli_error($con);
 exit;
 }
 mysqli_close($con);
 ?>

 </br>
 <form method="get" action="file_3.php">
 <input type="submit" value="Effettua un altro inserimento">
 </form>
 <h4><a href="Homepage.html">Ritorna alla Home</a></h4>
 </body>
 </html>