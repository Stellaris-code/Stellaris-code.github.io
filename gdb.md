# Fiche d'utilisation de GDB
---

### Éxécuter un programme sous GDB :
```sh
$ gdb programme
  (gdb) run
```

### Quitter un programme sous GDB :
```sh
  (gdb) quit
```
### Afficher le code assembleur exécuté :
```sh
  (gdb) layout asm
```
![Imgur](https://imgur.com/kRFfpxi.png)
### Passer en syntaxe Intel :
```sh
  (gdb) set disassembly-flavor intel
```

### Afficher l'adresse d'une fonction :
```sh
  (gdb) print &fonction
```

### Afficher le code d'une fonction :
```sh
  (gdb) disass fonction
```
![Imgur](https://imgur.com/wQPEHjE.png)
### Ajouter un point d'arrêt à une addresse :
```sh
  (gdb) b *adresse
```

### Ajouter un point d'arrêt à une fonction :
```sh
  (gdb) b fonction
```
### Reprendre l'exécution :
```sh
  (gdb) continue
```

### Afficher le code au niveau du pointeur d'instruction :
>"n" représente le nombre d'instructions à afficher
```sh
  (gdb) x/ni $pc 
```
![Imgur](https://imgur.com/0LK7CCR.png)
### Avancer d'une instruction :
```sh
  (gdb) si 
```
### Avancer d'une instruction, en 'sautant' les appels de fonction :
```sh
  (gdb) ni 
```
### Afficher la valeur d'un registre :
```sh
  (gdb) print $registre
```
### Afficher la valeur d'une adresse mémoire :
```sh
  (gdb) print addresse
```
### Afficher la pile d'appels de fonction :
```sh
  (gdb) backtrace
```
