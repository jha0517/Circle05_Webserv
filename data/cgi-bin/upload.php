<html>
	<body>
	<?php
			if (getenv("REQUEST_METHOD") == "POST") 
			{
				echo "POST IS HERE";
				if (getenv('UPLOAD_ERROR')=='0')
					echo("File Uploaded Successfully");
				else
					echo("Error uploading file");
			}
		?>
	</body>
</html>
