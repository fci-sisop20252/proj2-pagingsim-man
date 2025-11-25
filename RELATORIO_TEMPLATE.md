# Relatório do Projeto 2: Simulador de Memória Virtual

**Disciplina:** Sistemas Operacionais
**Professor:** Lucas Figueiredo
**Data:**

## Integrantes do Grupo

- Andre Doerner Duarte – 10427938

- Matheus Leonardo Cardoso Kroeff – 10426434

- Naoto Ushizaki – 10437445

---

## 1. Instruções de Compilação e Execução

### 1.1 Compilação

Descreva EXATAMENTE como compilar seu projeto. Inclua todos os comandos necessários.

**Exemplo:**
```bash
1: gcc -Wall -Wextra -Iinclude src/*.c -o main
 
```

### 1.2 Execução

Forneça exemplos completos de como executar o simulador.

**Exemplo com FIFO:**
```bash
./simulador fifo ../tests/config_1.txt ../tests/acessos_1.txt > output.txt
```
Dessa forma é possível compilar o arquivo, pegar os casos testes do diretório tests e escrever seu resultado no arquivo output.txt

**Exemplo com Clock:**
```bash
./main fifo tests/config_1.txt tests/acessos_1.txt >> src/output.txt
```

---

## 2. Decisões de Design

### 2.1 Estruturas de Dados

Descreva as estruturas de dados que você escolheu para representar:

**Tabela de Páginas:**
- Qual estrutura usou? (array, lista, hash map, etc.)
- Quais informações armazena para cada página?
- Como organizou para múltiplos processos?
- **Justificativa:** Por que escolheu essa abordagem?

### **Respostas(na ordem):**
- array fixo de 1024 entradas (TabelaPagina TP[MAX_PAGES]).
- Para cada página são armazenados: end_virtual, num_frame (frame físico que contém a página), valid_bit, referenced_bit e loaded_time (usado pelo FIFO).
- Após a leitura dos dados dos arquivos Config e Acessos foram realizados, estes dados foram inseridos em arrays em structs criados no início do código. Em seguida foi montada uma tabela de páginas que armazena a página virtual, frame físico, pid da página, valid bit, referenced bit e tempo de carregamento(para o FIFO).
- Simples, eficiente e de acesso direto por índice; Fácil de manipular para os algoritmos FIFO e Clock;
---
**Frames Físicos:**
- Como representou os frames da memória física?
- Quais informações armazena para cada frame?
- Como rastreia frames livres vs ocupados?
- **Justificativa:** Por que escolheu essa abordagem?
### **Respostas(na ordem):**
- Seu número e se está ocupado.
- Através de 2 loops criados na função PageFaultCorrection, onde o primeiro loop percorre os frames e o segundo checa se o frame atual escolhido existe (valid bit = 1 e num do frame == frame) e se existir é porque está ocupada. Caso contrário, este frame está livre.
- Essa abordagem é simples e evita criar uma estrutura duplicada (como Frame frames[]). Além de ser adequado para simuladores, reduz a complexidade e evita inconsistência entre dados.
--- 
**Estrutura para FIFO:**
- Como mantém a ordem de chegada das páginas?
- Como identifica a página mais antiga?
- **Justificativa:** Por que escolheu essa abordagem?

### **Respostas(na ordem):**
- Cada página recebe um carimbo de tempo (loaded_time = clock()) no momento em que é carregada na memória física.
- Percorre TODAS as páginas válidas e escolhe aquela com valid_bit = 1 e menor loaded_time. Essa seria a página que tinha entrado primeiro.
- Usar o tempo como métrica (clock()), não é necessário usar fila, contador ou lista encadeada.
--- 

**Estrutura para Clock:**
- Como implementou o ponteiro circular?
- Como armazena e atualiza os R-bits?
- **Justificativa:** Por que escolheu essa abordagem?
### **Respostas(na ordem):**
- Inicialmente foi criado um static unsigned int ponteiro, que inicia em 0 e é incrementado em ciclos (ponteiro + 1) % num_frames.
- Cada página possui seu próprio referenced bit. Portanto o fluxo foi: Toda vez que for um HIT (referenced bit = 1), o algortimo seta esse bit como 0 (Second Chance). Caso encontre um bit = 0, escolhe essa página como vítima.
- Além de deixax o código mais claro, é simples enxergar o que está acontecendo, simples encontrar erros e ajustar o ponteiro, e as estruturas ficam independentes umas das outras, o que evita confusão na hora de atualizar R-bits e frames. Isso tudo torna o algoritmo confiável e fácil de manter.
--- 

### 2.2 Organização do Código

Descreva como organizou seu código:

- Quantos arquivos/módulos criou?
- Qual a responsabilidade de cada arquivo/módulo?
- Quais são as principais funções e o que cada uma faz?

### **Respostas(na ordem):**
- 5 Arquivos C e 5 arquivos H foram criados.
- A responsabilidade do arquivo 'arquivo.c'
---

Estrutura tree:

<img width="214" height="260" alt="image" src="https://github.com/user-attachments/assets/15ccaf3e-632d-4143-ae7b-3eb1bfec3ffc" />


### 2.3 Algoritmo FIFO

Explique **como** implementou a lógica FIFO:

- Como mantém o controle da ordem de chegada?
- Como seleciona a página vítima?
- Quais passos executa ao substituir uma página?

### **Respostas(na ordem):**
- O controle de ordem chegada é mantida por um campo de registro de tempo de chegada da página (Como o TP[pagina].loaded_time = clock()).
- A página vítima é selecionada a página que tiver o menor 'loaded_time' entre todas (mais antiga).
- O algoritmo retorna a página vítima, busca-se em que frame ela está na tabela de página e depois ela é invalidada. Em seguida, a nova página é carregada no lugar dessa página vítima e marca o tempo que ela entrou.
---


### 2.4 Algoritmo Clock

Explique **como** implementou a lógica Clock:

- Como gerencia o ponteiro circular?
- Como implementou a "segunda chance"?
- Como trata o caso onde todas as páginas têm R=1?
- Como garante que o R-bit é setado em todo acesso?
### **Respostas(na ordem):**
- O ponteiro circular é gerenciado da seguinte maneira: Ela inicia com 0 e a cada iteração ela avanca somando 1 nela mesma e divide pelo número de frames. E por fim, pega-se o resultado do resto desta conta, dando um ciclo com o ponteiro.
- Em um loop, o algoritmo verifica se o bit de referência é 0 e caso for verdadeiro, a vítima será nesse índice que atualmente o sistema está. O ponteiro realiza o ciclo e retorna a vítima. Caso contrário, zera esse bit.
- O algoritmo percorre todas as páginas dando segunda chance e zerando o R-bit daquelas com R=1, completa uma volta deixando todas com R=0 e, na volta seguinte, escolhe como vítima a primeira página encontrada com R=0. Isso é possível, pelo while(1) do algoritmo.
- Na tradução de endereços (função) quando ele recebe as páginas, ele as vasculha todo valid_bit lido da tabela de página for 1, o bit de referência também será 1; 
---


### 2.5 Tratamento de Page Fault

Explique como seu código distingue e trata os dois cenários:

**Cenário 1: Frame livre disponível**
- Como identifica que há frame livre?
- Quais passos executa para alocar a página?
### **Respostas(na ordem):**
- É criado uma variável de verificação de se frame está ocupado ou não. Dois loops são criados para percorrer todos os frames e ver o seu valid_bit e seu número. Caso o bit == 1, a variável de verificação vale 1. E caso essa variável tenha qualquer valor, tirando o 1, o frame livre estará no índice em que o loop parou.
- Na atualização da tabela de página no próprio PageFaultCorrection, um if é criado que se frame livre for diferente de -1 (existe), ele atualiza os metadados da página (número da página, endereço virtual e pid) incluindo colocando a página nova no frame livre e seta os bits para 1. As informações são todas contidas nas struct TP.
---
**Cenário 2: Memória cheia (substituição)**
- Como identifica que a memória está cheia?
- Como decide qual algoritmo usar (FIFO vs Clock)?
- Quais passos executa para substituir uma página?
### **Respostas(na ordem):**
- No momento em que o sistema percorre todos os frames (verifica os valid_bit) e conclui que nenhum frame está desocupado, chega na conclusão de que a memória cheia.
- Inicialmente, é incluído a biblioteca 'string.h'. No main, ele recebe o comando e compara se no índice escolhido está escrito 'fifo' ou 'clock'. E quando uma delas forem reconhecidas, o algortimo respectivo será implementado. Essas funções retornam o número da página vítima que deve ser removida. E, qualquer outro valor aborta o programa.
---

## 3. Análise Comparativa FIFO vs Clock

### 3.1 Resultados dos Testes

Preencha a tabela abaixo com os resultados de pelo menos 3 testes diferentes:

| Descrição do Teste | Total de Acessos | Page Faults FIFO | Page Faults Clock | Diferença |
|-------------------|------------------|------------------|-------------------|-----------|
| Teste 1 - Básico  |       8          |       5          |        5          |     0     |
| Teste 2 - Memória Pequena | 10       |       3          |        3          |     0     |
| Teste 3 - Simples |        7         |       4          |        4          |     0     |
| Teste Próprio 1   |       11         |       9          |        9          |     0     |

### 3.2 Análise

Com base nos resultados acima, responda:

1. **Qual algoritmo teve melhor desempenho (menos page faults)?**
### **Resposta:**
 
---
2. **Por que você acha que isso aconteceu?** Considere:
   - Como cada algoritmo escolhe a vítima
   - O papel do R-bit no Clock
   - O padrão de acesso dos testes
### **Respostas(na ordem):**
- 
---

3. **Em que situações Clock é melhor que FIFO?**
   - Dê exemplos de padrões de acesso onde Clock se beneficia
### **Resposta:**
 
---
4. **Houve casos onde FIFO e Clock tiveram o mesmo resultado?**
   - Por que isso aconteceu?
### **Resposta:**
 
---
5. **Qual algoritmo você escolheria para um sistema real e por quê?**
### **Resposta:**
 
---

## 4. Desafios e Aprendizados

### 4.1 Maior Desafio Técnico

Descreva o maior desafio técnico que seu grupo enfrentou durante a implementação:

- Qual foi o problema?
  ### **Resposta:** O maior desafio foi fazer a função de correção de page fault funcionar corretamente. No início, algumas páginas não eram removidas direito e acabavam com frames marcados como ocupados por mais de uma página, ou páginas inválidas ainda apareciam como válidas
- Como identificaram o problema?
  ### **Resposta:** Percebemos o problema rodando os testes e vendo que os algoritmos FIFO e CLOCK escolhiam páginas “erradas” ou repetidas. Logo o erro estava na atualização dos bits da tabela e não no algoritmo em si
- Como resolveram?
  ### **Resposta:** Resolvemos reorganizando a lógica da função. Primeiro limpando corretamente a página vítima e só depois carregando a nova página. Também adicionamos uma busca por frame livre antes de chamar o algoritmo de substituição
- O que aprenderam com isso?
  ### **Resposta:** Aprendemos que quando gerenciamos memória tudo é mais sensível do que parece, e que quem programou esses algorítimos nos SOs de verdade realmente merece os parabéns.

### 4.2 Principal Aprendizado

Descreva o principal aprendizado sobre gerenciamento de memória que vocês tiveram com este projeto:

- O que vocês não entendiam bem antes e agora entendem?
   ### **Resposta:** Como é na prática o funcionamento da memória virtual. Antes do projeto, a gente sabia a teoria passada em aula, mas não entendia bem como os bits (valid, referenced, frame, tempo) eram realmente usados, nem como os algorítimos de FIFO e CLOCK realmente rodavam.
- Como este projeto mudou sua compreensão de memória virtual?
   ### **Resposta:** Como este projeto mudou sua compreensão de memória virtual?
 Não tinhamos a idéia da real complexidade e quantidade de abstrações nescessárias que um processo precisa para acessar e manipular memória. Algo que parece tão simples como declarar uma variavel com 'int main' ou usando 'malloc' esconde processos MUITO mais interessantes!
- Que conceito das aulas ficou mais claro após a implementação?
   ### **Resposta:** Que conceito das aulas ficou mais claro após a implementação?
 Principalmente o conceito de tabela de páginas era algo que nos confundia bastante. Agora ficou um pouco mais claro!


---

## 5. Vídeo de Demonstração

**Link do vídeo:** [Insira aqui o link para YouTube, Google Drive, etc.]

### Conteúdo do vídeo:

Confirme que o vídeo contém:

- [ ✅ ] Demonstração da compilação do projeto
- [ ✅ ] Execução do simulador com algoritmo FIFO
- [ ✅ ] Execução do simulador com algoritmo Clock
- [ ✅ ] Explicação da saída produzida
- [ ✅ ] Comparação dos resultados FIFO vs Clock
- [ ✅ ] Breve explicação de uma decisão de design importante

---

## Checklist de Entrega

Antes de submeter, verifique:

- [ ✅ ] Código compila sem erros conforme instruções da seção 1.1
- [ ✅ ] Simulador funciona corretamente com FIFO
- [ ✅ ] Simulador funciona corretamente com Clock
- [ ✅ ] Formato de saída segue EXATAMENTE a especificação do ENUNCIADO.md
- [ ✅ ] Testamos com os casos fornecidos em tests/
- [ ✅ ] Todas as seções deste relatório foram preenchidas
- [ ✅ ] Análise comparativa foi realizada com dados reais
- [ ✅ ] Vídeo de demonstração foi gravado e link está funcionando
- [ ✅ ] Todos os integrantes participaram e concordam com a submissão

---
## Referências
W3Schools – snprintf W3SCHOOLS. C Library – snprintf() function. Disponível em: <https://www.w3schools.com/c/ref_stdio_snprintf.php>. Acesso em: 24 nov. 2025.

Microsoft Learn – clock MICROSOFT. Função clock – Biblioteca de tempo de execução C. Disponível em: <https://learn.microsoft.com/pt-br/cpp/c-runtime-library/reference/clock?view=msvc-170>. Acesso em: 24 nov. 2025.

---

## Comentários Finais

---
