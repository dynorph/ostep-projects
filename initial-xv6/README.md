
# Intro To Kernel Hacking

Para compreender melhor o funcionamento de um sistema operacional, você também irá desenvolver alguns projetos dentro de um sistema operacional real. O kernel que iremos utilizar, chamado de [Xv6](https://github.com/mit-pdos/xv6-public) e desenvolvido no MIT, é baseado no Unix e foi originalmente projetado para a arquitetura x86, tendo sido portado para a arquitteura RISC-v (esta é a única versáo suportada atualmente). Uma vez que o Xv6 é um kernel reduzido e seu código-fonte é de compreensão relativamente fácil, podemos utilizá-lo para desenvolver projetos simples como parte do curso de Sistemas Operacionais.

O nosso primeiro projeto no Xv6 é um aquecimento e, portanto, não é muito trabalhoso. O objetivo do projeto é simples: incluir uma nova chamada de sistema no RISC-V. Essa nova chamada de sistema, **getreadcount()**, simplesmente retorna quantas vezes a chamada de sistema **read()** foi executada desde o último boot.

## Background

Para começar, assista [este vídeo](https://youtu.be/SYRUMY9jqV4) onde eu falo sobre como o xv6 implementa o tratamento de chamadas de sistema e também explico como o projeto deve ser executado. Além disso, eu também estou disponibilizando dois conjuntos de slides que você pode utilizar para obter mais informações sobre o xv6: [Tratamento de Traps](https://cefetrjbr-my.sharepoint.com/:b:/g/personal/11429539712_cefet-rj_br/ESKP0py-yjhIiNacSrDUT5YBNa3CcJ-NBGOF9NjgXDg9BQ?e=5W34MH) e [Gerenciamento de Memória](https://cefetrjbr-my.sharepoint.com/:b:/g/personal/11429539712_cefet-rj_br/Ecpo8VQOQE1IiAQPHP3jP-EBTGFzjbtJbSAb6MpVXIrrfg?e=uL3v0x). Mais informações sobre o xv6, incluindo o ótivo livro escrito pelo pessoal do MIT que desenvolveu o xv6 estão disponíveis [aqui](https://pdos.csail.mit.edu/6.828/2023/xv6.html).


## A System Call

Sua nova system call deve ter o seguinte valor de retorno e parâmetros: 

```c
int getreadcount(void)
```

A system call retorna o valor de um contador (possivelmente chamado de **readcount** ou algo do tipo) o qual é incrementado toda vez que qualquer processo executa a chamada de sistema **read()**. Simples assim!

## Tips

Antes de iniciar o projeto, assista [este vídeo](https://youtu.be/SYRUMY9jqV4). Ele contém um passo a passo bem detalhado com tudo que você precisa para realizar o projeto.

Uma boa maneira de proceder com a inclusão de uma funcionalidade em uma grande base de código é encontrar alguma outra funcionalidade similar aquele que você quer incluir e cuidadosamente copiar essa funionalidade e modificá-la de forma a atender aos requisitos da nova funcionalidade que você quer incluir. No nosso contexto, você deve encontrar a implementação de alguma outra system call, como por exemplo **getpid()** (ou qualquer outra system call simples). Em seguida, copie essa system call e a modifique até você alcançar seu objetivo.

A maior parte do seu tempo gasto no projeto será destinada a ler e compreender o código do xv6. Para esse projeto, você não deve adicionar muitas linhas de código.

A utilização do gdb (the debugger) pode ser útil na compreensão do código, através de traces de código, e será util também em projetos futuros. Se familiarize com essa poderosa ferramenta.
tool!

# Executando Testes

Se você está utilizando a máquina virtual fornecida no curso, entyão seu diretório de usuário deve conter os seguintes diretórios:

```sh
aluno@Ubuntu-OS:~$ ls SO_Projetos
ostep-projects  xv6-public  xv6-riscv
```
O diretório ostep-projects disponível na sua máquina representa uma versão antiga e, portanto, deve ser removido. Para tanto, execute o seguinte comando:

```sh
aluno@Ubuntu-OS:~$ rm -r SO_Projetos/ostep-projects
```

Em seguida, você precisa clonar o repositório ostep-projects (dessa vez o fork que eu criei e não a versão original) utilizando o seguinte comando:

```sh
aluno@Ubuntu-OS:~$ cd SO_Projetos
aluno@Ubuntu-OS:~/SO_Projetos$ git clone https://github.com/igorcompuff/ostep-projects.git
```

Os scripts de teste requerem que o código do xv6 esteja dentro do diretório ostep-projects/src. Como esse diretório não existe, é preciso criá-lo antes. Utilize os seguintes comandos:

```sh
aluno@Ubuntu-OS:~/SO_Projetos$ mkdir ostep-projects/initial-xv6/src
aluno@Ubuntu-OS:~/SO_Projetos$ cp -r xv6-riscv/* ostep-projects/initial-xv6/src
aluno@Ubuntu-OS:~/SO_Projetos$ cd ostep-projects/initial-xv6
aluno@Ubuntu-OS:~/SO_Projetos/ostep-projects/initial-xv6$
```
Agora você pode modificar o código do xv6 em ostep-projects/initial-xv6/src para realizar o projeto. Quando terminar, basta executar o script de testes da seguinte maneira:

```sh
aluno@Ubuntu-OS:~/SO_Projetos/ostep-projects/initial-xv6$ ./test-getreadcounts.sh
```

Se você implementou tudo corretamente você verá a uma mensagem para cada teste informando que o teste passou. Caso contrário, ...

Note que o script executa o clean build do código fonte do xv6 uma vez ao ser executado utilizando o makefile chamado **Makefile.test** recém criado pelo framework de testes. Você pode utilizar esse mesmo makefile caso necessite recompilar o xv6 durante a fase de depuração do código:

```sh
aluno@Ubuntu-OS:~/SO_Projetos/ostep-projects/initial-xv6$ cd src/
aluno@Ubuntu-OS:~/SO_Projetos/ostep-projects/initial-xv6/src$ make -f Makefile.test
aluno@Ubuntu-OS:~/SO_Projetos/ostep-projects/initial-xv6/src$ make -f Makefile.test qemu
```

Você pode suprimir a recompilação do código do xv6 utilizando a flag
`-s`. Isso permite repetir os testes de forma mais rápida:

```sh
aluno@Ubuntu-OS:~/SO_Projetos/ostep-projects/initial-xv6$ ./test-getreadcounts.sh -s
```

As demais flags de teste também estão disponíveis. Acesse [readme](https://github.com/igorcompuff/ostep-projects/blob/master/README.md) para mais detalhes.
