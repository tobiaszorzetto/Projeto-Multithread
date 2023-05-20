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
- a proporção mínima que cada grupo aceita 

(obs: utiliza-se o piso do número dividido pela proporção ex: barco = 5 & proporção = 0.5 => grupo aceita entrar no barco com 2 outros do mesmo tipo que sí)

## Como Variar os Parametros
Para configurar o tamanho do barco basta alterar o macro BOAT_SIZE e para configurar a quantidade de grupos basta alterar o macro NUM_GROUPS, ambos localizados no arquivo main.c
Porém, é importante mencionar que, caso a quantidade de grupos seja alterada, deve-se informar as proporções adequadas para cada grupo listando as onde há ... na função abaixo

~~~
int main() {
	init_State(BOAT_SIZE,NUM_GROUPS,...);
    (...)
}
~~~

Para definir que pessoas estão tentando atravessar o rio, basta alterar o vetor abaixo.
Cada número representa o tipo de uma pessoa tentando cruzar o rio, tal que pessoas[i] = tipo da pessoa i
~~~
int main(){
    (...)
    int pessoas[20] = {0,1,1,0,1,0,0,0,0,1,1,0,1,0,1,1,0,1,0,1};
    (...)
}
~~~

## Executando o algorítmo
Para rodar o codigo basta utilizar compilar o programa com o comando(obs: é necessario criar um pasta obj dentro da pasta src para que isto funcione):
~~~
    make main
~~~
e roda-lo com o comando:
~~~
    ./main
~~~

## Requisitos

É previsto que o programa seja rodado em um ambiente linux. Para compilar o código é necessario instalar a biblioteca 'ncurses'