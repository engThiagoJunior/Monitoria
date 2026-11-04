# Sistema de Controle de Iluminação Inteligente

Projeto final da disciplina ECOS03 — Sistemas Operacionais Embarcados (2024.2), na UNIFEI. O sistema controla oito LEDs, um buzzer e um display LCD na placa RedPill (STM32F103), com todas as funções executadas em threads de um sistema operacional de tempo real.

**Tecnologias:** C · STM32F103 · CMSIS-RTOS · Keil RTX · Keil µVision · ADC · PWM · LCD 16x2

**Desenvolvedores:** Gabriel Fazion dos Santos e Thiago de Oliveira Sousa Júnior

## Proposta

A proposta, do Prof. Otávio Gomes, pedia um sistema de iluminação inteligente em que os padrões dos LEDs fossem gerenciados por threads. O código deveria partir da base de referência da disciplina, deixar o laço da `main` vazio e dar prioridade maior às threads de controle.

## O que foi pedido e o que fizemos

| Requisito | Implementação |
|---|---|
| **Função 01:** alternar LEDs pares e ímpares | Sequência que alterna ímpares e pares e acumula mais LEDs a cada passo |
| **Função 02:** piscar em código Gray | Percorre os 256 estados de 8 bits com `i ^ (i >> 1)` |
| **Função 03:** barra de progresso pelo potenciômetro | Divide a leitura do ADC em 9 faixas, de nenhum LED aceso até os oito |
| **Função 04:** som que acompanha a barra, em thread separada | Thread própria com frequência de 500 Hz a 1,2 kHz, conforme o número de LEDs acesos |
| **Seleção de modo:** botões C, D, E e F | Uma thread lê os botões e acorda a tarefa escolhida com `osSignalSet` |
| **Velocidade:** botões Y, A, X e B | Metade do período, dobro do período, valor de 1 s e valor do potenciômetro |
| **Suavização das mudanças de velocidade** | A cada 100 ms, o período se aproxima 30% do valor desejado |
| **Display com opções, teclas e estado** | Thread mostra a função, o botão e o switch atuais |
| **Três velocidades básicas** | Botões L, M e N com períodos de 0,5 s, 2 s e 10 s |
| **Todas as funções em threads** | Oito threads e laço da `main` sem código |

## Threads

| Thread | Prioridade | Função |
|---|---|---|
| `lcd_atualiza` | Realtime | Atualiza o display |
| `leitura_funcao` | High | Lê os botões de modo |
| `leitura_controle` | High | Lê os botões de velocidade |
| `buzzer` | AboveNormal | Gera o feedback sonoro |
| `smooth_Time` | AboveNormal | Suaviza as mudanças de velocidade |
| `led_par_impar` | Normal | Executa a Função 01 |
| `led_gray` | Normal | Executa a Função 02 |
| `led_pot` | Normal | Executa a Função 03 |

## Diferenças em relação à proposta

- **RTOS:** a proposta cita o FreeRTOS, mas o projeto usa a API CMSIS-RTOS com o kernel Keil RTX.
- **Sincronização:** a proposta sugeria considerar mutexes e semáforos. O projeto usa sinais do CMSIS-RTOS e não usa mutexes nem semáforos.
- **Função 01:** a proposta sugere alternar a cada segundo. O projeto inicia com 300 ms, e a velocidade pode ser ajustada pelos botões.
- **Entradas:** o controle é feito por botões e potenciômetro. Não há agendamento por horário nem outros sensores.

### 🛠️ Pré-requisitos

#### Hardware:
- Placa RedPill (STM32F103)
- Cabo USB para programação
- Computador com porta USB

#### Software:
- [STM32 ST-LINK Utility](https://www.st.com/en/development-tools/stsw-link004.html#get-software)
- [Keil uVision5](https://www.keil.com/download/product/)

### 🚀 Como Executar o Projeto

#### Clone do repositório
```bash
git clone https://github.com/engThiagoJunior/Monitoria.git
cd Monitoria/ecos03-ecos13-sistemas-operacionais-embarcados/projeto-final/TF_SOE
```

#### Configuração e Upload:

- Abra `final.uvprojx` no Keil uVision;
- Compile o projeto (F7);
- Conecte a placa RedPill via USB;
- Grave o código na placa;
- Pressione o botão de reset na placa;
- O sistema iniciará automaticamente.

## 🎮 Como Usar

### Seleção de Modo:
Um toque liga o modo escolhido. O toque seguinte em C, D, E ou F desliga o modo ativo.

* **Botão C:** Função 01 (LEDs pares/ímpares)
* **Botão D:** Função 02 (Código Gray)
* **Botão E:** Função 03 (Potenciômetro)
* **Botão F:** Função 04 (Sonoro/Mudo)

### Controle de Velocidade:
* **Botão Y:** Dobra velocidade
* **Botão A:** Metade da velocidade
* **Botão X:** Período de 1000 ms
* **Botão B:** Velocidade por potenciômetro
* **Botão L:** Período de 500 ms
* **Botão M:** Período de 2000 ms
* **Botão N:** Período de 10000 ms

---
