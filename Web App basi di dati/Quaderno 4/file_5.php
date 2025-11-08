<!DOCTYPE html>
<html>
<head>
<title>Inserimento nuova valutazione</title>
</head>

<body>
<h3> Inserimento nuova valutazione</h3>
 
<form method="get" action="file_6.php">
    <table>
        <tr>
            <td>Codice Fiscale:</td>
        </tr>
        <tr>
            <td><select name="CodFisc">
            <option value="0">Selezione codice fiscale:</option>
            <?php

            $con = mysqli_connect('localhost','root','','QUADERNO4');

            if (mysqli_connect_errno())
            {
            echo "Failed to connect to MySQL: " . mysqli_connect_error();
            }

            mysqli_set_charset($con, 'utf8mb4');    
            
            $sql=" SELECT CodFisc
                   FROM UTENTE";

            $result = mysqli_query($con,$sql);

            if( !$result )
            die('Query error: ' . mysqli_error($con));
            
            if( mysqli_num_rows($result) > 0 ){
                    while($row = mysqli_fetch_array($result)) {
                        $fiscal_code = $row["CodFisc"];
                        echo "<option value='$fiscal_code'>$fiscal_code</option>";
                    }
                }
            ?>
            </select>
            </td>
        </tr>
        <tr>
            <td>Codice contenuto:</td>
        </tr>
        <tr>
            <td><select name="CodContenuto">
            <option value="0">Scegli il codice del contenuto multimediale:</option>
                <?php
                $con = mysqli_connect('localhost','root','','QUADERNO4');

                if (mysqli_connect_errno())
                {
                echo "Failed to connect to MySQL: " . mysqli_connect_error();
                }
    
                mysqli_set_charset($con, 'utf8mb4');    
                
                $sql=" SELECT CodContenuto
                       FROM CONTENUTO_MULTIMEDIALE";
    
                $result = mysqli_query($con,$sql);
    
                if( !$result )
                die('Query error: ' . mysqli_error($con));
                
                if( mysqli_num_rows($result) > 0 ){
                        while($row = mysqli_fetch_array($result)) {
                            $content_code = $row["CodContenuto"];
                            echo "<option value='$content_code'>$content_code</option>";
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
