# EuroTripAv - Planejador de Roteiro Europeu

Este projeto implementa um planejador de viagens entre cidades europeias, modelando trajetos de avião e apresentando rotas otimizadas em termos de custo, tempo e distância.

## Autores
Desenvolvido por: Mariana Alves e Giovanna de Melo

## Objetivo

O sistema simula viagens entre várias cidades europeias, ajudando o usuário a encontrar o melhor roteiro, custo total de uma infraestrutura mínima de voos entre as cidades, e visualizando os dados relevantes (custo, distância, tempo).

## Funcionalidades

- **Preparação dos Dados**: Utiliza o algoritmo de Floyd-Warshall para calcular os caminhos mínimos entre todas as cidades, considerando rotas diretas e indiretas.
- **Problema do Caixeiro Viajante (TSP)**: Gera todas as combinações possíveis de rotas para visitar todas as cidades partindo da cidade inicial, retorna à origem e apresenta o itinerário de menor custo.
- **Árvore Geradora Mínima (AGM)**: Usa o algoritmo de Prim para obter o conjunto mínimo de voos que conecta todas as cidades com o menor custo.
- **Impressão de Matrizes**: Mostra tabelas detalhadas com os custos, distâncias e tempos entre todas as cidades do roteiro.
- **Visualização**: Exibe, de modo organizado, os resultados e destaques dos melhores itinerários e opções de conectividade.

## Como usar

- Compile o arquivo `av2.cpp` usando um compilador C++, por exemplo:
  ```
  g++ av2.cpp -o eurotrip
  ```
- Execute o programa.
- O sistema irá mostrar tabelas com dados das cidades, propor o melhor roteiro para visitar todas as cidades partindo de Curitiba, e apresentar o custo mínimo da infraestrutura de voos.

## Principais Estruturas e Algoritmos

- **Grafo**: Cidades como vértices e voos como arestas, cada uma com custo, distância e tempo.
- **Floyd-Warshall**: Calcula caminhos mínimos entre todos os pares de cidades.
- **Next Permutation (Caixeiro Viajante)**: Gera todas as rotas para o problema do TSP.
- **Prim (Árvore Geradora Mínima)**: Para conectar cidades pelo menor custo.
- **Impressão Bonita**: Tabelas e resumos formatados para fácil entendimento.

## Dados das cidades simuladas

Cidades utilizadas no projeto: Curitiba, Londres, Paris, Sevilha, Berlim, Florença, Atenas.

Voos diretos são definidos com distâncias, tempos de voo e custo em Reais.

## Observações

O programa é educativo, com algoritmos clássicos de grafos, ideal para trabalhos acadêmicos e demonstração de problemas de roteamento e conectividade.

---

```
**********************************************
* EUROTRIP PLANNER 2025             *
* Museus: Louvre, Acropole e muito mais   *
**********************************************
Desenvolvido por: Mariana Alves e Giovanna de Melo
----------------------------------------------
```

---
