### Afficher le code assembleur d'un exécutable :
```sh
$ objdump -Cd -M intel programme
```

### Afficher les strings d'un exécutable :
```sh
  (gdb) strings programme
```

### Afficher la section .data (variables) d'un exécutable :
```sh
  (gdb) readelf -x .data programme
```
### Afficher la section .rodata (chaînes de caractères) d'un exécutable :
```sh
  (gdb) readelf -x .rodata programme
```
