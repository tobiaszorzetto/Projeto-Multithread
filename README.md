# Solução problema 'river crossing'
## Estrutura das pastas

~~~
├── README.md <- explicação do programa
│
├── include    <- arquivos header
│
└── src        <- arquivos .c & makefile
~~~

## Descrição do Problema
O código soluciona uma versão generalizada do problema 'river crossing' descrito no livro  [The Little Book of Semaphores](https://greenteapress.com/wp/semaphores/) de Allen B. O algoritmo desenvolvido permite variar: 
- o tamanho do barco
- a quantidade de grupos distintos
- a proporção mínima que cada grupo aceita(obs: utiliza-se o piso do número dividido pela proporção ex: barco = 5 & proporção = 0.5 => grupo aceita entrar no barco )

## Como Variar os Parametros

