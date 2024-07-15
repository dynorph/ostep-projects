
# Projects for an Operating Systems Class

Esse repositório contém um conjunto de projetos que podem ser utilizados em disciplinas de sistemas operacionais ofertadas em cursos de graduação em computação (ou áreas afins). Na realidade, esse repositório é um fork de https://github.com/remzi-arpacidusseau/ostep-projects.git. No repositório original, os projetos que lidam com o Xv6 utilizam sua versão para a arquitetura x86, a qual não é mais suportada. Dessa forma, a ideia deste repositório é portar os projetos para operarem com a versão do sistema Xv6 para arquitetura RISC-V e traduzir a descrição dos projetos, de forma a facilitar o aprendizado para alunos que não dominam o idioma inglês.

Além dos projetos em si, o repositório também contém um framework para executar tests automatizados. Eventualmente, todos os projetos terão um conjunto de `testes` disponível. O framework de testes pode ser encontrado [aqui](https://github.com/igorcompuff/ostep-projects/tree/master/tester). Cada projeto possui um script que pode ser utilizado para executar os seus testes automatizados.

Por exmeplo, no projeto initial utilities, o programa `wcat` pode ser testado executando-se o script `test-wcat.sh`. Isso pode ser feito através dos seguintes comandos:
```sh
prompt> git clone https://github.com/remzi-arpacidusseau/ostep-projects
prompt> cd ostep-projects/initial-utilities/wcat
prompt> emacs -nw wcat.c
prompt> gcc -o wcat wcat.c -Wall 
prompt> ./test-wcat.sh
test 1: passed
test 2: passed
test 3: passed
test 4: passed
test 5: passed
test 6: passed
test 7: passed
prompt> 
```
É claro que a sequência acima supõe que: a) você utiliza o editor `emacs` para escrever o código de wcat.c, (b) Seu código é escrito todo de uma vez (incrível) e (c) seu código compila e executa perfeitamente (parabéns!). Mesmo para projetos simples, é provável que ciclo compilação/execução/depuração seja executado por alguma iterações.

## Projetos C/Linux

### Initial Projects

Esse projeto tem o objetivo de te aquecer na programação C/Linux
These projects are meant to get you warmed up with programming in the C/UNIX
environment. None are meant to be particularly hard, but should be enough so
that you can get more comfortable programming. 

Realize the best thing you can do to learn to program in any environment is to
program **a lot**. These small projects are only the beginning of that
journey; you'll have to do more on your own to truly become proficient.

* [Unix Utilities](initial-utilities) (cat, grep, zip/unzip)
* Sort (text-based)
* Sort (binary)
* [Reverse](initial-reverse) (very simple reverse program)

### Processes and Scheduling

* [Shell](processes-shell)

### Virtual Memory

* Memory Allocator

### Concurrency

* [Web Server](concurrency-webserver)
* [Parallel Zip](concurrency-pzip)
* [MapReduce](concurrency-mapreduce)
* Web Crawler

### File Systems

* [File System Checker](filesystems-checker)

### Distributed Systems


## Kernel Hacking Projects (xv6)

These projects all are to be done inside the
[xv6](https://pdos.csail.mit.edu/6.828/2017/xv6.html) kernel based on an early
version of Unix and developed at MIT. Unlike the C/Linux projects, these give
you direct experience inside a real, working operating system (albeit a simple
one).

Read the [install notes](INSTALL-xv6.md) to see how to download the latest xv6 
and install the tools you'll need.

### Initial Projects

* [Intro To xv6](initial-xv6)

### Processes and Scheduling

* [Scheduling (Lottery)](scheduling-xv6-lottery)

### Virtual Memory

* [Virtual Memory (Null Pointer and Read-Only Regions)](vm-xv6-intro)

### Concurrency

* [Kernel Threads (Basic Implementation)](concurrency-xv6-threads)

### File Systems



