<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="content-type" content="text/html; charset=UTF-8">
        <title>Hello!</title>
    </head>
    <body>
            This is Ratatouille Server!<br><br>
            <a href="/fruits">Test GET images</a>,<br>
            <br> Test Post File <br>
            <form action="/query.php">
              <label for="fname">Enter Your Name:</label>
              <input type="text" id="fname" name="fname"><br><br>

              <!-- <label for="lname">Last name:</label>
              <input type="text" id="lname" name="lname"><br><br> -->
              <input type="submit" value="Submit">
			<?php
				echo "Welcome, ";
				echo $_GET["fname"];
				echo "!";
				?>
			</form><br><br>
            <form action="upload.php" method="post" enctype="multipart/form-data">
            <input type="file" name="file"/>
            <input type="submit" value="Upload" />
            </form>

    </body>
</html>
