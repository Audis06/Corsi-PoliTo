<!DOCTYPE html>
<html> 
<body>

<h1>Interrogazione del database</h1>  

<form action="file_2.php">
    <select id="fiscal_code" name="fiscal_code" width="60">
    <option value=''>Seleziona un utente</option>
    <?php

        /* Establish DB connection */
        $conn = mysqli_connect("localhost","root", "", "QUADERNO3");


        if (mysqli_connect_errno()) {
            echo "Failed to connect to MySQL: " . mysqli_connect_error ();
        }
        

        /* Query construction */
        $query = "SELECT CodiceFiscaleChef FROM CHEF";
        
        /* Query execution */
        $result = mysqli_query ( $conn, $query );
        if (!$result){
            die ( 'Query error: ' . mysqli_error ( $conn ) );
        }

        /* Check if course found */
        if (mysqli_num_rows ( $result ) > 0) {
            while($row = mysqli_fetch_array($result)) {
                $fiscal_code = $row["CodiceFiscaleChef"];
                echo "<option value='$fiscal_code'>$fiscal_code</option>";
            }
        }

    ?>
    </select>
    <br>
    <br>
    <input type="submit" value="Cerca">
</form> 
<h4><a href="Homepage.html">Ritorna alla Home</a></h4>
</body>
</html>