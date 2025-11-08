<!DOCTYPE html>
<html>
<head>
<title>Inserimento di un nuovo chef e/o di una nuova apparizione</title>
</head>

<body>
<h3>Inserimento di un nuovo chef e/o di una nuova apparizione</h3>
 
<form method="get" action="file_4.php">
    <table>
        <tr>
            <td>Codice contenuto:</td>
        </tr>
        <tr>
            <td><select name="CodContenuto">
            <option value="0">Scegli il titolo del programma tv:</option>
                <?php
                $con = mysqli_connect('localhost','root','','QUADERNO3');

                if (mysqli_connect_errno())
                {
                echo "Failed to connect to MySQL: " . mysqli_connect_error();
                }
    
                mysqli_set_charset($con, 'utf8mb4');    
                
                $sql=" SELECT Titolo
                       FROM ProgrammaTV";
    
                $result = mysqli_query($con,$sql);
    
                if( !$result )
                die('Query error: ' . mysqli_error($con));
                
                if( mysqli_num_rows($result) > 0 ){
                        while($row = mysqli_fetch_array($result)) {
                            $program_code = $row["CodProgramma"];
                            echo "<option value='$program_code'>$program_code</option>";
                        }
                    }
                ?>
            </td>
        </tr>
        <tr>
            <td>Data:</td>
        </tr>
        <tr>
            <td><input type="date" name="Data" size="20"></td>
        </tr>
        <tr>
            <td>Valutazione:</td>
        </tr>
        <tr>
            <td><input type="text" name="Valutazione" size="20"></td>
        </tr>
    </table>

 <p> <input type="submit" value="Inserisci">
 </form>
 <h4><a href="Homepage.html">Ritorna alla Home</a></h4>
 </body>
 </html>