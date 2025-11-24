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
1: cd src
2: gcc -g ProjetoPaginacao.c -o simulador
 
```

ou

```bash
make
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
./simulador clock ../tests/config_1.txt ../tests/acessos_1.txt > output.txt
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
- 
---

**Exemplo:**
```
simulador.c
├── main() - lê argumentos e coordena execução
├── ler_config() - processa arquivo de configuração
├── processar_acessos() - loop principal de simulação
├── traduzir_endereco() - calcula página e deslocamento
├── consultar_tabela() - verifica se página está na memória
├── tratar_page_fault() - lida com page faults
├── algoritmo_fifo() - seleciona vítima usando FIFO
└── algoritmo_clock() - seleciona vítima usando Clock
```

### 2.3 Algoritmo FIFO

Explique **como** implementou a lógica FIFO:

- Como mantém o controle da ordem de chegada?
- Como seleciona a página vítima?
- Quais passos executa ao substituir uma página?

### **Respostas(na ordem):**
- 
---


### 2.4 Algoritmo Clock

Explique **como** implementou a lógica Clock:

- Como gerencia o ponteiro circular?
- Como implementou a "segunda chance"?
- Como trata o caso onde todas as páginas têm R=1?
- Como garante que o R-bit é setado em todo acesso?
### **Respostas(na ordem):**
- 
---


### 2.5 Tratamento de Page Fault

Explique como seu código distingue e trata os dois cenários:

**Cenário 1: Frame livre disponível**
- Como identifica que há frame livre?
- Quais passos executa para alocar a página?
### **Respostas(na ordem):**
- 
---
**Cenário 2: Memória cheia (substituição)**
- Como identifica que a memória está cheia?
- Como decide qual algoritmo usar (FIFO vs Clock)?
- Quais passos executa para substituir uma página?
### **Respostas(na ordem):**
- 
---

## 3. Análise Comparativa FIFO vs Clock

### 3.1 Resultados dos Testes

Preencha a tabela abaixo com os resultados de pelo menos 3 testes diferentes:

| Descrição do Teste | Total de Acessos | Page Faults FIFO | Page Faults Clock | Diferença |
|-------------------|------------------|------------------|-------------------|-----------|
| Teste 1 - Básico  |                  |                  |                   |           |
| Teste 2 - Memória Pequena |          |                  |                   |           |
| Teste 3 - Simples |                  |                  |                   |           |
| Teste Próprio 1   |                  |                  |                   |           |

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
- Como identificaram o problema?
- Como resolveram?
- O que aprenderam com isso?

### 4.2 Principal Aprendizado

Descreva o principal aprendizado sobre gerenciamento de memória que vocês tiveram com este projeto:

- O que vocês não entendiam bem antes e agora entendem?
- Como este projeto mudou sua compreensão de memória virtual?
- Que conceito das aulas ficou mais claro após a implementação?

---

## 5. Vídeo de Demonstração

**Link do vídeo:** [Insira aqui o link para YouTube, Google Drive, etc.]

### Conteúdo do vídeo:

Confirme que o vídeo contém:

- [ ] Demonstração da compilação do projeto
- [ ] Execução do simulador com algoritmo FIFO
- [ ] Execução do simulador com algoritmo Clock
- [ ] Explicação da saída produzida
- [ ] Comparação dos resultados FIFO vs Clock
- [ ] Breve explicação de uma decisão de design importante

---

## Checklist de Entrega

Antes de submeter, verifique:

- [ ] Código compila sem erros conforme instruções da seção 1.1
- [ ] Simulador funciona corretamente com FIFO
- [ ] Simulador funciona corretamente com Clock
- [ ] Formato de saída segue EXATAMENTE a especificação do ENUNCIADO.md
- [ ] Testamos com os casos fornecidos em tests/
- [ ] Todas as seções deste relatório foram preenchidas
- [ ] Análise comparativa foi realizada com dados reais
- [ ] Vídeo de demonstração foi gravado e link está funcionando
- [ ] Todos os integrantes participaram e concordam com a submissão

---
## Referências
Liste aqui quaisquer referências que utilizaram para auxiliar na implementação (livros, artigos, sites, **links para conversas com IAs.**)


---

## Comentários Finais

Use este espaço para quaisquer observações adicionais que julguem relevantes (opcional).

---
