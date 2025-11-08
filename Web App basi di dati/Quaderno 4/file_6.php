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

if(!isset($_REQUEST["CodFisc"]) or 
   !isset($_REQUEST["CodContenuto"])or
   !isset($_REQUEST["Data"])or
   !isset($_REQUEST["Valutazione"]))
   {
    echo "<div class = 'rosso'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: inserire tutti i dati richiesti</p>
    </div>";
    exit;   
   }

   $CodFisc=$_REQUEST["CodFisc"];
   $CodContenuto=$_REQUEST["CodContenuto"];
   $Data=$_REQUEST["Data"];
   $Valutazione=$_REQUEST["Valutazione"];

   if($CodFisc=="")
 echo "<div class = 'rosso'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Codice fiscale non valido</p>
    </div>";

    if($CodContenuto=="")
 echo "<div class = 'rosso'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Codice contenuto non valido</p>
    </div>";

    if($Data=="")
 echo "<div class = 'rosso'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Data non valida</p>
    </div>";

    if($Valutazione=="")
 echo "<div class = 'rosso'>
    <h2>Errore di inserimento!</h2>
    <p>Errore: Valutazione non valida</p>
    </div>";

    if($CodFisc=="" || $CodContenuto=="" || $Data=="" || $Valutazione=="")
    die();

    if(!is_numeric($Valutazione))
    {
        echo "<div class = 'rosso'>
        <h2>Errore di inserimento!</h2>
        <p>Errore: La valutazione deve essere un valore numerico</p>
        </div>";
        exit;
    }

    if($Valutazione<0 || $Valutazione>11)
    {
        echo "<div class = 'rosso'>
        <h2>Errore di inserimento!</h2>
        <p>Errore: La valutazione dev'essere un valore tra 0 e 10</p>
        </div>";
        exit;
    }

    $con = mysqli_connect('localhost','root','','QUADERNO4');

    if (mysqli_connect_errno())
    {
        echo "Failed to connect to MySQL: " . mysqli_connect_error();
    }

    mysqli_set_charset($con, 'utf8mb4');

    if(mysqli_query($con,"INSERT INTO VALUTAZIONE(CodFisc,CodContenuto,Data,Valutazione)
    VALUES('$CodFisc', '$CodContenuto', '$Data', '$Valutazione');"))
    {
        echo "<div class = 'verde'>
        <h2>Inserimento avvenuto!</h2>
        <p>Inserimento valutazione di $CodFisc per il contenuto $CodContenuto riuscito.</p>
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
 <form method="get" action="file_5.php">
 <input type="submit" value="Effettua un altro inserimento">
 </form>
 <h4><a href="Homepage.html">Ritorna alla Home</a></h4>
 </body>
 </html>
