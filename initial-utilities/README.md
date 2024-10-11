
# Unix Utilities

**Antes de Começar:** Leia esse [tutorial](http://pages.cs.wisc.edu/~remzi/OSTEP/lab-tutorial.pdf); ele contém algumas informações úteis para programação em c.

Neste projeto, você irá desenvolver uma versão simplificada dos comandos UNIX **cat**, **grep**, **zip** e **unzip**. Para não haver confusão, utilize os nomes **wcat**, **wgrep**, **wzip** e **wunzip**, respectivamente.

Objetivos:
* Se (re)familiarizar com a linguagem de programação c;
* Se (re)familiarizar com a utilização de um shell / terminal / linha de comando UNIX;
* Aprender (como efeito colateral) como utilizar um editor de código, como o visual studio code;
* Aprender um pouco sobre como os comandos UNIX são implementados.

Ainda que este projeto foque em escrever programas simples em C, você pode observar, a partir da listagem acima, que mesmo essa tarefa relativamente simples requer um conjunto de outros conhecimentos, incluindo uma ideia básica do que é um shell e como utilizar a linha de comando em sistemas baseados em UNIX, como o Linux e o macOS, como utilizar um editor de código como o visual studio code e, obviamnete, uma compreensão básica de progrtamação em c. Se você ainda **não tem** essas habilidades, vai precisar correr atrás.

Resumo do que deve ser entregue:
* Os arquivos .c dos comando que você desenvolveu: **wcat.c**, **wgrep.c**, **wzip.c**, and **wunzip.c**.
* Todos os arquivos devem compilar sem erros mesmo utilizando as flags **-Wall** e **-Werror**.
* Todos os arquivos devem passar em todos os testes fornecidos. Cada teste que falhar irá representar uma redução de 1/N na nota do projeto, onde N é o número de testes fornecidos.

## wcat

O programa **wcat** é bastante simples. Ele recebe como argumento um ou mais arquivos, os quais são lidos e seu conteúdo é impresso. 
Uma utilização típica é mostrada abaixo, onde o usuártios deseja imprimir o conteúdo do arquivo main.c: 

```
prompt> ./wcat main.c
#include <stdio.h>
...
```

Como mostrado, **wcat** lê o arquivo **main.c** e imprime seu conteúdo na tela. O "**./**" antes de **wcat** é uma característica do UNIX (o "**.**" indica o diretório atual). 

Após escrever o código de **wcat.c**, você irá compilá-lo da seguinte forma:

```
prompt> gcc -o wcat wcat.c -Wall -Werror
prompt> 
```

Isso irá criar o arquivo executável **wcat**, o qual você pode executar como mostrado anteriormente. 

Você precisará aprender como utilizar algumas funções da biblioteca padrão da linguagem c (comumente chamada de **libc**) para escrever o código deste programa. Ao compilar o programa como mostrado acima, a **libc** é automaticamente linkada com o binário, permitindo que o seu código tenha acesso a um amblo conjunto de funções úteis que você pode chamar para implementar o seu programa. Leia mais sobre a **libc** [aqui](https://en.wikipedia.org/wiki/C_standard_library) e também [aqui](https://www-s.acm.illinois.edu/webmonkeys/book/c_guide/)<sup>[1](#myfootnote1)</sup>.  

Para esse projeto, é recomendada a utilização das seguintes funções para manipular arquivos: **fopen()**, **fgets()** e **fclose()**. Sempre que você precisar utilizar uma função nova, como nesse caso, a primeira coisa que você deve fazer é ler a documentação dela. Nos sistema baseados em UNIX, a melhor maneira de ler sobre determinada função é utilizar o manual, chamado de **man** pages. A primeira vista, o manual pode parecer um pouco antiquado, mas ele é útil, informativo e geralmente fácil de utilizar.

Para acessar as páginas do manual para a função **fopen()**, por exemplo, digite o seguinte comando no shell do seu sistema: 
```
prompt> man fopen
```

A partir daí, leia! Ler as páginas do manual é algo que exige prática, então por que não começar agora?

Daremos também uma visão geral aqui. A função **fopen()** "abre" um arquivo. Esse é um modo comum de iniciar o acesso a um arquivo em sistemas UNIX. A função **fopen()** retorna um ponteiro para uma struct do tipo **FILE**, o qual pode ser usado como argumento em outras funções que manipulam arquivos. 

O trecho de código abaixo ilustra uma utilização típica de **fopen()**:

```c
FILE *fp = fopen("main.c", "r");
if (fp == NULL) {
    printf("cannot open file\n");
    exit(1);
}
```

Algumas observações importantes. Primeiro, note que **fopen()** recebe dois argumentos, sendo o primeiro o *nome* do arquivo e o modo no qual o arquivo será aberto, o qual indica o que queremos fazer com o arquivo. No exemplo acima queremos abrir o arquivo "main.c" apenas para leitura (modo = "r"). Leia o manual para saber quais outras opções estão disponíveis. Segundo, note que após chamar a função **fopen()** devemos verificar se ela foi bem sucedida ou não, pois caso não tenha sido, o valor do ponteiro retornado será NULL. Diferente de outras linguagens como Java, C# e C++, não há excessões em c. Normalmente as funções indicam seu sucesso ou falha pelo valor retornado por elas. Leia o manual para mais informações.

Terceiro, note que quando o caso de erro ocorre, o programa imprime uma mensagem e termina com código de status 1. No UNIX, a tradição sugere que em caso de sucesso, o programa deve retornar 0 e, caso contrário, deve retornar um valor diferente de zero. No nosso exemplo, utilizamos 1 para indicar a falha.

Observação: existem diversas causas que podem levar a função **fopen()** a falhar. Você pode utilizar as funções **perror()** ou **strerror()** para imprimir uma mensagem informativa sobre a causa da falha. Para seber mais, leia o manual para essas funções.

Uma vez que o arquivo é aberto, existem diferentes maneira de ler seus dados. A que estamos sugerindo aqui é fazer a leitura através da função **fgets()**, a qual é utilizada para ler arquivos de texto uma linha por vez. Para imprimir o conteúdo de um arquivo, simplesmnete utilize a função **printf()**. Por exmeplo, depois de ler uma linha do arquivo com a função **fgets()** para a variável **buffer**, você pode imprimir essa linha da seguinte maneira:

```c
printf("%s", buffer);
```

Note que você não deve adicionar um caractere de nova linha (\\n) à string de formatação, pois a função **printf()** já inclui automaticamnete o caractere de nova linha.

Por fim, quando você tiver terminado de ler e imprimir todsas as linhas do arquivo, utilize a função **fclose()** para fechar o arquivo (assim indicando que você não precisa mais fazer sua leitura).

**Detalhes**

* Seu programa **wcat** deve ser implementado de forma a permitir um ou mais arquivos como argumento. Se dois ou mais arquivos forem fornecidos, **wcat** deve imprimir o conteúdo de cada um deles, um por um;
* Sempre que nenhum erro ocorrer, **wcat** deve retornar o código de status 0 (usualmente através de um return 0 na função **main()** ou chamando a função **exit(0)**;
* Se nenhum arquivo for especificado na linha de comando, **wcat** deverá simplesmente encerrar, retornando 0. Note que esse comportamento é ligeiramente diferente daquele apresentado pelo programa **cat** do UNIX (verifique !);
* Se a chamada para **fopen()** falhar, **wcat** deverá imprimir exatamnete a seguinte mensagem, seguida por uma nova linha: "wcat: cannot open file". Após imprimir a mensagem, o programa deve encerrar com código de status 1. Se múltiplos arquivos forem especificados na linha de comando, os arquivos devem ser impressos em ordem até a última linha do último arquivo ou até que uma falha de abertura de arquivo ocorra (caso onde **wcat** imprime a mensagem de erro e encerra, como explicado anteriormente). 


## wgrep

O segundo programa que você irá desenvolver é chamado de **wgrep** e é uma variação simplificada do comando UNIX **grep**. Esse programa lê um arquivo linha por linha buscando por um padrão fornecido pelo usuário. Somente as linhas que contiverem o padrão serão impressas. 

Esse é um exemplo de como o usuário poderia utilizar o **wgrep** para imprimir linhas que contenham a palavra **"foo"** no arquivo **bar.txt**:

```
prompt> ./wgrep foo bar.txt
this line has foo in it
so does this foolish line; do you see where?
even this line, which has barfood in it, will be printed.
```

**Detalhes**

* Os argumentos de linha de comando para o programa **wgrep** são um termo de busca e zero ou mais arquivos, onde o termo será buscado (ou seja, é possível buscar em mais de um arquivo). O processamento será feito linha a linha 
  para cada cada arquivo passado como argumento via linha de comando, onde a linha será impressa somente se ela contiver o termo de busca;
* A comparação do termo de busca com cada linha deve ser feita de forma a considerar diferença entre maiúsculas e minúsculas (case sensitive). Assim, ao buscar por **foo**, linhas contendo **Foo** não resultarão em uma combinação;
* Linhas podem ser arbitrariamente longas (ou seja, você pode encontrar caracteres muitos caracteres antes de encontrar uma nova linha, \\n). O **wgrep** deve funcionar como esperado mesmo na presença de linhas muito longas. Por 
  esse motivo sugiro dar uma olhada na função **getline()** da *libc* (ao invés de usar **fgets()**);
* Se nenhum argumento de linha de comando for passado para o **wgrep**, ele deve imprimir a mensagem "wgrep: searchterm [file ...]", seguindo de uma nova linha e, em seguida, deve finalizar (chamar **exit()**) com código de 
  status 1;
* Se o **wgrep** encontrar um arquivo que não puder ser aberto, ele deve imprimir a mensagem "wgrep: cannot open file", seguido de uma nova linha e, em seguida, finalizar (chamar **exit()**) com código de status 1;
* Em todos os outros casos, **wgrep** deve encerrar retornando o código de status 0;
* Se um termo de busca for fornecido como argumento de linha de comando, mas nenhum arquivo for especificado, o **wgrep** irá ler os dados a partir do *standard input*. Fazer isso é fácil, uma vez que o stream **stdin** já é 
  aberto automaticamente quando o programa é executado. Você pode utilizar a função **fgets()** (ou funções similares) para ler a partir do **stdin**;
* Por simplicidade, se o usuário passar uma string vazia como o argumento do termo de busca, **wgrep** pode considerar que todas as linhas têm uma correspondência ou nenhuma delas.

## wzip and wunzip

A próxima ferramenta que você irá desenvolver é, na realidade, um par de programas:

* **wzip**: realiza a compressão de um ou mais arquivos especificados como argumentos de linha de comando;
* **wunzip**: realiza a descompressão de um ou mais arquivos especificados como argumentos de linha de comando e que foram comprimidos pelo programa **wzip**. 

O tipo de compressão utilizado aqui é uma forma simplificada de um algoritmo de compressão chamado de *run-Length encoding* (*RLE*). O funcionamento do *RLE* é bastante simples: quando uma sequência de **n** caracteres iguais é encontrada em uma linha de um arquivo, essa sequência é escrita na saída padrão como o valor de **n** seguido de uma instância do caracter repetido.

Assim, se temos um arquivo com o seguinte conteúdo:
```
aaaaaaaaaabbbb
```
a ferramenta irá gerar o seguinte resultado:
```
10a4b
```

Entretanto, note que o formato exato do arquivo comprimido é bastante importante. Para cada sequência de caracteres repetidos encontrada, o **wzip** irá escrever um inteiro de 4 bytes (int) em sua representação binária, seguido do valor ASCII (1 byte) do caracter repetido. Ou seja, o arquivo comprimido será composto por **k** entradas de 5 bytes cada, sendo cada entrada contendo um inteiro de 4 bytes (representando o número de repetições do caractere) e 1 byte representando o caracter em si. 

Para escrever um número inteiro utilizando sua representação binária (não a representação ASCII do número), você deverá utilizar a função **fwrite()** da libc. Leia a página do manual sobre essa função para entender como ela deve ser utilizada. O resultado do programa **wzip** será escrito na saída padrão utilizando o stream **stdout**, que assim como o **stdin** também é aberto automaticamente quando o programa é executado. 

Observe que o uso típico do programa **wzip** irá utilizar o redirecionamento de saída para gerar um arquivo de saída comprimido. Por exemplo, para comprimir o arquivo **file.txt** de forma a obter o arquivo comprimido **file.z**, você deve executar o programa **wzip** da seguinte forma:

```
prompt> ./wzip file.txt > file.z
```

O sinal "maior que" é utilizado para redirecionar os dados escritos na saída parão pelo programa da esquerda para o arquivo especificado do lado direito. Caso esse redirecionamento não seja feito, os dados gerados por **wzip** serão impressos na tela. Nós veremos como os redirecionamentos são implementados mais a frente no curso.

O programa **wunzip** simplesmente executa o processo contrário do **wzip**. Ele recebe como argumento um arquivo comprimido pelo **wzip**, faz a descompressão e imprime o resultado também na saída padrão. Por exemplo, para ver o conteúdo original do arquivo **file.txt** a partir do arquivo **file.z**, execute o seguinte comando:

```
prompt> ./wunzip file.z
```

O programa **wunzip** deve ler o arquivo comprimido (possivelmente utilizando a função **fread()**) e imprimir a saída descomprimida na saída padrão utilizando a função **printf()**.

**Detalhes**

* Para a correta invocação dos programas **wzip** e **wunzip**, é necessário passar um ou mais arquivos via linha de comando para serem comprimidos;
* Se nenhum arquivo for fornecido, o programa deve imprimir a mensagem  "wzip: file1 [file2 ...]" ou "wunzip: file1 [file2 ...]" (seguida de nova linha) e encerrar com código de status 1;
* O formato do arquivo comprimido deve corresponder exatamente aquele descrito neste documento (inteiro de 4 bytes seguido por um character para cada sequência de caracteres repetidos).
* Note que se múltiplos arquivos forem passados como argumentos para **wzip**, eles serão comprimidos em uma única saída. Por esse motivo, quando o arquivo comprimido por descomprimido por **wunzip**, o resultado será fluxo único de caracteres (ou seja, a informação de que originalmente múltiplos arquivos fonte deram origem ao arquivo comprimido será perdida). O mesmo pode ser dito sobre o **wunzip**. 




