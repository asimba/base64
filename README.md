# base64
Simple C base64 code.

_**Build instructions:**_  
```
tcc b64enc.c -o b64enc.exe -m32 -Wl,-subsystem=console
tcc b64dec.c -o b64dec.exe -m32 -Wl,-subsystem=console
```  
_**Usage:**_  
```
b64enc <source file> <destination file>
b64dec <source file> <destination file>
```  
