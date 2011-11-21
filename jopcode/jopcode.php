<?php

include_once("opcodes.php");

$content = file($argv[1]);
$code = '';

foreach($content as $line) {
  
  $line = preg_replace("'\s+'", " ",  $line);
  $line = trim($line);

  if($line == "")
    continue;
  
  if($line[0] == ';')
    continue;

  if($line[0] == "\n")
    continue;

  $data = explode(" ", $line);
  
  $mnemonic = $data[0];
  $args = '';
  $found = 0;

  foreach($opcodes as $opc) {
    if($opc[0] == $mnemonic) {
      for($i = 0; $i < $opc[2]; $i++) {
	$args .= $data[$i+1].", ";
      }

      $args = str_replace("\n", "", $args);
      $code .= sprintf("    0x%x, %s // %s\n", $opc[1], $args, $line);

      $found = 1;

    }
  }

  if(!$found) {
    $code .= sprintf("    invalid mnemonic %s, // %s\n", $mnemonic, $line);
  }

}

echo "u1 opc[] = {\n";
echo $code;
echo "};\n";
