const char webpage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no" />
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
  </head>
  <body>
  <div class="container-fluid">
     <script> 
         
      function ajaxDrive(value){
        
        $.ajax({"url": "ajaxDrive?ajaxDrive="+value});
      };
      function ajaxSter(value){
        $.ajax({"url": "ajaxSter?ajaxSter="+value});
        };
    </script>

<p>Adress of this device:</p>
<p>%MAC_ADDR%</p>
    
<div class="forw">
  <input type="range" id="forward" name="forward"
         min="0" max="100" value="50" onchange="ajaxDrive(this.value)"> 
</div>
<br/><br/><br/><hr>
<div>
    <input type="range" id="skręt" name="skret" 
         min="0" max="100" value="50"
         onchange="ajaxSter(this.value)">
  
</div>
</div>
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>       
 </body>
</html>
)rawliteral";
