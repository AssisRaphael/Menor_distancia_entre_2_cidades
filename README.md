# Menor_distancia_entre_2_cidades

Dadas N cidades e as distâncias entre elas, este programa retorna o total de quilômetros do menor percurso entre duas dessas cidades.

A entrada fornecida deve ser um arquivo texto com o seguinte formato:

     Número de estradas (arestas)
     CidadeX CidadeY Distância
     ...
     CidadeOrigem CidadeDestino
O nome do arquivo é solicitado pelo programa.

Exemplo:

Dadas as cidades A, B, C, D e E, cujas distâncias (em Km) estão na tabela abaixo, o arquivo de entrada correspondente será:

![Tabela](https://sites.google.com/site/nataliacefetmg/distancias.png)
~~~c
10
A B 18
A C 119
A D 152
A E 133
B C 12
B D 150
B E 200
C D 17
C E 120
D E 199
A D
~~~

As cidades e as distâncias de cada viagem (em qualquer um dos sentidos) também podem ser representadas por um grafo (entre cada par de cidades há uma aresta cujo custo é a distância).

![Grafo](https://sites.google.com/site/nataliacefetmg/grafo.png)

Saída:
~~~c
Digite o nome do arquivo de entrada: teste.txt
Menor percurso: A B C D
Distancia total: 47 Km
~~~
